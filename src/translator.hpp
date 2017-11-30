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
}