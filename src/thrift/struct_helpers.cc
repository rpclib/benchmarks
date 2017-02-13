#include "thrift/struct_helpers.h"
#include "target_code.h"
#include <stdlib.h>

namespace thrift_code {

static Date random_Date() {
  Date date;
  date.year = rand() % 30 + 1900;
  date.month = static_cast<char>(rand() % 12 + 1);
  date.day = static_cast<char>(rand() % 30 + 1);
  return date;
}

static Address random_Address() {
  Address addr;
  addr.city = rand_str(12);
  addr.zipcode = rand() % 3000 + 5000;
  addr.street = rand_str(16);
  addr.number = static_cast<short>(rand() % 125 + 1);
  return addr;
}

static School random_School() {
  School result;
  result.name = rand_str(36);
  result.address = random_Address();
  result.foundation = random_Date();
  for (size_t i = 0; i < item_count; ++i) {
    result.email_addresses.push_back(rand_str(37));
  }
  return result;
}

static Subject random_Subject() {
  Subject s;
  s.id = rand() % 28345;
  s.title = rand_str(22);
  s.code = rand_str(16);
  return s;
}

static Student random_Student() {
  Student s;
  s.name = rand_str(43);
  s.friends = rand() % 600;
  s.home_address = random_Address();
  s.birth_place = random_Address();
  s.birth = random_Date();

  for (size_t i = 0; i < item_count; ++i) {
    s.favorite_subjects.push_back(random_Subject());
    s.email_addresses.push_back(rand_str(37));
    s.schools.push_back(random_School());
  }
  return s;
}

static std::vector<Student> struct_cache;

void fill_struct_cache() {
  for (std::size_t i = 0; i < item_count; ++i) {
    struct_cache.push_back(random_Student());
  }
}

std::vector<Student> &get_structs() { return struct_cache; }

}
