#include "translator_methods.hpp"
#include "dictionary_funcs.hpp"
#include "value_methods.hpp"
#include "dictionary_methods.hpp"
#include "std.hpp"

using namespace cuttle;

unsigned int cuttle::translate_function_call(translate_state_t &state) {
    for (auto prioritized_function_index : state.dictionary.prioritized_functions) {
        auto function_index = prioritized_function_index.second;
        state.dictionary_index_to_index.clear();
        state.ps_parameters.clear();
        if (lookup(state.dictionary, state.tree, state.tokens, state.dictionary_index_to_index, state.ps_parameters,
                   function_index, state.index)) {
            auto child_state = state;
            vm::context_t child_context;
            child_context.parent = state.contexts.local;
            child_state.contexts.local = &child_context;
            child_state.translate_function_index = function_index;
            return child_state.dictionary.translate_functions[child_state.translate_function_index](child_state);
        }
    }
    state.ps_parameters.clear();
    state.dictionary_index_to_index.clear();
    return dictionary_funcs::copy(state);
}

void translator_copy_hot_places_nodes(cuttle::translate_state_t &state) {
    using namespace cuttle;

    for (const auto &pair : state.hot_places_destination) {
        const auto key = pair.first;
        const auto index = pair.second;

        for (const auto &src_index : state.hot_places_source[key]) {
            auto child_state = state;
            state.index = src_index;
            auto translate_function_call(child_state);
        }
    }
}

void cuttle::translate(
	const translator_t &translator, const tokens_t &tokens, const call_tree_t &tree,
	values_t &values, call_tree_t &new_tree
) {
    tree_src_elements_t root_args;
    dictionary_t dictionary = translator.dictionary;
    tree_src_element_t new_index = 0;
    tree_src_element_t root_arg_index;
    index_reference_t index_reference;
    custom_state_num_t custom_state_num;
    dictionary_index_to_index_t dictionary_index_to_index;
    vm::context_t context, local_context;
    populate(context);
    local_context.parent = &context;
	translate_state_t state = {
		dictionary, tokens, tree, 0, values,
		new_tree, new_index, index_reference, custom_state_num,
		{&context, &local_context}, 0, dictionary_index_to_index,
        {}, {}, {}
	};

	for (auto index : tree.src.back()) {
        auto child_state = state;
        child_state.index = index;
        root_arg_index = translate_function_call(child_state);
        root_args.push_back(root_arg_index);
    }

	translator_copy_hot_places_nodes(state);

    new_tree.src.push_back(root_args);
}