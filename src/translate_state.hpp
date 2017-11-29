#pragma once

#include <map>
#include "value.hpp"
#include "token.hpp"
#include "call_tree.hpp"

namespace cuttle {
	using index_reference_t = std::map<int, int>;
	using translate_state_t = struct {
		const tokens_t& tokens;
		const call_tree_t& tree;
		int index;
		values_t& values;
		call_tree_t& new_tree;
		int& new_index;
		index_reference_t& index_reference;
	};
}