#pragma once

#include <ostream>
#include "value.hpp"

namespace cuttle {
	value_type value_from_token_type(enum token_type token_type);

	bool operator==(const value_t& left, const value_t& right);

    std::ostream &operator<<(std::ostream& stream, const value_type& type);
}