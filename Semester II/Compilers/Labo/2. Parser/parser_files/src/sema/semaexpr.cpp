//
// Configuration
//

#include "ast.hpp"
#include "auxiliary.hpp"
#include "sema.hpp"

#define DEBUG_TYPE "cheetah::sema"

using namespace llvm;
using namespace cheetah;

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

AST::IntLiteral *Sema::ParseInt(AST::Expr *SubExpr) {

}

AST::FloatLiteral *Sema::ParseFloat(AST::Expr *SubExpr) {
  print(*SubExpr);
}

AST::StringLiteral *Sema::ParseString(AST::Expr *SubExpr) {

}
