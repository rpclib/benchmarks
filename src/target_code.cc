#include "target_code.h"
#include <chrono>
#include <map>
#include <stdlib.h>
#include <thread>

int get_answer(int num) {
  std::this_thread::sleep_for(std::chrono::milliseconds(20));
  return 41 + num;
}

static std::map<int, std::string> blob_cache;

std::string get_blob(int size) {
  if (blob_cache.find(size) != end(blob_cache)) {
    return blob_cache[size];
  }

  std::string s;
  s.resize(size);
  for (auto &c : s) {
    c = static_cast<unsigned char>(rand() % 256);
  }

  blob_cache[size] = s;
  return s;
}
