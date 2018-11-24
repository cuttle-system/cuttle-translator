#pragma once

#include "vm_context.hpp"

namespace cuttle {
    struct context_holder_t {
        vm::context_t& global;
        vm::context_t& local;
    };
}