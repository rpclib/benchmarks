#pragma once

#ifndef FIXTURE_H_NNOJDJZG
#define FIXTURE_H_NNOJDJZG

#include "benchmark/benchmark.h"

#include <capnp/ez-rpc.h>

#include "capnp/capnp_service.capnp.h"
#include "capnp/struct_helpers.h"
#include "target_code.h"
#include "port_numbers.h"

class capnp_bench : public benchmark::Fixture {
private:
  static int blob_size_;
  class capnp_server : public capnp_code::CapnpServiceBenchmark::Server {
  public:
    kj::Promise<void> getAnswer(GetAnswerContext context) override {
      auto num = context.getParams().getNumber();
      context.getResults().setResult(::get_answer(num));
      return kj::READY_NOW;
    }

    kj::Promise<void> getBlob(GetBlobContext context) override {
      auto& blob = ::get_blob(blob_size_);
      kj::ArrayPtr<unsigned char> arr((unsigned char *)blob.data(),
                                      blob.size());
      context.getResults().setResult(capnp::Data::Reader(arr));
      return kj::READY_NOW;
    }

    kj::Promise<void> getStructs(GetStructsContext context) override {
      context.getResults().setResult(capnp_code::get_structs());
      return kj::READY_NOW;
    }
  };

public:
  void SetUp(benchmark::State &) override {
    using std::make_unique;
    server_addr_ = "127.0.0.1:" + std::to_string(capnp_port);
    server = make_unique<capnp::EzRpcServer>(kj::heap<capnp_server>(),
                                             server_addr_);
    reader_options = {256 * 1024 * 1024, 64};
    client_thing =
        make_unique<capnp::EzRpcClient>(server_addr_, 8080, reader_options);
    client = make_unique<capnp_code::CapnpServiceBenchmark::Client>(
        client_thing->getMain<capnp_code::CapnpServiceBenchmark>());
    auto &wait_scope = server->getWaitScope();
    server->getPort().wait(wait_scope);
  }

  void TearDown(benchmark::State &) override {
    server.reset();
    client.reset();
    client_thing.reset();
  }

  void get_answer(int param) {
    (void)param;
    auto request = client->getAnswerRequest();
    request.setNumber(23);
    auto resultPromise = request.send();
    int a;
    benchmark::DoNotOptimize(
        a = resultPromise.wait(client_thing->getWaitScope()).getResult());
  }

  void get_blob(int param) {
    blob_size_ = param;
    auto request = client->getBlobRequest();
    auto resultPromise = request.send();
    auto result = resultPromise.wait(client_thing->getWaitScope());
    benchmark::DoNotOptimize(result.getResult().size());
  }

  void get_structs(int param) {
    (void)param;
    auto request = client->getStructsRequest();
    auto resultPromise = request.send();
    auto result = resultPromise.wait(client_thing->getWaitScope())
                      .getResult()
                      .getStudents();
    std::size_t count;
    benchmark::DoNotOptimize(count = result.size());
  }

  ~capnp_bench() noexcept {}

  std::unique_ptr<capnp::EzRpcServer> server;
  capnp::ReaderOptions reader_options;
  std::unique_ptr<capnp::EzRpcClient> client_thing;
  std::unique_ptr<capnp_code::CapnpServiceBenchmark::Client> client;
  std::string server_addr_;
};

#endif /* end of include guard: FIXTURE_H_NNOJDJZG */
