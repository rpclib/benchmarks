#include "benchmark/benchmark.h"

#define RPCLIB_FIXTURE
//#define MSGPACK_USE_DEFINE_MAP

#include "target_code.h"

#include "capnp/fixture.h"
#include "direct/fixture.h"
#include "grpc/fixture.h"
#include "rpclib/fixture.h"
#include "thrift/fixture.h"

#include <sstream>

int capnp_bench::blob_size_ = 0;

#define MAKE_BENCHMARK(FixtureName, Benchmark)                                 \
  BENCHMARK_DEFINE_F(FixtureName, Benchmark)(benchmark::State & st) {          \
    auto num = st.range(0);                                                    \
    while (st.KeepRunning()) {                                                 \
      Benchmark(num);                                                          \
    }                                                                          \
  }                                                                            \
  BENCHMARK_REGISTER_F(FixtureName, Benchmark)

#define MAKE_BENCHMARK0(FixtureName, Benchmark)                                 \
  BENCHMARK_DEFINE_F(FixtureName, Benchmark)(benchmark::State & st) {          \
    while (st.KeepRunning()) {                                                 \
      Benchmark(0);                                                          \
    }                                                                          \
  }                                                                            \
  BENCHMARK_REGISTER_F(FixtureName, Benchmark)

constexpr std::size_t min_size = 4 << 10;
constexpr std::size_t max_size = 32 << 10 << 10;
constexpr std::size_t multiplier = 4;

//MAKE_BENCHMARK(direct_bench, get_blob)->RangeMultiplier(multiplier)->Range(min_size, max_size);
//MAKE_BENCHMARK(rpclib_bench, get_blob)->RangeMultiplier(multiplier)->Range(min_size, max_size);
//MAKE_BENCHMARK(capnp_bench, get_blob)->RangeMultiplier(multiplier)->Range(min_size, max_size);
//MAKE_BENCHMARK(thrift_bench, get_blob)->RangeMultiplier(multiplier)->Range(min_size, max_size);
//MAKE_BENCHMARK(grpc_bench, get_blob)->RangeMultiplier(multiplier)->Range(min_size, max_size);
MAKE_BENCHMARK0(rpclib_bench, get_structs);
//MAKE_BENCHMARK(rpclib_bench, get_answer)
//MAKE_BENCHMARK(capnp_bench, get_answer)
//MAKE_BENCHMARK(capnp_bench, get_blob);
// MAKE_BENCHMARK(thrift_bench, get_answer)
//MAKE_BENCHMARK(thrift_bench, get_blob);
// MAKE_BENCHMARK(grpc_bench, get_answer)

int main(int argc, char *argv[]) {
  printf("Initalizing blob cache...\n");
  for (std::size_t s = min_size; s < max_size; ++s) {
    get_blob(s);
    s *= multiplier;
  }
  printf("Initalizing struct cache...\n");
  fill_struct_cache();
  benchmark::Initialize(&argc, argv);
  return benchmark::RunSpecifiedBenchmarks();
}

