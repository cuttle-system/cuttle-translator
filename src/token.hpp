#pragma once

#include <string>
#include <vector>

namespace cuttle {
	enum token_type {
		ATOM_TOKEN,
		STRING_TOKEN,
		NUMBER_TOKEN
	};

	using token_t = struct token {
		enum token_type type;
		const std::string value;
		const unsigned short line;
		const unsigned short col;
	};

	using tokens_t = std::vector<token_t>;
}
