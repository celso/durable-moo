import { spawn } from "node:child_process";
import { mkdir, readFile, writeFile } from "node:fs/promises";
import { fileURLToPath } from "node:url";
import { parse } from "jsonc-parser";

const root = new URL("../", import.meta.url);
const errors = [];
const config = parse(await readFile(new URL("wrangler.jsonc", root), "utf8"), errors);
if (errors.length) throw new Error("Cannot parse wrangler.jsonc");
// Reuse the real configuration, but never bind its TCP port or touch its world.
config.name = "durable-moo-browser-tests";
config.main = fileURLToPath(new URL(config.main, root));
config.assets.directory = fileURLToPath(new URL(config.assets.directory + "/", root));
config.build.cwd = fileURLToPath(root);
config.build.watch_dir = fileURLToPath(new URL("web/", root));
config.connect = [{ protocol: "tcp", port: 17777 }];
const configPath = new URL(".wrangler/browser-tests-config.json", root);
await mkdir(new URL(".wrangler/", root), { recursive: true });
await writeFile(configPath, JSON.stringify(config));
const child = spawn("pnpm", ["exec", "wrangler", "dev", "--config", fileURLToPath(configPath),
  "--local", "--ip", "127.0.0.1", "--port", "8797", "--inspector-port", "9247",
  "--persist-to", fileURLToPath(new URL(".wrangler/browser-tests/", root))], {
  cwd: fileURLToPath(root), stdio: "inherit",
});
for (const signal of ["SIGTERM", "SIGINT"]) process.on(signal, () => child.kill(signal));
child.on("error", (error) => { console.error(error); process.exitCode = 1; });
child.on("exit", (code) => { process.exitCode = code ?? 0; });
