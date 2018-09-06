#define BOOST_TEST_DYN_LINK

#include <iostream>
#include <boost/test/unit_test.hpp>
#include "dictionary_methods.hpp"
#include "dictionary_funcs.hpp"
#include "value_methods.hpp"

using namespace cuttle;

struct copy_return_values_fixture {
    values_t values;
    call_tree_t new_tree;
    index_reference_t index_reference;
};

BOOST_FIXTURE_TEST_SUITE(copy_basic_function_suite, copy_return_values_fixture)

    BOOST_AUTO_TEST_CASE(case1) {
		tokens_t tokens = {
			{ token_type::number, "1", 0, 0 },
			{ token_type::atom, "plus", 0, 0 },
			{ token_type::number, "2", 0, 0 }
		};
		call_tree_t tree = { {
			{},{ 0, 2 },{}
			} };
		unsigned int new_index = 0;
		translate_state_t state = {
			tokens, tree, 1, values, new_tree, new_index, index_reference
		};
		auto ret = dictionary_funcs::copy(state);
		BOOST_CHECK_EQUAL(ret, 0u);
		BOOST_CHECK_EQUAL(new_index, 3u);
		BOOST_CHECK(new_tree.src == (tree_src_t{
			{ 1, 2 },{},{}
		}));
		BOOST_CHECK(values == (values_t{
			{ "plus", value_type::func_name },{ "1", value_type::number },{ "2", value_type::number }
		}));
		BOOST_CHECK(index_reference.find(0) != index_reference.end());
		BOOST_CHECK(index_reference.find(1) != index_reference.end());
		BOOST_CHECK(index_reference.find(2) != index_reference.end());
		BOOST_CHECK_EQUAL(index_reference[0], 1u);
		BOOST_CHECK_EQUAL(index_reference[1], 0u);
		BOOST_CHECK_EQUAL(index_reference[2], 2u);
	}


    BOOST_AUTO_TEST_CASE(case2) {
		tokens_t tokens = {
			{ token_type::atom, "-", 0, 0 },
			{ token_type::number, "1", 0, 0 },
			{ token_type::number, "2", 0, 0 }
		};
		call_tree_t tree = { {
			{ 1, 2 }, {}, {}
			} };
		unsigned int new_index = 0;
		translate_state_t state = {
			tokens, tree, 0, values, new_tree, new_index, index_reference
		};
		auto ret = dictionary_funcs::copy(state);
		BOOST_CHECK_EQUAL(ret, 0u);
		BOOST_CHECK_EQUAL(new_index, 3u);
		BOOST_CHECK(new_tree.src == (tree_src_t{
			{ 1, 2 },{},{}
		}));
		BOOST_CHECK(values == (values_t{
			{ "-", value_type::func_name },{ "1", value_type::number },{ "2", value_type::number }
		}));
		BOOST_CHECK(index_reference.find(0) != index_reference.end());
		BOOST_CHECK(index_reference.find(1) != index_reference.end());
		BOOST_CHECK(index_reference.find(2) != index_reference.end());
		BOOST_CHECK_EQUAL(index_reference[0], 0u);
		BOOST_CHECK_EQUAL(index_reference[1], 1u);
		BOOST_CHECK_EQUAL(index_reference[2], 2u);
	}

    BOOST_AUTO_TEST_CASE(case3) {
		tokens_t tokens = {
			{ token_type::number, "5", 0, 0 },
			{ token_type::atom, "!", 0, 0 }
		};
		call_tree_t tree = { {
			{},{0}
			} };
		unsigned int new_index = 0;
		translate_state_t state = {
			tokens, tree, 1, values, new_tree, new_index, index_reference
		};
		auto ret = dictionary_funcs::copy(state);
		BOOST_CHECK_EQUAL(ret, 0u);
		BOOST_CHECK_EQUAL(new_index, 2u);
		BOOST_CHECK(new_tree.src == (tree_src_t{
			{ 1 },{}
		}));
		BOOST_CHECK(values == (values_t{
			{ "!", value_type::func_name },{ "5", value_type::number }
		}));
		BOOST_CHECK(index_reference.find(0) != index_reference.end());
		BOOST_CHECK(index_reference.find(1) != index_reference.end());
		BOOST_CHECK_EQUAL(index_reference[0], 1u);
		BOOST_CHECK_EQUAL(index_reference[1], 0u);
	}

    BOOST_AUTO_TEST_CASE(case4) {
		tokens_t tokens = {
			{ token_type::atom, "concat", 0, 0 },
			{ token_type::number, "5", 0, 0 },
			{ token_type::string, "value", 0, 0 }
		};
		call_tree_t tree = { {
			{ 1, 2 }, {}, {}
			} };
		unsigned int new_index = 0;
		translate_state_t state = {
			tokens, tree, 0, values, new_tree, new_index, index_reference
		};
		auto ret = dictionary_funcs::copy(state);
		BOOST_CHECK_EQUAL(ret, 0u);
		BOOST_CHECK_EQUAL(new_index, 3u);
		BOOST_CHECK(new_tree.src == (tree_src_t{
			{ 1, 2 }, {}, {}
		}));
		BOOST_CHECK(values == (values_t{
			{ "concat", value_type::func_name }, { "5", value_type::number }, { "value", value_type::string }
		}));
		BOOST_CHECK(index_reference.find(0) != index_reference.end());
		BOOST_CHECK(index_reference.find(1) != index_reference.end());
		BOOST_CHECK(index_reference.find(2) != index_reference.end());
		BOOST_CHECK_EQUAL(index_reference[0], 0u);
		BOOST_CHECK_EQUAL(index_reference[1], 1u);
		BOOST_CHECK_EQUAL(index_reference[2], 2u);
	}

