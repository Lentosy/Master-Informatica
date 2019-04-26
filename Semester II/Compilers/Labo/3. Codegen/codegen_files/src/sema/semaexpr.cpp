//
// Configuration
//

#include "ast.hpp"
#include "auxiliary.hpp"
#include "sema.hpp"

#include <cstdlib>

#define DEBUG_TYPE "cheetah::sema"

using namespace llvm;
using namespace cheetah;

AST::IntLiteral *Sema::ParseIntLiteral(const Location &,
                                       std::string IntToken) {
  return new AST::IntLiteral(atoi(IntToken.c_str()));
}

AST::FloatLiteral *Sema::ParseFloatLiteral(const Location &Loc,
                                           std::string) {
  throw(semantic_error(Loc, "unsupported floating-point literal"));
}

AST::ExprList *Sema::ParseExprList(AST::Expr *SubExpr,
                                   AST::ExprList *RunningExprList) {
  // Re-use any running expression list statement (this is due to how we parse
  // groups of expressions)
  auto *ExprList = RunningExprList;
  if (ExprList == nullptr)
    ExprList = new AST::ExprList();

  // Ignore empty expressions
  if (SubExpr != nullptr)
    ExprList->push_back(SubExpr);

  return ExprList;
}
