import assert from "node:assert/strict";
import { test } from "node:test";
import stringWidth from "string-width";
import { LineEditor } from "../web/line-editor";

test("inline editing supports cursor movement, insertion, deletion, and kill shortcuts", () => {
  const editor = new LineEditor();
  editor.insert("say helo");
  editor.move(-1);
  editor.insert("l");
  assert.equal(editor.value, "say hello");
  editor.home(); editor.delete(); editor.insert("s"); editor.end();
  editor.killWord();
  assert.equal(editor.value, "say ");
  editor.insert("world"); editor.move(-5); editor.killAfter();
  assert.equal(editor.value, "say ");
  editor.killBefore();
  assert.equal(editor.value, "");
});

test("deletes graphemes, not individual Unicode code units", () => {
  const editor = new LineEditor();
  editor.insert("e\u0301👩‍💻");
  editor.backspace();
  assert.equal(editor.value, "e\u0301");
  editor.backspace();
  assert.equal(editor.value, "");
});

test("bounds input in UTF-8 bytes and strips display control sequences", () => {
  const editor = new LineEditor();
  assert.ok(editor.insert("é".repeat(4096)));
  assert.equal(editor.insert("x"), false);
  assert.equal(editor.value.length, 4096);
  editor.clear();
  editor.insert("hello\x1b\r\n\0\x7fworld");
  assert.equal(editor.value, "helloworld");
});

test("long ASCII and wide-character input stays on one terminal row", () => {
  for (const text of ["say " + "a".repeat(500), "say " + "界".repeat(100)]) {
    const editor = new LineEditor();
    editor.insert(text);
    for (const columns of [12, 32, 80]) {
      editor.end();
      for (let cursor = 0; cursor < text.length; cursor++) {
        const view = editor.view(columns);
        assert.ok(stringWidth(view.text) < columns);
        assert.ok(view.column >= 2 && view.column < columns);
        editor.move(-1);
      }
    }
  }
});

test("credentials are masked before local echo, omitted from history, and cleared on submit", () => {
  const editor = new LineEditor();
  editor.insert("look"); editor.submit();
  for (const command of ["connect alice secret", "create alice secret", "@password old secret", ';player.password = crypt("secret")']) {
    editor.insert(command);
    assert.ok(!editor.display.includes("secret"));
    assert.equal(editor.submit(), command);
    assert.equal(editor.value, "");
    editor.recall(-1);
    assert.equal(editor.value, "look");
    editor.clear();
  }
  editor.insert("connect alice ");
  assert.equal(editor.display, "connect alice ");
  editor.insert("s");
  assert.equal(editor.display, "connect alice *");
  editor.home(); editor.delete();
  assert.doesNotMatch(editor.display, /alice/);
  editor.submit(); editor.recall(-1);
  assert.equal(editor.value, "look");
});

test("history restores drafts, private mode omits secrets, and disconnect clears history", () => {
  const editor = new LineEditor();
  editor.insert("look"); editor.submit();
  editor.insert("who"); editor.submit();
  editor.insert("say draft"); editor.recall(-1);
  assert.equal(editor.value, "who");
  editor.recall(-1); assert.equal(editor.value, "look");
  editor.recall(1); editor.recall(1);
  assert.equal(editor.value, "say draft");
  editor.clear(); editor.privateMode = true; editor.insert("sensitive answer");
  assert.equal(editor.display, "****************");
  editor.submit(); editor.privateMode = false; editor.recall(-1);
  assert.equal(editor.value, "who");
  editor.reset(); editor.recall(-1);
  assert.equal(editor.value, "");
});
