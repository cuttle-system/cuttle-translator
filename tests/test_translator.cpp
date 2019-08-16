#define BOOST_TEST_DYN_LINK

#include <iostream>
#include <boost/test/unit_test.hpp>
#include "translator_methods.hpp"
#include "dictionary_methods.hpp"
#include "dictionary_funcs.hpp"
#include "value_methods.hpp"

using namespace cuttle;

struct translates_basic_function_call_suite_fixture {
    translator_t translator = {{"mylang1", 1},
                               {"mylang2", 1},
                               {}};
    values_t values;
    call_tree_t new_tree;

    void setup() {
        initialize(translator.dictionary);
        add(translator.dictionary,
            call_tree_t{{{1u, 2u}, {}, {}, {0}}},
            tokens_t{{token_type::atom,    "plus"},
                     {token_type::macro_p, "_a"},
                     {token_type::macro_p, "_b"}},
            [](translate_state_t &state) {
                        auto func_i = dictionary_funcs::function_name(state, "+");
                        auto a_i = dictionary_funcs::parameter(state, "_a");
                        auto b_i = dictionary_funcs::parameter(state, "_b");
                        return dictionary_funcs::function(state, func_i, {a_i, b_i});
                    });
        add(translator.dictionary,
            call_tree_t{{{1u, 2u}, {}, {}, {0}}},
            tokens_t{{token_type::atom,    "-"},
                     {token_type::macro_p, "_a"},
                     {token_type::macro_p, "_b"}},
            [](translate_state_t &state) {
                        auto func_i = dictionary_funcs::function_name(state, "minus");
                        auto a_i = dictionary_funcs::parameter(state, "_b");
                        auto b_i = dictionary_funcs::parameter(state, "_a");
                        return dictionary_funcs::function(state, func_i, {a_i, b_i});
                    });
    }
};

BOOST_FIXTURE_TEST_SUITE(translates_basic_function_call_suite, translates_basic_function_call_suite_fixture)

    BOOST_AUTO_TEST_CASE(case1) {
        tokens_t tokens = {
                {token_type::number, "1",    0, 0},
                {token_type::atom,   "plus", 0, 0},
                {token_type::number, "2",    0, 0}
        };
        call_tree_t tree = {{
                                    {}, {0, 2}, {}, {1}
                            }};
        translate(translator, tokens, tree, values, new_tree);
        BOOST_CHECK(new_tree.src == (tree_src_t{
                {1, 2},
                {},
                {},
                {0}
        }));
        BOOST_CHECK(values == (values_t{
                {"+", value_type::func_name},
                {"1", value_type::number},
                {"2", value_type::number}
        }));
    }

    BOOST_AUTO_TEST_CASE(case2) {
        tokens_t tokens = {
                {token_type::atom,   "plus", 0, 0},
                {token_type::number, "1",    0, 0},
                {token_type::number, "2",    0, 0}
        };
        call_tree_t tree = {{
                                    {1, 2}, {}, {}, {0}
                            }};
        translate(translator, tokens, tree, values, new_tree);
        BOOST_CHECK(new_tree.src == (tree_src_t{
                {1, 2},
                {},
                {},
                {0}
        }));
        BOOST_CHECK(values == (values_t{
                {"+", value_type::func_name},
                {"1", value_type::number},
                {"2", value_type::number}
        }));
    }

    BOOST_AUTO_TEST_CASE(case3) {
        tokens_t tokens = {
                {token_type::number, "1", 0, 0},
                {token_type::atom,   "-", 0, 0},
                {token_type::number, "2", 0, 0}
        };
        call_tree_t tree = {{
                                    {}, {0, 2}, {}, {1}
                            }};
        translate(translator, tokens, tree, values, new_tree);
        BOOST_CHECK(new_tree.src == (tree_src_t{
                {1, 2},
                {},
                {},
                {0}
        }));
        BOOST_CHECK(values == (values_t{
                {"minus", value_type::func_name},
                {"2",     value_type::number},
                {"1",     value_type::number}
        }));
    }

    BOOST_AUTO_TEST_CASE(case4) {
		tokens_t tokens = {
			{ token_type::atom, "-", 0, 0 },
			{ token_type::number, "1", 0, 0 },
			{ token_type::number, "2", 0, 0 }
		};
		call_tree_t tree = { {
			{ 1, 2 },{},{}, {0}
		} };
		translate(translator, tokens, tree, values, new_tree);
		BOOST_CHECK(new_tree.src == (tree_src_t{
			{ 1, 2 },{},{}, {0}
		}));
		BOOST_CHECK(values == (values_t{
			{ "minus", value_type::func_name },{ "2", value_type::number },{ "1", value_type::number }
		}));
	}

    BOOST_AUTO_TEST_CASE(case5) {
		tokens_t tokens = {
			{ token_type::atom, "foo", 0, 0 },
			{ token_type::number, "1", 0, 0 },
			{ token_type::number, "2", 0, 0 }
		};
		call_tree_t tree = { {
			{ 1, 2 },{},{}, {0}
			} };
		translate(translator, tokens, tree, values, new_tree);
		BOOST_CHECK(new_tree.src == (tree_src_t{
			{ 1, 2 },{},{}, {0}
		}));
		BOOST_CHECK(values == (values_t{
			{ "foo", value_type::func_name },{ "1", value_type::number },{ "2", value_type::number }
		}));
	}

