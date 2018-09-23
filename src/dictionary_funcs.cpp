#include <utility>

#include "dictionary_funcs.hpp"
#include "value_methods.hpp"
#include "translator_methods.hpp"

using namespace cuttle;

tree_src_element_t cuttle::dictionary_funcs::value(translate_state_t& state, const std::string& value, enum cuttle::value_type type) {
	state.new_tree.src.push_back({});
	state.values.push_back({ value, type });
	return state.new_index++;
}

tree_src_element_t cuttle::dictionary_funcs::function_name(translate_state_t& state, const std::string& value) {
	return cuttle::dictionary_funcs::value(state, value, value_type::func_name);
}

tree_src_element_t cuttle::dictionary_funcs::string(translate_state_t& state, const std::string& value) {
	return cuttle::dictionary_funcs::value(state, value, value_type::string);
}

tree_src_element_t cuttle::dictionary_funcs::number(translate_state_t& state, const std::string& value) {
	return cuttle::dictionary_funcs::value(state, value, value_type::number);
}

tree_src_element_t cuttle::dictionary_funcs::function(translate_state_t &state,
	tree_src_element_t function_name_index,
	std::vector<unsigned int> args_indexes
) {
	state.new_tree.src[function_name_index] = std::move(args_indexes);
	return function_name_index;
}

unsigned int cuttle::dictionary_funcs::copy(translate_state_t& state) {
    tree_src_element_t new_arg_index;

	token_t function_name_token = state.tokens[state.index];
	tree_src_element_t function_index = dictionary_funcs::function(
			state, dictionary_funcs::function_name(state, function_name_token.value), {});

    state.index_reference[state.index] = function_index;

    for (auto arg_index : state.tree.src[state.index]) {
	    token_t token = state.tokens[arg_index];
	    if (token.type == token_type::atom) {
	        translate_state_t child_state = state;
	        child_state.index = arg_index;
            new_arg_index = translate_function_call(child_state);
	    } else {
	        new_arg_index = dictionary_funcs::value(state,
	                token.value, value_from_token_type(token.type));
        }
        state.new_tree.src[function_index].push_back(new_arg_index);
        state.index_reference[arg_index] = new_arg_index;
	}

	return function_index;
}
