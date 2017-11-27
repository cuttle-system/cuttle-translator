#include <string>
#include "dictionary.hpp"

void cuttle::add(cuttle::dictionary_t& dictionary, std::string name, cuttle::arg_number_t arg_number, cuttle::translate_function_t *function) {
	using namespace cuttle;

	dictionary[name][arg_number] = function;
}

int cuttle::dictionary_funcs::copy(TRANSLATE_FUNCTION_ARGS) {
	size_t new_size = new_index + tree.src[index].size() + 1;
	int function_index = new_index;
	
	if (values.size() < new_size) {
		values.resize(new_size);
	}
	if (new_tree.src.size() < new_size) {
		new_tree.src.resize(new_size);
	}

	values[function_index] = { tokens[index].value, TYPE_FUNCTION_NAME };
	new_tree.src[function_index].resize(tree.src[index].size());
	++new_index;
	
	for (int i = 0; i < tree.src[index].size(); ++i) {
		auto arg_index = tree.src[index][i];
		token_t token = tokens[arg_index];
		values[new_index] = { token.value, value_from_token_type(token.type) };
		new_tree.src[function_index][i] = new_index;
		++new_index;
	}

	return function_index;
}
