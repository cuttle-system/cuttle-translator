#pragma once

#include "translate_state.hpp"
#include "dictionary.hpp"

namespace cuttle {
	namespace dictionary_funcs {
		unsigned int copy(translate_state_t& state);

		unsigned int value(translate_state_t& state, const std::string& value, enum value_type type);
		unsigned int function_name(translate_state_t& state, const std::string& value);
		unsigned int string(translate_state_t& state, const std::string& value);
		unsigned int number(translate_state_t& state, const std::string& value);

		unsigned int function(translate_state_t &state, unsigned int function_name_index,
                              std::vector<unsigned int> args_indexes);
	}
}