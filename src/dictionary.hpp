#pragma once

#include <map>
#include <string>
#include "call_tree.hpp"
#include "value.hpp"
#include "token.hpp"

namespace cuttle {
	struct translate_state_t;

	using arg_number_t = int;
	const arg_number_t DICTIONARY_ANY_ARG_NUMBER = -1;
	using translate_function_t = unsigned int(translate_state_t& state);
	using dictionary_t = std::map<std::string, std::map<arg_number_t, translate_function_t *> >;
}