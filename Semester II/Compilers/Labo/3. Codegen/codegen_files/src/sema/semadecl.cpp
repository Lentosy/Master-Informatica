//
// Configuration
//

#include "ast.hpp"
#include "auxiliary.hpp"
#include "sema.hpp"

#define DEBUG_TYPE "cheetah::sema"

using namespace llvm;
using namespace cheetah;

AST::VariableList *Sema::ParseVariableList(AST::VarDecl *SubVariable,
                                           AST::VariableList *RunningVarList) {
  // Re-use any running expression list statement (this is due to how we parse
  // groups of variables)
  auto *VarList = RunningVarList;
  if (VarList == nullptr)
    VarList = new AST::VariableList();

  // Ignore empty expressions
  if (SubVariable != nullptr)
    VarList->push_back(SubVariable);

  return VarList;
}