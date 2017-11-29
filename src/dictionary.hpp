#pragma once

#include <map>
#include <string>
#include "call_tree.hpp"
#include "value.hpp"
#include "token.hpp"

#define TRANSLATE_INPUT_ARGS const tokens_t& tokens, const call_tree_t& tree, int index
#define TRANSLATE_INPUT_ARGS_NO_TYPE tokens, tree, index

#define TRANSLATE_OUTPUT_ARGS values_t& values, call_tree_t& new_tree, int& new_index
#define TRANSLATE_OUTPUT_ARGS_NO_TYPE values, new_tree, new_index

#define TRANSLATE_ARGS_ENV_ARGS index_reference_t& index_reference
#define TRANSLATE_ARGS_ENV_ARGS_NO_TYPE index_reference

#define TRANSLATE_OUTPUT_ENV_ARGS TRANSLATE_OUTPUT_ARGS, TRANSLATE_ARGS_ENV_ARGS
#define TRANSLATE_OUTPUT_ENV_ARGS_NO_TYPE TRANSLATE_OUTPUT_ARGS_NO_TYPE, TRANSLATE_ARGS_ENV_ARGS_NO_TYPE

#define TRANSLATE_FUNCTION_ARGS TRANSLATE_INPUT_ARGS, TRANSLATE_OUTPUT_ENV_ARGS
#define TRANSLATE_FUNCTION_ARGS_NO_TYPE TRANSLATE_INPUT_ARGS_NO_TYPE, TRANSLATE_OUTPUT_ENV_ARGS_NO_TYPE


namespace cuttle {
	using index_reference_t = std::map<int, int>;
	using arg_number_t = int;
	using translate_function_t = int(TRANSLATE_FUNCTION_ARGS);
	using dictionary_t = std::map<std::string, std::map<arg_number_t, translate_function_t *> >;

	void add(dictionary_t& dictionary, std::string name, arg_number_t arg_number, translate_function_t *function);

	namespace dictionary_funcs {
		int copy(TRANSLATE_FUNCTION_ARGS);

		int value(TRANSLATE_OUTPUT_ARGS, std::string value, enum value_type type);
		int function_name(TRANSLATE_OUTPUT_ARGS, std::string value);
		int string(TRANSLATE_OUTPUT_ARGS, std::string value);
		int number(TRANSLATE_OUTPUT_ARGS, std::string value);
	}
}