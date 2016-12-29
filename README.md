# rpclib benchmarks

This is a set of benchmarks that compares the performance of various RPC libraries/frameworks in
specific situations.

## Libraries

This is a WIP. The following libraries are or will be benchmarked:

  - [x] [rpclib](http://rpclib.net)
  - [x] [cap'n'proto rpc](https://capnproto.org/cxxrpc.html)
  - [x] [xmlrpc-c](http://xmlrpc-c.sourceforge.net/)
  - [x] [Apache Thrift](https://thrift.apache.org/)
  - [ ] [json-rpc-cpp](https://github.com/cinemast/libjson-rpc-cpp)
  - [ ] [grpc](https://grpc.io)

## Results

TBD

## Compiling and running

TBD

## FAQ

### What is `rpclib`?

`rpclib` is a modern msgpack-rpc implementation for library. It provides a very clean interface
inspired by Boost.Python. See [rpclib.net](http://rpclib.net) for more information.

### I think your implementation for library XXX is suboptimal. Will you change it?

Probably yes, please send a PR. I'm not an expert in the other libraries, so it's entirely possible
that I used them wrong. If your PR is about an optimization that not all libraries can do (e.g.
caching request objects), then create a separate benchmark for it.

### Why don't you measure against XXX library?

One of the following reasons:

  * I did not know about the library
  * There was no conan package for it and I didn't have time to make one
  * I didn't have time to learn the library

So by all means, please let me know if there is library that is worth looking at. Bonus points if
you make a conan package for it.

