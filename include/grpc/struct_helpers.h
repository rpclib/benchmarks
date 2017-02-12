#pragma once

#ifndef STRUCT_HELPERS_H_9WVRLQU4
#define STRUCT_HELPERS_H_9WVRLQU4

#include <vector>
#include "grpc/grpc_service.pb.h"

namespace grpc_code {

std::vector<Student>& get_structs();
StudentDataResponse* get_full_structs_response();
void fill_struct_cache();

}

#endif /* end of include guard: STRUCT_HELPERS_H_9WVRLQU4 */
