#!/bin/sh
set -eu
exec pnpm exec wrangler dev --ip 127.0.0.1 "$@"
