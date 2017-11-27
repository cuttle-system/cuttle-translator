#include "translator.hpp"

void cuttle::translate(
	const cuttle::translator_t & translator, const cuttle::tokens_t & tokens, const cuttle::call_tree_t & tree, cuttle::values_t & values, cuttle::call_tree_t & new_tree
) {
	using namespace cuttle;

	dictionary_t dictionary = translator.dictionary;
	int new_index = 0;

	for (int index = 0; index < tree.src.size(); ++index) {
		token_t token = tokens[index];
		if (token.type == ATOM_TOKEN) {
			if (dictionary.find(token.value) != dictionary.end()) {
				dictionary[token.value][tree.src[index].size()](tokens, tree, index, values, new_tree, new_index);
			} else {
				dictionary_funcs::copy(tokens, tree, index, values, new_tree, new_index);
			}
		}
	}
}