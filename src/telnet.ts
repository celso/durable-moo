const MAX_LINE_BYTES = 8192;

/** Minimal Telnet framing, including negotiations split across TCP chunks. */
export class TelnetLines {
  private line: number[] = [];
  private state: "data" | "iac" | "option" | "subnegotiation" | "subnegotiation-iac" = "data";
  private failed = false;

  receive(data: Uint8Array, onLine: (line: Uint8Array) => void, onOverflow: () => void): void {
    for (const byte of data) {
      if (this.failed) return;
      if (this.state === "option") { this.state = "data"; continue; }
      if (this.state === "subnegotiation") {
        if (byte === 255) this.state = "subnegotiation-iac";
        continue;
      }
      if (this.state === "subnegotiation-iac") {
        this.state = byte === 240 ? "data" : "subnegotiation";
        continue;
      }
      if (this.state === "iac") {
        this.state = byte >= 251 && byte <= 254 ? "option"
          : byte === 250 ? "subnegotiation" : "data";
        if (byte !== 255) continue;
      } else if (byte === 255) {
        this.state = "iac";
        continue;
      }
      if (byte === 10) {
        const line = new Uint8Array(this.line);
        this.line = [];
        onLine(line);
      } else if (byte !== 13 && byte !== 0) {
        if (this.line.length === MAX_LINE_BYTES) {
          this.failed = true;
          this.line = [];
          onOverflow();
          return;
        }
        this.line.push(byte);
      }
    }
  }
}
