import { test, expect } from "@playwright/test";
import { createConnection } from "node:net";
import { randomUUID } from "node:crypto";
import { execFile } from "node:child_process";
import { promisify } from "node:util";
import WebSocket from "ws";

async function command(page, line) {
  await page.locator("#terminal").focus();
  await expect(page.locator("#terminal-input")).toBeFocused();
  await page.keyboard.insertText(line);
  await page.keyboard.press("Enter");
}

test("self-hosted Rioterm loads, logs in, edits commands, quits, and reconnects", async ({ page }, testInfo) => {
  const errors = [];
  page.on("pageerror", (error) => errors.push(error.message));
  const resources = [];
  page.on("request", (request) => resources.push(request.url()));
  await page.goto("/");
  await expect(page.getByRole("status")).toHaveText("Connected");
  await expect(page.locator("#terminal")).toContainText("Welcome to the LambdaCore database");
  await expect(page.locator("#terminal")).toContainText("❯ telnet 127.0.0.1 7777");
  await expect(page.locator("#terminal")).toContainText("Trying 127.0.0.1...");
  await expect(page.locator("#terminal")).toContainText("Escape character is '^]'.");
  await expect(page.getByRole("link", { name: "Durable MOO on GitHub (opens in a new tab)" })).toHaveAttribute("href", "https://github.com/celso/durable-moo");
  await expect(page.getByText("A WORLD AT THE EDGE")).toHaveCount(0);
  await expect(page.locator("footer")).toHaveCount(0);
  await command(page, "connect wizard");
  await expect(page.locator("#terminal")).toContainText("The First Room");
  await page.locator("#terminal").click({ position: { x: 8, y: 8 } });
  await expect(page.locator("#terminal-input")).toBeFocused();
  await page.keyboard.insertText(";1 + 9");
  await page.keyboard.press("Backspace");
  await page.keyboard.insertText("2");
  await expect(page.locator("#terminal")).toContainText("> ;1 + 2");
  await page.keyboard.press("Enter");
  await expect(page.locator("#terminal")).toContainText("=> 3");
  await expect(page.locator("form")).toHaveCount(0);
  await page.keyboard.press("ArrowUp");
  await page.keyboard.press("Enter");
  await expect.poll(async () => ((await page.locator("#terminal").innerText()).match(/=> 3/g) ?? []).length).toBe(2);
  await page.screenshot({ path: testInfo.outputPath("desktop.png"), fullPage: true });
  await page.keyboard.press("Control+BracketRight");
  await expect(page.locator("#terminal")).toContainText("telnet>");
  await page.keyboard.insertText("status");
  await page.keyboard.press("Enter");
  await expect(page.locator("#terminal")).toContainText("telnet> status");
  await page.keyboard.press("Enter");
  await command(page, "@quit");
  await expect(page.getByRole("status")).toHaveText("Disconnected");
  await page.getByRole("button", { name: "Reconnect" }).click();
  await expect(page.getByRole("status")).toHaveText("Connected");
  expect(resources.some((url) => url.endsWith("/assets/rioterm.wasm"))).toBe(true);
  expect(resources.every((url) => url.startsWith("http://127.0.0.1:8797/"))).toBe(true);
  expect(errors).toEqual([]);
});

test("login secrets are masked in the terminal and never echoed to the transcript", async ({ page }) => {
  await page.goto("/");
  await expect(page.getByRole("status")).toHaveText("Connected");
  await page.locator("#terminal").focus();
  const password = randomUUID();
  await page.keyboard.insertText(`connect nobody ${password}`);
  await expect(page.locator("#terminal")).toContainText("connect nobody ****");
  await expect(page.locator("#terminal")).not.toContainText(password);
  await page.keyboard.press("Enter");
  await expect(page.locator("#terminal-input")).toHaveValue(" ");
  await expect(page.locator("#terminal")).toContainText("Either that player does not exist");
  await expect(page.locator("#terminal")).not.toContainText(password);
  expect(await page.evaluate(() => ({ local: localStorage.length, session: sessionStorage.length }))).toEqual({ local: 0, session: 0 });
});

