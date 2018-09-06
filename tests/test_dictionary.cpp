#define BOOST_TEST_DYN_LINK

#include <iostream>
#include <boost/test/unit_test.hpp>
#include "context_methods.hpp"
#include "dictionary_methods.hpp"

using namespace cuttle;

struct dictionary_fixture {
	dictionary_t dictionary;
};

BOOST_FIXTURE_TEST_SUITE(adds_entries_with_one_argument_suite, dictionary_fixture)

	BOOST_AUTO_TEST_CASE(case1) {
		translate_function_t *func = [](translate_state_t& state) { return 0u; };
		add(dictionary, "foo", 1, func);
		BOOST_CHECK_EQUAL(dictionary.size(), 1u);
		BOOST_CHECK(dictionary.find("foo") != dictionary.end());
		BOOST_CHECK_EQUAL(dictionary["foo"].size(), 1u);
		BOOST_CHECK(dictionary["foo"].find(1) != dictionary["foo"].end());
		BOOST_CHECK_EQUAL(dictionary["foo"][1], func);
	}

	BOOST_AUTO_TEST_CASE(case2) {
		translate_function_t *func = [](translate_state_t& state) { return 0u; };
		add(dictionary, "foo", 2, func);
		BOOST_CHECK_EQUAL(dictionary.size(), 1u);
		BOOST_CHECK(dictionary.find("foo") != dictionary.end());
		BOOST_CHECK_EQUAL(dictionary["foo"].size(), 1u);
		BOOST_CHECK(dictionary["foo"].find(2) != dictionary["foo"].end());
		BOOST_CHECK_EQUAL(dictionary["foo"][2], func);
	}

	BOOST_AUTO_TEST_CASE(case3) {
		translate_function_t *func = [](translate_state_t& state) { return 0u; };
		add(dictionary, "foo", 150, func);
		BOOST_CHECK_EQUAL(dictionary.size(), 1u);
		BOOST_CHECK(dictionary.find("foo") != dictionary.end());
		BOOST_CHECK_EQUAL(dictionary["foo"].size(), 1u);
		BOOST_CHECK(dictionary["foo"].find(150) != dictionary["foo"].end());
		BOOST_CHECK_EQUAL(dictionary["foo"][150], func);
	}

	BOOST_AUTO_TEST_CASE(case4) {
		translate_function_t *func1 = [](translate_state_t& state) { return 0u; };
		translate_function_t *func2 = [](translate_state_t& state) { return 0u; };
		add(dictionary, "foo", 150, func1);
		add(dictionary, "bar", 130, func2);
		BOOST_CHECK_EQUAL(dictionary.size(), 2u);
		BOOST_CHECK(dictionary.find("foo") != dictionary.end());
		BOOST_CHECK_EQUAL(dictionary["foo"].size(), 1u);
		BOOST_CHECK(dictionary["foo"].find(150) != dictionary["foo"].end());
		BOOST_CHECK_EQUAL(dictionary["foo"][150], func1);
		BOOST_CHECK(dictionary.find("bar") != dictionary.end());
		BOOST_CHECK_EQUAL(dictionary["bar"].size(), 1u);
		BOOST_CHECK(dictionary["bar"].find(130) != dictionary["bar"].end());
		BOOST_CHECK_EQUAL(dictionary["bar"][130], func2);
	}
BOOST_AUTO_TEST_SUITE_END()


BOOST_FIXTURE_TEST_SUITE(adds_entries_with_multiple_arguments_suite, dictionary_fixture)

	BOOST_AUTO_TEST_CASE(case1) {
		translate_function_t *func1 = [](translate_state_t& state) { return 0u; };
		translate_function_t *func2 = [](translate_state_t& state) { return 0u; };
		translate_function_t *func3 = [](translate_state_t& state) { return 0u; };
		add(dictionary, "foo", 1, func1);
		add(dictionary, "foo", 2, func2);
		add(dictionary, "foo", 3, func3);
		BOOST_CHECK_EQUAL(dictionary.size(), 1u);
		BOOST_CHECK(dictionary.find("foo") != dictionary.end());
		BOOST_CHECK_EQUAL(dictionary["foo"].size(), 3u);
		BOOST_CHECK(dictionary["foo"].find(1) != dictionary["foo"].end());
		BOOST_CHECK_EQUAL(dictionary["foo"][1], func1);
		BOOST_CHECK(dictionary["foo"].find(2) != dictionary["foo"].end());
		BOOST_CHECK_EQUAL(dictionary["foo"][2], func2);
		BOOST_CHECK(dictionary["foo"].find(3) != dictionary["foo"].end());
		BOOST_CHECK_EQUAL(dictionary["foo"][3], func3);
	}
}