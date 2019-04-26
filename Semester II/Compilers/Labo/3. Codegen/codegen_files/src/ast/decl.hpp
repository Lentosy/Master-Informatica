//
// Configuration
//

#pragma once

#include <string>
#include <vector>

#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Type.h>

#include "loc.hpp"

namespace cheetah {
namespace AST {
struct Expr;
struct Stmt;
} // namespace AST
} // namespace cheetah


//
// Base structures
//

namespace cheetah {
namespace AST {

struct Identifier {
  std::string string;
  Location location;

  Identifier(const std::string &str) : string(str) {}
};

struct Decl {
  Identifier *name;
  Location location;

  Decl(Identifier *name) : name(name) {}
  virtual ~Decl() { delete name; }
  virtual CODEGEN = 0;
};


//
// Value declarations
//


/// Declaration of something with a value (and hence a type)
struct ValueDecl : public Decl {
  llvm::Type *type;

  ValueDecl(Identifier *Id, llvm::Type *T) : Decl(Id), type(T) {}
  virtual ~ValueDecl(){};
};

/// Variable declaration or definition
struct VarDecl : public ValueDecl {
  Expr *init;

  VarDecl(Identifier *Id, llvm::Type *T, Expr *init = nullptr)
      : ValueDecl(Id, T), init(init) {}
  ~VarDecl() {
    if (init)
      delete init;
  }
  CODEGEN final;
};

typedef std::vector<VarDecl *> VariableList;

/// Function declaration or definition
struct FuncDecl : public ValueDecl {
  Stmt *body;
  VariableList args;

  FuncDecl(Identifier *Id, llvm::Type *T, VariableList args, Stmt *body)
      : ValueDecl(Id, T), body(body), args(args) {}
  ~FuncDecl() {
    delete body;
    for (auto arg : args)
      delete arg;
  }
  CODEGEN final;
};
} // namespace AST
} // namespace cheetah