test("browser and TCP players share broadcasts in both directions", async ({ page }) => {
  await page.goto("/");
  await expect(page.getByRole("status")).toHaveText("Connected");
  await command(page, "connect wizard");
  await expect(page.locator("#terminal")).toContainText("The First Room");
  const name = `web${randomUUID().replaceAll("-", "").slice(0, 10)}`;
  await command(page, `;;p = create($player); p.name = "${name}"; p.aliases = {"${name}"}; $wiz_utils:set_player(p); p.password = crypt("${name}"); move(p, player.location); return p;`);
  await expect(page.locator("#terminal")).toContainText("=> #");
  const created = (await page.locator("#terminal").innerText()).match(/=> (#\d+)/)?.[1];
  expect(created).toBeTruthy();
  const tcp = createConnection({ host: "127.0.0.1", port: 17777 });
  tcp.setEncoding("utf8");
  let output = "";
  tcp.on("data", (chunk) => { output += chunk; });
  const failure = [];
  tcp.on("error", (error) => failure.push(error.message));
  try {
    await expect.poll(() => output).toContain("Welcome to the LambdaCore database");
    tcp.write(`connect ${name} ${name}\r\n`);
    await expect.poll(() => output).toContain("The First Room");
    await command(page, `say ${name}-from-browser`);
    await expect.poll(() => output).toContain(`${name}-from-browser`);
    tcp.write(`say ${name}-from-tcp\r\n`);
    await expect(page.locator("#terminal")).toContainText(`${name}-from-tcp`);
    // Incoming output must not discard or corrupt a partially typed command.
    await page.locator("#terminal").focus();
    await page.keyboard.insertText(`say ${name}-draft`);
    tcp.write(`say ${name}-interrupt\r\n`);
    await expect(page.locator("#terminal")).toContainText(`${name}-interrupt`);
    await expect(page.locator("#terminal")).toContainText(`> say ${name}-draft`);
    await page.keyboard.press("Enter");
    await expect.poll(() => output).toContain(`${name}-draft`);
    tcp.write("@quit\r\n");
    await expect.poll(() => output).toContain("*** Disconnected ***");
    await command(page, `;;recycle(${created}); return "cleaned";`);
    await expect(page.locator("#terminal")).toContainText('=> "cleaned"');
    expect(failure).toEqual([]);
  } finally {
    tcp.destroy();
  }
});

test("reflows on mobile and supports touch focus, virtual keyboard input, and scrollback", async ({ browser }, testInfo) => {
  const context = await browser.newContext({ viewport: { width: 320, height: 740 }, isMobile: true, hasTouch: true });
  const page = await context.newPage();
  try {
    await page.goto("http://127.0.0.1:8797/");
    await expect(page.getByRole("status")).toHaveText("Connected");
    await page.locator("#terminal").tap({ position: { x: 8, y: 8 } });
    await expect(page.locator("#terminal-input")).toBeFocused();
    await page.keyboard.insertText("connect wizard");
    await page.keyboard.press("Enter");
    await expect(page.locator("#terminal")).toContainText("The First Room");
    const width = await page.evaluate(() => ({ scroll: document.documentElement.scrollWidth, client: document.documentElement.clientWidth }));
    expect(width.scroll).toBeLessThanOrEqual(width.client);
    await expect(page.locator("form")).toHaveCount(0);
    await page.locator("#terminal").focus();
    await page.keyboard.press("PageUp");
    await page.keyboard.press("PageDown");
    await page.screenshot({ path: testInfo.outputPath("mobile.png"), fullPage: true });
  } finally { await context.close(); }
});

test("multiline paste and IME composition feed the in-terminal editor", async ({ page }) => {
  await page.goto("/");
  await expect(page.getByRole("status")).toHaveText("Connected");
  await command(page, "connect wizard");
  await expect(page.locator("#terminal")).toContainText("The First Room");
  await page.locator("#terminal").focus();
  await page.evaluate(() => {
    const input = document.querySelector("#terminal-input");
    const transfer = new DataTransfer();
    transfer.setData("text/plain", ";12 + 1\n;12 + 2\n");
    input.dispatchEvent(new ClipboardEvent("paste", { clipboardData: transfer, bubbles: true }));
  });
  await expect(page.locator("#terminal")).toContainText("=> 13");
  await expect(page.locator("#terminal")).toContainText("=> 14");
  await page.evaluate(() => {
    const input = document.querySelector("#terminal-input");
    input.dispatchEvent(new CompositionEvent("compositionstart"));
    input.value = " say こんにちは";
    input.dispatchEvent(new InputEvent("input", { data: "say こんにちは", inputType: "insertCompositionText", isComposing: true }));
    input.dispatchEvent(new CompositionEvent("compositionend", { data: "say こんにちは" }));
  });
  await expect(page.locator("#terminal")).toContainText("> say こんにちは");
  await page.keyboard.press("Enter");
  await expect(page.locator("#terminal")).toContainText('You say, "こんにちは"');
});

test("Wasm load failures show recovery guidance instead of an empty terminal", async ({ page }) => {
  await page.route("**/assets/rioterm.wasm", (route) => route.abort());
  await page.goto("/");
  await expect(page.getByRole("status")).toHaveText("Terminal unavailable");
  await expect(page.locator("#notice")).toContainText("Refresh to retry");
  await expect(page.locator("#terminal")).toHaveAttribute("aria-disabled", "true");
});

test("HTTP routes reject invalid upgrades and cross-origin requests", async ({ request }) => {
  expect((await request.get("/ws")).status()).toBe(426);
  expect((await request.get("/ws", { headers: { Upgrade: "websocket", Origin: "https://other.example" } })).status()).toBe(403);
  expect((await request.get("/missing")).status()).toBe(404);
  const page = await request.get("/");
  expect(page.headers()["content-security-policy"]).toContain("frame-ancestors 'none'");
  const wasm = await request.get("/assets/rioterm.wasm");
  expect(wasm.headers()["content-type"]).toContain("application/wasm");
});

test("oversized WebSocket input closes without executing the trailing command", async () => {
  const ws = new WebSocket("ws://127.0.0.1:8797/ws", { origin: "http://127.0.0.1:8797" });
  const closed = new Promise((resolve, reject) => {
    ws.on("error", reject);
    ws.on("close", resolve);
  });
  ws.on("open", () => ws.send(Buffer.alloc(8195, 97)));
  expect(await closed).toBe(1009);
});

test("the original native TCP smoke suite still passes", async () => {
  const { stdout } = await promisify(execFile)(process.execPath, ["scripts/smoke-tcp.mjs"], {
    env: { ...process.env, TCP_PORT: "17777" }, timeout: 25000,
  });
  expect(stdout).toContain("TCP smoke test passed");
});
