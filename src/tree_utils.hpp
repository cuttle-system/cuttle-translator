#pragma once

#include <deque>

#include "vm_context.hpp"
#include "call_tree.hpp"
#include "token.hpp"

namespace cuttle {
    void
    construct_tree(vm::context_t &context, std::deque<vm::value_t> &arg_stack, call_tree_t &tree, tokens_t &tokens);
}