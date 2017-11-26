#pragma once

#include <map>
#include <string>
#include "call_tree.hpp"
#include "value.hpp"
#include "token.hpp"

namespace cuttle {
	using arg_number_t = int;
	using translate_function_t = void(const tokens_t& tokens, const call_tree_t& tree, int index, values_t& values, call_tree_t& new_tree);
	using dictionary_t = std::map<std::string, std::map<arg_number_t, translate_function_t *> >;

	void add(dictionary_t& dictionary, std::string name, arg_number_t arg_number, translate_function_t *function);
}