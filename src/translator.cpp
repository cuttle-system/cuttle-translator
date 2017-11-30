#include "translator_methods.hpp"
#include "translate_state.hpp"
#include "dictionary_funcs.hpp"

void cuttle::translate(
	const cuttle::translator_t & translator, const cuttle::tokens_t & tokens, const cuttle::call_tree_t & tree, cuttle::values_t & values, cuttle::call_tree_t & new_tree
) {
	using namespace cuttle;

	dictionary_t dictionary = translator.dictionary;
	int new_index = 0;
	index_reference_t index_reference;
	translate_state_t state = {
		tokens, tree, 0, values, new_tree, new_index, index_reference
	};

	for (state.index = 0; state.index < tree.src.size(); ++state.index) {
		token_t token = tokens[state.index];
		if (token.type == token_type::atom) {
			if (dictionary.find(token.value) != dictionary.end()) {
				dictionary[token.value][tree.src[state.index].size()](state);
			} else {
				dictionary_funcs::copy(state);
			}
		}
	}
}