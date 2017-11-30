#include <iostream>
#include "test.hpp"
#include "translator_methods.hpp"
#include "dictionary_methods.hpp"
#include "dictionary_funcs.hpp"
#include "value_methods.hpp"

using namespace cuttle;

inline void test_translates_basic_function_call() {
	dictionary_t dictionary;
	add(dictionary, "plus", 2, [](translate_state_t& state) {
		auto i = dictionary_funcs::copy(state);
		state.values[i].value = "+";
		return i;
	});
	add(dictionary, "-", 2, [](translate_state_t& state) {
		auto i = dictionary_funcs::copy(state);
		state.values[i].value = "minus";
		return i;
	});

	translator_t translator = { { "mylang1", 1 }, { "mylang2", 1 }, dictionary };

	{
		tokens_t tokens = {
			{ token_type::number, "1", 0, 0 },
			{ token_type::atom, "plus", 0, 0 },
			{ token_type::number, "2", 0, 0 }
		};
		call_tree_t tree = { {
			{}, {0, 2}, {}
		} };
		values_t values;
		call_tree_t new_tree;
		translate(translator, tokens, tree, values, new_tree);
		AssertEqual(new_tree.src, (tree_src_t{
			{1, 2}, {}, {}
		}), "New tree");
		AssertEqual(values, (values_t{
			{"+", value_type::func_name}, {"1", value_type::number}, {"2", value_type::number}
		}), "Values");
	}
	{
		tokens_t tokens = {
			{ token_type::atom, "plus", 0, 0 },
			{ token_type::number, "1", 0, 0 },
			{ token_type::number, "2", 0, 0 }
		};
		call_tree_t tree = { {
			{ 1, 2 }, {},{}
		} };
		values_t values;
		call_tree_t new_tree;
		translate(translator, tokens, tree, values, new_tree);
		AssertEqual(new_tree.src, (tree_src_t{
			{ 1, 2 },{},{}
		}), "New tree");
		AssertEqual(values, (values_t{
			{ "+", value_type::func_name },{ "1", value_type::number },{ "2", value_type::number }
		}), "Values");
	}
	{
		tokens_t tokens = {
			{ token_type::number, "1", 0, 0 },
			{ token_type::atom, "-", 0, 0 },
			{ token_type::number, "2", 0, 0 }
		};
		call_tree_t tree = { {
			{},{ 0, 2 },{}
		} };
		values_t values;
		call_tree_t new_tree;
		translate(translator, tokens, tree, values, new_tree);
		AssertEqual(new_tree.src, (tree_src_t{
			{ 1, 2 },{},{}
		}), "New tree");
		AssertEqual(values, (values_t{
			{ "minus", value_type::func_name },{ "1", value_type::number },{ "2", value_type::number }
		}), "Values");
	}
	{
		tokens_t tokens = {
			{ token_type::atom, "-", 0, 0 },
			{ token_type::number, "1", 0, 0 },
			{ token_type::number, "2", 0, 0 }
		};
		call_tree_t tree = { {
			{ 1, 2 },{},{}
		} };
		values_t values;
		call_tree_t new_tree;
		translate(translator, tokens, tree, values, new_tree);
		AssertEqual(new_tree.src, (tree_src_t{
			{ 1, 2 },{},{}
		}), "New tree");
		AssertEqual(values, (values_t{
			{ "minus", value_type::func_name },{ "1", value_type::number },{ "2", value_type::number }
		}), "Values");
	}
	{
		tokens_t tokens = {
			{ token_type::atom, "foo", 0, 0 },
			{ token_type::number, "1", 0, 0 },
			{ token_type::number, "2", 0, 0 }
		};
		call_tree_t tree = { {
			{ 1, 2 },{},{}
			} };
		values_t values;
		call_tree_t new_tree;
		translate(translator, tokens, tree, values, new_tree);
		AssertEqual(new_tree.src, (tree_src_t{
			{ 1, 2 },{},{}
		}), "New tree");
		AssertEqual(values, (values_t{
			{ "foo", value_type::func_name },{ "1", value_type::number },{ "2", value_type::number }
		}), "Values");
	}
}

inline void test_translates_nested_function_call() {
	dictionary_t dictionary;
	add(dictionary, "plus", 2, [](translate_state_t& state) {
		auto i = dictionary_funcs::copy(state);
		state.values[i].value = "+";
		return i;
	});
	add(dictionary, "-", 2, [](translate_state_t& state) {
		auto i = dictionary_funcs::copy(state);
		state.values[i].value = "minus";
		return i;
	});

	translator_t translator = { { "mylang1", 1 },{ "mylang2", 1 }, dictionary };

	{
		tokens_t tokens = {
			{ token_type::number, "1", 0, 0 },
			{ token_type::atom, "plus", 0, 0 },
			{ token_type::number, "2", 0, 0 },
			{ token_type::atom, "-", 0, 0 },
			{ token_type::number, "3", 0, 0 }
		};
		call_tree_t tree = { {
			{},{ 0, 2 },{},
			{1, 4},{}
			} };
		values_t values;
		call_tree_t new_tree;
		translate(translator, tokens, tree, values, new_tree);
		AssertEqual(new_tree.src, (tree_src_t{
			{ 1, 2 },{},{},
			{0, 4},{}
		}), "New tree");
		AssertEqual(values, (values_t{
			{ "+", value_type::func_name },{ "1", value_type::number },{ "2", value_type::number },
			{ "minus", value_type::func_name }, { "3", value_type::number }
		}), "Values");
	}
	{
		tokens_t tokens = {
			{ token_type::atom, "foo", 0, 0 },
			{ token_type::number, "1", 0, 0 },
			{ token_type::atom, "plus", 0, 0 },
			{ token_type::number, "2", 0, 0 },
			{ token_type::atom, "-", 0, 0 },
			{ token_type::number, "3", 0, 0 }
		};
		call_tree_t tree = { {
			{4}, {}, { 1, 3 },{},
			{ 2, 5 },{}
			} };
		values_t values;
		call_tree_t new_tree;
		translate(translator, tokens, tree, values, new_tree);
		AssertEqual(new_tree.src, (tree_src_t{
			{1}, { 2, 5 }, {3, 4}, {},
			{},{}
		}), "New tree");
		AssertEqual(values, (values_t{
			{"foo", value_type::func_name },
			{ "minus", value_type::func_name },
			{ "+", value_type::func_name },
			{ "1", value_type::number },{ "2", value_type::number },{ "3", value_type::number }
		}), "Values");
	}
}

void run_translator_tests() {
	TESTCASE
	test_translates_basic_function_call();
	test_translates_nested_function_call();
}