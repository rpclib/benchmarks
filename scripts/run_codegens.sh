#! /bin/sh

set -e

SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
BENCHMARKS_ROOT="$SCRIPT_DIR/.."

pushd $SCRIPT_DIR

# 1. grpc
echo "> Generating grpc code"
protoc --grpc_out=. -I$BENCHMARKS_ROOT/idl --plugin=protoc-gen-grpc=`which grpc_cpp_plugin` $BENCHMARKS_ROOT/idl/grpc_service.proto
echo "> Generating grpc code #2"
protoc --cpp_out=. -I$BENCHMARKS_ROOT/idl --plugin=protoc-gen-grpc=`which grpc_cpp_plugin` $BENCHMARKS_ROOT/idl/grpc_service.proto
mv $SCRIPT_DIR/*.h $BENCHMARKS_ROOT/include/grpc
mv $SCRIPT_DIR/*.cc $BENCHMARKS_ROOT/src/grpc

# 2. thrift
echo "> Generating thrift code"
thrift -r --gen cpp $BENCHMARKS_ROOT/idl/thrift_service.thrift
mv $SCRIPT_DIR/gen-cpp/*.h $BENCHMARKS_ROOT/include/thrift
mv $SCRIPT_DIR/gen-cpp/*.cpp $BENCHMARKS_ROOT/src/thrift
rm -r $SCRIPT_DIR/gen-cpp

# 3. cap'n'proto
# TODO

popd
