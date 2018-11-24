#include <utility>
#include <vector>
#include <sstream>

#include "dictionary_funcs.hpp"
#include "value_methods.hpp"
#include "translator_methods.hpp"
#include "interpreter.hpp"
#include "vm_context_methods.hpp"
#include "tree_utils.hpp"

using namespace cuttle;

tree_src_element_t
cuttle::dictionary_funcs::value(translate_state_t &state, const std::string &value, enum cuttle::value_type type) {
    state.new_tree.src.push_back({});
    state.values.push_back({value, type});
    return state.new_index++;
}

tree_src_element_t cuttle::dictionary_funcs::function_name(translate_state_t &state, const std::string &value) {
    return cuttle::dictionary_funcs::value(state, value, value_type::func_name);
}

tree_src_element_t cuttle::dictionary_funcs::parameter(translate_state_t &state, const std::string &name) {
    dictionary_element_t dictionary_index = state.dictionary.parameter_indexes[state.translate_function_index][name];
    auto child_state = state;
    child_state.index = state.dictionary_index_to_index[dictionary_index];
    auto subtree_i = cuttle::translate_function_call(child_state);
    return subtree_i;
}

tree_src_element_t cuttle::dictionary_funcs::string(translate_state_t &state, const std::string &value) {
    return cuttle::dictionary_funcs::value(state, value, value_type::string);
}

tree_src_element_t cuttle::dictionary_funcs::number(translate_state_t &state, const std::string &value) {
    return cuttle::dictionary_funcs::value(state, value, value_type::number);
}

tree_src_element_t cuttle::dictionary_funcs::function(translate_state_t &state,
                                                      tree_src_element_t function_name_index,
                                                      std::vector<unsigned int> args_indexes
) {
    state.new_tree.src[function_name_index] = std::move(args_indexes);
    return function_name_index;
}

tree_src_element_t cuttle::dictionary_funcs::copy(translate_state_t &state) {
    token_t root_token = state.tokens[state.index];
    tree_src_element_t index;
    if (root_token.type == token_type::atom) {
        index = dictionary_funcs::function(
                state, dictionary_funcs::function_name(state, root_token.value), {});
    } else {
        index = dictionary_funcs::value(state, root_token.value, value_from_token_type(root_token.type));
    }
    tree_src_element_t new_arg_index;
    state.index_reference[state.index] = index;

    for (auto arg_index : state.tree.src[state.index]) {
        if (arg_index == CALL_TREE_SRC_NIL) {
            new_arg_index = CALL_TREE_SRC_NIL;
        } else {
            token_t token = state.tokens[arg_index];
            translate_state_t child_state = state;
            child_state.index = arg_index;
            new_arg_index = translate_function_call(child_state);
            state.index_reference[arg_index] = new_arg_index;
        }
        state.new_tree.src[index].push_back(new_arg_index);
    }

    return index;
}

tree_src_element_t cuttle::dictionary_funcs::apply_pattern_output(translate_state_t &state) {
    auto func_index = state.translate_function_index;
    if (state.dictionary.output_trees.count(func_index)) {
        const auto &output_tree = state.dictionary.output_trees[func_index];
        const auto &output_tokens = state.dictionary.output_tokens[func_index];
        return apply_pattern_output(state, (tree_src_element_t) (output_tree.src.size() - 1), output_tree, output_tokens);
    } else {
        std::stringstream ss;
        ss.str(state.dictionary.vm_output_trees[func_index]);
        call_tree_t output_tree;
        tokens_t output_tokens;
        std::deque<vm::value_t> arg_stack;
        std::string global_context_name = CUTTLE_GLOBAL_CONTEXT_NAME;
        auto global_context_value = vm::value_t{{vm::type_id::object}, (vm::any_t *) &state.contexts.global};
        add(state.contexts.local, CUTTLE_GLOBAL_CONTEXT_NAME, global_context_value);
        vm::interpret(ss, state.contexts.local, arg_stack);
        construct_tree(state.contexts.local, arg_stack, output_tree, output_tokens);
        return apply_pattern_output(state, (tree_src_element_t) (output_tree.src.size() - 1), output_tree, output_tokens);
    }
}

tree_src_element_t
cuttle::dictionary_funcs::apply_pattern_output(translate_state_t &state, tree_src_element_t index,
                                               const call_tree_t &output_tree, const tokens_t &output_tokens) {
    tree_src_element_t new_arg_index;
    tree_src_element_t new_index;
    if (index != output_tree.src.size() - 1) {
        new_index = value(state, output_tokens[index].value, value_from_token_type(output_tokens[index].type));
    } else {
        new_index = value(state, CUTTLE_MERGE_WITH_PARENT_FUNC, value_type::func_name);
    }

    for (const auto arg_index : output_tree.src[index]) {
        if (arg_index == CALL_TREE_SRC_NIL) {
            new_arg_index = CALL_TREE_SRC_NIL;
        } else {
            token_t token = output_tokens[arg_index];
            if (token.type == token_type::macro_p || token.type == token_type::macro_pf ||
                token.type == token_type::macro_ps
                    ) {
                new_arg_index = parameter(state, token.value);
            } else {
                new_arg_index = apply_pattern_output(state, arg_index, output_tree, output_tokens);
            }
        }
        state.new_tree.src[new_index].push_back(new_arg_index);
    }

    return new_index;
}

std::vector<tree_src_element_t>
cuttle::dictionary_funcs::copy(translate_state_t &state, const std::vector<tree_src_element_t> &elements) {
    std::vector<tree_src_element_t> copied;
    for (auto &elem : elements) {
        auto child_state = state;
        child_state.index = elem;
        copied.push_back(copy(child_state));
    }
    return copied;
}