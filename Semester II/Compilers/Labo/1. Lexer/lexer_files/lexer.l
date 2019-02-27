/* set-up */
%option c++
%option yyclass="Lexer"
%option warn
%option noyywrap

/* code reproduced verbatim */
%{
  #include <iostream>
  #include "lexer.hpp"
  #define YY_USER_ACTION update_location();
  #include <memory.h>  /*zelf toegevoegd*/
%}


 /*
   Definitions
  */

DIGIT    [0-9]
WHITESPACE   [ \t\n\r]
ID    [a-z_][a-z0-9_]*
COMMENT   "//"[^\n\r]*
FLOAT   [0-9]+\.[0-9]*
STRING \"[^\n]+\"
/* 3.4: Definiëren van de toestand 'BLOCK_COMMENT' */
%x BLOCK_COMMENT 



%%



 /*
   Rules
  */
"="        return EQUAL;
"=="       return CEQ;
"!="       return CNE;
"<"        return CLT;
">"        return CGT;
"<="       return CLE;
">="       return CGE;
"+"        return PLUS;
"-"        return MINUS;
"*"        return MUL;
"/"        return DIV;
"^"        return EXP;
"%"        return MOD;
","        return ',';
";"        return ';'; /*opgelet, werkt niet met " en in regex deel zonder haakjes of met "" */
"("        return '(';
")"        return ')';
"{"        return '{';
"}"        return '}';
"["        return '[';
"]"        return ']';
"return"  return RETURN;
"if"      return IF;
"else"    return ELSE;
"while"   return WHILE;
"for"     return FOR;
{COMMENT}     /*must be ignored*/
{FLOAT}       return FLOAT;
{DIGIT}+      return INTEGER;
{WHITESPACE}+       
{ID}          return IDENTIFIER;
{STRING}      return STRING;
.             error("unknown symbol");



<INITIAL>{ /* 3.4: De 'INITIAL' staat is voorgedefinieerd */
	"/*" BEGIN(BLOCK_COMMENT); /* 3.4: Als we het startsymbool van een block comment tegenkomen, begint C_COMMENT */
}
<BLOCK_COMMENT>{ /* 3.4: Nodig dat 'C_COMMENT' gedefinieerd wordt bij definities, met %x optie */
	"*/"    BEGIN(INITIAL);  /* Als we het einde van een block comment tegenkomen, keren we terug naar INITIAL staat. Dit zal ofwel opnieuw een startsymbool tegenkomen, ofwel niets */
	[^*\n]+   // Alles opeten behalve new line
	\n      yylineno++; // dan new line opeten als die bestaat en lijnnummer incrementeren
	<<EOF>> {
			error("unterminated block comment"); 
			BEGIN(INITIAL);
		}
}

%%

char *buffer = (char*)malloc(YY_BUF_SIZE);
// update the location information of the lexer
void Lexer::update_location() {
  if(yytext[0] == '\n' || yytext[0] == '\r'){
   begin.column = 1; 
   end.column = 1;
   begin.line++; 
   end.line++;
   free(buffer);
   buffer = (char*)malloc(YY_BUF_SIZE);
  } else {
    begin.column = end.column;
    end.column += strlen(yytext);
    strcat(buffer, yytext);
  }
}

// report a syntax error
void Lexer::error(const std::string &message) {
  std::cerr << "Syntax error: " << message << " at line " << begin.line << 
  " column " << begin.column << std::endl;
  std::cerr << buffer << std::endl;
  printf("%*c^\n", (int)begin.column-1, ' ');
}
