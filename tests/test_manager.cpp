#include <iostream>
#include "test_file_access.hpp"
#include "test_dictionary.hpp"
#include "test_translator.hpp"
#include "test_dictionary_funcs.hpp"

void run_tests() {
    run_file_access_tests();
	run_dictionary_tests();
	run_dictionary_funcs_tests();
	run_translator_tests();
}