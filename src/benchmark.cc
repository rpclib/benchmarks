#include "target_code.h"

#include "rpclib/fixture.h"
#include "capnp/fixture.h"
#include "thrift/fixture.h"

#define MAKE_BENCHMARK(FixtureName, Benchmark, Runs, Iterations)                          \
  BENCHMARK_F(FixtureName, Benchmark, Runs, Iterations) { Benchmark(); }

MAKE_BENCHMARK(rpclib_bench, get_answer, 100, 5000)
MAKE_BENCHMARK(capnp_bench, get_answer, 100, 5000)
MAKE_BENCHMARK(thrift_bench, get_answer, 100, 5000)
