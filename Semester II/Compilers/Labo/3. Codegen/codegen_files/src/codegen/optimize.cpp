// functionality related to the optimization of code

#include "auxiliary.hpp"
#include "codegen.hpp"

using namespace cheetah;

// non-formatted output function for quick printing of instructions
llvm::raw_ostream &cheetah::operator<<(llvm::raw_ostream &O,
                                       const Instruction &inst) {
  O << "    " << inst.name << " ";

  // emit the arguments
  if (inst.arguments.size() > 0) {
    for (size_t i = 0; i < inst.arguments.size(); i++) {
      O << "" << inst.arguments[i];
      if (i != inst.arguments.size() - 1)
        O << ", ";
    }
  }

  O << "\n";
  return O;
}

// main entry-point
void cheetah::optimize(Program &prog) {
  bool changed;
  do {
    changed = false;

    // iterate blocks
    auto block = prog.blocks.begin();
    auto block_end = prog.blocks.end();
    while (block != block_end) {
      auto block_next = std::next(block, 1);

      // iterate instructions
      auto inst = block->instructions.begin();
      auto inst_end = block->instructions.end();
      while (inst != inst_end) {
        auto inst_next = std::next(inst, 1);

        // 1-instruction patterns
        {
          // movq $0, %reg
          // -> simplify to xor
          if (inst->name == "movq" && inst->arguments[0] == "$0" &&
              inst->arguments[1][0] == '%') {
            llvm::errs() << "Simplifying register zeroing:\n" << *inst;
            *inst =
                Instruction{"xorq", {inst->arguments[1], inst->arguments[1]}};
            changed = true;
          }
        }

        // 2-instruction patterns
        {
            // push ...
            // pop %reg
            // -> simplify to mov ..., %reg


            
        }
        // TODO: add more patterns

        ++inst;
      }
      ++block;
    }
  } while (changed);
}
