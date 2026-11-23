import assert from "node:assert/strict";
import { test } from "node:test";
import { TcpSession } from "../src/tcp-session";

const encode = (text: string) => new TextEncoder().encode(text);

test("preserves output order, drains before close and disconnects once", async () => {
  const output: string[] = [];
  const input = new ReadableStream<Uint8Array>({ start(c) { c.enqueue(encode("quit")); } });
  const session = new TcpSession(input, new WritableStream({
    async write(data) { await Promise.resolve(); output.push(new TextDecoder().decode(data)); },
    close() { output.push("closed"); },
  }));
  let disconnected = 0;
  await session.run(() => session.write(encode("welcome")), () => {
    session.write(encode("bye"));
    session.end();
    session.write(encode("ignored"));
  }, () => disconnected++);
  assert.deepEqual(output, ["welcome", "bye", "closed"]);
  assert.equal(disconnected, 1);
});

test("client EOF still drains output (half-close)", async () => {
  const output: Uint8Array[] = [];
  const input = new ReadableStream<Uint8Array>({ start(c) { c.close(); } });
  const session = new TcpSession(input, new WritableStream({ write(data) { output.push(data); } }));
  await session.run(() => session.write(encode("welcome")), () => {}, () => {});
  assert.equal(new TextDecoder().decode(output[0]), "welcome");
});

test("failed writes cancel input and remove the connection", async () => {
  let cancelled = false;
  let disconnected = 0;
  const session = new TcpSession(new ReadableStream({ cancel() { cancelled = true; } }),
    new WritableStream({ write() { throw new Error("client gone"); } }));
  await assert.rejects(session.run(() => session.write(encode("hello")), () => {},
    () => disconnected++), /client gone/);
  assert.ok(cancelled);
  assert.equal(disconnected, 1);
});

test("oversized output is bounded and terminates the connection", async () => {
  let disconnected = 0;
  const session = new TcpSession(new ReadableStream(), new WritableStream());
  await assert.rejects(session.run(() => session.write(new Uint8Array(1024 * 1024 + 1)),
    () => {}, () => disconnected++), /output buffer limit/);
  assert.equal(disconnected, 1);
});

test("runtime failures cancel the input and reject the session", async () => {
  let disconnected = 0;
  const session = new TcpSession(new ReadableStream(), new WritableStream());
  await assert.rejects(session.run(() => { throw new Error("checkpoint failed"); },
    () => {}, () => disconnected++), /checkpoint failed/);
  assert.equal(disconnected, 1);
});

test("many queued writes cannot bypass the byte limit", { timeout: 2000 }, async () => {
  const session = new TcpSession(new ReadableStream(), new WritableStream());
  await assert.rejects(session.run(() => {
    for (let index = 0; index < 512; index++) session.write(new Uint8Array(4096));
  }, () => {}, () => {}), /output buffer limit/);
});
