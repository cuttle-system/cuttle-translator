#include "translator_methods.hpp"
#include "dictionary_funcs.hpp"
#include "value_methods.hpp"

using namespace cuttle;

unsigned int cuttle::translate_function_call(translate_state_t &state) {
    token_t token = state.tokens[state.index];
    if (state.dictionary.find(token.value) != state.dictionary.end()) {
        return state.dictionary[token.value][state.tree.src[state.index].size()](state);
    } else if (state.dictionary.find(TRANSLATOR_ANY_NAME) != state.dictionary.end()) {
        auto translate_functions = state.dictionary[TRANSLATOR_ANY_NAME];
        if (translate_functions.find(DICTIONARY_ANY_ARG_NUMBER) != translate_functions.end()) {
            return translate_functions[DICTIONARY_ANY_ARG_NUMBER](state);
        } else {
            return dictionary_funcs::copy(state);
        }
    }
    return dictionary_funcs::copy(state);
}

void cuttle::translate(
	const translator_t &translator, const tokens_t &tokens, const call_tree_t &tree,
	values_t &values, call_tree_t &new_tree
) {
    tree_src_elements_t root_args;
    dictionary_t dictionary = translator.dictionary;
    unsigned int new_index = 0;
    unsigned int root_arg_index;
    index_reference_t index_reference;
	translate_state_t state = {
		dictionary, tokens, tree, 0, values, new_tree, new_index, index_reference
	};

	for (auto index : tree.src.back()) {
		state.index = index;
        token_t token = state.tokens[state.index];
        if (token.type == token_type::atom) {
            root_arg_index = translate_function_call(state);
        } else {
            root_arg_index = dictionary_funcs::value(state, token.value, value_from_token_type(token.type));
        }
        root_args.push_back(root_arg_index);
    }

	new_tree.src.push_back(root_args);
}