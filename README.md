[//]: # ({% raw %})

# Cuttle Translator
A call tree translator to be used in Cuttle System

## API

Set `dictionary_t` rules as in the following code example.

```cpp
translator_t translator = {{ "mylang1", 1 },{ "mylang2", 1 }, {}};
initialize(translator.dictionary);

add(translator.dictionary,
    call_tree_t{{{1u, 2u}, {}, {}, {0}}},
    tokens_t{{token_type::atom, "plus"}, {token_type::macro_p, "_a"}, {token_type::macro_p, "_b"}},
    [](translate_state_t &state) {
        auto func_i = dictionary_funcs::function_name(state, "+");
        auto a_i = dictionary_funcs::parameter(state, "_a");
        auto b_i = dictionary_funcs::parameter(state, "_b");
        return dictionary_funcs::function(state, func_i, {a_i, b_i});
    });
add(translator.dictionary, call_tree_t{{{1u, 2u}, {}, {}, {0}}},
    tokens_t{{token_type::atom, "-"}, {token_type::macro_p, "_a"}, {token_type::macro_p, "_b"}},
    [](translate_state_t &state) {
        auto func_i = dictionary_funcs::function_name(state, "minus");
        auto a_i = dictionary_funcs::parameter(state, "_b");
        auto b_i = dictionary_funcs::parameter(state, "_a");
        return dictionary_funcs::function(state, func_i, {a_i, b_i});
    });

values_t values;
call_tree_t new_tree;
translate(translator, tokens, tree, values, new_tree);
```

## Building

### Prerequisites
 
- CMake 3.0.2
- Cygwin or MSYS Git if on Windows
- GCC 8.1.0
- GNU Make if manual process is followed

### Default process

1. Enable CMake support in your IDE (Visual Studio or CLion).
2. Open directory using your IDE.

### Manual process

1. Under the project directory execute `./scripts/get-deps.sh`
2. Create directory build under the project directory.
3. Under the project directory run 
    1. `cd build`
    2. `cmake ..`
    3. `make`

[//]: # ({% endraw %})
