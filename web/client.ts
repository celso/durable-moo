import { DOMRenderer, Terminal, defaultTheme, initWasm } from "rioterm";
import { LineEditor } from "./line-editor";

function element<T extends HTMLElement>(selector: string): T {
  const result = document.querySelector<T>(selector);
  if (!result) throw new Error(`Missing element: ${selector}`);
  return result;
}

const viewport = element<HTMLDivElement>("#terminal");
const connection = element<HTMLButtonElement>("#connection");
const status = element<HTMLParagraphElement>("#status");
const notice = element<HTMLParagraphElement>("#notice");
const encoder = new TextEncoder();
let socket: WebSocket | undefined;

function notify(text: string): void {
  notice.textContent = text;
  notice.hidden = false;
}

function setStatus(text: string, connected = false): void {
  status.textContent = text;
  status.dataset.connected = String(connected);
  viewport.setAttribute("aria-disabled", String(!connected));
}

async function start(): Promise<void> {
  await initWasm(new URL("/assets/rioterm.wasm", location.href));
  const terminal = new Terminal({ cols: 80, rows: 24, scrollback: 2000, convertEol: true, detectUrls: false });
  // The headless core and DOM renderer keep remote OSC clipboard/link actions
  // disabled. A transparent, cursor-anchored textarea captures keys, IME, and
  // touch keyboards; the actual input line and caret are painted by Rioterm.
  const renderer = new DOMRenderer(terminal, {
    fontSize: 14, lineHeight: 1.5,
    fontFamily: '"SF Mono", Consolas, "Liberation Mono", monospace',
    theme: {
      ...defaultTheme,
      background: "#FFFDFB", foreground: "#521000", cursor: "#521000",
      selectionBackground: "#EBD5C1", selectionForeground: "#521000",
    },
  });
  renderer.element.style.userSelect = "text";
  viewport.append(renderer.element);
  const input = document.createElement("textarea");
  input.id = "terminal-input";
  input.setAttribute("aria-label", "Terminal input");
  input.setAttribute("aria-describedby", "terminal-help");
  input.setAttribute("autocomplete", "off");
  input.setAttribute("autocapitalize", "off");
  input.setAttribute("autocorrect", "off");
  input.spellcheck = false;
  input.disabled = true;
  viewport.append(input);

  const editor = new LineEditor();
  let promptVisible = false;
  let promptNewline = false;
  let outputColumn = 0;
  let composing = false;
  let telnetMode = false;
  const connected = () => socket?.readyState === WebSocket.OPEN;
  const resetInput = () => { input.value = " "; input.setSelectionRange(1, 1); };
  resetInput();

  function positionInput(): void {
    const cursor = terminal.cursorPosition();
    input.style.left = `${cursor.col * renderer.cellWidth}px`;
    input.style.top = `${Math.min(terminal.options.rows - 1, Math.max(0, cursor.line)) * renderer.cellHeight}px`;
  }

  function clearPrompt(): void {
    if (!promptVisible) return;
    terminal.scrollLines(-terminal.displayOffset());
    terminal.write("\r\x1b[2K");
    // A temporary newline keeps input below a partial server output line.
    // Restore that output position so later frames join it without corruption.
    if (promptNewline) terminal.write(`\x1b[1A\r\x1b[${outputColumn}C`);
    promptVisible = false;
  }

  function drawPrompt(): void {
    if (!connected()) return;
    if (!promptVisible) {
      outputColumn = terminal.cursorPosition().col;
      promptNewline = outputColumn !== 0;
      if (promptNewline) terminal.write("\r\n");
    }
    const view = editor.view(terminal.options.cols, telnetMode ? "telnet> " : "> ");
    terminal.write(`\r\x1b[2K${view.text}\r\x1b[${view.column}C`);
    promptVisible = true;
    positionInput();
  }

  const resize = new ResizeObserver(() => {
    clearPrompt();
    renderer.fit(viewport.clientWidth, viewport.clientHeight);
    drawPrompt();
  });
  resize.observe(viewport);
  renderer.fit(viewport.clientWidth, viewport.clientHeight);
  viewport.addEventListener("focus", () => { if (connected()) input.focus({ preventScroll: true }); });
  viewport.addEventListener("pointerup", () => {
    if (connected() && window.getSelection()?.isCollapsed !== false) input.focus({ preventScroll: true });
  });
  viewport.addEventListener("wheel", (event) => {
    if (!event.deltaY) return;
    terminal.scrollLines(-Math.sign(event.deltaY) * 3);
    event.preventDefault();
  }, { passive: false });

  function submit(): void {
    if (!socket || !connected()) return;
    if (socket.bufferedAmount > 64 * 1024) {
      notify("Connection is busy. Please wait before sending another command.");
      return;
    }
    clearPrompt();
    if (terminal.cursorPosition().col !== 0) terminal.write("\r\n");
    terminal.write(`${telnetMode ? "telnet> " : "> "}${editor.display}\r\n`);
    const line = editor.submit();
    if (telnetMode) {
      const command = line.trim().toLowerCase();
      if (["q", "quit", "close"].includes(command)) socket.close(1000, "Disconnected by player");
      else if (!command) telnetMode = false;
      else if (command === "status") terminal.write("Connected to localhost.\r\n");
      else terminal.write("Commands: close, quit, status, help. Press Enter on an empty line to return to the world.\r\n");
    } else socket.send(encoder.encode(line + "\n"));
    resetInput();
    drawPrompt();
  }

  function insert(text: string): void {
    if (!connected()) return;
    // A bounded multiline paste behaves like a CLI, not an unbounded frame.
    if (encoder.encode(text).byteLength > 64 * 1024) {
      notify("Paste too large. Paste at most 64 KiB at a time.");
      return;
    }
    const lines = text.replace(/\r\n?/g, "\n").split("\n");
    for (let index = 0; index < lines.length; index++) {
      if (!editor.insert(lines[index])) {
        notify("Command too long. The limit is 8 KiB.");
        break;
      }
      if (index < lines.length - 1) submit();
    }
    terminal.scrollLines(-terminal.displayOffset());
    drawPrompt();
  }

  input.addEventListener("keydown", (event) => {
    if (event.isComposing || composing || !connected()) return;
    const ctrl = event.ctrlKey && !event.altKey && !event.metaKey;
    if ((event.ctrlKey || event.metaKey) && event.key.toLowerCase() === "c" && !window.getSelection()?.isCollapsed) return;
    let handled = true;
    if (ctrl && (event.key === "]" || event.code === "BracketRight")) {
      clearPrompt(); editor.clear(); telnetMode = true;
      terminal.write("\r\n");
    } else if (event.altKey && event.key.toLowerCase() === "p") {
      editor.privateMode = !editor.privateMode;
      notify(editor.privateMode ? "Private input on. Alt+P to show typing again." : "Private input off. Login and password commands are still masked.");
    } else if (ctrl && event.key.toLowerCase() === "a") editor.home();
    else if (ctrl && event.key.toLowerCase() === "e") editor.end();
    else if (ctrl && event.key.toLowerCase() === "u") editor.killBefore();
    else if (ctrl && event.key.toLowerCase() === "k") editor.killAfter();
    else if (ctrl && event.key.toLowerCase() === "w") editor.killWord();
    else if (ctrl && event.key.toLowerCase() === "c") {
      clearPrompt(); editor.clear(); terminal.write("^C\r\n");
    } else if (ctrl && event.key.toLowerCase() === "l") {
      clearPrompt(); terminal.write("\x1b[2J\x1b[H");
    } else if (ctrl && event.key.toLowerCase() === "d") {
      if (editor.value) editor.delete(); else socket?.close(1000, "Disconnected by player");
    } else if (event.key === "Enter") submit();
    else if (event.key === "Backspace") editor.backspace();
    else if (event.key === "Delete") editor.delete();
    else if (event.key === "ArrowLeft") editor.move(-1);
    else if (event.key === "ArrowRight") editor.move(1);
    else if (event.key === "Home") editor.home();
    else if (event.key === "End") editor.end();
    else if (event.key === "ArrowUp") editor.recall(-1);
    else if (event.key === "ArrowDown") editor.recall(1);
    else if (event.key === "PageUp" || event.key === "PageDown") {
      terminal.scrollLines((event.key === "PageUp" ? 1 : -1) * Math.max(1, terminal.options.rows - 1));
      event.preventDefault(); return;
    } else handled = false;
    if (handled) { event.preventDefault(); resetInput(); drawPrompt(); }
  });
  input.addEventListener("paste", (event) => {
    event.preventDefault();
    insert(event.clipboardData?.getData("text/plain") ?? "");
    resetInput();
  });
  const consumeInput = () => {
    const text = input.value.startsWith(" ") ? input.value.slice(1) : input.value;
    if (text) insert(text);
    resetInput();
  };
  input.addEventListener("compositionstart", () => { composing = true; });
  input.addEventListener("compositionend", () => { composing = false; consumeInput(); });
  input.addEventListener("input", (event) => {
    if (composing || event.isComposing) return;
    if (event.inputType === "deleteContentBackward") { editor.backspace(); resetInput(); drawPrompt(); }
    else if (event.inputType === "deleteContentForward") { editor.delete(); resetInput(); drawPrompt(); }
    else consumeInput();
  });

  function connect(): void {
    if (socket && socket.readyState < WebSocket.CLOSING) return;
    setStatus("Connecting…");
    connection.disabled = true;
    connection.textContent = "Connecting…";
    // Cosmetic telnet transcript: the actual transport remains same-origin WS.
    terminal.write("❯ telnet localhost 7777\r\nTrying localhost...\r\n");
    const url = new URL("/ws", location.href);
    url.protocol = location.protocol === "https:" ? "wss:" : "ws:";
    const current = new WebSocket(url);
    current.binaryType = "arraybuffer";
    socket = current;
    const timeout = window.setTimeout(() => current.close(), 15000);
    current.addEventListener("open", () => {
      clearTimeout(timeout);
      if (current !== socket) return;
      setStatus("Connected", true);
      notice.hidden = true;
      notice.textContent = "";
      editor.reset();
      telnetMode = false;
      resetInput();
      input.disabled = false;
      connection.textContent = "Disconnect";
      connection.disabled = false;
      terminal.write("Connected to localhost.\r\nEscape character is '^]'.\r\n\r\n");
      drawPrompt();
      // Do not summon a mobile keyboard until the player taps the terminal.
      if (matchMedia("(pointer: fine)").matches) input.focus({ preventScroll: true });
    });
    current.addEventListener("message", (event: MessageEvent<unknown>) => {
      if (current !== socket || !(event.data instanceof ArrayBuffer)) return;
      clearPrompt();
      terminal.write(new Uint8Array(event.data));
      drawPrompt();
      if (current.readyState === WebSocket.OPEN) current.send(String(event.data.byteLength));
    });
    current.addEventListener("error", () => { if (current === socket) setStatus("Connection failed"); });
    current.addEventListener("close", () => {
      clearTimeout(timeout);
      if (current !== socket) return;
      clearPrompt();
      editor.reset();
      telnetMode = false;
      resetInput();
      input.disabled = true;
      setStatus("Disconnected");
      connection.textContent = "Reconnect";
      connection.disabled = false;
      terminal.write("\r\n[Disconnected. Reconnect to log in again.]\r\n");
    });
  }

  connection.addEventListener("click", () => {
    if (connected()) socket?.close(1000, "Disconnected by player");
    else connect();
  });
  window.addEventListener("pagehide", () => { editor.reset(); resetInput(); socket?.close(1000, "Page closed"); });
  window.addEventListener("pageshow", (event) => { if (event.persisted) connect(); });
  connect();
}

start().catch(() => {
  setStatus("Terminal unavailable");
  notify("The browser terminal could not load. Refresh to retry, or use a Telnet client.");
});
