#include <iostream>
#include "test_token.hpp"
#include "test_file_access.hpp"
#include "test_dictionary.hpp"
#include "test_translator.hpp"

void run_tests() {
    run_token_tests();
    run_file_access_tests();
	run_dictionary_tests();
	run_translator_tests();
}