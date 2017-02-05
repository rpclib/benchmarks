
@0xd4857e0f5efbe114;

using Cxx = import "/capnp/c++.capnp";
$Cxx.namespace("capnp_code");

struct Date {
  year @0 :Int32;
  month @1 :Int8;
  day @2 :Int8;
}

struct Address {
  city @0 :Text;
  zipcode @1 :Int32;
  street @2 :Text;
  number @3 :Int16;
}

struct School {
  name @0 :Text;
  address @1 :Address;
  foundation @2 :Date;
  emailAddresses @3 :List(Text);
}

struct Subject {
  id @0 :Int32;
  title @1 :Text;
  code @2 :Text;
}

struct Student {
  name @0 :Text;
  friends @1 :Int32;
  homeAddress @2 :Address;
  birthPlace @3 :Address;
  birth @4 :Date;
  favoriteSubjects @5 :List(Subject);
  emailAddresses @6 :List(Text);
  schools @7 :List(School);
}

struct StudentDataResponse {
  students @0 :List(Student);
}

interface CapnpServiceBenchmark {
    getAnswer @0 (number :Int32) -> (result :Int32);
    getBlob @1 () -> (result :Data);
    getStructs @2 () -> (result :StudentDataResponse);
}
