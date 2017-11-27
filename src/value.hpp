#pragma once

#include <vector>
#include <string>

#include "token.hpp"

namespace cuttle {
	enum value_type {
		TYPE_FUNCTION_NAME,
		TYPE_STRING,
		TYPE_NUMBER
	};

	using value_t = struct {
		std::string value;
		enum value_type type;
	};

	using values_t = std::vector<value_t>;

	enum value_type value_from_token_type(enum token_type token_type);

	bool operator==(const value_t& left, const value_t& right);
}