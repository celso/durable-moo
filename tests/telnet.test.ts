import assert from "node:assert/strict";
import { test } from "node:test";
import { TelnetLines } from "../src/telnet";

function parse(chunks: number[][]) {
  const parser = new TelnetLines();
  const lines: number[][] = [];
  let overflows = 0;
  for (const chunk of chunks) parser.receive(new Uint8Array(chunk),
    (line) => lines.push([...line]), () => overflows++);
  return { lines, overflows };
}

test("frames CRLF/LF, partial lines, and ignores NUL", () => {
  assert.deepEqual(parse([[97, 13], [10, 98, 0, 99, 10, 10, 100]]), {
    lines: [[97], [98, 99], []], overflows: 0,
  });
});

test("negotiations, subnegotiations, escaped IAC and two-byte commands", () => {
  const bytes = [255, 251, 1, 97, 255, 250, 24, 0, 120, 255, 255, 255, 240,
    255, 241, 98, 255, 255, 10];
  for (let split = 0; split <= bytes.length; split++) {
    assert.deepEqual(parse([bytes.slice(0, split), bytes.slice(split)]), {
      lines: [[97, 98, 255]], overflows: 0,
    });
  }
});

test("accepts exactly the limit including CRLF; rejects one extra byte once", () => {
  const line = Array(8192).fill(97);
  assert.deepEqual(parse([line, [13, 10]]), { lines: [line], overflows: 0 });
  assert.deepEqual(parse([line, [98, 10, 99, 10], [100, 10]]), { lines: [], overflows: 1 });
});
