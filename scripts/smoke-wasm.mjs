import assert from "node:assert/strict";
import { readFile } from "node:fs/promises";
import { WASI } from "node:wasi";

const wasmBytes = await readFile(new URL("../lambdamoo/dist/lambdamoo.wasm", import.meta.url));
const database = await readFile(new URL("../lambdamoo/LambdaCore-17May04.db", import.meta.url));
const module = await WebAssembly.compile(wasmBytes);

const expectedImports = [
  "env.emscripten_notify_memory_growth",
  "env.moo_host_close",
  "env.moo_host_output",
  "wasi_snapshot_preview1.clock_time_get",
  "wasi_snapshot_preview1.environ_get",
  "wasi_snapshot_preview1.environ_sizes_get",
  "wasi_snapshot_preview1.fd_close",
  "wasi_snapshot_preview1.fd_seek",
  "wasi_snapshot_preview1.fd_write",
  "wasi_snapshot_preview1.proc_exit",
];
const actualImports = WebAssembly.Module.imports(module)
  .map(({ module, name }) => `${module}.${name}`)
  .sort();
assert.deepEqual(actualImports, expectedImports);

async function createRuntime(output, clockStepMilliseconds = 0) {
  const wasi = new WASI({ version: "preview1" });
  let memory;
  const imports = wasi.getImportObject();
  if (clockStepMilliseconds > 0) {
    let now = BigInt(Date.now()) * 1_000_000n;
    imports.wasi_snapshot_preview1.clock_time_get = (_, __, outputPointer) => {
      new DataView(memory.buffer).setBigUint64(outputPointer, now, true);
      now += BigInt(clockStepMilliseconds) * 1_000_000n;
      return 0;
    };
  }
  imports.env = {
    emscripten_notify_memory_growth() {},
    moo_host_close(connectionPointer) {
      output.push({ connection: readCString(connectionPointer), close: true });
    },
    moo_host_output(connectionPointer, dataPointer, length) {
      output.push({
        connection: readCString(connectionPointer),
        data: Buffer.from(memory.buffer, dataPointer, length).toString(),
      });
    },
  };

  const instance = await WebAssembly.instantiate(module, imports);
  memory = instance.exports.memory;
  wasi.initialize(instance);

  function readCString(pointer) {
    const bytes = new Uint8Array(memory.buffer);
    let end = pointer;
    while (bytes[end] !== 0) end++;
    return Buffer.from(bytes.subarray(pointer, end)).toString();
  }

  function copyBytes(bytes, nulTerminate = false) {
    const pointer = instance.exports.moo_alloc(bytes.length + Number(nulTerminate));
    const destination = new Uint8Array(memory.buffer, pointer, bytes.length + Number(nulTerminate));
    destination.set(bytes);
    if (nulTerminate) destination[bytes.length] = 0;
    return pointer;
  }

  return { instance, memory, copyBytes };
}

const output = [];
const runtime = await createRuntime(output);
const databasePointer = runtime.copyBytes(database);
assert.equal(runtime.instance.exports.moo_initialize(databasePointer, database.length), 1);
runtime.instance.exports.moo_free(databasePointer);

const connection = Buffer.from("smoke");
const connectionPointer = runtime.copyBytes(connection, true);
assert.equal(runtime.instance.exports.moo_connect(connectionPointer), 1);
for (const line of ["connect wizard", "@quit"]) {
  const linePointer = runtime.copyBytes(Buffer.from(line), true);
  assert.equal(runtime.instance.exports.moo_input(connectionPointer, linePointer), 1);
  runtime.instance.exports.moo_free(linePointer);
}
assert.equal(runtime.instance.exports.moo_checkpoint(), 1);

const snapshotPointer = runtime.instance.exports.moo_snapshot_data();
const snapshotLength = runtime.instance.exports.moo_snapshot_size();
assert.ok(snapshotLength > 0);
const snapshot = Buffer.from(runtime.memory.buffer, snapshotPointer, snapshotLength);
assert.match(snapshot.toString("utf8", 0, 64), /^\*\* LambdaMOO Database/);

runtime.instance.exports.moo_free(connectionPointer);
assert.ok(output.some((event) =>
  event.connection === "smoke" && event.data?.includes("Welcome to the LambdaCore database.")));
assert.ok(output.some((event) => event.connection === "smoke" && event.close));

const restored = await createRuntime([]);
const snapshotCopy = restored.copyBytes(snapshot);
assert.equal(restored.instance.exports.moo_initialize(snapshotCopy, snapshot.length), 1);
restored.instance.exports.moo_free(snapshotCopy);

// A cold start must not reuse an anonymous player ID restored in the snapshot.
// LambdaCore counts login commands by that ID and eventually boots a reused one.
let coldStartSnapshot = database;
for (let cycle = 0; cycle < 12; cycle++) {
  const cycleOutput = [];
  const cycleRuntime = await createRuntime(cycleOutput);
  const cycleDatabase = cycleRuntime.copyBytes(coldStartSnapshot);
  assert.equal(cycleRuntime.instance.exports.moo_initialize(cycleDatabase, coldStartSnapshot.length), 1);
  cycleRuntime.instance.exports.moo_free(cycleDatabase);

  const cycleConnectionName = `cold-start-${cycle}`;
  const cycleConnection = cycleRuntime.copyBytes(Buffer.from(cycleConnectionName), true);
  assert.equal(cycleRuntime.instance.exports.moo_connect(cycleConnection), 1);
  cycleRuntime.instance.exports.moo_free(cycleConnection);
  assert.ok(cycleOutput.some((event) =>
    event.connection === cycleConnectionName && event.data?.includes("Welcome to the LambdaCore database.")));
  assert.ok(!cycleOutput.some((event) => event.data?.includes("too many commands")));

  assert.equal(cycleRuntime.instance.exports.moo_checkpoint(), 1);
  const cycleSnapshotPointer = cycleRuntime.instance.exports.moo_snapshot_data();
  const cycleSnapshotLength = cycleRuntime.instance.exports.moo_snapshot_size();
  coldStartSnapshot = Buffer.from(
    cycleRuntime.memory.buffer,
    cycleSnapshotPointer,
    cycleSnapshotLength,
  );
}

// Advancing the monotonic clock on every query forces the login task's
// one-second execution timer to expire at its first cooperative poll.
const timeoutOutput = [];
const timeoutRuntime = await createRuntime(timeoutOutput, 10_000);
const timeoutDatabase = timeoutRuntime.copyBytes(database);
assert.equal(timeoutRuntime.instance.exports.moo_initialize(timeoutDatabase, database.length), 1);
timeoutRuntime.instance.exports.moo_free(timeoutDatabase);
const timeoutConnection = timeoutRuntime.copyBytes(Buffer.from("timeout"), true);
assert.equal(timeoutRuntime.instance.exports.moo_connect(timeoutConnection), 1);
timeoutRuntime.instance.exports.moo_free(timeoutConnection);
assert.ok(timeoutOutput.some((event) => event.data?.includes("seconds")));

console.log(`Wasm smoke test passed (${snapshotLength} byte snapshot, timeout enforced)`);
