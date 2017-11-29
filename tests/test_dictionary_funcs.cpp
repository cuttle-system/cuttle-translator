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
		auto ret = dictionary_funcs::copy(tokens, tree, 1, values, new_tree, new_index, index_reference);
		AssertEqual(ret, 0, "Return value");
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
	{
		tokens_t tokens = {
			{ ATOM_TOKEN, "-", 0, 0 },
			{ NUMBER_TOKEN, "1", 0, 0 },
			{ NUMBER_TOKEN, "2", 0, 0 }
		};
		call_tree_t tree = { {
			{ 1, 2 }, {}, {}
			} };
		values_t values;
		call_tree_t new_tree;
		int new_index = 0;
		index_reference_t index_reference;
		auto ret = dictionary_funcs::copy(tokens, tree, 0, values, new_tree, new_index, index_reference);
		AssertEqual(ret, 0, "Return value");
		AssertEqual(new_index, 3, "New index");
		AssertEqual(new_tree.src, (tree_src_t{
			{ 1, 2 },{},{}
		}), "New tree");
		AssertEqual(values, (values_t{
			{ "-", TYPE_FUNCTION_NAME },{ "1", TYPE_NUMBER },{ "2", TYPE_NUMBER }
		}), "Values");
		AssertNotEqual(index_reference.find(0), index_reference.end(), "Index exists");
		AssertNotEqual(index_reference.find(1), index_reference.end(), "Index exists");
		AssertNotEqual(index_reference.find(2), index_reference.end(), "Index exists");
		AssertEqual(index_reference[0], 0, "Index reference");
		AssertEqual(index_reference[1], 1, "Index reference");
		AssertEqual(index_reference[2], 2, "Index reference");
	}
	{
		tokens_t tokens = {
			{ NUMBER_TOKEN, "5", 0, 0 },
			{ ATOM_TOKEN, "!", 0, 0 }
		};
		call_tree_t tree = { {
			{},{0}
			} };
		values_t values;
		call_tree_t new_tree;
		int new_index = 0;
		index_reference_t index_reference;
		auto ret = dictionary_funcs::copy(tokens, tree, 1, values, new_tree, new_index, index_reference);
		AssertEqual(ret, 0, "Return value");
		AssertEqual(new_index, 2, "New index");
		AssertEqual(new_tree.src, (tree_src_t{
			{ 1 },{}
		}), "New tree");
		AssertEqual(values, (values_t{
			{ "!", TYPE_FUNCTION_NAME },{ "5", TYPE_NUMBER }
		}), "Values");
		AssertNotEqual(index_reference.find(0), index_reference.end(), "Index exists");
		AssertNotEqual(index_reference.find(1), index_reference.end(), "Index exists");
		AssertEqual(index_reference[0], 1, "Index reference");
		AssertEqual(index_reference[1], 0, "Index reference");
	}
	{
		tokens_t tokens = {
			{ ATOM_TOKEN, "concat", 0, 0 },
			{ NUMBER_TOKEN, "5", 0, 0 },
			{ STRING_TOKEN, "value", 0, 0 }
		};
		call_tree_t tree = { {
			{ 1, 2 }, {}, {}
			} };
		values_t values;
		call_tree_t new_tree;
		int new_index = 0;
		index_reference_t index_reference;
		auto ret = dictionary_funcs::copy(tokens, tree, 0, values, new_tree, new_index, index_reference);
		AssertEqual(ret, 0, "Return value");
		AssertEqual(new_index, 3, "New index");
		AssertEqual(new_tree.src, (tree_src_t{
			{ 1, 2 }, {}, {}
		}), "New tree");
		AssertEqual(values, (values_t{
			{ "concat", TYPE_FUNCTION_NAME }, { "5", TYPE_NUMBER }, { "value", TYPE_STRING }
		}), "Values");
		AssertNotEqual(index_reference.find(0), index_reference.end(), "Index exists");
		AssertNotEqual(index_reference.find(1), index_reference.end(), "Index exists");
		AssertNotEqual(index_reference.find(2), index_reference.end(), "Index exists");
		AssertEqual(index_reference[0], 0, "Index reference");
		AssertEqual(index_reference[1], 1, "Index reference");
		AssertEqual(index_reference[2], 2, "Index reference");
	}
}

inline void test_copy_nested_functions() {
	{
		tokens_t tokens = {
			{ NUMBER_TOKEN, "1", 0, 0 },
			{ ATOM_TOKEN, "+", 0, 0 },
			{ NUMBER_TOKEN, "2", 0, 0 },
			{ ATOM_TOKEN, "-", 0, 0 },
			{ NUMBER_TOKEN, "3", 0, 0 }
		};
		call_tree_t tree = { {
			{},{ 0, 2 },{},
			{ 1, 4 },{}
			} };
		values_t values;
		call_tree_t new_tree;
		int new_index = 0;
		index_reference_t index_reference;
		
		auto ret1 = dictionary_funcs::copy(tokens, tree, 3, values, new_tree, new_index, index_reference);
		AssertEqual(ret1, 0, "Return value");
		AssertEqual(new_index, 3, "New index");
		AssertEqual(new_tree.src, (tree_src_t{
			{ 1, 2 },{},{}
		}), "New tree");
		AssertEqual(values, (values_t{
			{ "-", TYPE_FUNCTION_NAME },{ "+", TYPE_FUNCTION_NAME },{ "3", TYPE_NUMBER }
		}), "Values");
		AssertEqual(index_reference.find(0), index_reference.end(), "Index not exists");
		AssertNotEqual(index_reference.find(1), index_reference.end(), "Index zexists");
		AssertEqual(index_reference.find(2), index_reference.end(), "Index exists");
		AssertNotEqual(index_reference.find(3), index_reference.end(), "Index exists");
		AssertNotEqual(index_reference.find(4), index_reference.end(), "Index exists");
		AssertEqual(index_reference[1], 1, "Index reference");
		AssertEqual(index_reference[3], 0, "Index reference");
		AssertEqual(index_reference[4], 2, "Index reference");

		auto ret2 = dictionary_funcs::copy(tokens, tree, 1, values, new_tree, new_index, index_reference);
		AssertEqual(ret2, 1, "Return value");
		AssertEqual(new_index, 5, "New index");
		AssertEqual(new_tree.src, (tree_src_t{
			{ 1, 2 },{ 3, 4 },{},{},{}
		}), "New tree");
		AssertEqual(values, (values_t{
			{ "-", TYPE_FUNCTION_NAME }, { "+", TYPE_FUNCTION_NAME },{ "3", TYPE_NUMBER },{ "1", TYPE_NUMBER },{ "2", TYPE_NUMBER }
		}), "Values");
		AssertNotEqual(index_reference.find(0), index_reference.end(), "Index exists");
		AssertNotEqual(index_reference.find(1), index_reference.end(), "Index exists");
		AssertNotEqual(index_reference.find(2), index_reference.end(), "Index exists");
		AssertNotEqual(index_reference.find(3), index_reference.end(), "Index exists");
		AssertNotEqual(index_reference.find(4), index_reference.end(), "Index exists");
		AssertEqual(index_reference[0], 3, "Index reference");
		AssertEqual(index_reference[1], 1, "Index reference");
		AssertEqual(index_reference[2], 4, "Index reference");
		AssertEqual(index_reference[3], 0, "Index reference");
		AssertEqual(index_reference[4], 2, "Index reference");
	}
}

void run_dictionary_funcs_tests() {
    TESTCASE
    test_copy_basic_function();
	test_copy_nested_functions();
}