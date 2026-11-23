# Durable MOO port

## Preserved

- LambdaMOO runtime and Wasm ABI, including the pinned Emscripten build.
- Canonical LambdaCore seed database and classic database snapshot format.
- One authoritative `GameWorld` per named world, currently `default`.
- Chunked SQLite snapshot generations committed before command output.
- Durable Object alarms for suspended tasks.

## Native TCP migration

- Replace vendored `@cloudflare/net` ingress with the Worker's `connect()` handler.
- Transfer native socket byte streams to `GameWorld.serve()` over RPC.
- Await each session through the handler's lifetime.
- Replace EventEmitter-style sockets with bounded Web Streams output.
- Remove Zig proxy, control/data WebSockets, proxy secrets, and intermediary DOs.
- Configure Wrangler's local TCP listener and document Spectrum production ingress.
- Test framing, session cleanup, Wasm behavior, and actual local TCP connections.

## Follow-ups

- Deployment/restart and alarm recovery integration tests.
- Admission limits, rate limiting, authentication hardening, and load tests before
  untrusted public hosting.
- Measure full snapshot costs; optimize checkpointing without weakening durability.
- Benchmark multi-user throughput and slow-client behavior under sustained load.
