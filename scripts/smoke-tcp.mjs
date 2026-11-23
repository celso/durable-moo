// Node is only the test client; the Worker itself uses native Workers sockets.
import assert from "node:assert/strict";
import { createConnection } from "node:net";
import { randomUUID } from "node:crypto";

const port = Number(process.env.TCP_PORT ?? 7777);
const clients = [];
const marker = `tcp${randomUUID().replaceAll("-", "").slice(0, 12)}`;

function client() {
  const socket = createConnection({ host: "127.0.0.1", port, allowHalfOpen: true });
  let text = "";
  let ended = false;
  let failure;
  const waiters = new Set();
  const changed = () => { for (const waiter of [...waiters]) waiter(); };
  socket.setEncoding("utf8");
  socket.on("data", (data) => { text += data; changed(); });
  socket.on("end", () => { ended = true; socket.end(); changed(); });
  socket.on("error", (error) => { failure = error; changed(); });
  socket.on("close", () => { ended = true; changed(); });
  function wait(predicate, label) {
    return new Promise((resolve, reject) => {
      const timer = setTimeout(() => finish(new Error(`Timed out: ${label}\n${text.slice(-2000)}`)), 15000);
      const check = () => {
        if (failure) finish(failure);
        else if (predicate()) finish();
        else if (ended) finish(new Error(`Connection ended: ${label}\n${text.slice(-2000)}`));
      };
      function finish(error) {
        clearTimeout(timer);
        waiters.delete(check);
        if (error) reject(error); else resolve();
      }
      waiters.add(check);
      check();
    });
  }
  const result = {
    socket,
    get text() { return text; },
    expect: (pattern, offset = 0) => wait(() => pattern.test(text.slice(offset)), String(pattern)),
    closed: () => wait(() => ended, "server EOF"),
    async command(command, pattern) {
      const offset = text.length;
      socket.write(`${command}\r\n`);
      await result.expect(pattern, offset);
      return text.slice(offset);
    },
  };
  clients.push(result);
  return result;
}

try {
  const wizard = client();
  await wizard.expect(/Welcome to the LambdaCore database/);
  await wizard.command("connect wizard", /The First Room/);
  await wizard.command(`;;add_property(player, "${marker}", "${marker}", {player, ""}); return player.${marker};`,
    new RegExp(`=> "${marker}"`));

  // Make a disposable second account to exercise broadcasts in a shared world.
  const created = await wizard.command(
    `;;p = create($player); p.name = "${marker}"; p.aliases = {"${marker}"}; $wiz_utils:set_player(p); p.password = crypt("${marker}"); move(p, player.location); return p;`,
    /=> #\d+/);
  const player = created.match(/=> (#\d+)/)[1];
  const second = client();
  await second.expect(/Welcome to the LambdaCore database/);
  await second.command(`connect ${marker} ${marker}`, /The First Room/);
  const offset = second.text.length;
  await wizard.command(`say ${marker}-broadcast`, new RegExp(`${marker}-broadcast`));
  await second.expect(new RegExp(`${marker}-broadcast`), offset);
  await second.command("@quit", /\*\*\* Disconnected \*\*\*/);
  await second.closed();
  await wizard.command(`;;recycle(${player}); return "recycled";`, /=> "recycled"/);
  await wizard.command("@quit", /\*\*\* Disconnected \*\*\*/);
  await wizard.closed();

  const reconnected = client();
  await reconnected.expect(/Welcome to the LambdaCore database/);
  await reconnected.command("connect wizard", /The First Room/);
  await reconnected.command(`;return player.${marker};`, new RegExp(`=> "${marker}"`));
  await reconnected.command(`;;delete_property(player, "${marker}"); return "cleaned";`, /=> "cleaned"/);
  await reconnected.command("@quit", /\*\*\* Disconnected \*\*\*/);
  await reconnected.closed();

  const oversized = client();
  await oversized.expect(/Welcome to the LambdaCore database/);
  oversized.socket.write("x".repeat(8193) + "\nconnect wizard\n");
  await oversized.expect(/Input line too long/);
  await oversized.closed();
  assert.doesNotMatch(oversized.text, /The First Room/);

  const halfClosed = client();
  await halfClosed.expect(/Welcome to the LambdaCore database/);
  halfClosed.socket.end("connect wizard\r\nlook\r\n");
  await halfClosed.expect(/The First Room/);
  await halfClosed.closed();
  console.log("TCP smoke test passed (login, broadcast, reconnect, limits, half-close, quit)");
} finally {
  for (const { socket } of clients) socket.destroy();
}
