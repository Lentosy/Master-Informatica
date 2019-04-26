// set-up
%require "2.5"
%skeleton "lalr1.cc"
%error-verbose
%defines
%define api.location.type {AST::Location}
%define api.namespace {cheetah}
%define parser_class_name {Parser}

// code reproduced verbatim
%code requires {
  #include <vector>

  #include "ast.hpp"
  #include "auxiliary.hpp"

  namespace cheetah {
    class Driver;
    class Lexer;
    class Sema;
  }
}

%code provides {
  namespace cheetah {
    // Syntax-sugar to make token definitions more concise
    typedef Parser::token token;

    // A equivalent of `syntax_error` for reporting errors from sema
    struct semantic_error : Parser::syntax_error
    {
      semantic_error (const Parser::location_type& l, const std::string& m);
    };
  }
}

%lex-param { Lexer &lexer }
%parse-param { Lexer &lexer }

%parse-param { Sema &sema }

%lex-param { Driver &driver }
%parse-param { Driver &driver }

%locations

%initial-action {
  // Initialize the initial location.
  @$.begin.filename = @$.end.filename = &driver.filename();
  @$.end.line = @$.end.column = 1;
};

%code {
  #include "driver.hpp"
  #include "sema.hpp"

  using namespace cheetah;

  // forward declaration of the Flex interface
  static int yylex(Parser::semantic_type *value,
                   Parser::location_type *location,
                   Lexer &lexer, Driver &driver);
  static std::string yytext(Lexer &lexer);
}

// Represents the different ways we can access our data
%union {
  AST::Stmt *stmt_t;
  AST::CompoundStmt *compoundstmt_t;

  AST::Expr *expr_t;
  AST::DeclRefExpr *decl_expr_t;
  AST::ExprList *exprlist_t;

  AST::Identifier *ident_t;
  AST::Decl *decl_t;
  AST::VarDecl *var_decl_t;
  AST::VariableList *varlist_t;
}

// Define our terminal symbols (tokens). This should match our lexer.l lex file.
%token RETURN IF ELSE WHILE FOR
%token IDENTIFIER INTEGER FLOAT STRING
%token EQUAL
%token CEQ CNE CLT CLE CGT CGE
%token PLUS MINUS MUL DIV EXP MOD

// Define the type of node our nonterminal symbols represent.
// The types refer to the %union declaration above.
%type <stmt_t> stmt ifstmt whilestmt forstmt
%type <compoundstmt_t> stmts block program

%type <expr_t> expr call literal decl_expr
%type <exprlist_t> call_args

%type <ident_t> ident
%type <decl_t> decl func_decl
%type <var_decl_t> var_decl
%type <varlist_t> func_args

// Regular precedence rules for mathematical operators
%precedence EQUAL
%nonassoc CEQ CNE CLT CLE CGT CGE
%left PLUS MINUS
%left MUL DIV MOD
%precedence UNARY
%right EXP

%start program
%%

program:
    stmts {
      driver.setProgram($1);
    }
  ;



////////////////////////////////////////////////////////////////////////////////
// Statements
//

stmt:
    ';' { $$ = nullptr; }
  | expr ';' {
      $$ = $1;
    }
  | decl {
      $$ = new AST::DeclStmt($1);
    }
  | ifstmt
  | whilestmt
  | forstmt
  | RETURN expr ';' {
      $$ = new AST::ReturnStmt($2);
    }
  | RETURN ';' {
      $$ = new AST::ReturnStmt();
    }
  ;

stmts:
    stmt {
      $$ = sema.ParseCompoundStmt(@$, $1);
    }
  | stmts stmt {
      $$ = sema.ParseCompoundStmt(@$, $2, $1);
    }
  ;

block:
    '{' '}' {
      $$ = sema.ParseCompoundStmt(@$);
    }
  | '{' stmts '}' {
      $$ = $2;
    }
  ;


//
// Control flow
//

ifstmt:
    IF '(' expr ')' block {
      $$ = new AST::IfStmt($3, $5);
    }
  | IF '(' expr ')' block ELSE block {
      $$ = new AST::IfStmt($3, $5, $7);
    }
  ;

whilestmt:
    WHILE '(' expr ')' block {
      $$ = new AST::WhileStmt($3, $5);
    }
  ;

forstmt:
    FOR '(' forinit ';' expr ';' expr ')' block {
      $$ = new AST::ForStmt($<stmt_t>3, $5, $7, $9);
    }
  ;

forinit:
    var_decl {
      $<stmt_t>$ = new AST::DeclStmt($1);
    }
  | expr {
      $<stmt_t>$ = $1;
    }
  ;



