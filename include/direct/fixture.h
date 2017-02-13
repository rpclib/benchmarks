#pragma once

#ifndef FIXTURE_H_RFGFCJ3X
#define FIXTURE_H_RFGFCJ3X

#include "benchmark/benchmark.h"

#include "target_code.h"
#include "rpclib/struct_helpers.h"

// direct function call
class direct_bench : public benchmark::Fixture {
public:
  void get_answer(int param) {
    (void)param;
    int a;
    benchmark::DoNotOptimize(a = ::get_answer(23));
  }

  void get_blob(int param) {
    std::string s;
    benchmark::DoNotOptimize(s = ::get_blob(param));
    std::size_t size;
    benchmark::DoNotOptimize(size = s.size());
  }

  void get_structs(int param) {
    std::vector<rpclib_code::Student> result;
    benchmark::DoNotOptimize(result = rpclib_code::get_structs());
  }
};

#endif /* end of include guard: FIXTURE_H_RFGFCJ3X */