BOOST_AUTO_TEST_SUITE_END()

BOOST_FIXTURE_TEST_SUITE(copy_nested_functions_suite, copy_return_values_fixture)

    BOOST_AUTO_TEST_CASE(case1) {
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
		unsigned int new_index = 0;
		translate_state_t state = {
			tokens, tree, 3, values, new_tree, new_index, index_reference
		};

		auto ret1 = dictionary_funcs::copy(state);
		BOOST_CHECK_EQUAL(ret1, 0u);
		BOOST_CHECK_EQUAL(new_index, 3u);
		BOOST_CHECK(new_tree.src == (tree_src_t{
			{ 1, 2 },{},{}
		}));
		BOOST_CHECK(values == (values_t{
			{ "-", value_type::func_name },{ "+", value_type::func_name },{ "3", value_type::number }
		}));
		BOOST_CHECK(index_reference.find(0) == index_reference.end());
		BOOST_CHECK(index_reference.find(1) != index_reference.end());
		BOOST_CHECK(index_reference.find(2) == index_reference.end());
		BOOST_CHECK(index_reference.find(3) != index_reference.end());
		BOOST_CHECK(index_reference.find(4) != index_reference.end());
		BOOST_CHECK_EQUAL(index_reference[1], 1u);
		BOOST_CHECK_EQUAL(index_reference[3], 0u);
		BOOST_CHECK_EQUAL(index_reference[4], 2u);

		state.index = 1;
		auto ret2 = dictionary_funcs::copy(state);
		BOOST_CHECK_EQUAL(ret2, 1u);
		BOOST_CHECK_EQUAL(new_index, 5u);
		BOOST_CHECK(new_tree.src == (tree_src_t{
			{ 1, 2 },{ 3, 4 },{},{},{}
		}));
		BOOST_CHECK(values == (values_t{
			{ "-", value_type::func_name }, { "+", value_type::func_name },{ "3", value_type::number },{ "1", value_type::number },{ "2", value_type::number }
		}));
		BOOST_CHECK(index_reference.find(0) != index_reference.end());
		BOOST_CHECK(index_reference.find(1) != index_reference.end());
		BOOST_CHECK(index_reference.find(2) != index_reference.end());
		BOOST_CHECK(index_reference.find(3) != index_reference.end());
		BOOST_CHECK(index_reference.find(4) != index_reference.end());
		BOOST_CHECK_EQUAL(index_reference[0], 3u);
		BOOST_CHECK_EQUAL(index_reference[1], 1u);
		BOOST_CHECK_EQUAL(index_reference[2], 4u);
		BOOST_CHECK_EQUAL(index_reference[3], 0u);
		BOOST_CHECK_EQUAL(index_reference[4], 2u);
	}

