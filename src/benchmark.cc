#include "benchmark/benchmark.h"

#include "target_code.h"

#include "capnp/fixture.h"
#include "direct/fixture.h"
#include "grpc/fixture.h"
#include "rpclib/fixture.h"
#include "thrift/fixture.h"

#include "grpc/struct_helpers.h"
#include "rpclib/struct_helpers.h"
#include "thrift/struct_helpers.h"
#include "capnp/struct_helpers.h"

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

#define MAKE_BENCHMARK0(FixtureName, Benchmark)                                \
  BENCHMARK_DEFINE_F(FixtureName, Benchmark)(benchmark::State & st) {          \
    while (st.KeepRunning()) {                                                 \
      Benchmark(0);                                                            \
    }                                                                          \
  }                                                                            \
  BENCHMARK_REGISTER_F(FixtureName, Benchmark)

constexpr std::size_t min_size = 1 << 10;
constexpr std::size_t max_size = 16 << 10 << 10;
// constexpr std::size_t grpc_max_size = 1 << 10 << 10; // https://github.com/grpc/grpc/issues/9510
constexpr std::size_t multiplier = 2;

MAKE_BENCHMARK(direct_bench, get_blob)->RangeMultiplier(multiplier)->Range(min_size, max_size);
MAKE_BENCHMARK(rpclib_bench, get_blob)->RangeMultiplier(multiplier)->Range(min_size, max_size);
MAKE_BENCHMARK(capnp_bench, get_blob)->RangeMultiplier(multiplier)->Range(min_size, max_size);
MAKE_BENCHMARK(thrift_bench, get_blob)->RangeMultiplier(multiplier)->Range(min_size, max_size);
// MAKE_BENCHMARK(grpc_bench, get_blob)->RangeMultiplier(multiplier)->Range(min_size, grpc_max_size);

MAKE_BENCHMARK0(direct_bench, get_structs);
MAKE_BENCHMARK0(rpclib_bench, get_structs);
MAKE_BENCHMARK0(thrift_bench, get_structs);
MAKE_BENCHMARK0(grpc_bench, get_structs);
MAKE_BENCHMARK0(capnp_bench, get_structs);

MAKE_BENCHMARK0(direct_bench, get_answer);
MAKE_BENCHMARK0(rpclib_bench, get_answer);
MAKE_BENCHMARK0(capnp_bench, get_answer);
MAKE_BENCHMARK0(thrift_bench, get_answer);
MAKE_BENCHMARK0(grpc_bench, get_answer);

int main(int argc, char *argv[]) {
  printf("Initalizing blob cache...\n");
  for (std::size_t s = min_size; s <= max_size; s *= multiplier) {
    get_blob(s);
  }

  printf("Initalizing struct cache...\n");
  rpclib_code::fill_struct_cache();
  thrift_code::fill_struct_cache();
  grpc_code::fill_struct_cache();
  capnp_code::fill_struct_cache();

  printf("Starting benchmarks...\n");
  benchmark::Initialize(&argc, argv);
  return benchmark::RunSpecifiedBenchmarks();
}

