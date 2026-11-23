import { build } from "esbuild";
import { copyFile, mkdir } from "node:fs/promises";
import { fileURLToPath } from "node:url";

const root = new URL("../", import.meta.url);
const output = new URL("dist/web/", root);
await mkdir(new URL("assets/", output), { recursive: true });
await Promise.all([
  ...["index.html", "style.css"].map((name) => copyFile(new URL(`web/${name}`, root), new URL(name, output))),
  copyFile(new URL("../wasm/librio_wasm_bg.wasm", import.meta.resolve("rioterm")), new URL("assets/rioterm.wasm", output)),
  copyFile(new URL("web/rioterm-LICENSE.txt", root), new URL("assets/rioterm-LICENSE.txt", output)),
  copyFile(new URL("web/octicons-LICENSE.txt", root), new URL("assets/octicons-LICENSE.txt", output)),
  build({
    entryPoints: [fileURLToPath(new URL("web/client.ts", root))],
    outfile: fileURLToPath(new URL("assets/client.js", output)),
    bundle: true,
    format: "esm",
    platform: "browser",
    target: "es2022",
    minify: true,
    legalComments: "eof",
  }),
]);
console.log("Built browser terminal assets in dist/web");
