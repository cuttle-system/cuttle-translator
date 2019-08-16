#pragma once

#include <map>
#include "value.hpp"
#include "token.hpp"
#include "call_tree.hpp"
#include "dictionary.hpp"
#include "context_holder.hpp"

namespace cuttle {
	using index_reference_t = std::map<unsigned int, unsigned int>;
	using dictionary_index_to_index_t = std::map<dictionary_element_t, tree_src_element_t>;
	using custom_state_num_t = std::map<std::string, long long>;
	using ps_parameters_t = std::map<std::string, tree_src_elements_t>;
	using hot_places_destination_t = std::map<std::string, tree_src_element_t>;
	using hot_places_source_t = std::map<std::string, tree_src_elements_t>;
	struct translate_state_t {
        dictionary_t &dictionary;
        const tokens_t &tokens;
        const call_tree_t &tree;
        unsigned int index;
        values_t &values;
		call_tree_t &new_tree;
		unsigned int &new_index;
		index_reference_t &index_reference;
		custom_state_num_t &custom_state_num;
        context_holder_t contexts;
        dictionary_element_t translate_function_index;
		dictionary_index_to_index_t dictionary_index_to_index;
        ps_parameters_t ps_parameters;
		hot_places_destination_t hot_places_destination;
		hot_places_source_t hot_places_source;
	};
}