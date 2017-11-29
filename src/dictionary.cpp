#include <string>
#include "dictionary.hpp"

void cuttle::add(cuttle::dictionary_t& dictionary, std::string name, cuttle::arg_number_t arg_number, cuttle::translate_function_t *function) {
	using namespace cuttle;

	dictionary[name][arg_number] = function;
}

int cuttle::dictionary_funcs::value(translate_state_t& state, std::string value, enum cuttle::value_type type) {
	using namespace cuttle;

	state.new_tree.src.push_back({});
	state.values.push_back({ value, type });
	return state.new_index++;
}

int cuttle::dictionary_funcs::function_name(translate_state_t& state, std::string value) {
	return cuttle::dictionary_funcs::value(state, value, TYPE_FUNCTION_NAME);
}

int cuttle::dictionary_funcs::string(translate_state_t& state, std::string value) {
	return cuttle::dictionary_funcs::value(state, value, TYPE_STRING);
}

int cuttle::dictionary_funcs::number(translate_state_t& state, std::string value) {
	return cuttle::dictionary_funcs::value(state, value, TYPE_NUMBER);
}

int cuttle::dictionary_funcs::function(translate_state_t& state, int function_name_index, std::initializer_list<int> args_indexes) {
	state.new_tree.src[function_name_index] = args_indexes;
	return function_name_index;
}

int cuttle::dictionary_funcs::copy(translate_state_t& state) {
	using namespace cuttle;

	int function_index;

	if (state.index_reference.find(state.index) == state.index_reference.end()) {
		function_index = state.new_index;
		state.values.push_back({ state.tokens[state.index].value, TYPE_FUNCTION_NAME });
		state.new_tree.src.push_back({});
		state.index_reference[state.index] = state.new_index;
		++state.new_index;
	} else {
		function_index = state.index_reference[state.index];
	}

	state.new_tree.src[function_index].resize(state.tree.src[state.index].size());
	
	for (int i = 0; i < state.tree.src[state.index].size(); ++i) {
		auto arg_index = state.tree.src[state.index][i];
		if (state.index_reference.find(arg_index) == state.index_reference.end()) {
			token_t token = state.tokens[arg_index];
			state.values.push_back({ token.value, value_from_token_type(token.type) });
			state.new_tree.src[function_index][i] = state.new_index;
			state.new_tree.src.push_back({});
			state.index_reference[arg_index] = state.new_index;
			++state.new_index;
		} else {
			state.new_tree.src[function_index][i] = state.index_reference[arg_index];
		}
	}

	return function_index;
}
