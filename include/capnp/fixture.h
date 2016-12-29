#pragma once

#ifndef FIXTURE_H_NNOJDJZG
#define FIXTURE_H_NNOJDJZG

#include "benchmark/benchmark.h"

#include "capnp/ez-rpc.h"

#include "target_code.h"

#include "capnp/capnp_service.capnp.h"

class capnp_server : public CapnpServiceBenchmark::Server {
public:
  kj::Promise<void> getAnswer(GetAnswerContext context) override {
    auto num = context.getParams().getNumber();
    context.getResults().setResult(::get_answer(num));
    return kj::READY_NOW;
  }
};

class capnp_bench : public benchmark::Fixture {
public:
  capnp_bench()
      : server(kj::heap<capnp_server>(), "127.0.0.1:8081"),
        client_thing("127.0.0.1:8081"),
        client(client_thing.getMain<CapnpServiceBenchmark>()) {
    auto &wait_scope = server.getWaitScope();
    server.getPort().wait(wait_scope);
  }

  void get_answer() {
      auto request = client.getAnswerRequest();
      request.setNumber(23);
      auto resultPromise = request.send();
      int a = resultPromise.wait(client_thing.getWaitScope()).getResult();
      (void)a;
  }

  ~capnp_bench() noexcept {}

  capnp::EzRpcServer server;
  capnp::EzRpcClient client_thing;
  CapnpServiceBenchmark::Client client;
};


#endif /* end of include guard: FIXTURE_H_NNOJDJZG */
