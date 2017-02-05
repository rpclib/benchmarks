#include "rpclib/struct_helpers.h"

namespace rpclib_code {

static std::vector<Student> struct_cache;

void fill_struct_cache() {
  for (std::size_t i = 0; i < item_count; ++i) {
    struct_cache.push_back(Student::random());
  }
}

std::vector<Student> &get_structs() { return struct_cache; }

} /* rpclib_bench */
