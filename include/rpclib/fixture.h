#pragma once

#ifndef FIXTURE_H_EWLDRJT7
#define FIXTURE_H_EWLDRJT7

#include "benchmark/benchmark.h"

#include "target_code.h"
#include "rpclib/struct_helpers.h"
#include "port_numbers.h"

#include "rpc/client.h"
#include "rpc/server.h"

class rpclib_bench : public benchmark::Fixture {
public:
  void SetUp(benchmark::State&) override {
    // losing a bit of perf. on indirection, but gbenchmark creates all
    // fixtures on startup and destroys them only on exit which in the case of
    // rpclib will throw an exception due to reusing the port. Rather then
    // pulling tricks like randomizing port numbers, let's just accept that this
    // is something to be improved in rpclib.
    server = std::make_unique<rpc::server>(rpclib_port);
    client = std::make_unique<rpc::client>("localhost", rpclib_port);

    server->bind("get_answer", &::get_answer);
    server->bind("get_blob", [this]() { return ::get_blob(blob_size_); });
    server->bind("get_structs", &rpclib_code::get_structs);
    server->async_run(1);
  }

  void TearDown(benchmark::State&) override {
    server.reset();
    client.reset();
  }

  void get_answer(int param) {
    (void)param;
    int a;
    benchmark::DoNotOptimize(a = client->call("get_answer", 23).as<int>());
  }

  void get_blob(int param) {
    blob_size_ = param;
    std::string s;
    benchmark::DoNotOptimize(s = client->call("get_blob").as<std::string>());
    std::size_t size;
    benchmark::DoNotOptimize(size = s.size());
  }

  void get_structs(int param) {
    std::vector<rpclib_code::Student> result;
    benchmark::DoNotOptimize(
        result =
            client->call("get_structs").as<std::vector<rpclib_code::Student>>());
    std::size_t size;
    benchmark::DoNotOptimize(size = result.size());
  }

  int blob_size_;
  std::unique_ptr<rpc::server> server;
  std::unique_ptr<rpc::client> client;
};

#endif /* end of include guard: FIXTURE_H_EWLDRJT7 */
