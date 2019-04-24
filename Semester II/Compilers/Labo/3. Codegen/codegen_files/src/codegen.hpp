//
// Configuration
//

#pragma once

#include <string>
#include <vector>

#include <llvm/Support/FormattedStream.h>

namespace cheetah {
namespace AST {
struct CompoundStmt;
}
} // namespace cheetah


//
// Code generation and optimization
//

namespace cheetah {

struct Instruction {
  std::string name;
  std::vector<std::string> arguments = {};
  std::string comment = "";
};

struct Block {
  std::string name;
  bool global = false;
  std::string comment = "";

  std::vector<Instruction> instructions = std::vector<Instruction>();
};

struct Program {
  std::vector<Block> blocks;
};

Program &operator<<(Program &, Block);
Program &operator<<(Program &, Instruction);

// member function for AST nodes
#define CODEGEN void emit(Program &) const

Program codegen(AST::CompoundStmt *);

void optimize(Program &prog);

llvm::raw_ostream &operator<<(llvm::raw_ostream &O, const Instruction &inst);

llvm::formatted_raw_ostream &operator<<(llvm::formatted_raw_ostream &,
                                        const Program &);
llvm::formatted_raw_ostream &operator<<(llvm::formatted_raw_ostream &,
                                        const Block &);
llvm::formatted_raw_ostream &operator<<(llvm::formatted_raw_ostream &,
                                        const Instruction &);

} // namespace cheetah
