#include "benchmark/benchmark.h"

#include "target_code.h"

#include "capnp/fixture.h"
#include "direct/fixture.h"
#include "grpc/fixture.h"
#include "rpclib/fixture.h"
#include "thrift/fixture.h"

//#define BACKWARD_HAS_DW 1
#define BACKWARD_HAS_BFD 1
#include "backward/backward.hpp"

int capnp_bench::blob_size_ = 0;

#define MAKE_BENCHMARK(FixtureName, Benchmark)                                 \
  BENCHMARK_DEFINE_F(FixtureName, Benchmark)(benchmark::State & st) {          \
    auto num = st.range(0);                                                    \
    while (st.KeepRunning()) {                                                 \
      Benchmark(num);                                                          \
    }                                                                          \
  }                                                                            \
  BENCHMARK_REGISTER_F(FixtureName, Benchmark)

namespace backward {

backward::SignalHandling sh;

} // namespace backward
// MAKE_BENCHMARK(direct_bench, get_answer)

constexpr std::size_t min_size = 4 << 10;
constexpr std::size_t max_size = 32 << 10 << 10;
constexpr std::size_t multiplier = 4;

MAKE_BENCHMARK(direct_bench, get_blob)->RangeMultiplier(multiplier)->Range(min_size, max_size);
MAKE_BENCHMARK(rpclib_bench, get_blob)->RangeMultiplier(multiplier)->Range(min_size, max_size);
MAKE_BENCHMARK(capnp_bench, get_blob)->RangeMultiplier(multiplier)->Range(min_size, max_size);
MAKE_BENCHMARK(thrift_bench, get_blob)->RangeMultiplier(multiplier)->Range(min_size, max_size);
MAKE_BENCHMARK(grpc_bench, get_blob)->RangeMultiplier(multiplier)->Range(min_size, max_size);
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
  benchmark::Initialize(&argc, argv);
  return benchmark::RunSpecifiedBenchmarks();
}

