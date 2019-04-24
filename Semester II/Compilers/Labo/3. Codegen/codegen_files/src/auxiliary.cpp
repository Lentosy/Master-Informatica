//
// Configuration
//

#include <iostream>

#include <llvm/Support/Path.h>

#include "auxiliary.hpp"

using namespace llvm;
using namespace cheetah;


//
// Errors
//

void cheetah::parser_error(const std::string error, const std::string *filename,
                           int line, int column) {
  std::cerr << "parser error:";
  if (filename != nullptr)
    std::cerr << " " << sys::path::filename(*filename).str() << ":";
  if (line != 0) {
    std::cerr << line << ":";
    if (column != 0)
      std::cerr << column << ":";
  }
  std::cerr << " " << error << std::endl;

  exit(EXIT_FAILURE);
}

void cheetah::codegen_error(const std::string error) {
  std::cerr << "codegen error: " << error << std::endl;
  abort();
}

void cheetah::backend_error(const std::string error) {
  std::cerr << "backend error: " << error << std::endl;
  exit(EXIT_FAILURE);
}
