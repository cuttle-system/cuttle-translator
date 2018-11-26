#include <string>
#include <algorithm>
#include "dictionary_methods.hpp"
#include "dictionary_funcs.hpp"

using namespace cuttle;

void count_priority(const call_tree_t &tree, int i, int height, int &vertex_count, int &max_height) {
    ++vertex_count;
    ++height;

    for (tree_src_element_t j : tree.src[i]) {
        if (j != CALL_TREE_SRC_NIL && j != CALL_TREE_SRC_UNDEFINED) {
            count_priority(tree, j, height, vertex_count, max_height);
        }
    }

    if (tree.src[i].empty()) {
        max_height = std::max(max_height, height);
    }
}

dictionary_element_t cuttle::add(dictionary_t &dictionary, const call_tree_t &pattern_tree, const tokens_t &pattern_tokens,
                                 translate_function_t *function) {
    dictionary.translate_functions.push_back(function);
    dictionary_element_t function_index = (dictionary_element_t) dictionary.translate_functions.size() - 1;

    dictionary.pattern_trees.insert({function_index, pattern_tree});
    dictionary.pattern_tokens.insert({function_index, pattern_tokens});

    int vertex_count = 0, max_height = 0;
    count_priority(pattern_tree, pattern_tree.src.size() - 1, 0, vertex_count, max_height);
    dictionary.prioritized_functions.insert({{vertex_count, max_height}, function_index});

    return function_index;
}

dictionary_element_t cuttle::add(dictionary_t &dictionary, const call_tree_t &pattern_tree, const tokens_t &pattern_tokens,
                                 translate_function_t *function, const call_tree_t &output_tree, const tokens_t &output_tokens) {
    dictionary_element_t function_index = add(dictionary, pattern_tree, pattern_tokens, function);

    dictionary.output_trees.insert({function_index, output_tree});
    dictionary.output_tokens.insert({function_index, output_tokens});

    return function_index;
}

bool cuttle::lookup(dictionary_t &dictionary, const call_tree_t &tree, const tokens_t &tokens,
        dictionary_index_to_index_t &dictionary_index_to_index, ps_parameters_t &ps_parameters, dictionary_element_t function_index,
        tree_src_element_t index, tree_src_element_t dictionary_index) {

    if (index == CALL_TREE_SRC_NIL || dictionary_index == CALL_TREE_SRC_NIL) {
        return index == dictionary_index;
    }

    if (dictionary_index == TREE_SRC_ROOT_INDEX) {
        dictionary_index = (tree_src_element_t) dictionary.pattern_trees[function_index].src.size() - 1;
        dictionary_index = dictionary.pattern_trees[function_index].src[dictionary_index][0];
    }

    dictionary_index_to_index[dictionary_index] = index;

    auto token = tokens[index];
    auto dict_token = dictionary.pattern_tokens[function_index][dictionary_index];

    if (dict_token.type == token_type::macro_p) {
        dictionary.parameter_indexes[function_index].insert({dict_token.value, dictionary_index});
        return true;
    } else if (dict_token.type == token_type::macro_pf && token.type != token_type::string && token.type != token_type::number) {
        dictionary.parameter_indexes[function_index].insert({dict_token.value, dictionary_index});
        return true;
    } else if (dict_token.type == token.type && dict_token.value == token.value) {
        int before_macro_ps = 0;
        int after_macro_ps;
        bool has_macro_ps = false;
        std::string parameter_name;

        for (tree_src_element_t i = 0; i < dictionary.pattern_trees[function_index].src[dictionary_index].size(); ++i) {
            auto inner_index = dictionary.pattern_trees[function_index].src[dictionary_index][i];
            if (dictionary.pattern_tokens[function_index][inner_index].type == token_type::macro_ps) {
                has_macro_ps = true;
                parameter_name = dictionary.pattern_tokens[function_index][inner_index].value;
                break;
            }
            ++before_macro_ps;
        }

        after_macro_ps = ((tree_src_element_t) dictionary.pattern_trees[function_index].src[dictionary_index].size()) - before_macro_ps - 1;

        if (has_macro_ps) {
            ps_parameters[parameter_name] = {};
            for (tree_src_element_t i = 0; i < before_macro_ps; ++i) {
                if (!lookup(dictionary, tree, tokens, dictionary_index_to_index, ps_parameters,
                        function_index, tree.src[index][i],
                            dictionary.pattern_trees[function_index].src[dictionary_index][i])) {
                    return false;
                }
            }

            for (tree_src_element_t i = before_macro_ps; i < tree.src[index].size() - after_macro_ps; ++i) {
                ps_parameters[parameter_name].push_back(tree.src[index][i]);
            }

            for (tree_src_element_t i = 0; i < after_macro_ps; --i) {
                if (!lookup(dictionary, tree, tokens, dictionary_index_to_index, ps_parameters, function_index, tree.src[index][tree.src[index].size() - 1 - i],
                            dictionary.pattern_trees[function_index].src[dictionary_index][before_macro_ps + 1 + i])) {
                    return false;
                }
            }
        } else {
            if (tree.src[index].size() < dictionary.pattern_trees[function_index].src[dictionary_index].size()) {
                return false;
            }
            for (tree_src_element_t i = 0; i < tree.src[index].size(); ++i) {
                if (i >= dictionary.pattern_trees[function_index].src[dictionary_index].size()) {
                    return false;
                }

                if (!lookup(dictionary, tree, tokens, dictionary_index_to_index, ps_parameters, function_index, tree.src[index][i],
                            dictionary.pattern_trees[function_index].src[dictionary_index][i])) {
                    return false;
                }
            }
        }
        return true;
    }

    return false;
}

void cuttle::initialize(dictionary_t &dictionary) {
    dictionary.translate_functions.clear();
    dictionary.prioritized_functions.clear();

    dictionary.pattern_trees.clear();
    dictionary.pattern_tokens.clear();

    dictionary.parameter_indexes.clear();
    dictionary.vm_output_trees.clear();

    dictionary.output_trees.clear();
    dictionary.output_tokens.clear();
}