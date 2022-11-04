#!/bin/bash
NODE=${NODE:=$(which node)}
exec $NODE --experimental-wasm-reftypes noderun.js "$@"
