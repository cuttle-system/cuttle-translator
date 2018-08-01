#pragma once

#include <map>
#include "value.hpp"
#include "token.hpp"
#include "call_tree.hpp"

namespace cuttle {
	using index_reference_t = std::map<unsigned int, unsigned int>;
	struct translate_state_t {
		const tokens_t& tokens;
		const call_tree_t& tree;
		unsigned int index;
		values_t& values;
		call_tree_t& new_tree;
		unsigned int& new_index;
		index_reference_t& index_reference;
	};
}