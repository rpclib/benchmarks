#! /bin/sh

# This script assumes that the executable is stored in ./build/bin/rpclib_benchmark,
# relative to the script itself.

SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

$SCRIPT_DIR/build/bin/rpclib_benchmark --benchmark_min_time=3.0 --benchmark_repetitions=5 --benchmark_out=benchmark.json --benchmark_out_format=json
