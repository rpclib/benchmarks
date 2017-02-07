#include "capnp/struct_helpers.h"
#include "target_code.h"
#include <capnp/message.h>
#include <stdlib.h>

namespace capnp_code {

capnp::MallocMessageBuilder msg;
StudentDataResponse::Builder struct_cache = msg.initRoot<StudentDataResponse>();

void fill_struct_cache() {
  auto random_Date = []() {
    Date::Builder date = msg.initRoot<Date>();
    date.setYear(rand() % 30 + 1900);
    date.setMonth(static_cast<char>(rand() % 12 + 1));
    date.setDay(static_cast<char>(rand() % 30 + 1));
    return date;
  };

  auto random_Address =
      [&]() {
        Address::Builder addr = msg.initRoot<Address>();
        addr.setCity(rand_str(12));
        addr.setZipcode(rand() % 3000 + 5000);
        addr.setStreet(rand_str(16));
        addr.setNumber(static_cast<short>(rand() % 125 + 1));
        return addr;
      };

  auto random_School =
      [&]() {
        School::Builder result = msg.initRoot<School>();
        result.setName(rand_str(36));
        result.setAddress(random_Address());
        result.setFoundation(random_Date());
        result.initEmailAddresses(item_count);
        for (size_t i = 0; i < item_count; ++i) {
          result.getEmailAddresses().set(i, rand_str(37));
        }
        return result;
      };

  auto random_Subject = []() {
    Subject::Builder s = msg.initRoot<Subject>();
    s.setId(rand() % 28345);
    s.setTitle(rand_str(22));
    s.setCode(rand_str(16));
    return s;
  };

  auto random_Student = [&]() {
    Student::Builder s = msg.initRoot<Student>();
    s.setName(rand_str(43));
    s.setFriends(rand() % 600);
    s.setHomeAddress(random_Address());
    s.setBirthPlace(random_Address());
    s.setBirth(random_Date());

    s.initSchools(item_count);
    s.initFavoriteSubjects(item_count);
    s.initEmailAddresses(item_count);
    for (size_t i = 0; i < item_count; ++i) {
      s.getFavoriteSubjects().setWithCaveats(i, random_Subject());
      s.getEmailAddresses().set(i, rand_str(37));
    }
    return s;
  };

  auto builder = struct_cache.initStudents(item_count);
  for (std::size_t i = 0; i < item_count; ++i) {
      builder.setWithCaveats(i, random_Student());
  }
}

StudentDataResponse::Builder& get_structs() { return struct_cache; }

}
