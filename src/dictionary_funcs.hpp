#pragma once

#include "translate_state.hpp"
#include "dictionary.hpp"

namespace cuttle {
	namespace dictionary_funcs {
		tree_src_element_t copy(translate_state_t& state);

		tree_src_element_t value(translate_state_t& state, const std::string& value, enum value_type type);
		tree_src_element_t function_name(translate_state_t& state, const std::string& value);
		tree_src_element_t parameter(translate_state_t& state, const std::string& name);
		tree_src_element_t string(translate_state_t& state, const std::string& value);
		tree_src_element_t number(translate_state_t& state, const std::string& value);

		tree_src_element_t function(translate_state_t &state, tree_src_element_t function_name_index,
                              std::vector<tree_src_element_t> args_indexes);
	}
}