////////////////////////////////////////////////////////////////////////////////
// Expressions
//

expr:
    decl_expr {
      $$ = $1;
    }
  | decl_expr EQUAL expr {
      $$ = new AST::Assignment($<decl_expr_t>1, $3);
    }
  | '(' expr ')' {
      $$ = $2;
    }
  | call
  | literal
  | expr CEQ expr          { $$ = new AST::BinaryOp($1, AST::Operator::CEQ,   $3); }
  | expr CNE expr          { $$ = new AST::BinaryOp($1, AST::Operator::CNE,   $3); }
  | expr CLT expr          { $$ = new AST::BinaryOp($1, AST::Operator::CLT,   $3); }
  | expr CLE expr          { $$ = new AST::BinaryOp($1, AST::Operator::CLE,   $3); }
  | expr CGT expr          { $$ = new AST::BinaryOp($1, AST::Operator::CGT,   $3); }
  | expr CGE expr          { $$ = new AST::BinaryOp($1, AST::Operator::CGE,   $3); }
  | expr PLUS expr         { $$ = new AST::BinaryOp($1, AST::Operator::PLUS,  $3); }
  | expr MINUS expr        { $$ = new AST::BinaryOp($1, AST::Operator::MINUS, $3); }
  | expr MUL expr          { $$ = new AST::BinaryOp($1, AST::Operator::MUL,   $3); }
  | expr DIV expr          { $$ = new AST::BinaryOp($1, AST::Operator::DIV,   $3); }
  | expr MOD expr          { $$ = new AST::BinaryOp($1, AST::Operator::MOD,   $3); }
  | MINUS expr %prec UNARY { $$ = new AST::UnaryOp(     AST::Operator::MINUS, $2); }
  | PLUS expr %prec UNARY  { $$ = new AST::UnaryOp(     AST::Operator::PLUS,  $2); }
  | expr EXP expr          { $$ = new AST::BinaryOp($1, AST::Operator::EXP,   $3); }
  ;

decl_expr:
    ident {
      $$ = new AST::DeclRefExpr($1);
    }
  | ident '[' expr ']' {
      $$ = new AST::DeclRefExpr($1, $3);
    }
  ;


//
// Literals
//

literal:
    INTEGER {
      $$ = sema.ParseIntLiteral(@$, yytext(lexer));
    }
  ;


//
// Functions
//

call:
    ident '(' call_args ')' {
      $$ = new AST::CallExpr($1, *$3);
      delete $3;
     }

call_args:
    %empty {
      $$ = sema.ParseExprList();
    }
  | expr {
      $$ = sema.ParseExprList($1);
    }
  | call_args ',' expr {
      $$ = sema.ParseExprList($3, $1);
    }
  ;



////////////////////////////////////////////////////////////////////////////////
// Declarations
//

ident:
    IDENTIFIER {
      $$ = new AST::Identifier(yytext(lexer));
    }
  ;

decl:
    var_decl ';' {
      $$ = $1;
    }
  | func_decl {
      $$ = $1;
    }
  ;


//
// Variables
//

var_decl:
    ident ident {
      auto type = sema.ParseTypeName($1);
      delete $1;

      $$ = new AST::VarDecl($2, type);
    }
  | ident ident EQUAL expr {
      auto type = sema.ParseTypeName($1);
      delete $1;

      $$ = new AST::VarDecl($2, type, $4);
    }
  ;


//
// Functions
//

func_decl:
    ident ident '(' func_args ')' block {
      auto type = sema.ParseTypeName($1);
      delete $1;

      $$ = new AST::FuncDecl($2, type, *$4, $6);
      delete $4;
    }
  ;

func_args:
    %empty {
      $$ = sema.ParseVariableList();
    }
  | var_decl {
      $$ = sema.ParseVariableList($1);
    }
  | func_args ',' var_decl {
      $$ = sema.ParseVariableList($3, $1);
    }
  ;

%%

// We have to implement the error function
void Parser::error(const Parser::location_type &loc,
                   const std::string &err) {
  parser_error(err, loc.begin.filename, loc.begin.line, loc.begin.column);
}

// Now that we have the parser declared, we can declare the Lexer and implement
// the Flex interface
#include "lexer.hpp"
static int yylex(Parser::semantic_type *value,
                 Parser::location_type *location,
                 Lexer &lexer, Driver &) {
  return lexer.yylex(value, location);
}
static std::string yytext(Lexer &lexer) {
  return lexer.YYText();
}

semantic_error::semantic_error(const Parser::location_type& l,
                               const std::string& m) : Parser::syntax_error(l, m)
{ }
