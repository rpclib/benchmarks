#pragma once

#ifndef FIXTURE_H_ALZERDCI
#define FIXTURE_H_ALZERDCI

#include <atomic>
#include <boost/make_shared.hpp>
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
#include "port_numbers.h"

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
  void SetUp(benchmark::State &) override {
    using boost::make_shared;
    using std::make_unique;
    handler = make_shared<thrift_server>();
    processor =
        make_shared<thrift_code::ThriftServiceBenchmarkProcessor>(handler);
    serverTransport =
        make_shared<apache::thrift::transport::TServerSocket>(thrift_port);
    transportFactory =
        make_shared<apache::thrift::transport::TBufferedTransportFactory>();
    protocolFactory =
        make_shared<apache::thrift::protocol::TBinaryProtocolFactory>();
    clientSocket = make_shared<apache::thrift::transport::TSocket>("127.0.0.1",
                                                                   thrift_port);
    clientTransport =
        make_shared<apache::thrift::transport::TBufferedTransport>(
            clientSocket);
    clientProtocol =
        make_shared<apache::thrift::protocol::TBinaryProtocol>(clientTransport);
    client =
        make_unique<thrift_code::ThriftServiceBenchmarkClient>(clientProtocol);
    server = make_unique<apache::thrift::server::TSimpleServer>(
        processor, serverTransport, transportFactory, protocolFactory);
    std::thread serve_thread([this]() {
      server_running = true;
      server->serve();
      server_running = false;
    });
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    clientTransport->open();
    serve_thread.detach();
  }

  void TearDown(benchmark::State&) override {
    clientTransport->close();
    server->stop();
    while (server_running)
      ;
  }

  void get_answer(int param) {
    (void)param;
    int a;
    benchmark::DoNotOptimize(a = client->get_answer(23));
  }

  void get_blob(int param) {
    handler->blob_size = param;
    std::string s;
    client->get_blob(s);
  }

  void get_structs(int param) {
    (void)param;
    std::vector<thrift_code::Student> students;
    client->get_structs(students);
    std::size_t count;
    benchmark::DoNotOptimize(count = students.size());
  }

  boost::shared_ptr<thrift_server> handler;
  boost::shared_ptr<apache::thrift::TProcessor> processor;
  boost::shared_ptr<apache::thrift::server::TServerTransport> serverTransport;
  boost::shared_ptr<apache::thrift::server::TTransportFactory> transportFactory;
  boost::shared_ptr<apache::thrift::protocol::TProtocolFactory> protocolFactory;
  boost::shared_ptr<apache::thrift::protocol::TTransport> clientSocket;
  boost::shared_ptr<apache::thrift::protocol::TTransport> clientTransport;
  boost::shared_ptr<apache::thrift::protocol::TProtocol> clientProtocol;
  std::unique_ptr<thrift_code::ThriftServiceBenchmarkClient> client;
  std::unique_ptr<apache::thrift::server::TSimpleServer> server;
  std::atomic_bool server_running;
};

#endif /* end of include guard: FIXTURE_H_ALZERDCI */
