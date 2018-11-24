#pragma once

#include "dictionary.hpp"
#include "translate_state.hpp"

namespace cuttle {
    const tree_src_element_t TREE_SRC_ROOT_INDEX = std::numeric_limits<tree_src_element_t>::max() - 2;

    dictionary_element_t add(dictionary_t &dictionary, const call_tree_t &pattern_tree, const tokens_t &pattern_tokens,
                                 translate_function_t *function);

    dictionary_element_t add(dictionary_t &dictionary, const call_tree_t &pattern_tree, const tokens_t &pattern_tokens,
                                 translate_function_t *function, const call_tree_t &output_tree, const tokens_t &output_tokens);

    bool lookup(dictionary_t &dictionary, const call_tree_t &tree, const tokens_t &tokens,
                dictionary_index_to_index_t &dictionary_index_to_index, dictionary_element_t function_index,
                tree_src_element_t index, tree_src_element_t dictionary_index = TREE_SRC_ROOT_INDEX);

    void initialize(dictionary_t &dictionary);
}