#include <iostream>
#include "test.hpp"
#include "dictionary_methods.hpp"

using namespace cuttle;

inline void test_adds_entries_with_one_argument() {
	{
		translate_function_t *func = [](translate_state_t& state) { return 0u; };
		dictionary_t dictionary;
		add(dictionary, "foo", 1, func);
		AssertEqual(dictionary.size(), 1, "Dictionary size");
		AssertNotEqual(dictionary.find("foo"), dictionary.end(), "Entry exists");
		AssertEqual(dictionary["foo"].size(), 1, "Dictionary entry size");
		AssertNotEqual(dictionary["foo"].find(1), dictionary["foo"].end(), "Dictionary entry of argument exists");
		AssertEqual(dictionary["foo"][1], func, "Dictionary entry function matches");
	}
	{
		translate_function_t *func = [](translate_state_t& state) { return 0u; };
		dictionary_t dictionary;
		add(dictionary, "foo", 2, func);
		AssertEqual(dictionary.size(), 1, "Dictionary size");
		AssertNotEqual(dictionary.find("foo"), dictionary.end(), "Entry exists");
		AssertEqual(dictionary["foo"].size(), 1, "Dictionary entry size");
		AssertNotEqual(dictionary["foo"].find(2), dictionary["foo"].end(), "Dictionary entry of argument exists");
		AssertEqual(dictionary["foo"][2], func, "Dictionary entry function matches");
	}
	{
		translate_function_t *func = [](translate_state_t& state) { return 0u; };
		dictionary_t dictionary;
		add(dictionary, "foo", 150, func);
		AssertEqual(dictionary.size(), 1, "Dictionary size");
		AssertNotEqual(dictionary.find("foo"), dictionary.end(), "Entry exists");
		AssertEqual(dictionary["foo"].size(), 1, "Dictionary entry size");
		AssertNotEqual(dictionary["foo"].find(150), dictionary["foo"].end(), "Dictionary entry of argument exists");
		AssertEqual(dictionary["foo"][150], func, "Dictionary entry function matches");
	}
	{
		translate_function_t *func1 = [](translate_state_t& state) { return 0u; };
		translate_function_t *func2 = [](translate_state_t& state) { return 0u; };
		dictionary_t dictionary;
		add(dictionary, "foo", 150, func1);
		add(dictionary, "bar", 130, func2);
		AssertEqual(dictionary.size(), 2, "Dictionary size");
		AssertNotEqual(dictionary.find("foo"), dictionary.end(), "Entry exists");
		AssertEqual(dictionary["foo"].size(), 1, "Dictionary entry size");
		AssertNotEqual(dictionary["foo"].find(150), dictionary["foo"].end(), "Dictionary entry of argument exists");
		AssertEqual(dictionary["foo"][150], func1, "Dictionary entry function matches");
		AssertNotEqual(dictionary.find("bar"), dictionary.end(), "Entry exists");
		AssertEqual(dictionary["bar"].size(), 1, "Dictionary entry size");
		AssertNotEqual(dictionary["bar"].find(130), dictionary["bar"].end(), "Dictionary entry of argument exists");
		AssertEqual(dictionary["bar"][130], func2, "Dictionary entry function matches");
	}
}

inline void test_adds_entries_with_multiple_arguments() {
	{
		translate_function_t *func1 = [](translate_state_t& state) { return 0u; };
		translate_function_t *func2 = [](translate_state_t& state) { return 0u; };
		translate_function_t *func3 = [](translate_state_t& state) { return 0u; };
		dictionary_t dictionary;
		add(dictionary, "foo", 1, func1);
		add(dictionary, "foo", 2, func2);
		add(dictionary, "foo", 3, func3);
		AssertEqual(dictionary.size(), 1, "Dictionary size");
		AssertNotEqual(dictionary.find("foo"), dictionary.end(), "Entry exists");
		AssertEqual(dictionary["foo"].size(), 3, "Dictionary entry size");
		AssertNotEqual(dictionary["foo"].find(1), dictionary["foo"].end(), "Dictionary entry of argument exists");
		AssertEqual(dictionary["foo"][1], func1, "Dictionary entry function matches");
		AssertNotEqual(dictionary["foo"].find(2), dictionary["foo"].end(), "Dictionary entry of argument exists");
		AssertEqual(dictionary["foo"][2], func2, "Dictionary entry function matches");
		AssertNotEqual(dictionary["foo"].find(3), dictionary["foo"].end(), "Dictionary entry of argument exists");
		AssertEqual(dictionary["foo"][3], func3, "Dictionary entry function matches");
	}
}

void run_dictionary_tests() {
    TESTCASE
    test_adds_entries_with_one_argument();
	test_adds_entries_with_multiple_arguments();
}