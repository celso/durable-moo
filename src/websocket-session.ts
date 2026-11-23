import type { SessionSocket } from "./session-socket";

const MAX_PENDING_BYTES = 1024 * 1024;
const MAX_INPUT_FRAME_BYTES = 8194;

type BrowserSocket = Pick<WebSocket, "close" | "addEventListener"> & {
  send(data: Uint8Array): void;
};

/** Binary input/output. Text frames acknowledge rendered output bytes.
 * Application acknowledgements bound output even without a platform drain API.
 */
export class WebSocketSession implements SessionSocket {
  private stopped = false;
  private disconnected = false;
  private pendingBytes = 0;

  constructor(
    private readonly socket: BrowserSocket,
    onData: (data: Uint8Array) => void,
    private readonly onClose: () => void,
  ) {
    socket.addEventListener("message", (event) => {
      if (this.stopped) return;
      try {
        if (typeof event.data === "string") {
          if (event.data.length > 128) return this.close(1008, "Invalid acknowledgement");
          let ack: unknown;
          try { ack = JSON.parse(event.data); } catch {
            return this.close(1008, "Invalid acknowledgement");
          }
          if (typeof ack !== "number" || !Number.isSafeInteger(ack) || ack <= 0 || ack > this.pendingBytes) {
            return this.close(1008, "Invalid acknowledgement");
          }
          this.pendingBytes -= ack;
        } else if (event.data instanceof ArrayBuffer) {
          if (event.data.byteLength > MAX_INPUT_FRAME_BYTES) return this.close(1009, "Input frame too large");
          onData(new Uint8Array(event.data));
        } else {
          this.close(1003, "Binary input required");
        }
      } catch {
        this.close(1011, "Session failed");
      }
    });
    socket.addEventListener("close", () => this.finish());
    socket.addEventListener("error", () => this.close(1011, "Connection failed"));
  }

  get closing(): boolean { return this.stopped; }

  write(data: Uint8Array): void {
    if (this.stopped || data.byteLength === 0) return;
    if (this.pendingBytes + data.byteLength > MAX_PENDING_BYTES) {
      this.close(1008, "Output buffer limit exceeded");
      return;
    }
    try {
      this.pendingBytes += data.byteLength;
      this.socket.send(data);
    } catch {
      this.close(1011, "Connection failed");
    }
  }

  end(message?: string): void {
    if (message) this.write(new TextEncoder().encode(message));
    this.close(1000, "Session ended");
  }

  private close(code: number, reason: string): void {
    if (this.stopped) return;
    this.stopped = true;
    try { this.socket.close(code, reason); } catch { /* Transport already failed. */ }
    // end() can be called from inside a Wasm mutation. Do not re-enter it.
    queueMicrotask(() => this.finish());
  }

  private finish(): void {
    if (this.disconnected) return;
    this.stopped = true;
    this.disconnected = true;
    this.onClose();
  }
}
