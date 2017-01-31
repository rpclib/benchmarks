#pragma once

#ifndef FIXTURE_H_EWLDRJT7
#define FIXTURE_H_EWLDRJT7

#include "benchmark/benchmark.h"

#include "target_code.h"

#include "rpc/client.h"
#include "rpc/server.h"

class rpclib_bench : public benchmark::Fixture {
public:
  rpclib_bench() : server(8086), client("127.0.0.1", 8086) {
    server.bind("get_answer", &::get_answer);
    server.bind("get_blob", [this]() { return ::get_blob(blob_size_); });
    server.bind("get_structs", &::get_structs);
    server.async_run(1);
  }

  void get_answer(int param) {
    (void)param;
    int a;
    benchmark::DoNotOptimize(a = client.call("get_answer", 23).as<int>());
  }

  void get_blob(int param) {
    blob_size_ = param;
    std::string s;
    benchmark::DoNotOptimize(s = client.call("get_blob").as<std::string>());
    std::size_t size;
    benchmark::DoNotOptimize(size = s.size());
  }

  void get_structs(int param) {
    std::vector<Student> result;
    benchmark::DoNotOptimize(
        result = client.call("get_structs").as<std::vector<Student>>());
  }

  int blob_size_;
  rpc::server server;
  rpc::client client;
};

#endif /* end of include guard: FIXTURE_H_EWLDRJT7 */
