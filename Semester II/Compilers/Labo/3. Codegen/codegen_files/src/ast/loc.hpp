//
// Configuration
//

#pragma once

#include <iosfwd>

#include <llvm/Support/raw_ostream.h>

namespace cheetah {
namespace AST {

class Location {
public:
  struct Position {
    unsigned int line = 0;
    unsigned int column = 0;
    std::string *filename = nullptr;

    bool isValid() const;
  };
  Position begin;
  Position end;

  bool isValid() const;
};

llvm::raw_ostream &operator<<(llvm::raw_ostream &out,
                              const Location::Position &pos);
llvm::raw_ostream &operator<<(llvm::raw_ostream &out, const Location &loc);

std::ostream &operator<<(std::ostream &out, const Location &loc);
} // namespace AST
} // namespace cheetah
