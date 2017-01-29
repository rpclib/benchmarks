#! /bin/sh

set -e

SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
BENCHMARKS_ROOT="$SCRIPT_DIR/.."

pushd $SCRIPT_DIR

# 1. grpc
echo "Generating grpc code"
protoc --grpc_out=. -I$BENCHMARKS_ROOT/idl --plugin=protoc-gen-grpc=`which grpc_cpp_plugin` $BENCHMARKS_ROOT/idl/grpc_service.proto
echo "Generating grpc code #2"
protoc --cpp_out=. -I$BENCHMARKS_ROOT/idl --plugin=protoc-gen-grpc=`which grpc_cpp_plugin` $BENCHMARKS_ROOT/idl/grpc_service.proto
mv ./*.h $BENCHMARKS_ROOT/include/grpc
mv ./*.cc $BENCHMARKS_ROOT/src/grpc

# 2. thrift
# TODO

# 3. cap'n'proto
# TODO

popd
