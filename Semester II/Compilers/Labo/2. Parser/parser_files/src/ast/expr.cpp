//
// Configuration
//

#include <iostream>

#include <llvm/Support/raw_os_ostream.h>

#include "ast.hpp"

using namespace llvm;
using namespace cheetah;
using namespace AST;

namespace cheetah {

std::string AST::to_string(const Operator &op) {
  switch(op) {
    case Operator::EQUAL: return "EQUAL";
    case Operator::CEQ:   return "CEQ";
    case Operator::CNE:   return "CNE";
    case Operator::CLT:   return "CLT";
    case Operator::CLE:   return "CLE";
    case Operator::CGT:   return "CGT";
    case Operator::CGE:   return "CGE";
    case Operator::PLUS:  return "PLUS";
    case Operator::MINUS: return "MINUS";
    case Operator::MUL:   return "MUL";
    case Operator::DIV:   return "DIV";
    case Operator::EXP:   return "EXP";
    case Operator::MOD:   return "MOD";
    default:              return "unknown operator";
  }
}

raw_ostream &AST::operator<<(llvm::raw_ostream &O, const Operator &op) {
  O << to_string(op);
  return O;
}

} // namespace cheetah
