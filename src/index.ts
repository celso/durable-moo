import { DurableObject } from "cloudflare:workers";
import { TcpSession } from "./tcp-session";
import { TelnetLines } from "./telnet";
import { WebSocketSession } from "./websocket-session";
import { secureAssetResponse, validateWebSocketRequest } from "./http";
import type { SessionSocket } from "./session-socket";

import seedDatabase from "../lambdamoo/LambdaCore-17May04.db";
import mooModule from "../lambdamoo/dist/lambdamoo.wasm";

const SNAPSHOT_CHUNK_SIZE = 1024 * 1024;

interface MooExports extends WebAssembly.Exports {
  memory: WebAssembly.Memory;
  _initialize(): void;
  moo_initialize(database: number, length: number): number;
  moo_connect(connection: number): number;
  moo_input(connection: number, line: number): number;
  moo_disconnect(connection: number): number;
  moo_run_ready_tasks(): number;
  moo_next_task_start(): number;
  moo_checkpoint(): number;
  moo_snapshot_data(): number;
  moo_snapshot_size(): number;
  moo_alloc(length: number): number;
  moo_free(pointer: number): void;
}

interface ConnectionState {
  socket: SessionSocket;
  lines: TelnetLines;
}

export class GameWorld extends DurableObject<Env> {
  private runtime!: MooExports;
  private readonly connections = new Map<string, ConnectionState>();
  private readonly pendingOutput = new Map<string, Uint8Array[]>();
  private readonly pendingClose = new Set<string>();
  private readonly runtimeClosed = new Set<string>();
  private readonly ready: Promise<void>;

  constructor(ctx: DurableObjectState, env: Env) {
    super(ctx, env);
    this.ready = ctx.blockConcurrencyWhile(async () => this.initialize());
  }

  // Stream ownership transfers over RPC; the ingress handler awaits this entire
  // session so the native inbound socket stays alive until both directions end.
  async serve(readable: ReadableStream<Uint8Array>, writable: WritableStream<Uint8Array>): Promise<void> {
    await this.ready;
    const id = crypto.randomUUID();
    const socket = new TcpSession(readable, writable);
    this.connections.set(id, { socket, lines: new TelnetLines() });
    await socket.run(
      () => this.mutate(() => this.withCString(id, (pointer) => this.runtime.moo_connect(pointer))),
      (data) => this.receive(id, data),
      () => this.disconnect(id),
    );
  }

  async fetch(request: Request): Promise<Response> {
    const invalid = validateWebSocketRequest(request);
    if (invalid) return invalid;
    await this.ready;
    const [client, server] = Object.values(new WebSocketPair());
    server.binaryType = "arraybuffer";
    // Standard sockets deliberately keep the in-memory Wasm world awake, just
    // like TCP sessions. Hibernation would require restoring live MOO sessions.
    server.accept();
    const id = crypto.randomUUID();
    const socket = new WebSocketSession(server, (data) => this.receive(id, data), () => this.disconnect(id));
    this.connections.set(id, { socket, lines: new TelnetLines() });
    try {
      this.mutate(() => this.withCString(id, (pointer) => this.runtime.moo_connect(pointer)));
    } catch (error) {
      socket.end();
      throw error;
    }
    return new Response(null, { status: 101, webSocket: client });
  }

  async alarm(): Promise<void> {
    await this.ready;
    this.mutate(() => this.runtime.moo_run_ready_tasks(), false);
  }

