//
// Configuration
//

#include <cstdlib>
#include <memory>
#include <string>

#include <llvm/ADT/StringRef.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/Support/CommandLine.h>
#include <llvm/Support/Path.h>

#include "ast.hpp"
#include "auxiliary.hpp"
#include "driver.hpp"

namespace llvm {
class Function;
}

namespace cheetah {
llvm::LLVMContext LLVMContext;
}

using namespace cheetah;
using namespace llvm;

static cl::OptionCategory LLVMOptCat("LLVM options",
                                     "These control inner LLVM settings.");

static cl::OptionCategory CheetahOptCat("Cheetah options",
                                        "These control the Cheetah compiler.");

static cl::opt<std::string> InputFilenameOpt(cl::Positional,
                                             cl::desc("<input file>"),
                                             cl::Required,
                                             cl::cat(CheetahOptCat));

static cl::opt<std::string>
    OutputFilenameOpt("o",
                      cl::desc("Output filename (standard output if omitted)"),
                      cl::value_desc("filename"), cl::cat(CheetahOptCat));

int main(int argc, char **argv) {
  // Hide some LLVM command-line options
  StringMap<cl::Option *> &OptionMap = cl::getRegisteredOptions();
  for (auto &Option : OptionMap) {
    if (Option.second->Category == &cl::GeneralCategory) {
      Option.second->setCategory(LLVMOptCat);
      Option.second->setHiddenFlag(cl::Hidden);
    }
  }

  cl::ParseCommandLineOptions(argc, argv);

  Driver driver;

  StringRef IFN = InputFilenameOpt;
  if (IFN != "-" && !IFN.endswith(".c")) {
    errs() << "error: unknown input file (should end in '.c')\n";
    return EXIT_FAILURE;
  }
  StringRef OFN = OutputFilenameOpt;
  if (OFN.empty()) {
    OFN = "-";
  }

  std::unique_ptr<AST::CompoundStmt> root(driver.parse(IFN));
  if (root == nullptr) {
    errs() << "warning: empty program\n";
    return EXIT_SUCCESS;
  }

  driver.dump(root.get(), OFN);

  return EXIT_SUCCESS;
}
