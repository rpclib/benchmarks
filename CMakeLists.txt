cmake_minimum_required(VERSION 3.0.0)
project(rpclib_benchmark)

set(CMAKE_EXPORT_COMPILE_COMMANDS "ON") # for YCM

if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/build/conanbuildinfo.cmake) #Clion, with conanbuildinfo.cmake in build folder
    include(${CMAKE_CURRENT_SOURCE_DIR}/build/conanbuildinfo.cmake)
else()
    include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake) # Not CLion
endif()

conan_basic_setup()

add_executable(rpclib_benchmark
    src/target_code.cc
    src/benchmark.cc
    src/capnp/capnp_service.capnp.cc
    src/thrift/thrift_service_constants.cpp
    src/thrift/thrift_service_types.cpp
    src/thrift/ThriftServiceBenchmark.cpp
    src/thrift/struct_helpers.cc
    src/grpc/grpc_service.pb.cc
    src/grpc/grpc_service.grpc.pb.cc
    src/grpc/struct_helpers.cc
    src/rpclib/struct_helpers.cc
    )

target_link_libraries(rpclib_benchmark ${CONAN_LIBS} dw bfd)
set_target_properties(
        rpclib_benchmark
        PROPERTIES
        CXX_STANDARD 14)
target_compile_definitions(rpclib_benchmark PUBLIC ${CONAN_DEFINES})
target_include_directories(rpclib_benchmark PUBLIC include)
target_include_directories(rpclib_benchmark PUBLIC include/thrift)
target_include_directories(rpclib_benchmark PUBLIC include/capnp)
target_include_directories(rpclib_benchmark PUBLIC include/grpc)

add_custom_command(TARGET rpclib_benchmark POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E
                   copy ${CMAKE_BINARY_DIR}/compile_commands.json ${CMAKE_BINARY_DIR}/../compile_commands.json)

