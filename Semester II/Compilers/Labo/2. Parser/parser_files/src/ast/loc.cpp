//
// Configuration
//

#include <iostream>

#include <llvm/Support/raw_os_ostream.h>

#include "ast.hpp"
#include "auxiliary.hpp"

using namespace llvm;
using namespace cheetah;
using namespace AST;


raw_ostream &AST::operator<<(raw_ostream &O, const Location::Position &pos) {
  if (pos.filename)
    O << *pos.filename << ":";
  return O << pos.line << "." << pos.column;
}

raw_ostream &AST::operator<<(raw_ostream &O, const Location &loc) {
  unsigned int end_col = 0 < loc.end.column ? loc.end.column - 1 : 0;
  O << loc.begin;
  if (loc.end.filename &&
      (!loc.begin.filename || *loc.begin.filename != *loc.end.filename))
    O << "-" << loc.end.filename << ":" << loc.end.line << "." << end_col;
  else if (loc.begin.line < loc.end.line)
    O << "-" << loc.end.line << "." << end_col;
  else if (loc.begin.column < end_col)
    O << "-" << end_col;
  return O;
}

std::ostream &AST::operator<<(std::ostream &O, const Location &loc) {
  raw_os_ostream wrapper(O);
  wrapper << loc;
  return O;
}

bool AST::Location::Position::isValid() const {
  return filename != nullptr && line != 0 && column != 0;
}

bool AST::Location::isValid() const { return begin.isValid() && end.isValid(); }
