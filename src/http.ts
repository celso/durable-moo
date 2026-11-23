/** Reject cross-origin browser upgrades before waking the world. */
export function validateWebSocketRequest(request: Request): Response | undefined {
  if (request.method !== "GET") {
    return new Response("Method not allowed", { status: 405, headers: { Allow: "GET" } });
  }
  if (request.headers.get("Upgrade")?.toLowerCase() !== "websocket") {
    return new Response("WebSocket upgrade required", { status: 426, headers: { Upgrade: "websocket" } });
  }
  if (request.headers.get("Origin") !== new URL(request.url).origin) {
    return new Response("Same-origin WebSocket required", { status: 403 });
  }
}

export function secureAssetResponse(response: Response): Response {
  const secured = new Response(response.body, response);
  secured.headers.set("Content-Security-Policy", [
    "default-src 'none'",
    "script-src 'self' 'wasm-unsafe-eval'",
    // Rioterm's DOM renderer sets per-cell inline styles.
    "style-src 'self' 'unsafe-inline'",
    "connect-src 'self'",
    "img-src 'self'",
    "base-uri 'none'",
    "form-action 'none'",
    "frame-ancestors 'none'",
  ].join("; "));
  secured.headers.set("X-Content-Type-Options", "nosniff");
  secured.headers.set("Referrer-Policy", "no-referrer");
  secured.headers.set("Permissions-Policy", "camera=(), microphone=(), geolocation=(), clipboard-write=()");
  return secured;
}
