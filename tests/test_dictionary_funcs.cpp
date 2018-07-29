#include <iostream>
#include "test.hpp"
#include "dictionary_methods.hpp"
#include "dictionary_funcs.hpp"
#include "value_methods.hpp"

using namespace cuttle;

inline void test_copy_basic_function() {
	{
		tokens_t tokens = {
			{ token_type::number, "1", 0, 0 },
			{ token_type::atom, "plus", 0, 0 },
			{ token_type::number, "2", 0, 0 }
		};
		call_tree_t tree = { {
			{},{ 0, 2 },{}
			} };
		values_t values;
		call_tree_t new_tree;
		unsigned int new_index = 0;
		index_reference_t index_reference;
		translate_state_t state = {
			tokens, tree, 1, values, new_tree, new_index, index_reference
		};
		auto ret = dictionary_funcs::copy(state);
		AssertEqual(ret, 0, "Return value");
		AssertEqual(new_index, 3, "New index");
		AssertEqual(new_tree.src, (tree_src_t{
			{ 1, 2 },{},{}
		}), "New tree");
		AssertEqual(values, (values_t{
			{ "plus", value_type::func_name },{ "1", value_type::number },{ "2", value_type::number }
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
			{ token_type::atom, "-", 0, 0 },
			{ token_type::number, "1", 0, 0 },
			{ token_type::number, "2", 0, 0 }
		};
		call_tree_t tree = { {
			{ 1, 2 }, {}, {}
			} };
		values_t values;
		call_tree_t new_tree;
		unsigned int new_index = 0;
		index_reference_t index_reference;
		translate_state_t state = {
			tokens, tree, 0, values, new_tree, new_index, index_reference
		};
		auto ret = dictionary_funcs::copy(state);
		AssertEqual(ret, 0, "Return value");
		AssertEqual(new_index, 3, "New index");
		AssertEqual(new_tree.src, (tree_src_t{
			{ 1, 2 },{},{}
		}), "New tree");
		AssertEqual(values, (values_t{
			{ "-", value_type::func_name },{ "1", value_type::number },{ "2", value_type::number }
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
			{ token_type::number, "5", 0, 0 },
			{ token_type::atom, "!", 0, 0 }
		};
		call_tree_t tree = { {
			{},{0}
			} };
		values_t values;
		call_tree_t new_tree;
		unsigned int new_index = 0;
		index_reference_t index_reference;
		translate_state_t state = {
			tokens, tree, 1, values, new_tree, new_index, index_reference
		};
		auto ret = dictionary_funcs::copy(state);
		AssertEqual(ret, 0, "Return value");
		AssertEqual(new_index, 2, "New index");
		AssertEqual(new_tree.src, (tree_src_t{
			{ 1 },{}
		}), "New tree");
		AssertEqual(values, (values_t{
			{ "!", value_type::func_name },{ "5", value_type::number }
		}), "Values");
		AssertNotEqual(index_reference.find(0), index_reference.end(), "Index exists");
		AssertNotEqual(index_reference.find(1), index_reference.end(), "Index exists");
		AssertEqual(index_reference[0], 1, "Index reference");
		AssertEqual(index_reference[1], 0, "Index reference");
	}
	{
		tokens_t tokens = {
			{ token_type::atom, "concat", 0, 0 },
			{ token_type::number, "5", 0, 0 },
			{ token_type::string, "value", 0, 0 }
		};
		call_tree_t tree = { {
			{ 1, 2 }, {}, {}
			} };
		values_t values;
		call_tree_t new_tree;
		unsigned int new_index = 0;
		index_reference_t index_reference;
		translate_state_t state = {
			tokens, tree, 0, values, new_tree, new_index, index_reference
		};
		auto ret = dictionary_funcs::copy(state);
		AssertEqual(ret, 0, "Return value");
		AssertEqual(new_index, 3, "New index");
		AssertEqual(new_tree.src, (tree_src_t{
			{ 1, 2 }, {}, {}
		}), "New tree");
		AssertEqual(values, (values_t{
			{ "concat", value_type::func_name }, { "5", value_type::number }, { "value", value_type::string }
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
			{ token_type::number, "1", 0, 0 },
			{ token_type::atom, "+", 0, 0 },
			{ token_type::number, "2", 0, 0 },
			{ token_type::atom, "-", 0, 0 },
			{ token_type::number, "3", 0, 0 }
		};
		call_tree_t tree = { {
			{},{ 0, 2 },{},
			{ 1, 4 },{}
			} };
		values_t values;
		call_tree_t new_tree;
		unsigned int new_index = 0;
		index_reference_t index_reference;
		translate_state_t state = {
			tokens, tree, 3, values, new_tree, new_index, index_reference
		};

		auto ret1 = dictionary_funcs::copy(state);
		AssertEqual(ret1, 0, "Return value");
		AssertEqual(new_index, 3, "New index");
		AssertEqual(new_tree.src, (tree_src_t{
			{ 1, 2 },{},{}
		}), "New tree");
		AssertEqual(values, (values_t{
			{ "-", value_type::func_name },{ "+", value_type::func_name },{ "3", value_type::number }
		}), "Values");
		AssertEqual(index_reference.find(0), index_reference.end(), "Index not exists");
		AssertNotEqual(index_reference.find(1), index_reference.end(), "Index zexists");
		AssertEqual(index_reference.find(2), index_reference.end(), "Index exists");
		AssertNotEqual(index_reference.find(3), index_reference.end(), "Index exists");
		AssertNotEqual(index_reference.find(4), index_reference.end(), "Index exists");
		AssertEqual(index_reference[1], 1, "Index reference");
		AssertEqual(index_reference[3], 0, "Index reference");
		AssertEqual(index_reference[4], 2, "Index reference");

		state.index = 1;
		auto ret2 = dictionary_funcs::copy(state);
		AssertEqual(ret2, 1, "Return value");
		AssertEqual(new_index, 5, "New index");
		AssertEqual(new_tree.src, (tree_src_t{
			{ 1, 2 },{ 3, 4 },{},{},{}
		}), "New tree");
		AssertEqual(values, (values_t{
			{ "-", value_type::func_name }, { "+", value_type::func_name },{ "3", value_type::number },{ "1", value_type::number },{ "2", value_type::number }
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

inline void test_value_functions() {
	{
		values_t values;
		call_tree_t new_tree;
		unsigned int new_index = 0;
		index_reference_t index_reference;
		translate_state_t state = {
			{},{}, 0, values, new_tree, new_index, index_reference
		};

		auto ret = dictionary_funcs::value(state, "1", value_type::number);
		AssertEqual(ret, 0, "Return value");
		AssertEqual(new_index, 1, "New index");
		AssertEqual(new_tree.src, (tree_src_t{
			{}
		}), "New tree");
		AssertEqual(values, (values_t{
			{ "1", value_type::number }
		}), "Values");
	}
	{
		values_t values;
		call_tree_t new_tree;
		unsigned int new_index = 0;
		index_reference_t index_reference;
		translate_state_t state = {
			{},{}, 0, values, new_tree, new_index, index_reference
		};

		auto ret1 = dictionary_funcs::value(state, "1", value_type::number);
		AssertEqual(ret1, 0, "Return value");
		AssertEqual(new_index, 1, "New index");
		AssertEqual(new_tree.src, (tree_src_t{
			{}
		}), "New tree");
		AssertEqual(values, (values_t{
			{ "1", value_type::number }
		}), "Values");

		auto ret2 = dictionary_funcs::value(state, "foo", value_type::func_name);
		AssertEqual(ret2, 1, "Return value");
		AssertEqual(new_index, 2, "New index");
		AssertEqual(new_tree.src, (tree_src_t{
			{},{}
		}), "New tree");
		AssertEqual(values, (values_t{
			{ "1", value_type::number },{ "foo", value_type::func_name }
		}), "Values");
	}
	{
		values_t values;
		call_tree_t new_tree;
		unsigned int new_index = 0;
		index_reference_t index_reference;
		translate_state_t state = {
			{},{}, 0, values, new_tree, new_index, index_reference
		};

		auto ret1 = dictionary_funcs::number(state, "1");
		AssertEqual(ret1, 0, "Return value");
		AssertEqual(new_index, 1, "New index");
		AssertEqual(new_tree.src, (tree_src_t{
			{}
		}), "New tree");
		AssertEqual(values, (values_t{
			{ "1", value_type::number }
		}), "Values");

		auto ret2 = dictionary_funcs::function_name(state, "foo");
		AssertEqual(ret2, 1, "Return value");
		AssertEqual(new_index, 2, "New index");
		AssertEqual(new_tree.src, (tree_src_t{
			{},{}
		}), "New tree");
		AssertEqual(values, (values_t{
			{ "1", value_type::number },{ "foo", value_type::func_name }
		}), "Values");

		auto ret3 = dictionary_funcs::string(state, "foo bar");
		AssertEqual(ret3, 2, "Return value");
		AssertEqual(new_index, 3, "New index");
		AssertEqual(new_tree.src, (tree_src_t{
			{},{},{}
		}), "New tree");
		AssertEqual(values, (values_t{
			{ "1", value_type::number },{ "foo", value_type::func_name },{ "foo bar", value_type::string }
		}), "Values");
	}
}

inline void test_add_function_function() {
	{
		values_t values = { {"foo", value_type::func_name},{ "1", value_type::number },{"2", value_type::number} };
		call_tree_t new_tree = { { {}, {}, {} } };
		unsigned int new_index = 3;
		index_reference_t index_reference;
		translate_state_t state = {
			{},{}, 0, values, new_tree, new_index, index_reference
		};

		auto ret = dictionary_funcs::function(state, 0, { 1, 2 });
		AssertEqual(ret, 0, "Return value");
		AssertEqual(new_index, 3, "New index");
		AssertEqual(new_tree.src, (tree_src_t{
			{1, 2},{},{}
		}), "New tree");
		AssertEqual(values, (values_t{
			{ { "foo", value_type::func_name },{ "1", value_type::number },{ "2", value_type::number } }
		}), "Values");
	}
	{
		values_t values = { {"foo", value_type::func_name}, { "+", value_type::func_name },{ "1", value_type::number },{ "2", value_type::number } };
		call_tree_t new_tree = { { {},{},{},{} } };
		unsigned int new_index = 4;
		index_reference_t index_reference;
		translate_state_t state = {
			{},{}, 0, values, new_tree, new_index, index_reference
		};

		auto ret1 = dictionary_funcs::function(state, 1, {2, 3});
		AssertEqual(ret1, 1, "Return value");
		AssertEqual(new_index, 4, "New index");
		AssertEqual(new_tree.src, (tree_src_t{
			{},{2, 3},{},{}
		}), "New tree");
		AssertEqual(values, (values_t{
			{ { "foo", value_type::func_name },{ "+", value_type::func_name },{ "1", value_type::number },{ "2", value_type::number } }
		}), "Values");

		auto ret2 = dictionary_funcs::function(state, 0, {1});
		AssertEqual(ret2, 0, "Return value");
		AssertEqual(new_index, 4, "New index");
		AssertEqual(new_tree.src, (tree_src_t{
			{1},{ 2, 3 },{},{}
		}), "New tree");
		AssertEqual(values, (values_t{
			{ { "foo", value_type::func_name },{ "+", value_type::func_name },{ "1", value_type::number },{ "2", value_type::number } }
		}), "Values");
	}
}

inline void test_basic_interface() {
	{
		values_t values;
		call_tree_t new_tree;
		unsigned int new_index = 0;
		index_reference_t index_reference;
		translate_state_t state = {
			{},{}, 0, values, new_tree, new_index, index_reference
		};

		using namespace dictionary_funcs;

		auto ret = function(state, function_name(state, "foo"), {
			number(state, "1"),
			number(state, "2"),
		});
		AssertEqual(ret, 2, "Return value");
		AssertEqual(new_index, 3, "New index");
		AssertEqual(new_tree.src, (tree_src_t{
			{},{},{ 0, 1 }
		}), "New tree");
		AssertEqual(values, (values_t{
			{ "1", value_type::number },{ "2", value_type::number } ,{ "foo", value_type::func_name }
		}), "Values");
	}
	{
		values_t values;
		call_tree_t new_tree;
		unsigned int new_index = 0;
		index_reference_t index_reference;
		translate_state_t state = {
			{},{}, 0, values, new_tree, new_index, index_reference
		};

		using namespace dictionary_funcs;

		auto ret = function(state, function_name(state, "foo"), {
			function(state, function_name(state, "+"), {
				number(state, "1"),
				number(state, "2")
			})
		});
		AssertEqual(ret, 3, "Return value");
		AssertEqual(new_index, 4, "New index");
		AssertEqual(new_tree.src, (tree_src_t{
			{},{}, { 0, 1 },{2}
		}), "New tree");
		AssertEqual(values, (values_t{
			{ "1", value_type::number },{ "2", value_type::number },{ "+", value_type::func_name },{ "foo", value_type::func_name }
		}), "Values");
	}
}

void run_dictionary_funcs_tests() {
    TESTCASE
    test_copy_basic_function();
	test_copy_nested_functions();
	test_value_functions();
	test_add_function_function();
	test_basic_interface();
}