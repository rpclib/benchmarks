#pragma once

#ifndef FIXTURE_H_ALZERDCI
#define FIXTURE_H_ALZERDCI

#include <atomic>
#include <chrono>
#include <thread>

#include "benchmark/benchmark.h"

#include "ThriftServiceBenchmark.h"
#include "thrift/protocol/TBinaryProtocol.h"
#include "thrift/server/TSimpleServer.h"
#include "thrift/transport/TBufferTransports.h"
#include "thrift/transport/TServerSocket.h"
#include "thrift/transport/TSocket.h"
#include "thrift/transport/TTransportUtils.h"

#include "target_code.h"
#include "thrift/struct_helpers.h"

static constexpr uint16_t thrift_port = 8083;

class thrift_server : virtual public thrift_code::ThriftServiceBenchmarkIf {
public:
  int32_t get_answer(const int32_t number) override {
    return ::get_answer(number);
  }

  void get_blob(std::string &_return) override {
    _return = ::get_blob(blob_size);
  }

  void get_structs(std::vector<thrift_code::Student> &_return) override {
    _return = thrift_code::get_structs();
  }

  int blob_size;
};

class thrift_bench : public benchmark::Fixture {
public:
  thrift_bench()
      : handler(new thrift_server),
        processor(new thrift_code::ThriftServiceBenchmarkProcessor(handler)),
        serverTransport(
            new apache::thrift::transport::TServerSocket(thrift_port)),
        transportFactory(
            new apache::thrift::transport::TBufferedTransportFactory()),
        protocolFactory(new apache::thrift::protocol::TBinaryProtocolFactory()),
        clientSocket(
            new apache::thrift::transport::TSocket("127.0.0.1", thrift_port)),
        clientTransport(
            new apache::thrift::transport::TBufferedTransport(clientSocket)),
        clientProtocol(
            new apache::thrift::protocol::TBinaryProtocol(clientTransport)),
        client(clientProtocol),
        server(processor, serverTransport, transportFactory, protocolFactory) {
    std::thread serve_thread([this]() {
      server_running = true;
      server.serve();
      server_running = false;
    });
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    clientTransport->open();
    serve_thread.detach();
  }

  ~thrift_bench() override {
    clientTransport->close();
    server.stop();
    while (server_running)
      ;
  }

  void get_answer(int param) {
    (void)param;
    int a;
    benchmark::DoNotOptimize(a = client.get_answer(23));
  }

  void get_blob(int param) {
    handler->blob_size = param;
    std::string s;
    client.get_blob(s);
  }

  void get_structs(int param) {
    (void)param;
    std::vector<thrift_code::Student> students;
    client.get_structs(students);
  }

  boost::shared_ptr<thrift_server> handler;
  boost::shared_ptr<apache::thrift::TProcessor> processor;
  boost::shared_ptr<apache::thrift::server::TServerTransport> serverTransport;
  boost::shared_ptr<apache::thrift::server::TTransportFactory> transportFactory;
  boost::shared_ptr<apache::thrift::protocol::TProtocolFactory> protocolFactory;
  boost::shared_ptr<apache::thrift::protocol::TTransport> clientSocket;
  boost::shared_ptr<apache::thrift::protocol::TTransport> clientTransport;
  boost::shared_ptr<apache::thrift::protocol::TProtocol> clientProtocol;
  thrift_code::ThriftServiceBenchmarkClient client;
  apache::thrift::server::TSimpleServer server;
  std::atomic_bool server_running;
};

#endif /* end of include guard: FIXTURE_H_ALZERDCI */
