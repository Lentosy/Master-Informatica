//
// Configuration
//

#pragma once

#include <llvm/Support/raw_ostream.h>
#define DUMP std::string dump(llvm::raw_ostream &) const

#include "ast/decl.hpp"
#include "ast/stmt.hpp"
#include "ast/expr.hpp"
