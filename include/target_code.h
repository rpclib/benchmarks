#pragma once

#ifndef TARGET_CODE_H_MNJDLMEV
#define TARGET_CODE_H_MNJDLMEV

#include <stdlib.h>
#include <string>
#include <vector>

#include <rpc/server.h>


int get_answer(int num);
std::string get_blob(int size);

std::string rand_str(std::size_t length);

static constexpr std::size_t item_count = 34;

struct Date {
  int year;
  char month;
  char day;
  static Date random() {
    return {rand() % 30 + 1900, static_cast<char>(rand() % 12 + 1),
            static_cast<char>(rand() % 30 + 1)};
  }
#ifdef RPCLIB_FIXTURE
  MSGPACK_DEFINE(year, month, day);
#endif
};

struct Address {
  std::string city;
  int zipcode;
  std::string street;
  short number;
  static Address random() {
    return {rand_str(12), rand() % 3000 + 5000, rand_str(16),
            static_cast<short>(rand() % 125 + 1)};
  }
#ifdef RPCLIB_FIXTURE
  MSGPACK_DEFINE(city, zipcode, street, number);
#endif
};

struct School {
  std::string name;
  Address address;
  Date foundation;
  std::vector<std::string> email_addresses;
  static School random() {
    School result{rand_str(36), Address::random(), Date::random(), {}};
    for (size_t i = 0; i < item_count; ++i) {
      result.email_addresses.push_back(rand_str(37));
    }
    return result;
  }
#ifdef RPCLIB_FIXTURE
  MSGPACK_DEFINE(name, address, foundation, email_addresses);
#endif
};

struct Subject {
  int id;
  std::string title;
  std::string code;
  static Subject random() {
    return {rand() % 28345, rand_str(22), rand_str(16)};
  }
#ifdef RPCLIB_FIXTURE
  MSGPACK_DEFINE(id, title, code);
#endif
};

struct Student {
  std::string name;
  int friends;
  Address home_address;
  Address birth_place;
  Date birth;
  std::vector<Subject> favorite_subjects;
  std::vector<std::string> email_addresses;
  std::vector<School> schools;
  static Student random() {
    Student result{rand_str(43),
                   rand() % 600,
                   Address::random(),
                   Address::random(),
                   Date::random(),
                   {},
                   {},
                   {}};
    for (size_t i = 0; i < item_count; ++i) {
      result.favorite_subjects.push_back(Subject::random());
      result.email_addresses.push_back(rand_str(37));
      result.schools.push_back(School::random());
    }
    return result;
  }
#ifdef RPCLIB_FIXTURE
  MSGPACK_DEFINE(name, friends, home_address, birth_place, birth,
                 favorite_subjects, email_addresses, schools);
#endif
};

std::vector<Student>& get_structs();
void fill_struct_cache();

#endif /* end of include guard: TARGET_CODE_H_MNJDLMEV */
