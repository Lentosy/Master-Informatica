//
// Configuration
//

#pragma once

#include <string>

#include <llvm/ADT/StringRef.h>

#include "parser.hpp"

namespace llvm {
class Function;
class Module;
} // namespace llvm

namespace cheetah {
namespace AST {
struct Stmt;
}
} // namespace cheetah


//
// Driver
//

namespace cheetah {

class Driver {
public:
  Driver(){};
  Driver(const Driver &) = delete;

  std::string &filename();
  void setProgram(AST::CompoundStmt *program);

  AST::CompoundStmt *parse(const std::string &filename);
  void codegen(AST::CompoundStmt *root, llvm::StringRef filename,
               bool optimize);

private:
  AST::CompoundStmt *_program;
  std::string _filename;
};
} // namespace cheetah
