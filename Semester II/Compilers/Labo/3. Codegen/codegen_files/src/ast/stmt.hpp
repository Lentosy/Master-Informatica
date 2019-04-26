//
// Configuration
//

#pragma once

#include <vector>

#include "loc.hpp"

namespace cheetah {
namespace AST {
struct Decl;
struct Expr;
} // namespace AST
} // namespace cheetah


//
// Base structures
//

namespace cheetah {
namespace AST {

struct Stmt {
  virtual ~Stmt(){};
  virtual CODEGEN = 0;

  Location location;
};

// Adaptor class for mixing declarations with statements and expressions
struct DeclStmt : public Stmt {
  Decl *decl;

  DeclStmt(Decl *D) : decl(D) {}
  ~DeclStmt() { delete decl; }
  CODEGEN final;
};


//
// Functions
//

struct ReturnStmt : public Stmt {
  Expr *expr;

  ReturnStmt(Expr *E = nullptr) : expr(E) {}
  ~ReturnStmt() {
    if (expr)
      delete expr;
  }
  CODEGEN final;
};


//
// Compound statements
//

struct CompoundStmt : public Stmt {
  std::vector<Stmt *> body;

  ~CompoundStmt() {
    for (auto *S : body)
      delete S;
  }
  CODEGEN final;

  void push_back(Stmt *S) { body.push_back(S); }
};

struct IfStmt : public Stmt {
  Expr *cond;
  Stmt *then;
  Stmt *elsev;

  IfStmt(Expr *cond, Stmt *then, Stmt *elsev = nullptr)
      : cond(cond), then(then), elsev(elsev) {}
  ~IfStmt() {
    delete cond;
    delete then;
    if (elsev)
      delete elsev;
  }
  CODEGEN final;
};

struct WhileStmt : public Stmt {
  Expr *cond;
  Stmt *body;

  WhileStmt(Expr *cond, Stmt *body) : cond(cond), body(body) {}
  ~WhileStmt() {
    delete cond;
    delete body;
  }
  CODEGEN final;
};

struct ForStmt : public Stmt {
  Stmt *init;
  Expr *cond;
  Expr *inc;
  Stmt *body;

  ForStmt(Stmt *init, Expr *cond, Expr *inc, Stmt *body)
      : init(init), cond(cond), inc(inc), body(body) {}
  ~ForStmt() {
    delete init;
    delete cond;
    delete inc;
    delete body;
  }
  CODEGEN final;
};

} // namespace AST
} // namespace cheetah
