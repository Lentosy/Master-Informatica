//
// Configuration
//

#include <assert.h>
#include <cstdlib>
#include <fstream>
#include <vector>

#include <llvm/ADT/StringRef.h>
#include <llvm/Support/Debug.h>
#include <llvm/Support/FileSystem.h>
#include <llvm/Support/ToolOutputFile.h>

#include "ast.hpp"
#include "auxiliary.hpp"
#include "driver.hpp"
#include "lexer.hpp"
#include "parser.hpp"
#include "sema.hpp"

using namespace cheetah;
using namespace llvm;

struct noop {
  void operator()(...) const {}
};

AST::CompoundStmt *Driver::parse(const std::string &filename) {
  std::shared_ptr<std::istream> in_file;
  if (filename == "-")
    in_file.reset(&std::cin, noop());
  else
    in_file.reset(new std::ifstream(filename.c_str()));
  if (!in_file->good())
    parser_error("could not open file");
  _filename = filename;

  Lexer lexer(&*in_file);
  DEBUG_WITH_TYPE("cheetah::lexer", lexer.set_debug_level(1));

  Sema sema;

  Parser parser(lexer, sema, *this);
  DEBUG_WITH_TYPE("cheetah::parser", parser.set_debug_level(1));

  _program = nullptr;
  const int accept(0);
  if (parser.parse() != accept)
    parser_error("unknown parsing error");

  return _program;
}

void Driver::dump(AST::CompoundStmt *root, llvm::StringRef filename) {
  std::error_code EC;

  // Figure out where we are going to send the output.
  raw_fd_ostream dest(filename.data(), EC, sys::fs::F_Text);
  if (EC)
    backend_error(EC.message());

  root->dump(dest);
  dest.flush();
}

void Driver::setProgram(AST::CompoundStmt *program) { _program = program; }

std::string &Driver::filename() { return _filename; }
