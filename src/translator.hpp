#pragma once

#include <string>
#include "language.hpp"
#include "dictionary.hpp"
#include "call_tree.hpp"
#include "token.hpp"
#include "value.hpp"

namespace cuttle {
	const std::string CUTTLE_MERGE_WITH_PARENT_FUNC = "__cuttle_merge_with_parent_func";

	struct translator_t {
		language_t from;
		language_t to;
		dictionary_t dictionary;
	};
}