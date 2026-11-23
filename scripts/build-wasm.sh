#!/bin/sh
set -eu

image="emscripten/emsdk:4.0.15"
root_dir=$(CDPATH= cd -- "$(dirname -- "$0")/.." && pwd)

docker run --rm \
  --platform linux/amd64 \
  --volume "$root_dir:/workspace" \
  --volume "$root_dir/scripts/package-commonjs.json:/workspace/package.json:ro" \
  --workdir /workspace/lambdamoo \
  "$image" \
  sh -c 'apt-get update >/dev/null && apt-get install -y autoconf bison gperf >/dev/null && autoconf && ./configure --disable-net --disable-unicode --with-relib=ylo --disable-xml --disable-waifs --enable-sz=i32,bq32 --enable-svf-diff=! --enable-def-UNFORKED_CHECKPOINTS CC=emcc && make wasm'
