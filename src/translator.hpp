#pragma once

#include <string>
#include "dictionary.hpp"
#include "call_tree.hpp"
#include "token.hpp"
#include "value.hpp"

namespace cuttle {
	using translator_version_t = int;
	using language_t = struct {
		std::string name;
		translator_version_t version;
	};

	using translator_t = struct {
		language_t from;
		language_t to;
		dictionary_t dictionary;
	};

	void translate(const translator_t& translator, const tokens_t& tokens, const call_tree_t& tree, values_t& values, call_tree_t& new_tree);
}