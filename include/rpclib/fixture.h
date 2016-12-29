#pragma once

#ifndef FIXTURE_H_EWLDRJT7
#define FIXTURE_H_EWLDRJT7

#include "benchmark/benchmark.h"

#include "target_code.h"

#include "rpc/server.h"
#include "rpc/client.h"

class rpclib_bench : public benchmark::Fixture {
public:
    rpclib_bench()
        : server(8080), client("127.0.0.1", 8080) {
      server.bind("get_answer", &::get_answer);
      server.async_run(1);
    }

    void get_answer() {
        int a;
        benchmark::DoNotOptimize(a = client.call("get_answer", 23).as<int>());
    }

    rpc::server server;
    rpc::client client;
};

#endif /* end of include guard: FIXTURE_H_EWLDRJT7 */
