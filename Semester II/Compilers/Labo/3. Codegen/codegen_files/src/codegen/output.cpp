// functionality related to rendering code to its assembly representation

#include "auxiliary.hpp"
#include "codegen.hpp"

using namespace cheetah;

// main entry-point
llvm::formatted_raw_ostream &cheetah::operator<<(llvm::formatted_raw_ostream &O,
                                                 const Program &prog) {
  for (auto const &block : prog.blocks)
    O << block;

  return O;
}

llvm::formatted_raw_ostream &cheetah::operator<<(llvm::formatted_raw_ostream &O,
                                                 const Block &block) {
  if (block.global)
    O << ".globl " << block.name << "\n";

  O << block.name << ":";

  // emit a comment
  if (block.comment.length() > 0) {
    O.PadToColumn(32);
    O << "# " << block.comment;
  }

  O << "\n";

  for (auto const &inst : block.instructions)
    O << inst;

  return O;
}

llvm::formatted_raw_ostream &cheetah::operator<<(llvm::formatted_raw_ostream &O,
                                                 const Instruction &inst) {
  O << "    " << inst.name << " ";

  // emit the arguments
  if (inst.arguments.size() > 0) {
    O.PadToColumn(14);
    for (size_t i = 0; i < inst.arguments.size(); i++) {
      O << inst.arguments[i];
      if (i != inst.arguments.size() - 1)
        O << ", ";
    }
  }

  // emit a comment
  if (inst.comment.length() > 0) {
    O.PadToColumn(32);
    O << "# " << inst.comment;
  }

  O << "\n";
  return O;
}
