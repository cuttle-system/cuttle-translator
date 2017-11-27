#include <iostream>
#include "test.hpp"
#include "translator.hpp"

using namespace cuttle;

inline void test_translates_basic_function_call() {
	dictionary_t dictionary;
	add(dictionary, "plus", 2, [](TRANSLATE_FUNCTION_ARGS) {
		auto i = dictionary_funcs::copy(TRANSLATE_FUNCTION_ARGS_NO_TYPE);
		values[i].value = "+";
		return i;
	});
	add(dictionary, "-", 2, [](TRANSLATE_FUNCTION_ARGS) {
		auto i = dictionary_funcs::copy(TRANSLATE_FUNCTION_ARGS_NO_TYPE);
		values[i].value = "minus";
		return i;
	});

	translator_t translator = { { "mylang1", 1 }, { "mylang2", 1 }, dictionary };

	{
		tokens_t tokens = {
			{ NUMBER_TOKEN, "1", 0, 0 },
			{ ATOM_TOKEN, "plus", 0, 0 },
			{ NUMBER_TOKEN, "2", 0, 0 }
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
			{"+", TYPE_FUNCTION_NAME}, {"1", TYPE_NUMBER}, {"2", TYPE_NUMBER}
		}), "Values");
	}
	{
		tokens_t tokens = {
			{ ATOM_TOKEN, "plus", 0, 0 },
			{ NUMBER_TOKEN, "1", 0, 0 },
			{ NUMBER_TOKEN, "2", 0, 0 }
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
			{ "+", TYPE_FUNCTION_NAME },{ "1", TYPE_NUMBER },{ "2", TYPE_NUMBER }
		}), "Values");
	}
	{
		tokens_t tokens = {
			{ NUMBER_TOKEN, "1", 0, 0 },
			{ ATOM_TOKEN, "-", 0, 0 },
			{ NUMBER_TOKEN, "2", 0, 0 }
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
			{ "minus", TYPE_FUNCTION_NAME },{ "1", TYPE_NUMBER },{ "2", TYPE_NUMBER }
		}), "Values");
	}
	{
		tokens_t tokens = {
			{ ATOM_TOKEN, "-", 0, 0 },
			{ NUMBER_TOKEN, "1", 0, 0 },
			{ NUMBER_TOKEN, "2", 0, 0 }
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
			{ "minus", TYPE_FUNCTION_NAME },{ "1", TYPE_NUMBER },{ "2", TYPE_NUMBER }
		}), "Values");
	}
	{
		tokens_t tokens = {
			{ ATOM_TOKEN, "foo", 0, 0 },
			{ NUMBER_TOKEN, "1", 0, 0 },
			{ NUMBER_TOKEN, "2", 0, 0 }
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
			{ "foo", TYPE_FUNCTION_NAME },{ "1", TYPE_NUMBER },{ "2", TYPE_NUMBER }
		}), "Values");
	}
}

inline void test_translates_nested_function_call() {
	dictionary_t dictionary;
	add(dictionary, "plus", 2, [](TRANSLATE_FUNCTION_ARGS) {
		auto i = dictionary_funcs::copy(TRANSLATE_FUNCTION_ARGS_NO_TYPE);
		values[i].value = "+";
		return i;
	});
	add(dictionary, "-", 2, [](TRANSLATE_FUNCTION_ARGS) {
		auto i = dictionary_funcs::copy(TRANSLATE_FUNCTION_ARGS_NO_TYPE);
		values[i].value = "minus";
		return i;
	});

	translator_t translator = { { "mylang1", 1 },{ "mylang2", 1 }, dictionary };

	{
		tokens_t tokens = {
			{ NUMBER_TOKEN, "1", 0, 0 },
			{ ATOM_TOKEN, "plus", 0, 0 },
			{ NUMBER_TOKEN, "2", 0, 0 },
			{ ATOM_TOKEN, "-", 0, 0 },
			{ NUMBER_TOKEN, "3", 0, 0 }
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
			{ "+", TYPE_FUNCTION_NAME },{ "1", TYPE_NUMBER },{ "2", TYPE_NUMBER },
			{ "minus", TYPE_FUNCTION_NAME }, { "3", TYPE_NUMBER }
		}), "Values");
	}
	{
		tokens_t tokens = {
			{ ATOM_TOKEN, "foo", 0, 0 },
			{ NUMBER_TOKEN, "1", 0, 0 },
			{ ATOM_TOKEN, "plus", 0, 0 },
			{ NUMBER_TOKEN, "2", 0, 0 },
			{ ATOM_TOKEN, "-", 0, 0 },
			{ NUMBER_TOKEN, "3", 0, 0 }
		};
		call_tree_t tree = { {
			{2}, {}, { 1, 3 },{},
			{ 2, 4 },{}
			} };
		values_t values;
		call_tree_t new_tree;
		translate(translator, tokens, tree, values, new_tree);
		AssertEqual(new_tree.src, (tree_src_t{
			{2}, { 2, 3 }, {}, {},
			{ 1, 5 },{}
		}), "New tree");
		AssertEqual(values, (values_t{
			{"foo", TYPE_FUNCTION_NAME },
			{ "+", TYPE_FUNCTION_NAME },{ "1", TYPE_NUMBER },{ "2", TYPE_NUMBER },
			{ "minus", TYPE_FUNCTION_NAME },{ "3", TYPE_NUMBER }
		}), "Values");
	}
}

void run_translator_tests() {
	TESTCASE
	test_translates_basic_function_call();
	test_translates_nested_function_call();
}