#include "value_methods.hpp"

cuttle::value_type cuttle::value_from_token_type(cuttle::token_type token_type)
{
	using namespace cuttle;
	switch (token_type) {
	case token_type::atom:
		return value_type::func_name;
	case token_type::number:
		return value_type::number;
	case token_type::string:
		return value_type::string;
	default:
		return value_type::unknown;
	}
}

bool cuttle::operator==(const cuttle::value_t& left, const cuttle::value_t& right)
{
	return (left.value == right.value && left.type == right.type);
}