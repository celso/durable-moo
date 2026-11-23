import assert from "node:assert/strict";
import { test } from "node:test";
import { WebSocketSession } from "../src/websocket-session";

class FakeSocket extends EventTarget {
  readonly sent: Uint8Array[] = [];
  readonly closed: { code?: number; reason?: string }[] = [];
  failSend = false;
  send(data: Uint8Array): void {
    if (this.failSend) throw new Error("Client gone");
    this.sent.push(data);
  }
  close(code?: number, reason?: string): void { this.closed.push({ code, reason }); }
  message(data: unknown): void { this.dispatchEvent(new MessageEvent("message", { data })); }
}

test("binary input reaches the world; text ACKs do not", () => {
  const ws = new FakeSocket();
  const received: Uint8Array[] = [];
  const session = new WebSocketSession(ws, (data) => received.push(data), () => {});
  const data = new TextEncoder().encode("look\n");
  session.write(data);
  ws.message(String(data.byteLength));
  ws.message(data.buffer);
  assert.deepEqual(received, [data]);
  assert.equal(ws.closed.length, 0);
});

test("unacknowledged output is capped; acknowledged bytes free space", () => {
  const ws = new FakeSocket();
  const session = new WebSocketSession(ws, () => {}, () => {});
  const chunk = new Uint8Array(1024 * 1024);
  session.write(chunk);
  ws.message(String(chunk.byteLength));
  session.write(chunk);
  assert.equal(ws.closed.length, 0);
  session.write(new Uint8Array(1));
  assert.equal(ws.closed[0].code, 1008);
});

test("ACKs cannot claim unsent bytes", () => {
  for (const ack of ["-1", "0", "1.5", "1024", '"4"', "{}", "null", "not-json"]) {
    const ws = new FakeSocket();
    new WebSocketSession(ws, () => {}, () => {});
    ws.message(ack);
    assert.equal(ws.closed[0].code, 1008);
  }
});

test("oversized frames never reach the runtime", () => {
  const ws = new FakeSocket();
  let received = false;
  new WebSocketSession(ws, () => { received = true; }, () => {});
  ws.message(new ArrayBuffer(8195));
  assert.equal(ws.closed[0].code, 1009);
  assert.equal(received, false);
});

test("end sends final output and defers disconnect to avoid reentrant mutations", async () => {
  const ws = new FakeSocket();
  let disconnected = 0;
  const session = new WebSocketSession(ws, () => {}, () => disconnected++);
  session.end("goodbye");
  assert.equal(disconnected, 0);
  assert.equal(new TextDecoder().decode(ws.sent[0]), "goodbye");
  assert.equal(ws.closed[0].code, 1000);
  await Promise.resolve();
  ws.dispatchEvent(new Event("close"));
  assert.equal(disconnected, 1);
  assert.equal(session.closing, true);
});

test("write errors close and clean up once", async () => {
  const ws = new FakeSocket();
  let disconnected = 0;
  const session = new WebSocketSession(ws, () => {}, () => disconnected++);
  ws.failSend = true;
  session.write(new Uint8Array(1));
  await Promise.resolve();
  assert.equal(ws.closed[0].code, 1011);
  assert.equal(disconnected, 1);
});
