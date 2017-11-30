#pragma once

#include "translator.hpp"

namespace cuttle {
	void translate(const translator_t& translator, const tokens_t& tokens, const call_tree_t& tree, values_t& values, call_tree_t& new_tree);
}