# rpclib benchmarks

This is a set of benchmarks that compares the performance of various RPC libraries/frameworks in
specific situations.

## Libraries

This is a WIP. The following libraries are or will be benchmarked:

  - [x] [rpclib](http://rpclib.net)
  - [x] [cap'n'proto rpc](https://capnproto.org/cxxrpc.html)
  - [x] [Apache Thrift](https://thrift.apache.org/)
  - [x] [grpc](https://grpc.io)
  - [x] Direct function calls (for comparison)

## Results

TBD

## Compiling and running

TBD

## FAQ

### What kind of benchmarks are performed?

This is a WIP. These are the benchmarks that are implemented or will be implemented for each
library from the above list.

  - [x] `get_answer`: Perform a function call that returns a number and deserialize
    the result (so that it's available for the user code as an `int`)
  - [ ] `get_blob`: Perform a function call that returns a large blob and deserialize it into
    a byte buffer.
  - [ ] `get_big_struct`: Perform a function call that returns a nested struct with lots of
    fields and lots of data in it.

### What is `rpclib`?

`rpclib` is a modern msgpack-rpc implementation for library. It provides a very clean interface
inspired by Boost.Python. See [rpclib.net](http://rpclib.net) for more information.

### I think your implementation for library XXX is suboptimal. Will you change it?

Probably yes, please send a PR. I'm not an expert in the other libraries, so it's entirely possible
that I used them wrong.

### Why don't you measure against XYZ library?

One of the following reasons:

  * I did not know about the library
  * There was no conan package for it and I didn't have time to make one
  * I didn't have time to learn the library

So by all means, please let me know if there is library that is worth looking at. Bonus points if
you make a conan package and/or pull request with benchmark code for it.



