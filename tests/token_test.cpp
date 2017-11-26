#include <iostream>
#include "test.hpp"
#include "token.hpp"

using namespace cuttle;

inline void test_constructor() {
    token_t tok {NUMBER_TOKEN, "1", 2, 10};

    AssertTrue(tok.type == NUMBER_TOKEN, "Type constructor");
    AssertTrue(tok.value == "1", "Value constructor");
    AssertTrue(tok.line == 2, "Line constructor");
    AssertTrue(tok.col == 10, "Col constructor");
}

void run_token_tests() {
    TESTCASE
    test_constructor();
}