#include "translator_methods.hpp"
#include "dictionary_funcs.hpp"

void cuttle::translate(
	const cuttle::translator_t & translator, const cuttle::tokens_t & tokens, const cuttle::call_tree_t & tree, cuttle::values_t & values, cuttle::call_tree_t & new_tree
) {
	using namespace cuttle;

	tree_src_elements_t root_args;
	dictionary_t dictionary = translator.dictionary;
	unsigned int new_index = 0;
	index_reference_t index_reference;
	translate_state_t state = {
		tokens, tree, 0, values, new_tree, new_index, index_reference
	};

	for (state.index = 0; state.index < tree.src.size() - 1; ++state.index) {
		token_t token = tokens[state.index];
		if (token.type == token_type::atom) {
			if (dictionary.find(token.value) != dictionary.end()) {
                dictionary[token.value][tree.src[state.index].size()](state);
            } else if (dictionary.find(TRANSLATOR_ANY_NAME) != dictionary.end()) {
                auto translate_functions = dictionary[TRANSLATOR_ANY_NAME];
			    if (translate_functions.find(DICTIONARY_ANY_ARG_NUMBER) != translate_functions.end()) {
                    translate_functions[DICTIONARY_ANY_ARG_NUMBER](state);
                } else {
                   dictionary_funcs::copy(state);
			    }
			} else {
				dictionary_funcs::copy(state);
			}
		}
	}

	for (auto index : tree.src.back()) {
        root_args.push_back(index_reference[index]);
    }

	new_tree.src.push_back(root_args);
}