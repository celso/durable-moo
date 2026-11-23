/** Transport-independent player output; mutations persist before calling write. */
export interface SessionSocket {
  readonly closing: boolean;
  write(data: Uint8Array): void;
  end(message?: string): void;
}
