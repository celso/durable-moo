import stringWidth from "string-width";

const segmenter = new Intl.Segmenter(undefined, { granularity: "grapheme" });
const graphemes = (text: string) => Array.from(segmenter.segment(text), (part) => part.segment);
const encoder = new TextEncoder();

/** Local line discipline: MOO accepts whole lines and does not echo keystrokes. */
export class LineEditor {
  private characters: string[] = [];
  private cursor = 0;
  private history: string[] = [];
  private historyIndex = 0;
  private draft = "";
  private secretEntered = false;
  privateMode = false;

  get value(): string { return this.characters.join(""); }

  insert(text: string): boolean {
    // Never let pasted terminal control sequences reach the local display.
    const clean = text.replace(/[\u0000-\u001f\u007f-\u009f]/g, "");
    const before = this.characters.slice(0, this.cursor).join("");
    const after = this.characters.slice(this.cursor).join("");
    if (encoder.encode(before + clean + after).byteLength > 8192) return false;
    this.characters = graphemes(before + clean + after);
    this.cursor = graphemes(before + clean).length;
    if (/^\s*(?:connect|create)\s+\S+\s+\S|^\s*@(?:new)?password\s+\S|\b(?:password|crypt)\b/i.test(this.value)) this.secretEntered = true;
    return true;
  }

  move(delta: number): void { this.cursor = Math.max(0, Math.min(this.characters.length, this.cursor + delta)); }
  home(): void { this.cursor = 0; }
  end(): void { this.cursor = this.characters.length; }
  backspace(): void { if (this.cursor > 0) this.characters.splice(--this.cursor, 1); }
  delete(): void { this.characters.splice(this.cursor, 1); }
  killBefore(): void { this.characters.splice(0, this.cursor); this.cursor = 0; }
  killAfter(): void { this.characters.splice(this.cursor); }
  killWord(): void {
    while (this.cursor > 0 && /^\s+$/u.test(this.characters[this.cursor - 1])) this.backspace();
    while (this.cursor > 0 && !/^\s+$/u.test(this.characters[this.cursor - 1])) this.backspace();
  }

  private get sensitive(): boolean {
    return this.privateMode || this.secretEntered || /^\s*(?:connect|create|@password|@newpassword)(?:\s|$)|\b(?:password|crypt)\b/i.test(this.value);
  }

  get display(): string {
    const value = this.value;
    if (!this.sensitive) return value;
    let visible = 0;
    if (!this.privateMode) {
      const credentials = /^(\s*(?:connect|create)\s+\S+(?:\s+|$))/i.exec(value);
      const passwordCommand = /^(\s*(?:@password|@newpassword)\s+)/i.exec(value);
      if (credentials) visible = credentials[0].length;
      else if (passwordCommand) visible = passwordCommand[0].length;
      else if (/^\s*(?:connect|create)(?:\s|$)/i.test(value)) visible = value.length;
    }
    return value.slice(0, visible) + "*".repeat(graphemes(value.slice(visible)).length);
  }

  /** Keep the editable line on one terminal row, scrolling it horizontally. */
  view(columns: number, prompt = "> "): { text: string; column: number } {
    const characters = graphemes(this.display);
    const widths = characters.map((character) => stringWidth(character));
    const room = Math.max(1, columns - stringWidth(prompt) - 1);
    let start = this.cursor;
    let before = 0;
    while (start > 0 && before + widths[start - 1] < room) before += widths[--start];
    let end = this.cursor;
    let width = before;
    while (end < characters.length && width + widths[end] <= room) width += widths[end++];
    const prefix = start > 0 ? "< " : prompt;
    return { text: prefix + characters.slice(start, end).join(""), column: stringWidth(prefix) + before };
  }

  recall(delta: -1 | 1): void {
    if (!this.history.length) return;
    if (this.historyIndex === this.history.length) this.draft = this.sensitive ? "" : this.value;
    this.historyIndex = Math.max(0, Math.min(this.history.length, this.historyIndex + delta));
    this.characters = graphemes(this.history[this.historyIndex] ?? this.draft);
    this.secretEntered = false;
    this.end();
  }

  submit(): string {
    const value = this.value;
    if (value && !this.sensitive && this.history.at(-1) !== value) {
      this.history.push(value);
      if (this.history.length > 100) this.history.shift();
    }
    this.clear();
    return value;
  }

  clear(): void {
    this.characters = [];
    this.cursor = 0;
    this.draft = "";
    this.secretEntered = false;
    this.historyIndex = this.history.length;
  }

  reset(): void {
    this.history = [];
    this.privateMode = false;
    this.clear();
  }
}
