#include <string>
#include <algorithm>
#include "dictionary_methods.hpp"
#include "dictionary_funcs.hpp"

using namespace cuttle;

void inner_add(dictionary_t &dictionary, const call_tree_t &tree, const tokens_t &tokens,
               dictionary_element_t function_index, tree_src_element_t index, dictionary_element_t new_index
) {
    if (dictionary.functions_ended_on_index.size() <= new_index)
        dictionary.functions_ended_on_index.resize(new_index + 1);
    if (dictionary.parameter_sets.size() <= new_index)
        dictionary.parameter_sets.resize(new_index + 1);
    if (dictionary.children.size() <= new_index)
        dictionary.children.resize(new_index + 1);

    unsigned int arg_number = 0;
    if (tree.src[index].empty()) {
        dictionary.functions_ended_on_index[new_index].insert(function_index);
    }
    for (auto arg_index : tree.src[index]) {
        auto token = tokens[arg_index];
        dictionary_element_t child_new_index = new_index;
        if (dictionary.src[new_index].size() <= arg_number) {
            dictionary.src[new_index].resize(arg_number + 1);
        }
        if (dictionary.parameter_sets[new_index].size() <= arg_number) {
            dictionary.parameter_sets[new_index].resize(arg_number + 1);
        }
        if (dictionary.src[new_index][arg_number].find(token.type) != dictionary.src[child_new_index][arg_number].end()
            && dictionary.src[new_index][arg_number][token.type].find(token.value)
                != dictionary.src[child_new_index][arg_number][token.type].end()
        ) {
            child_new_index = dictionary.src[child_new_index][arg_number][token.type][token.value];
        } else {
            dictionary.src.emplace_back();
            child_new_index = (dictionary_element_t) dictionary.src.size() - 1;
            dictionary.src[new_index][arg_number][token.type][token.value] = child_new_index;
        }
        dictionary.children[new_index][function_index].push_back(child_new_index);
        if (dictionary.src[new_index][arg_number].find(token_type::macro_p)
            != dictionary.src[new_index][arg_number].end()
        ) {
            dictionary.parameter_sets[new_index][arg_number].insert(function_index);
            dictionary.parameter_indexes[function_index].insert({token.value, child_new_index});
        }
        inner_add(dictionary, tree, tokens, function_index, arg_index, child_new_index);
        ++arg_number;
    }
}

void cuttle::add(dictionary_t &dictionary, const call_tree_t &tree, const tokens_t &tokens,
                 translate_function_t *function, tree_src_element_t index
) {
    if (index == TREE_SRC_ROOT_INDEX) {
        index = (tree_src_element_t) tree.src.size() - 1;
    }

    dictionary.translate_functions.push_back(function);
    dictionary_element_t function_index = (dictionary_element_t) dictionary.translate_functions.size() - 1;
    dictionary_element_t new_index = 0u;

    inner_add(dictionary, tree, tokens, function_index, index, new_index);
}

bool inner_lookup(dictionary_t &dictionary, const call_tree_t &tree, const tokens_t &tokens, tree_src_element_t index,
                  std::set<dictionary_element_t> &function_indexes, dictionary_element_t new_index
) {
    unsigned int arg_number = 0;

    bool first = true;
    std::set<dictionary_element_t> recursive_function_indexes;
    std::set<dictionary_element_t> children_function_indexes;

    for (auto arg_index : tree.src[index]) {
        auto token = tokens[arg_index];
        auto child_function_indexes = recursive_function_indexes;
        dictionary_element_t child_new_index = new_index;

        if (dictionary.src[new_index].size() > arg_number) {
            if (dictionary.src[new_index][arg_number].find(token.type) != dictionary.src[new_index][arg_number].end()
                && dictionary.src[new_index][arg_number][token.type].find(token.value)
                    != dictionary.src[new_index][arg_number][token.type].end()
            ) {
                child_new_index = dictionary.src[child_new_index][arg_number][token.type][token.value];
                if (!inner_lookup(dictionary, tree, tokens, arg_index, child_function_indexes, child_new_index)) {
                    child_function_indexes = {};
                }
            } else if (dictionary.src[new_index][arg_number].find(token_type::macro_p) // TODO: type macros_if, macros_arg, macros_args, e.g
                != dictionary.src[new_index][arg_number].end()
            ) {
                child_function_indexes = dictionary.parameter_sets[new_index][arg_number];
            } else {
                child_function_indexes = {};
            }
        } else {
            child_function_indexes = {};
        }

        if (!recursive_function_indexes.empty()) {
            std::set<dictionary_element_t> new_function_indexes;
            std::set_intersection(
                    recursive_function_indexes.begin(), recursive_function_indexes.end(),
                    child_function_indexes.begin(), child_function_indexes.end(),
                    std::inserter(new_function_indexes, new_function_indexes.begin()));
            recursive_function_indexes = new_function_indexes;
        }

        if (!children_function_indexes.empty()) {
            std::set<dictionary_element_t> new_function_indexes;
            std::set_intersection(
                    dictionary.functions_ended_on_index[child_new_index].begin(),
                    dictionary.functions_ended_on_index[child_new_index].end(),
                    children_function_indexes.begin(), children_function_indexes.end(),
                    std::inserter(new_function_indexes, new_function_indexes.begin()));
            children_function_indexes = new_function_indexes;
        }

        if (first) {
            recursive_function_indexes = child_function_indexes;
            children_function_indexes = dictionary.functions_ended_on_index[child_new_index];
            first = false;
        }

        ++arg_number;
    }
    if (recursive_function_indexes.empty()) {
        function_indexes = children_function_indexes;
    } else {
        function_indexes = recursive_function_indexes;
    }
    return !function_indexes.empty();
}


void dfs(dictionary_t &dictionary, dictionary_element_t function_index, const call_tree_t &tree,
        tree_src_element_t index, dictionary_element_t new_index,
        std::map<dictionary_element_t, tree_src_element_t> &new_index_to_index) {
    new_index_to_index[new_index] = index;
    for (unsigned i = 0; i < dictionary.children[new_index][function_index].size(); ++i) {
        dfs(dictionary, function_index, tree, tree.src[index][i], dictionary.children[new_index][function_index][i], new_index_to_index);
    }
}

bool cuttle::lookup(dictionary_t &dictionary, const call_tree_t &tree, const tokens_t &tokens, tree_src_element_t index,
                    dictionary_element_t &function_index,
                    std::map<dictionary_element_t, tree_src_element_t> &new_index_to_index) {
    dictionary_element_t new_index = 0u;
    std::set<dictionary_element_t> function_indexes;
    if (index != TREE_SRC_ROOT_INDEX) {
        token_t token = tokens[index];
        for (auto arg_sub_tree : dictionary.src[new_index]) {
            if (arg_sub_tree.find(token.type) != arg_sub_tree.end()
                && arg_sub_tree[token.type].find(token.value) != arg_sub_tree[token.type].end()
            ) {
                new_index = arg_sub_tree[token.type][token.value];
                break;
            }
        }
        if (new_index == 0) return false;
    }
    bool result = inner_lookup(dictionary, tree, tokens, index, function_indexes, new_index);
    if (result) {
        function_index = *prev(function_indexes.end());
        dfs(dictionary, function_index, tree, index, new_index, new_index_to_index);
    }
    return result;
}

void cuttle::initialize(dictionary_t &dictionary) {
    dictionary.src.clear();
    dictionary.src.emplace_back();
    dictionary.functions_ended_on_index.clear();
    dictionary.functions_ended_on_index.emplace_back();
}