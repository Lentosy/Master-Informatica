/* set-up */
%option yyclass="Lexer"
%option noyywrap
%option c++
%option warn
%option yylineno

/* code reproduced verbatim */
%{
  #include <string>

  #include "lexer.hpp"

  using namespace llvm;
  using namespace cheetah;
  
  #define YY_USER_ACTION update_location();

  // Disable warnings about the deprecated 'register' storage class specifier
  #ifdef __clang__
  # pragma GCC diagnostic ignored "-Wdeprecated-register"
  #endif
%}

%%

[ \t\n]                   ;

"return"                  return token::RETURN;
"if"                      return token::IF;
"else"                    return token::ELSE;
"while"                   return token::WHILE;
"for"                     return token::FOR;
 
[a-zA-Z_][a-zA-Z0-9_]*    return token::IDENTIFIER;
[0-9]+\.[0-9]*            return token::FLOAT;
[0-9]+                    return token::INTEGER;
\"(\\.|[^\\"])*\"         return token::STRING;

"="                       return token::EQUAL;
"=="                      return token::CEQ;
"!="                      return token::CNE;
"<"                       return token::CLT;
"<="                      return token::CLE;
">"                       return token::CGT;
">="                      return token::CGE;
"+"                       return token::PLUS;
"-"                       return token::MINUS;
"*"                       return token::MUL;
"/"                       return token::DIV;
"^"                       return token::EXP;
"%"                       return token::MOD;

"("                       return '(';
")"                       return ')';
"{"                       return '{';
"}"                       return '}';
"["                       return '[';
"]"                       return ']';
","                       return ',';
";"                       return ';';

.                         { errs() << "Unknown symbol '" << YYText() << "'\n";
                            yyterminate(); }

%%

void Lexer::update_location() {
  location->begin = location->end;

  std::string text = YYText();
  for (char &c: text) {
    if (c == '\n') {
      location->end.line++;
      location->end.column = 1;
    } else {
      location->end.column++;
    }
  }
}
