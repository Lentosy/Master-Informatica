//
// Configuration
//

#pragma once

#include <string>


//
// Errors
//

namespace cheetah {

[[noreturn]] void parser_error(const std::string error,
                               const std::string *filename = nullptr,
                               int line = 0, int column = 0);

[[noreturn]] void backend_error(const std::string error);

} // namespace cheetah
