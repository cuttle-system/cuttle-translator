#pragma once

#include <vector>
#include <string>

#include "token.hpp"

namespace cuttle {
	enum class value_type {
		func_name,
		string,
		number,
		unknown
	};

	using value_t = struct {
		std::string value;
		value_type type;
	};

	using values_t = std::vector<value_t>;
}