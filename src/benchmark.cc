#include "benchmark/benchmark.h"

#include "target_code.h"

#include "direct/fixture.h"
#include "rpclib/fixture.h"
#include "capnp/fixture.h"
#include "thrift/fixture.h"
#include "grpc/fixture.h"

#define MAKE_BENCHMARK(FixtureName, Benchmark)                                 \
  BENCHMARK_F(FixtureName, Benchmark)(benchmark::State & st) {                 \
    while (st.KeepRunning()) {                                                 \
      Benchmark();                                                             \
    }                                                                          \
  }

MAKE_BENCHMARK(direct_bench, get_answer)
MAKE_BENCHMARK(rpclib_bench, get_answer)
MAKE_BENCHMARK(capnp_bench, get_answer)
MAKE_BENCHMARK(thrift_bench, get_answer)
MAKE_BENCHMARK(grpc_bench, get_answer)

BENCHMARK_MAIN();
