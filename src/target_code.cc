#include "target_code.h"
#include <thread>
#include <chrono>

int get_answer(int num) {
  std::this_thread::sleep_for(std::chrono::milliseconds(100));
  return 41 + num;
}