BOOST_AUTO_TEST_SUITE_END()


BOOST_FIXTURE_TEST_SUITE(value_functions_suite, copy_return_values_fixture)

    BOOST_AUTO_TEST_CASE(case1) {
		unsigned int new_index = 0;
		translate_state_t state = {
			{},{}, 0, values, new_tree, new_index, index_reference
		};

		auto ret = dictionary_funcs::value(state, "1", value_type::number);
		BOOST_CHECK_EQUAL(ret, 0u);
		BOOST_CHECK_EQUAL(new_index, 1u);
		BOOST_CHECK(new_tree.src == (tree_src_t{
			{}
		}));
		BOOST_CHECK(values == (values_t{
			{ "1", value_type::number }
		}));
	}

    BOOST_AUTO_TEST_CASE(case2) {
		unsigned int new_index = 0;
		translate_state_t state = {
			{},{}, 0, values, new_tree, new_index, index_reference
		};

		auto ret1 = dictionary_funcs::value(state, "1", value_type::number);
		BOOST_CHECK_EQUAL(ret1, 0u);
		BOOST_CHECK_EQUAL(new_index, 1u);
		BOOST_CHECK(new_tree.src == (tree_src_t{
			{}
		}));
		BOOST_CHECK(values == (values_t{
			{ "1", value_type::number }
		}));

		auto ret2 = dictionary_funcs::value(state, "foo", value_type::func_name);
		BOOST_CHECK_EQUAL(ret2, 1u);
		BOOST_CHECK_EQUAL(new_index, 2u);
		BOOST_CHECK(new_tree.src == (tree_src_t{
			{},{}
		}));
		BOOST_CHECK(values == (values_t{
			{ "1", value_type::number },{ "foo", value_type::func_name }
		}));
	}

    BOOST_AUTO_TEST_CASE(case3) {
		unsigned int new_index = 0;
		translate_state_t state = {
			{},{}, 0, values, new_tree, new_index, index_reference
		};

		auto ret1 = dictionary_funcs::number(state, "1");
		BOOST_CHECK_EQUAL(ret1, 0u);
		BOOST_CHECK_EQUAL(new_index, 1u);
		BOOST_CHECK(new_tree.src == (tree_src_t{
			{}
		}));
		BOOST_CHECK(values == (values_t{
			{ "1", value_type::number }
		}));

		auto ret2 = dictionary_funcs::function_name(state, "foo");
		BOOST_CHECK_EQUAL(ret2, 1u);
		BOOST_CHECK_EQUAL(new_index, 2u);
		BOOST_CHECK(new_tree.src == (tree_src_t{
			{},{}
		}));
		BOOST_CHECK(values == (values_t{
			{ "1", value_type::number },{ "foo", value_type::func_name }
		}));

		auto ret3 = dictionary_funcs::string(state, "foo bar");
		BOOST_CHECK_EQUAL(ret3, 2u);
		BOOST_CHECK_EQUAL(new_index, 3u);
		BOOST_CHECK(new_tree.src == (tree_src_t{
			{},{},{}
		}));
		BOOST_CHECK(values == (values_t{
			{ "1", value_type::number },{ "foo", value_type::func_name },{ "foo bar", value_type::string }
		}));
	}

BOOST_AUTO_TEST_SUITE_END()

struct index_reference_fixture {
    index_reference_t index_reference;
};

