#include <string>
#include "dictionary.hpp"

void cuttle::add(cuttle::dictionary_t& dictionary, std::string name, cuttle::arg_number_t arg_number, cuttle::translate_function_t *function) {
	using namespace cuttle;

	dictionary[name][arg_number] = function;
}