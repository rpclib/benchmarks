#pragma once

#ifndef FIXTURE_H_RFGFCJ3X
#define FIXTURE_H_RFGFCJ3X

#include "benchmark/benchmark.h"

#include "target_code.h"

// direct function call
class direct_bench : public benchmark::Fixture {
public:
    void get_answer() {
        int a;
        benchmark::DoNotOptimize(a = ::get_answer(23));
    }
};

#endif /* end of include guard: FIXTURE_H_RFGFCJ3X */
