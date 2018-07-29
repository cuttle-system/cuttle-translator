#pragma once

#include "translate_state.hpp"
#include "dictionary.hpp"

namespace cuttle {
	namespace dictionary_funcs {
		int copy(translate_state_t& state);

		int value(translate_state_t& state, const std::string& value, enum value_type type);
		int function_name(translate_state_t& state, const std::string& value);
		int string(translate_state_t& state, const std::string& value);
		int number(translate_state_t& state, const std::string& value);

		int function(translate_state_t& state, int function_name_index, std::initializer_list<int> args_indexes);
	}
}