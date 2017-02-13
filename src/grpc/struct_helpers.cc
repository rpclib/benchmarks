#include "grpc/struct_helpers.h"
#include "target_code.h"
#include <stdlib.h>

namespace grpc_code {

static Date random_Date() {
  Date date;
  date.set_year(rand() % 30 + 1900);
  date.set_month(static_cast<char>(rand() % 12 + 1));
  date.set_day(static_cast<char>(rand() % 30 + 1));
  return date;
}

static Address random_Address() {
  Address addr;
  addr.set_city(rand_str(12));
  addr.set_zipcode(rand() % 3000 + 5000);
  addr.set_street(rand_str(16));
  addr.set_number(static_cast<short>(rand() % 125 + 1));
  return addr;
}

static School random_School() {
  School result;
  result.set_name(rand_str(36));
  result.mutable_address()->CopyFrom(random_Address());
  result.mutable_foundation()->CopyFrom(random_Date());
  for (size_t i = 0; i < item_count; ++i) {
    result.add_email_addresses(rand_str(37));
  }
  return result;
}

static Subject random_Subject() {
  Subject s;
  s.set_id(rand() % 28345);
  s.set_title(rand_str(22));
  s.set_code(rand_str(16));
  return s;
}

static Student random_Student() {
  Student s;
  s.set_name(rand_str(43));
  s.set_friends(rand() % 600);
  s.mutable_home_address()->CopyFrom(random_Address());
  s.mutable_birth_place()->CopyFrom(random_Address());
  s.mutable_birth()->CopyFrom(random_Date());

  for (size_t i = 0; i < item_count; ++i) {
    auto subject = s.add_favorite_subjects();
    subject->CopyFrom(random_Subject());
    s.add_email_addresses(rand_str(37));
    auto school = s.add_schools();
    school->CopyFrom(random_School());
  }
  return s;
}

static StudentDataResponse struct_cache;

void fill_struct_cache() {
  for (std::size_t i = 0; i < item_count; ++i) {
    auto new_s = struct_cache.add_students();
    new_s->CopyFrom(random_Student());
  }
}

StudentDataResponse& get_structs() { return struct_cache; }



} /* grpc_code */