BOOST_AUTO_TEST_SUITE_END()

struct translates_nested_function_call_suite_fixture {
    translator_t translator = {{ "mylang1", 1 },{ "mylang2", 1 }, {}};
    values_t values;
    call_tree_t new_tree;

    void setup() {
        initialize(translator.dictionary);
        add(translator.dictionary,
            call_tree_t{{{1u, 2u}, {}, {}, {0}}},
            tokens_t{{token_type::atom,    "plus"},
                     {token_type::macro_p, "_a"},
                     {token_type::macro_p, "_b"}},
            [](translate_state_t &state) {
                        auto func_i = dictionary_funcs::function_name(state, "+");
                        auto a_i = dictionary_funcs::parameter(state, "_a");
                        auto b_i = dictionary_funcs::parameter(state, "_b");
                        return dictionary_funcs::function(state, func_i, {a_i, b_i});
                    });
        add(translator.dictionary,
            call_tree_t{{{1u, 2u}, {}, {}, {0}}},
            tokens_t{{token_type::atom,    "-"},
                     {token_type::macro_p, "_a"},
                     {token_type::macro_p, "_b"}},
            [](translate_state_t &state) {
                        auto func_i = dictionary_funcs::function_name(state, "minus");
                        auto a_i = dictionary_funcs::parameter(state, "_b");
                        auto b_i = dictionary_funcs::parameter(state, "_a");
                        return dictionary_funcs::function(state, func_i, {a_i, b_i});
                    });
    }
};

BOOST_FIXTURE_TEST_SUITE(translates_nested_function_call_suite, translates_nested_function_call_suite_fixture)

    BOOST_AUTO_TEST_CASE(case1) {
		tokens_t tokens = {
			{ token_type::number, "1", 0, 0 },
			{ token_type::atom, "plus", 0, 0 },
			{ token_type::number, "2", 0, 0 },
			{ token_type::atom, "-", 0, 0 },
			{ token_type::number, "3", 0, 0 }
		};
		call_tree_t tree = { {
			{},{ 0, 2 },{},
			{1, 4},{}, {3}
			} };
		translate(translator, tokens, tree, values, new_tree);
		BOOST_CHECK(new_tree.src == (tree_src_t{
			{ 1, 2 },
            {},
			{3, 4},{},{},
			{0}
		}));
		BOOST_CHECK(values == (values_t{
		    { "minus", value_type::func_name },
			{ "3", value_type::number },
			{ "+", value_type::func_name },{ "1", value_type::number },{ "2", value_type::number }
		}));
	}

    BOOST_AUTO_TEST_CASE(case2) {
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
			{ 2, 5 },{}, {0}
			} };
		translate(translator, tokens, tree, values, new_tree);
		BOOST_CHECK(new_tree.src == (tree_src_t{
			{1}, { 2, 3 }, {}, {4, 5}, {},
			{},{0}
		}));
		BOOST_CHECK(values == (values_t{
			{"foo", value_type::func_name },
			{ "minus", value_type::func_name },
			{ "3", value_type::number },
			{ "+", value_type::func_name },
			{ "1", value_type::number },{ "2", value_type::number }
		}));
	}

BOOST_AUTO_TEST_SUITE_END()

struct translates_wildcard_function_call_suite_fixture {
    translator_t translator = { { "mylang1", 1 },{ "mylang2", 1 }, {}};
    values_t values;
    call_tree_t new_tree;

