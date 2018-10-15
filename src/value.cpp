#include "value.hpp"
#include "value_methods.hpp"

cuttle::value_type cuttle::value_from_token_type(cuttle::token_type type) {
    using namespace cuttle;
    switch (type) {
        case token_type::atom:
            return value_type::func_name;
        case token_type::number:
            return value_type::number;
        case token_type::string:
            return value_type::string;
        case token_type::macro_if:
            return value_type::macro_if;
        case token_type::macro_p:
            return value_type::macro_p;
        case token_type::macro_pf:
            return value_type::macro_pf;
        case token_type::macro_ps:
            return value_type::macro_ps;
        default:
            return value_type::unknown;
    }
}

bool cuttle::operator==(const cuttle::value_t &left, const cuttle::value_t &right) {
    return (left.value == right.value && left.type == right.type);
}

std::ostream &cuttle::operator<<(std::ostream &stream, const cuttle::value_type &type) {
    using namespace cuttle;
    switch (type) {
        case value_type::func_name:
            stream << "func_name";
            break;
        case value_type::number:
            stream << "number";
            break;
        case value_type::string:
            stream << "string";
            break;
        default:
            stream << "unknown";
    }
    return stream;
}