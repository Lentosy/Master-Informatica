//
// Configuration
//

#pragma once

#include "ast.hpp"
#include "parser.hpp"


//
// Module definitions
//

namespace cheetah {

extern llvm::LLVMContext LLVMContext;

using namespace AST;

class Sema {
public:
  Sema() {}

  llvm::Type *ParseTypeName(const Identifier *type);
  llvm::Type *ParseArrayTypeName(const Identifier *type,
                                 const IntLiteral *elements);

  CompoundStmt *ParseCompoundStmt(const Location &Loc, Stmt *SubStmt = nullptr,
                                  CompoundStmt *RunningCompoundStmt = nullptr);

  IntLiteral *ParseIntLiteral(const Location &Loc, std::string IntToken);
  FloatLiteral *ParseFloatLiteral(const Location &Loc, std::string FloatToken);
  ExprList *ParseExprList(Expr *SubExpr = nullptr,
                          ExprList *RunningExprList = nullptr);

  VariableList *ParseVariableList(VarDecl *SubVariable = nullptr,
                                  VariableList *RunningVarList = nullptr);
};
} // namespace cheetah
