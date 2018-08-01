#pragma once

#include <map>
#include <string>
#include "call_tree.hpp"
#include "value.hpp"
#include "token.hpp"
#include "translate_state.hpp"

namespace cuttle {
	using arg_number_t = int;
	using translate_function_t = unsigned int(translate_state_t& state);
	using dictionary_t = std::map<std::string, std::map<arg_number_t, translate_function_t *> >;
}