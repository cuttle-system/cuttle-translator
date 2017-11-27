#pragma once

#include <map>
#include <string>
#include "call_tree.hpp"
#include "value.hpp"
#include "token.hpp"

#define TRANSLATE_FUNCTION_ARGS const tokens_t& tokens, const call_tree_t& tree, int index, values_t& values, call_tree_t& new_tree, int& new_index, index_reference_t& index_reference 
#define TRANSLATE_FUNCTION_ARGS_NO_TYPE tokens, tree, index, values, new_tree, new_index, index_reference

namespace cuttle {
	using index_reference_t = std::map<int, int>;
	using arg_number_t = int;
	using translate_function_t = int(TRANSLATE_FUNCTION_ARGS);
	using dictionary_t = std::map<std::string, std::map<arg_number_t, translate_function_t *> >;

	void add(dictionary_t& dictionary, std::string name, arg_number_t arg_number, translate_function_t *function);

	namespace dictionary_funcs {
		int copy(TRANSLATE_FUNCTION_ARGS);
	}
}