#pragma once

#include <map>
#include <string>
#include "call_tree.hpp"
#include "value.hpp"
#include "token.hpp"

#define TRANS_IN_ARGS_DEF const tokens_t& tokens, const call_tree_t& tree, int index
#define TRANS_IN_ARGS tokens, tree, index

#define TRANS_OUT_ARGS_DEF values_t& values, call_tree_t& new_tree, int& new_index
#define TRANS_OUT_ARGS values, new_tree, new_index

#define TRANS_ENV_ARGS_DEF index_reference_t& index_reference
#define TRANS_ENV_ARGS index_reference

#define TRANS_OUT_ENV_ARGS_DEF TRANS_OUT_ARGS_DEF, TRANS_ENV_ARGS_DEF
#define TRANS_OUT_ENV_ARGS TRANS_OUT_ARGS, TRANS_ENV_ARGS

#define TRANS_FUN_ARGS_DEF TRANS_IN_ARGS_DEF, TRANS_OUT_ENV_ARGS_DEF
#define TRANS_FUN_ARGS TRANS_IN_ARGS, TRANS_OUT_ENV_ARGS


namespace cuttle {
	using index_reference_t = std::map<int, int>;
	using arg_number_t = int;
	using translate_function_t = int(TRANS_FUN_ARGS_DEF);
	using dictionary_t = std::map<std::string, std::map<arg_number_t, translate_function_t *> >;

	void add(dictionary_t& dictionary, std::string name, arg_number_t arg_number, translate_function_t *function);

	namespace dictionary_funcs {
		int copy(TRANS_FUN_ARGS_DEF);

		int value(TRANS_OUT_ARGS_DEF, std::string value, enum value_type type);
		int function_name(TRANS_OUT_ARGS_DEF, std::string value);
		int string(TRANS_OUT_ARGS_DEF, std::string value);
		int number(TRANS_OUT_ARGS_DEF, std::string value);

		int function(TRANS_OUT_ARGS_DEF, int function_name_index, std::initializer_list<int> args_indexes);
	}
}