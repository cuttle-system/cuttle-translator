#include <string>
#include "dictionary.hpp"

void cuttle::add(cuttle::dictionary_t& dictionary, std::string name, cuttle::arg_number_t arg_number, cuttle::translate_function_t *function) {
	using namespace cuttle;

	dictionary[name][arg_number] = function;
}

int cuttle::dictionary_funcs::value(TRANS_OUT_ARGS_DEF, std::string value, enum cuttle::value_type type) {
	using namespace cuttle;

	new_tree.src.push_back({});
	values.push_back({ value, type });
	return new_index++;
}

int cuttle::dictionary_funcs::function_name(TRANS_OUT_ARGS_DEF, std::string value) {
	return cuttle::dictionary_funcs::value(TRANS_OUT_ARGS, value, TYPE_FUNCTION_NAME);
}

int cuttle::dictionary_funcs::string(TRANS_OUT_ARGS_DEF, std::string value) {
	return cuttle::dictionary_funcs::value(TRANS_OUT_ARGS, value, TYPE_STRING);
}

int cuttle::dictionary_funcs::number(TRANS_OUT_ARGS_DEF, std::string value) {
	return cuttle::dictionary_funcs::value(TRANS_OUT_ARGS, value, TYPE_NUMBER);
}

int cuttle::dictionary_funcs::function(TRANS_OUT_ARGS_DEF, int function_name_index, std::initializer_list<int> args_indexes) {
	new_tree.src[function_name_index] = args_indexes;
	return function_name_index;
}

int cuttle::dictionary_funcs::copy(TRANS_FUN_ARGS_DEF) {
	using namespace cuttle;

	int function_index;

	if (index_reference.find(index) == index_reference.end()) {
		function_index = new_index;
		values.push_back({ tokens[index].value, TYPE_FUNCTION_NAME });
		new_tree.src.push_back({});
		index_reference[index] = new_index;
		++new_index;
	} else {
		function_index = index_reference[index];
	}

	new_tree.src[function_index].resize(tree.src[index].size());
	
	for (int i = 0; i < tree.src[index].size(); ++i) {
		auto arg_index = tree.src[index][i];
		if (index_reference.find(arg_index) == index_reference.end()) {
			token_t token = tokens[arg_index];
			values.push_back({ token.value, value_from_token_type(token.type) });
			new_tree.src[function_index][i] = new_index;
			new_tree.src.push_back({});
			index_reference[arg_index] = new_index;
			++new_index;
		} else {
			new_tree.src[function_index][i] = index_reference[arg_index];
		}
	}

	return function_index;
}
