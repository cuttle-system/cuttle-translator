#include "tree_utils.hpp"
#include "token_methods.hpp"
#include "call_tree.hpp"
#include "cutvm_translator_nil.hpp"

using namespace cuttle;

token_t construct_token(const std::vector<vm::value_t> &token_array) {
    return {token_type_from_string(*token_array[0].data.string), *token_array[1].data.string};
}

tree_src_element_t construct_tree_inner(vm::context_t &context, const std::vector<vm::value_t> &call_array, call_tree_t &tree, tokens_t &tokens) {
    if (call_array[1].type.id == vm::type_id::string && *call_array[1].data.string == CUTTLE_CUTVM_CALL_TREE_NIL) {
        return CALL_TREE_SRC_NIL;
    }

    auto index = (tree_src_element_t) tokens.size();
    tree.src.push_back({});

    if (call_array[0].type.id == vm::type_id::string && *call_array[0].data.string == "f") {
        tree_src_element_t child_index;
        tokens.push_back(construct_token(*call_array[1].data.array));
        std::string function_name = tokens.back().value;

        for (unsigned i = 2; i < call_array.size(); ++i) {
            child_index = construct_tree_inner(context, *call_array[i].data.array, tree, tokens);
            tree.src[index].push_back(child_index);
        }
    } else {
        tokens.push_back(construct_token(call_array));
    }

    return index;
}

void cuttle::construct_tree(vm::context_t &context, std::deque<vm::value_t> &arg_stack, call_tree_t &tree, tokens_t &tokens) {
    tree_src_elements_t root_args;
    for (auto elem : arg_stack) {
        const std::vector<vm::value_t> &call_array = *elem.data.array;
        auto i = construct_tree_inner(context, call_array, tree, tokens);
        root_args.push_back({i});
    }
    tree.src.push_back(root_args);
}