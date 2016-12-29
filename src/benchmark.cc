#include "benchmark/benchmark.h"

#include "target_code.h"

#include "rpclib/fixture.h"
#include "capnp/fixture.h"
#include "thrift/fixture.h"
#include "xmlrpc-c/fixture.h"

#include <stdio.h>

#define MAKE_BENCHMARK(FixtureName, Benchmark, Runs, Iterations)                          \
  BENCHMARK_F(FixtureName, Benchmark, Runs, Iterations) { Benchmark(); }

//MAKE_BENCHMARK(rpclib_bench, get_answer, 100, 500)
//MAKE_BENCHMARK(capnp_bench, get_answer, 100, 500)
//MAKE_BENCHMARK(thrift_bench, get_answer, 100, 500)
//MAKE_BENCHMARK(xmlrpc_c_bench, get_answer, 10, 500)

//BENCHMARK_F(rpclib_bench, get_answer)(benchmark::State &st) {
  //while (st.KeepRunning()) {
    //get_answer();
  //}
//}

static void rpclib_get_answer(benchmark::State& state) {
  printf("start\n");
      rpclib_bench fixture;
  while (state.KeepRunning())
  {
      fixture.get_answer();
  }
  printf("finished\n");
}
BENCHMARK(rpclib_get_answer);

BENCHMARK_MAIN();
