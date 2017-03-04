# rpclib (micro)benchmarks

This is a set of benchmarks that compares the performance of various RPC libraries/frameworks in
specific situations. The benchmark suite is created as part of the [rpclib](http://rpclib.net)
project.

## Libraries

The following libraries are or will be benchmarked:

  - [x] [rpclib](http://rpclib.net)
  - [x] [cap'n'proto rpc](https://capnproto.org/cxxrpc.html)
  - [x] [Apache Thrift](https://thrift.apache.org/)
  - [x] [grpc](https://grpc.io)
  - [x] +1: Direct function calls (for comparison)

## Results

TBD

## Compiling and running

TBD

## FAQ

### What kind of benchmarks are performed?

These are the benchmarks that are implemented or will be implemented for each
library from the above list.

  - [x] `get_answer`: Perform a function call that returns a number and deserialize
    the result (so that it's available for the user code as an `int`)
  - [x] `get_blob`: Perform a function call that returns a large blob and deserialize it into
    a byte buffer. This is performed in increasing sizes.
  - [x] `get_struct`: Perform a function call that returns a nested struct with lots of
    fields and lots of data in it and intentionally bad alignment.

Each library is set up to create local client and server that communicate through a TCP socket.

### How are the benchmarks ran?

This benchmark suite uses [Google Benchmark](https://github.com/google/benchmark) to manage the
benchmarking. Each library has a fixture that is set up and torn down in each benchmark run once
(similarly to unit tests). The setup and teardown performance is not measured. Each microbenchmark is performed in a number of
iterations (determined by Google Benchmark). All runs are performed five times. The results are the means, medians and standard deviations of the
remaining three measured times.

### What is `rpclib`?

`rpclib` is a modern msgpack-rpc implementation for C++. It provides a very clean interface
inspired by Boost.Python. See [rpclib.net](http://rpclib.net) for more information.

### I think your implementation for library XYZ is suboptimal. Will you change it?

Probably yes, please send a PR. I'm not an expert in the other libraries, so it's entirely possible
that I used them wrong.

### Why don't you measure against library XYZ?

One or more of the following reasons:

  * I did not know about the library
  * There was no conan package for it and I didn't have time to make one
  * I didn't have time to learn the library
  * The library wasn't to my knowledge widespread enough to be interesting for this comparison.

However, by all means, please let me know if there is one that is worth looking at. Bonus points if
you make a conan package and/or pull request with benchmark code for it.

