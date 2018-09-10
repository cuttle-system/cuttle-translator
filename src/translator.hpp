#pragma once

#include <string>
#include "dictionary.hpp"
#include "call_tree.hpp"
#include "token.hpp"
#include "value.hpp"

namespace cuttle {
	using translator_version_t = int;

	const std::string TRANSLATOR_ANY_NAME;
    const translator_version_t TRANSLATOR_ANY_VERSION = -1;

    struct language_t {
		std::string name;
		translator_version_t version;
	};

	struct translator_t {
		language_t from;
		language_t to;
		dictionary_t dictionary;
	};
}