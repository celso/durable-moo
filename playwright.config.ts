import { defineConfig } from "@playwright/test";

export default defineConfig({
  testDir: "./tests/browser",
  fullyParallel: false,
  workers: 1,
  timeout: 30000,
  use: {
    baseURL: "http://127.0.0.1:8797",
    viewport: { width: 1280, height: 900 },
    launchOptions: process.env.BROWSER_EXECUTABLE ? { executablePath: process.env.BROWSER_EXECUTABLE } : {},
  },
  webServer: {
    command: "node scripts/browser-test-server.mjs",
    url: "http://127.0.0.1:8797/healthz",
    reuseExistingServer: false,
    timeout: 60000,
  },
});