  private async initialize(): Promise<void> {
    this.ctx.storage.sql.exec(`
      CREATE TABLE IF NOT EXISTS world_meta (
        key TEXT PRIMARY KEY,
        value TEXT NOT NULL
      );
      CREATE TABLE IF NOT EXISTS snapshot_chunks (
        generation INTEGER NOT NULL,
        chunk_index INTEGER NOT NULL,
        data BLOB NOT NULL,
        PRIMARY KEY (generation, chunk_index)
      );
    `);

    let memory: WebAssembly.Memory;
    const imports = {
      env: {
        emscripten_notify_memory_growth() {},
        moo_host_close: (connection: number) => this.closeSocket(this.readCString(memory, connection)),
        moo_host_output: (connection: number, data: number, length: number) => {
          const id = this.readCString(memory, connection);
          const chunks = this.pendingOutput.get(id) ?? [];
          chunks.push(new Uint8Array(memory.buffer.slice(data, data + length)));
          this.pendingOutput.set(id, chunks);
        },
      },
      wasi_snapshot_preview1: this.wasiImports(() => memory),
    };
    const instance = await WebAssembly.instantiate(mooModule, imports);
    this.runtime = instance.exports as MooExports;
    memory = this.runtime.memory;
    this.runtime._initialize();

    const storedSnapshot = this.loadSnapshot();
    const database = storedSnapshot ?? new Uint8Array(seedDatabase);
    const pointer = this.copyBytes(database);
    const initialized = this.runtime.moo_initialize(pointer, database.length);
    this.runtime.moo_free(pointer);
    if (!initialized) throw new Error("LambdaMOO rejected the database snapshot");
    this.persist();
    this.scheduleAlarm();
  }

  private receive(id: string, data: Uint8Array): void {
    const state = this.connections.get(id);
    if (!state) return;
    state.lines.receive(data, (line) => {
      if (state.socket.closing) return;
      this.mutate(() => this.withCString(id, (connection) =>
        this.withCString(line, (input) => this.runtime.moo_input(connection, input))));
    }, () => state.socket.end("*** Input line too long.\r\n"));
  }

  private disconnect(id: string): void {
    if (!this.connections.delete(id)) return;
    if (this.runtimeClosed.delete(id)) return;
    this.mutate(() => this.withCString(id, (pointer) => this.runtime.moo_disconnect(pointer)));
  }

  private mutate(operation: () => number, requireSuccess = true): void {
    this.pendingOutput.clear();
    const result = operation();
    if (requireSuccess && !result) throw new Error("LambdaMOO runtime operation failed");
    this.persist();
    for (const [id, chunks] of this.pendingOutput) {
      const socket = this.connections.get(id)?.socket;
      if (socket) for (const chunk of chunks) socket.write(chunk);
    }
    for (const id of this.pendingClose) this.connections.get(id)?.socket.end();
    this.pendingOutput.clear();
    this.pendingClose.clear();
    this.scheduleAlarm();
  }

  private persist(): void {
    if (!this.runtime.moo_checkpoint()) throw new Error("LambdaMOO checkpoint failed");
    const pointer = this.runtime.moo_snapshot_data();
    const length = this.runtime.moo_snapshot_size();
    const snapshot = new Uint8Array(this.runtime.memory.buffer.slice(pointer, pointer + length));
    const generation = Number(this.ctx.storage.sql
      .exec<{ value: string }>("SELECT value FROM world_meta WHERE key = 'generation'")
      .toArray()[0]?.value ?? 0) + 1;

    this.ctx.storage.transactionSync(() => {
      for (let offset = 0, index = 0; offset < snapshot.length; offset += SNAPSHOT_CHUNK_SIZE, index++) {
        this.ctx.storage.sql.exec(
          "INSERT INTO snapshot_chunks (generation, chunk_index, data) VALUES (?, ?, ?)",
          generation,
          index,
          snapshot.slice(offset, offset + SNAPSHOT_CHUNK_SIZE),
        );
      }
      this.ctx.storage.sql.exec(
        "INSERT INTO world_meta (key, value) VALUES ('generation', ?) ON CONFLICT (key) DO UPDATE SET value = excluded.value",
        String(generation),
      );
      this.ctx.storage.sql.exec("DELETE FROM snapshot_chunks WHERE generation < ?", generation);
    });
  }

