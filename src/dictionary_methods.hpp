#pragma once

#include "dictionary.hpp"

namespace cuttle {
    const tree_src_element_t TREE_SRC_ROOT_INDEX = std::numeric_limits<tree_src_element_t>::max();

	void add(dictionary_t& dictionary, const call_tree_t &tree, const tokens_t &tokens,
	        translate_function_t *function, tree_src_element_t index = TREE_SRC_ROOT_INDEX);

    bool lookup(dictionary_t &dictionary, const call_tree_t &tree, const tokens_t &tokens, tree_src_element_t index,
                dictionary_element_t &function_index);

    void initialize(dictionary_t &dictionary);
}