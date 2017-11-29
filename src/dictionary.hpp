#pragma once

#include <map>
#include <string>
#include "call_tree.hpp"
#include "value.hpp"
#include "token.hpp"
#include "translate_state.hpp"

namespace cuttle {
	using arg_number_t = int;
	using translate_function_t = int(translate_state_t& state);
	using dictionary_t = std::map<std::string, std::map<arg_number_t, translate_function_t *> >;

	void add(dictionary_t& dictionary, std::string name, arg_number_t arg_number, translate_function_t *function);

	namespace dictionary_funcs {
		int copy(translate_state_t& state);

		int value(translate_state_t& state, std::string value, enum value_type type);
		int function_name(translate_state_t& state, std::string value);
		int string(translate_state_t& state, std::string value);
		int number(translate_state_t& state, std::string value);

		int function(translate_state_t& state, int function_name_index, std::initializer_list<int> args_indexes);
	}
}