    void setup() {
        initialize(translator.dictionary);
        add(translator.dictionary,
            call_tree_t{{{}, {0}}},
            tokens_t{{token_type::macro_pva, "_func"}}, [](translate_state_t &state) {
                    namespace df = dictionary_funcs;

                    unsigned int i;
                    if (state.index_reference.find(state.index) != state.index_reference.end()) {
                        i = state.index_reference[state.index];
                        state.values[i] = {"any_function_here", value_type::func_name};
                    } else {
                        i = df::function_name(state, "any_function_here");
                    }

                    df::function(state, i, {});
                    return i;
                });
        add(translator.dictionary,
            call_tree_t{{{1u, 2u}, {}, {}, {0}}},
            tokens_t{{token_type::atom,    "+"},
                     {token_type::macro_p, "_a"},
                     {token_type::macro_p, "_b"}},
            [](translate_state_t &state) {
                        auto func_i = dictionary_funcs::function_name(state, "+");
                        auto a_i = dictionary_funcs::parameter(state, "_a");
                        auto b_i = dictionary_funcs::parameter(state, "_b");
                        return dictionary_funcs::function(state, func_i, {a_i, b_i});
                    });
        add(translator.dictionary,
            call_tree_t{{{1u, 2u}, {}, {}, {0}}},
            tokens_t{{token_type::atom,    "-"},
                     {token_type::macro_p, "_a"},
                     {token_type::macro_p, "_b"}},
            [](translate_state_t &state) {
                        auto func_i = dictionary_funcs::function_name(state, "minus");
                        auto a_i = dictionary_funcs::parameter(state, "_a");
                        auto b_i = dictionary_funcs::parameter(state, "_b");
                        return dictionary_funcs::function(state, func_i, {a_i, b_i});
                    });
    }
};

BOOST_FIXTURE_TEST_SUITE(translates_wildcard_function_call_suite, translates_wildcard_function_call_suite_fixture)

    BOOST_AUTO_TEST_CASE(case1) {
        tokens_t tokens = {
                { token_type::number, "2", 0, 0 },
                { token_type::atom, "*", 0, 0 },
                { token_type::number, "3", 0, 0 },
                { token_type::atom, "/", 0, 0 },
                { token_type::number, "3", 0, 0 }
        };
        call_tree_t tree = { {
                                     {},{ 0, 3 },{},
                                     {2, 4}, {}, {1}
                             } };
        translate(translator, tokens, tree, values, new_tree);
        BOOST_CHECK(new_tree.src == (tree_src_t{
                {}, {0}
        }));
        BOOST_CHECK(values == (values_t{
                { "any_function_here", value_type::func_name },
        }));
    }

    BOOST_AUTO_TEST_CASE(case2) {
        tokens_t tokens = {
                { token_type::number, "2", 0, 0 },
                { token_type::atom, "-", 0, 0 },
                { token_type::number, "3", 0, 0 },
                { token_type::atom, "+", 0, 0 },
                { token_type::number, "3", 0, 0 }
        };
        call_tree_t tree = { {
                                     {},{ 0, 3 },{},
                                     {2, 4}, {}, {1}
                             } };
        translate(translator, tokens, tree, values, new_tree);
        BOOST_CHECK(new_tree.src == (tree_src_t{
                { 1, 2 }, {},
                { 3, 4 }, {}, {}, {0}
        }));
        BOOST_CHECK(values == (values_t{
                { "minus", value_type::func_name },{ "2", value_type::number },
                { "+", value_type::func_name }, { "3", value_type::number }, { "3", value_type::number }
        }));
    }

    BOOST_AUTO_TEST_CASE(case3) {
        tokens_t tokens = {
                { token_type::number, "2", 0, 0 },
                { token_type::atom, "-", 0, 0 },
                { token_type::number, "3", 0, 0 },
                { token_type::atom, "/", 0, 0 },
                { token_type::number, "3", 0, 0 }
        };
        call_tree_t tree = { {
                                     {},{ 0, 3 },{},
                                     {2, 4}, {}, {1}
                             } };
        translate(translator, tokens, tree, values, new_tree);
        BOOST_CHECK(new_tree.src == (tree_src_t{
                { 1, 2 }, {}, {}, {0}
        }));
        BOOST_CHECK(values == (values_t{
                { "minus", value_type::func_name },{ "2", value_type::number },
                { "any_function_here", value_type::func_name }
        }));
    }

    BOOST_AUTO_TEST_CASE(case4) {
        tokens_t tokens = {
                { token_type::number, "2", 0, 0 },
                { token_type::atom, "/", 0, 0 },
                { token_type::number, "1", 0, 0 },
                { token_type::atom, "+", 0, 0 },
                { token_type::number, "3", 0, 0 }
        };
        call_tree_t tree = { {
                                     {},{ 0, 3 },{},
                                     {2, 4}, {}, {1}
                             } };
        translate(translator, tokens, tree, values, new_tree);
        BOOST_CHECK(new_tree.src == (tree_src_t{
            {}, {0}
        }));
        BOOST_CHECK(values == (values_t{
                { "any_function_here", value_type::func_name }
        }));
    }

BOOST_AUTO_TEST_SUITE_END()