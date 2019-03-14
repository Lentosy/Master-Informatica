//
// Configuration
//

#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/LLVMContext.h>

#include "ast.hpp"
#include "auxiliary.hpp"
#include "sema.hpp"

#define DEBUG_TYPE "cheetah::sema"

using namespace llvm;
using namespace cheetah;


Type *Sema::ParseTypeName(const AST::Identifier *type) {
  if (type->string.compare("int") == 0)
    return (Type *)Type::getInt32Ty(cheetah::LLVMContext);
  else if (type->string.compare("double") == 0)
    return Type::getFloatTy(cheetah::LLVMContext);
  else if (type->string.compare("void") == 0)
    return Type::getVoidTy(cheetah::LLVMContext);
  else
    throw semantic_error(type->location, "unknown type name " + type->string);
}

Type *Sema::ParseArrayTypeName(const AST::Identifier *type,
                               const AST::IntLiteral *elements) {
  Type *elementType = ParseTypeName(type);
  if (elements->value < 1)
    throw semantic_error(elements->location, "invalid array size");

  return cast<Type>(ArrayType::get(elementType, elements->value));
}
