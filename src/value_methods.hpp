#pragma once

#include "value.hpp"

namespace cuttle {
	value_type value_from_token_type(enum token_type token_type);

	bool operator==(const value_t& left, const value_t& right);
}