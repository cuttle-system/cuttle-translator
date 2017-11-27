#include <iostream>
#include "test.hpp"
#include "dictionary.hpp"

using namespace cuttle;

inline void test_copy_basic_function() {
	{
		tokens_t tokens = {
			{ NUMBER_TOKEN, "1", 0, 0 },
			{ ATOM_TOKEN, "plus", 0, 0 },
			{ NUMBER_TOKEN, "2", 0, 0 }
		};
		call_tree_t tree = { {
			{},{ 0, 2 },{}
			} };
		values_t values;
		call_tree_t new_tree;
		int new_index = 0;
		index_reference_t index_reference;
		dictionary_funcs::copy(tokens, tree, 1, values, new_tree, new_index, index_reference);
		AssertEqual(new_index, 3, "New index");
		AssertEqual(new_tree.src, (tree_src_t{
			{ 1, 2 },{},{}
		}), "New tree");
		AssertEqual(values, (values_t{
			{ "plus", TYPE_FUNCTION_NAME },{ "1", TYPE_NUMBER },{ "2", TYPE_NUMBER }
		}), "Values");
		AssertNotEqual(index_reference.find(0), index_reference.end(), "Index exists");
		AssertNotEqual(index_reference.find(1), index_reference.end(), "Index exists");
		AssertNotEqual(index_reference.find(2), index_reference.end(), "Index exists");
		AssertEqual(index_reference[0], 1, "Index reference");
		AssertEqual(index_reference[1], 0, "Index reference");
		AssertEqual(index_reference[2], 2, "Index reference");
	}
}

void run_dictionary_funcs_tests() {
    TESTCASE
    test_copy_basic_function();
}