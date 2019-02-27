#if !defined(yyFlexLexerOnce)
#include <FlexLexer.h>
#endif

#include <string>
#include <vector>

enum Token
{
  // begin at 256, allowing us to use plain ASCII as unnamed tokens
  RETURN = 256,
  IF, ELSE, WHILE, FOR,
  IDENTIFIER, INTEGER, FLOAT, STRING,
  EQUAL, CEQ, CNE, CLT, CLE, CGT, CGE, PLUS, MINUS, MUL, DIV, EXP, MOD
};

struct Location
{
  size_t line;
  size_t column;
};

class Lexer : public yyFlexLexer {
public:
  Lexer(std::istream *in) : yyFlexLexer(in) {};
  int yylex() override;

  void set_debug_level(int level) { yy_flex_debug = level; }

  Location begin = {1, 1}, end = {1, 1};

private:
  void update_location();

  void error(const std::string &message);
};
