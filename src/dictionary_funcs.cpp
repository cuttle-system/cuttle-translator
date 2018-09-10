#include <utility>

#include "dictionary_funcs.hpp"
#include "value_methods.hpp"

unsigned int cuttle::dictionary_funcs::value(translate_state_t& state, const std::string& value, enum cuttle::value_type type) {
	using namespace cuttle;

	state.new_tree.src.push_back({});
	state.values.push_back({ value, type });
	return state.new_index++;
}

unsigned int cuttle::dictionary_funcs::function_name(translate_state_t& state, const std::string& value) {
	return cuttle::dictionary_funcs::value(state, value, value_type::func_name);
}

unsigned int cuttle::dictionary_funcs::string(translate_state_t& state, const std::string& value) {
	return cuttle::dictionary_funcs::value(state, value, value_type::string);
}

unsigned int cuttle::dictionary_funcs::number(translate_state_t& state, const std::string& value) {
	return cuttle::dictionary_funcs::value(state, value, value_type::number);
}

unsigned int cuttle::dictionary_funcs::function(translate_state_t &state, unsigned int function_name_index,
												std::vector<unsigned int> args_indexes) {
	state.new_tree.src[function_name_index] = std::move(args_indexes);
	return function_name_index;
}

unsigned int cuttle::dictionary_funcs::copy(translate_state_t& state) {
	using namespace cuttle;

	unsigned int function_index;

	if (state.index_reference.find(state.index) == state.index_reference.end()) {
		function_index = state.new_index;
		state.values.push_back({ state.tokens[state.index].value, value_type::func_name });
		state.new_tree.src.push_back({});
		state.index_reference[state.index] = state.new_index;
		++state.new_index;
	}
	else {
		function_index = state.index_reference[state.index];
	}

	state.new_tree.src[function_index].resize(state.tree.src[state.index].size());

	for (unsigned int i = 0; i < state.tree.src[state.index].size(); ++i) {
		auto arg_index = state.tree.src[state.index][i];
		if (state.index_reference.find(arg_index) == state.index_reference.end()) {
			token_t token = state.tokens[arg_index];
			state.values.push_back({ token.value, value_from_token_type(token.type) });
			state.new_tree.src[function_index][i] = state.new_index;
			state.new_tree.src.push_back({});
			state.index_reference[arg_index] = state.new_index;
			++state.new_index;
		}
		else {
			state.new_tree.src[function_index][i] = state.index_reference[arg_index];
		}
	}

	return function_index;
}
