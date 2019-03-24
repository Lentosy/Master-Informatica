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

AST::IntLiteral *Sema::ParseIntLiteral(const Location &Loc, std::string IntToken) {

  long long parsed = strtol(IntToken.c_str(), nullptr, 0);
//  if(parsed == 0L){
//    throw semantic_error(Loc->location, "invalid conversion");
//  } 
  IntLiteral *IntLiteral = new AST::IntLiteral(parsed);
  IntLiteral->location = Loc;
  return IntLiteral;
}


AST::FloatLiteral *Sema::ParseFloatLiteral(const Location &Loc, std::string FloatToken) {
  float parsed = strtof(FloatToken.c_str(), nullptr);
//  if(parsed == 0.0) {
//    throw semantic_error(Loc->location, "invalid conversion");
//  }
  FloatLiteral *FloatLiteral = new AST::FloatLiteral(parsed);
  FloatLiteral->location = Loc;
  return FloatLiteral;
}