BOOST_FIXTURE_TEST_SUITE(add_function_suite, index_reference_fixture)

    BOOST_AUTO_TEST_CASE(case1) {
		values_t values = { {"foo", value_type::func_name},{ "1", value_type::number },{"2", value_type::number} };
		call_tree_t new_tree = { { {}, {}, {} } };
		unsigned int new_index = 3;
		translate_state_t state = {
			{},{}, 0, values, new_tree, new_index, index_reference
		};

		auto ret = dictionary_funcs::function(state, 0, { 1, 2 });
		BOOST_CHECK_EQUAL(ret, 0u);
		BOOST_CHECK_EQUAL(new_index, 3u);
		BOOST_CHECK(new_tree.src == (tree_src_t{
			{1, 2},{},{}
		}));
		BOOST_CHECK(values == (values_t{
			{ { "foo", value_type::func_name },{ "1", value_type::number },{ "2", value_type::number } }
		}));
	}

    BOOST_AUTO_TEST_CASE(case2) {
		values_t values = { {"foo", value_type::func_name}, { "+", value_type::func_name },{ "1", value_type::number },{ "2", value_type::number } };
		call_tree_t new_tree = { { {},{},{},{} } };
		unsigned int new_index = 4;
		translate_state_t state = {
			{},{}, 0, values, new_tree, new_index, index_reference
		};

		auto ret1 = dictionary_funcs::function(state, 1, {2, 3});
		BOOST_CHECK_EQUAL(ret1, 1u);
		BOOST_CHECK_EQUAL(new_index, 4u);
		BOOST_CHECK(new_tree.src == (tree_src_t{
			{},{2, 3},{},{}
		}));
		BOOST_CHECK(values == (values_t{
			{ { "foo", value_type::func_name },{ "+", value_type::func_name },{ "1", value_type::number },{ "2", value_type::number } }
		}));

		auto ret2 = dictionary_funcs::function(state, 0, {1});
		BOOST_CHECK_EQUAL(ret2, 0u);
		BOOST_CHECK_EQUAL(new_index, 4u);
		BOOST_CHECK(new_tree.src == (tree_src_t{
			{1},{ 2, 3 },{},{}
		}));
		BOOST_CHECK(values == (values_t{
			{ { "foo", value_type::func_name },{ "+", value_type::func_name },{ "1", value_type::number },{ "2", value_type::number } }
		}));
	}

BOOST_AUTO_TEST_SUITE_END()

BOOST_FIXTURE_TEST_SUITE(basic_interface_suite, copy_return_values_fixture)

    BOOST_AUTO_TEST_CASE(case1) {
		unsigned int new_index = 0;
		translate_state_t state = {
			{},{}, 0, values, new_tree, new_index, index_reference
		};

        namespace df = dictionary_funcs;

		auto ret = df::function(state, df::function_name(state, "foo"), {
			df::number(state, "1"),
			df::number(state, "2"),
		});
		BOOST_CHECK_EQUAL(ret, 2u);
		BOOST_CHECK_EQUAL(new_index, 3u);
		BOOST_CHECK(new_tree.src == (tree_src_t{
			{},{},{ 0, 1 }
		}));
		BOOST_CHECK(values == (values_t{
			{ "1", value_type::number },{ "2", value_type::number } ,{ "foo", value_type::func_name }
		}));
	}

    BOOST_AUTO_TEST_CASE(case2) {
		unsigned int new_index = 0;
		translate_state_t state = {
			{},{}, 0, values, new_tree, new_index, index_reference
		};

		namespace df = dictionary_funcs;

		auto ret = df::function(state, df::function_name(state, "foo"), {
			df::function(state, df::function_name(state, "+"), {
				df::number(state, "1"),
				df::number(state, "2")
			})
		});
		BOOST_CHECK_EQUAL(ret, 3u);
		BOOST_CHECK_EQUAL(new_index, 4u);
		BOOST_CHECK(new_tree.src == (tree_src_t{
			{},{}, { 0, 1 },{2}
		}));
		BOOST_CHECK(values == (values_t{
			{ "1", value_type::number },{ "2", value_type::number },{ "+", value_type::func_name },{ "foo", value_type::func_name }
		}));
	}

BOOST_AUTO_TEST_SUITE_END()