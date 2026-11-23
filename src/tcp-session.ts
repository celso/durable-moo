const MAX_PENDING_BYTES = 1024 * 1024;

/** A bounded output queue: a stalled client must not exhaust the world heap. */
export class TcpSession {
  private readonly reader: ReadableStreamDefaultReader<Uint8Array>;
  private readonly output: ReadableStream<Uint8Array>;
  private controller!: ReadableStreamDefaultController<Uint8Array>;
  private stopped = false;
  private cancelled?: Promise<void>;

  constructor(readable: ReadableStream<Uint8Array>, private readonly writable: WritableStream<Uint8Array>) {
    this.reader = readable.getReader();
    this.output = new ReadableStream<Uint8Array>({
      start: (controller) => { this.controller = controller; },
      cancel: () => this.cancelInput(),
    }, new ByteLengthQueuingStrategy({ highWaterMark: MAX_PENDING_BYTES }));
  }

  get closing(): boolean { return this.stopped; }

  write(data: Uint8Array): void {
    if (this.stopped) return;
    if (data.byteLength > (this.controller.desiredSize ?? 0)) {
      this.stopped = true;
      this.controller.error(new Error("TCP client exceeded the output buffer limit"));
      this.cancelInput();
      return;
    }
    this.controller.enqueue(data);
  }

  end(message?: string): void {
    if (message) this.write(new TextEncoder().encode(message));
    if (this.stopped) return;
    this.stopped = true;
    this.controller.close();
    this.cancelInput();
  }

  private cancelInput(): Promise<void> {
    this.stopped = true;
    this.cancelled ??= this.reader.cancel().catch(() => {});
    return this.cancelled;
  }

  async run(onOpen: () => void, onData: (data: Uint8Array) => void, onClose: () => void): Promise<void> {
    const output = this.output.pipeTo(this.writable);
    const input = (async () => {
      try {
        onOpen();
        while (!this.stopped) {
          const { value, done } = await this.reader.read();
          if (done) break;
          onData(value);
        }
      } finally {
        try { onClose(); } finally { this.end(); }
      }
    })();
    try {
      await Promise.all([input, output]);
    } catch (error) {
      this.cancelInput();
      // Also fail the writable side when input/runtime processing fails.
      try { this.controller.error(error); } catch { /* Already closed. */ }
      await Promise.allSettled([input, output]);
      throw error;
    } finally {
      await this.cancelled;
      this.reader.releaseLock();
    }
  }
}
