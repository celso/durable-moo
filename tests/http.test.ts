import assert from "node:assert/strict";
import { test } from "node:test";
import { secureAssetResponse, validateWebSocketRequest } from "../src/http";

test("WebSocket upgrades must be same-origin GET requests", () => {
  const request = (headers: Record<string, string>, method = "GET") => new Request("https://moo.example/ws", { headers, method });
  assert.equal(validateWebSocketRequest(request({} ))?.status, 426);
  assert.equal(validateWebSocketRequest(request({ Upgrade: "websocket" }))?.status, 403);
  assert.equal(validateWebSocketRequest(request({ Upgrade: "websocket", Origin: "https://other.example" }))?.status, 403);
  assert.equal(validateWebSocketRequest(request({ Upgrade: "websocket", Origin: "null" }))?.status, 403);
  assert.equal(validateWebSocketRequest(request({ Upgrade: "websocket", Origin: "https://moo.example" }, "POST"))?.status, 405);
  assert.equal(validateWebSocketRequest(request({ Upgrade: "WebSocket", Origin: "https://moo.example" })), undefined);
});

test("assets disallow third-party scripts, framing, and terminal clipboard writes", async () => {
  const response = secureAssetResponse(new Response("page", { headers: { "Content-Type": "text/html" } }));
  assert.equal(await response.text(), "page");
  assert.equal(response.headers.get("Content-Type"), "text/html");
  assert.match(response.headers.get("Content-Security-Policy")!, /script-src 'self' 'wasm-unsafe-eval'/);
  assert.match(response.headers.get("Content-Security-Policy")!, /frame-ancestors 'none'/);
  assert.match(response.headers.get("Permissions-Policy")!, /clipboard-write=\(\)/);
  assert.equal(response.headers.get("X-Content-Type-Options"), "nosniff");
});
