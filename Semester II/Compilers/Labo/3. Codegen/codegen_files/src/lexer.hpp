//
// Configuration
//

#pragma once

#if !defined(yyFlexLexerOnce)
#include <FlexLexer.h>
#endif

#include "parser.hpp"

// Override the interface for yylex since we namespaced it
#undef YY_DECL
#define YY_DECL int cheetah::Lexer::yylex()


//
// Module definitions
//

namespace cheetah {
class Lexer : public yyFlexLexer {
public:
  Lexer(std::istream *in)
      : yyFlexLexer(in), value(nullptr), location(nullptr){};

  // Save the pointer to value so we can change it, and invoke the lexer
  int yylex(cheetah::Parser::semantic_type *lval,
            cheetah::Parser::location_type *lloc) {
    value = lval;
    location = lloc;
    return (yylex());
  }

  void set_debug_level(int level) { yy_flex_debug = level; }

private:
  // Scanning function created by Flex; make this private to force usage
  // of the overloaded method so we can get a pointer to Bison's value
  int yylex() override;

  // Pointer to value and location (provided by Bison in overloaded yylex)
  Parser::semantic_type *value;
  Parser::location_type *location;

  void update_location();
};
} // namespace cheetah
