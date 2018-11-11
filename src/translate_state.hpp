#pragma once

#include <map>
#include "value.hpp"
#include "token.hpp"
#include "call_tree.hpp"
#include "dictionary.hpp"

namespace cuttle {
	using index_reference_t = std::map<unsigned int, unsigned int>;
	using dictionary_index_to_index_t = std::map<dictionary_element_t, tree_src_element_t>;
	struct translate_state_t {
        dictionary_t &dictionary;
        const tokens_t &tokens;
        const call_tree_t &tree;
        unsigned int index;
        values_t &values;
		call_tree_t &new_tree;
		unsigned int &new_index;
		index_reference_t &index_reference;
		dictionary_element_t translate_function_index;
		dictionary_index_to_index_t dictionary_index_to_index;
	};
}