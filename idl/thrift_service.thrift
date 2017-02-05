namespace cpp thrift_code

struct Date {
  1:i32 year;
  2:byte month;
  3:byte day;
}

struct Address {
  1:string city;
  2:i32 zipcode;
  3:string street;
  4:i16 number;
}

struct School {
  1:string name;
  2:Address address;
  3:Date foundation;
  4:list<string> email_addresses;
}

struct Subject {
  1:i32 id;
  2:string title;
  3:string code;
}

struct Student {
  1:string name;
  2:i32 friends;
  3:Address home_address;
  4:Address birth_place;
  5:Date birth;
  6:list<Subject> favorite_subjects;
  7:list<string> email_addresses;
  8:list<School> schools;
}

service ThriftServiceBenchmark {
  i32 get_answer(1:i32 number);
  binary get_blob();
  list<Student> get_structs();
}

