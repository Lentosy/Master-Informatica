//
// Configuration
//

#pragma once

#include <string>
#include <vector>

#include "decl.hpp"
#include "stmt.hpp"


//
// Base structures
//

namespace cheetah {
namespace AST {

struct Expr : public Stmt {
  virtual ~Expr() {}
  virtual CODEGEN = 0;
};

typedef std::vector<Expr *> ExprList;


//
// Literals
//


struct IntLiteral : public Expr {
  int64_t value;

  IntLiteral(long long value) : value(value) {}
  CODEGEN final;
};

struct FloatLiteral : public Expr {
  double value;

  FloatLiteral(double value) : value(value) {}
  CODEGEN final;
};

struct StringLiteral : public Expr {
  std::string value;

  StringLiteral(const std::string &value) : value(value) {}
  CODEGEN final;
};


//
// Operators
//

enum class Operator {
  EQUAL,
  CEQ, CNE, CLT, CLE, CGT, CGE,
  PLUS, MINUS, MUL, DIV, EXP, MOD,
  END_OPERATOR
};

std::string to_string(const Operator &op);
llvm::raw_ostream &operator<<(llvm::raw_ostream &O, const AST::Operator &op);

struct UnaryOp : public Expr {
  Operator op;
  Expr *right;

  UnaryOp(Operator op, Expr *right) : op(op), right(right) {}
  ~UnaryOp() { delete right; }
  CODEGEN final;
};

struct BinaryOp : public Expr {
  Expr *left;
  Operator op;
  Expr *right;

public:
  BinaryOp(Expr *left, Operator op, Expr *right)
      : left(left), op(op), right(right) {}
  ~BinaryOp() {
    delete left;
    delete right;
  }
  CODEGEN final;
};


//
// Functions
//

// A reference to a declared variable or other value declaration
struct DeclRefExpr : public Expr {
  Identifier *decl;
  Expr *index;

  DeclRefExpr(Identifier *decl, Expr *index = nullptr)
      : decl(decl), index(index) {}
  ~DeclRefExpr() {
    delete decl;
    if (index)
      delete index;
  }
  CODEGEN final;
};

// Function call
struct CallExpr : public Expr {
  Identifier *name;
  ExprList args;

  CallExpr(Identifier *name, ExprList &args) : name(name), args(args) {}
  CallExpr(Identifier *name) : name(name) {}
  ~CallExpr() {
    delete name;
    for (auto arg : args)
      delete arg;
  }
  CODEGEN final;
};


//
// Variables
//

struct Assignment : public Expr {
  DeclRefExpr *left;
  Expr *right;

  Assignment(DeclRefExpr *left, Expr *right) : left(left), right(right) {}
  ~Assignment() {
    delete left;
    delete right;
  }
  CODEGEN final;
};

} // namespace AST
} // namespace cheetah
