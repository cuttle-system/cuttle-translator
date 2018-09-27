#pragma once

#include <map>
#include <set>
#include <string>
#include "call_tree.hpp"
#include "value.hpp"
#include "token.hpp"

namespace cuttle {
	struct translate_state_t;

//	using arg_number_t = int;
//	const arg_number_t DICTIONARY_ANY_ARG_NUMBER = -1;
	using translate_function_t = tree_src_element_t(translate_state_t& state);

//	struct dictionary_node_t {
//        translate_function_t *translate_function;
//        std::map<std::pair<std::string, token_type>, dictionary_node_t *> connections;
//	};

//	using dictionary_t = dictionary_node_t *;
//	using dictionary_t = std::map<std::string, std::map<arg_number_t, translate_function_t *> >;

    using dictionary_element_t = unsigned int;
    using dictionary_elements_t = std::map<token_type, std::map<std::string, dictionary_element_t> >;

    struct dictionary_t {
        std::vector<std::vector<dictionary_elements_t> > src;
		std::vector<std::set<dictionary_element_t> > functions_ended_on_index;
        std::vector<std::vector<std::set<dictionary_element_t> > > parameter_sets;
        std::vector<std::map<dictionary_element_t, std::vector<dictionary_element_t> > > children;
        std::map<dictionary_element_t, std::map<std::string, dictionary_element_t> > parameter_indexes;
        std::vector<translate_function_t *> translate_functions;
    };
}