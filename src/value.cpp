#include "value.hpp"

enum cuttle::value_type cuttle::value_from_token_type(cuttle::token_type token_type)
{
	return (enum value_type) token_type;
}

bool cuttle::operator==(const cuttle::value_t& left, const cuttle::value_t& right)
{
	return (left.value == right.value && left.type == right.type);
}