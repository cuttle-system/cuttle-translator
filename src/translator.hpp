#pragma once

#include <string>
#include "language.hpp"
#include "dictionary.hpp"
#include "call_tree.hpp"
#include "token.hpp"
#include "value.hpp"

namespace cuttle {
	struct translator_t {
		language_t from;
		language_t to;
		dictionary_t dictionary;
	};
}