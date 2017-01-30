#include "benchmark/benchmark.h"

#include "target_code.h"
#include "grpc/fixture.h"

#define MAKE_BENCHMARK(FixtureName, Benchmark)                                 \
  BENCHMARK_DEFINE_F(FixtureName, Benchmark)(benchmark::State & st) {          \
    auto num = st.range(0);                                                    \
    while (st.KeepRunning()) {                                                 \
      Benchmark(num);                                                          \
    }                                                                          \
  }                                                                            \
  BENCHMARK_REGISTER_F(FixtureName, Benchmark)

constexpr std::size_t min_size = 4 << 10;
constexpr std::size_t max_size = 32 << 10 << 10;
constexpr std::size_t multiplier = 4;

MAKE_BENCHMARK(grpc_bench, get_blob)->RangeMultiplier(multiplier)->Range(min_size, max_size);

int main(int argc, char *argv[]) {
  printf("Initalizing blob cache...\n");
  for (std::size_t s = min_size; s < max_size; ++s) {
    get_blob(s);
    s *= multiplier;
  }
  benchmark::Initialize(&argc, argv);
  return benchmark::RunSpecifiedBenchmarks();
}

