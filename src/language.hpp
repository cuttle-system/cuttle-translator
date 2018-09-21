#pragma once

#include <string>

namespace cuttle {
    using translator_version_t = int;

    const std::string TRANSLATOR_ANY_NAME;
    const translator_version_t TRANSLATOR_ANY_VERSION = -1;

    struct language_t {
        std::string name;
        translator_version_t version;
    };
}