  private loadSnapshot(): Uint8Array | undefined {
    const chunks = this.ctx.storage.sql
      .exec<{ data: ArrayBuffer }>(`
        SELECT data FROM snapshot_chunks
        WHERE generation = (SELECT CAST(value AS INTEGER) FROM world_meta WHERE key = 'generation')
        ORDER BY chunk_index
      `)
      .toArray();
    if (chunks.length === 0) return undefined;
    const length = chunks.reduce((total, chunk) => total + chunk.data.byteLength, 0);
    const snapshot = new Uint8Array(length);
    let offset = 0;
    for (const chunk of chunks) {
      snapshot.set(new Uint8Array(chunk.data), offset);
      offset += chunk.data.byteLength;
    }
    return snapshot;
  }

  private scheduleAlarm(): void {
    const seconds = this.runtime.moo_next_task_start();
    if (seconds < 0) this.ctx.waitUntil(this.ctx.storage.deleteAlarm());
    else this.ctx.waitUntil(this.ctx.storage.setAlarm(Date.now() + Math.max(seconds * 1000, 1)));
  }

  private copyCString(value: string | Uint8Array): number {
    const bytes = typeof value === "string" ? new TextEncoder().encode(value) : value;
    const pointer = this.runtime.moo_alloc(bytes.length + 1);
    const destination = new Uint8Array(this.runtime.memory.buffer, pointer, bytes.length + 1);
    destination.set(bytes);
    destination[bytes.length] = 0;
    return pointer;
  }

  private withCString(value: string | Uint8Array, operation: (pointer: number) => number): number {
    const pointer = this.copyCString(value);
    try {
      return operation(pointer);
    } finally {
      this.runtime.moo_free(pointer);
    }
  }

  private copyBytes(bytes: Uint8Array): number {
    const pointer = this.runtime.moo_alloc(bytes.length);
    new Uint8Array(this.runtime.memory.buffer, pointer, bytes.length).set(bytes);
    return pointer;
  }

  private readCString(memory: WebAssembly.Memory, pointer: number): string {
    const bytes = new Uint8Array(memory.buffer);
    let end = pointer;
    while (bytes[end] !== 0) end++;
    return new TextDecoder().decode(bytes.subarray(pointer, end));
  }

  private closeSocket(id: string): void {
    this.runtimeClosed.add(id);
    this.pendingClose.add(id);
  }

  private wasiImports(getMemory: () => WebAssembly.Memory): Record<string, (...args: never[]) => number> {
    return {
      clock_time_get: ((_: number, __: bigint, output: number) => {
        new DataView(getMemory().buffer).setBigUint64(output, BigInt(Date.now()) * 1_000_000n, true);
        return 0;
      }) as (...args: never[]) => number,
      environ_get: () => 0,
      environ_sizes_get: ((count: number, size: number) => {
        const view = new DataView(getMemory().buffer);
        view.setUint32(count, 0, true);
        view.setUint32(size, 0, true);
        return 0;
      }) as (...args: never[]) => number,
      fd_close: () => 8,
      fd_seek: () => 8,
      fd_write: ((_: number, iovecs: number, count: number, written: number) => {
        const view = new DataView(getMemory().buffer);
        let length = 0;
        for (let index = 0; index < count; index++) length += view.getUint32(iovecs + index * 8 + 4, true);
        view.setUint32(written, length, true);
        return 0;
      }) as (...args: never[]) => number,
      proc_exit: ((code: number) => { throw new Error(`Wasm exited with status ${code}`); }) as (...args: never[]) => number,
    };
  }
}

export default {
  async connect(socket, env): Promise<void> {
    try {
      await env.GAME_WORLD.getByName("default").serve(socket.readable, socket.writable);
    } catch (error) {
      console.error({ event: "tcp_session_failed", error: String(error) });
    } finally {
      await socket.close().catch(() => {});
    }
  },
  async fetch(request, env): Promise<Response> {
    const url = new URL(request.url);
    if (url.pathname === "/ws") {
      const invalid = validateWebSocketRequest(request);
      return invalid ?? env.GAME_WORLD.getByName("default").fetch(request);
    }
    if (url.pathname === "/healthz") return new Response("LambdaMOO TCP ingress is ready.");
    return secureAssetResponse(await env.ASSETS.fetch(request));
  },
} satisfies ExportedHandler<Env>;
