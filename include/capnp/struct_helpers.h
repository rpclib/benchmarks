#pragma once

#ifndef STRUCT_HELPERS_H_8D7IKUZ5
#define STRUCT_HELPERS_H_8D7IKUZ5

#include <vector>
#include <capnp/list.h>

#include "capnp/capnp_service.capnp.h"

namespace capnp_code {

StudentDataResponse::Builder& get_structs();
void fill_struct_cache();

} /* capnp_code */

#endif /* end of include guard: STRUCT_HELPERS_H_8D7IKUZ5 */
