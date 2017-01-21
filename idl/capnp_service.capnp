
@0xd4857e0f5efbe114;

interface CapnpServiceBenchmark {
    getAnswer @0 (number :Int32) -> (result :Int32);
    getBlob @1 () -> (result :Data);
}
