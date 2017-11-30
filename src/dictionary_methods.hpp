#pragma once

#include "dictionary.hpp"

namespace cuttle {
	void add(dictionary_t& dictionary, std::string name, arg_number_t arg_number, translate_function_t *function);
}