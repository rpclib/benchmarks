#pragma once

#ifndef FIXTURE_H_0IQFRKXE
#define FIXTURE_H_0IQFRKXE

#include <atomic>
#include <thread>
#include <chrono>
#include <stdio.h>

#include "hayai/hayai.hpp"

#include "xmlrpc-c/base.hpp"
#include "xmlrpc-c/registry.hpp"
#include "xmlrpc-c/server_abyss.hpp"
#include "xmlrpc-c/client_simple.hpp"
#include "xmlrpc-c/girerr.hpp"

#include "target_code.h"

static constexpr uint16_t xmlrpc_c_port = 8084;

class get_answer_method : public xmlrpc_c::method {
public:
  get_answer_method() {
    this->_signature = "i:i";
  }

  void execute(xmlrpc_c::paramList const &paramList,
               xmlrpc_c::value *const retvalP) {

    auto number = paramList.getInt(0);
    paramList.verifyEnd(1);
    *retvalP = xmlrpc_c::value_int(::get_answer(number));
  }
};

class xmlrpc_c_bench : public hayai::Fixture {
public:
  xmlrpc_c_bench()
      : server(xmlrpc_c::serverAbyss::constrOpt()
                .registryP(&registry)
                .portNumber(xmlrpc_c_port)),
        get_answer_ptr(new get_answer_method) {
    registry.addMethod("get_answer", get_answer_ptr);
    std::thread serve_thread([this]() {
      server_running = true;
      server.run();
      server_running = false;
    });
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    serve_thread.detach();
  }

  void get_answer() {
    xmlrpc_c::value result;
    client.call(server_url, "get_answer", "i", &result, 23);
    int a = xmlrpc_c::value_int(result);
    (void)a;
  }

  ~xmlrpc_c_bench() {
    server.terminate();
    while (server_running) ;
  }

  std::atomic_bool server_running;
  xmlrpc_c::registry registry;
  xmlrpc_c::methodPtr get_answer_ptr;
  xmlrpc_c::serverAbyss server;
  xmlrpc_c::clientSimple client;
  static constexpr const char* server_url = "http://localhost:8084/RPC2";
};

#endif /* end of include guard: FIXTURE_H_0IQFRKXE */
