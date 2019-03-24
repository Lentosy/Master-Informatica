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

  AST::Identifier *ident_t;
  AST::Decl *decl_t;
  AST::VarDecl *var_decl_t;
  AST::VariableList *varlist_t;

  AST::CallExpr *call_expr_t;
  AST::ExprList *expr_list_t;
  // TODO: add some more semantic value types
}

// Define our terminal symbols (tokens). This should match our lexer.l lex file.
%token RETURN IF ELSE WHILE FOR
%token IDENTIFIER INTEGER FLOAT STRING
%token EQUAL
%token CEQ CNE CLT CLE CGT CGE
%token PLUS MINUS MUL DIV EXP MOD

// Define the type of node our nonterminal symbols represent.
// The types refer to the %union declaration above.
%type <stmt_t> stmt
%type <compoundstmt_t> stmts block program

%type <expr_t> expr decl_expr

%type <ident_t> ident
%type <decl_t> decl func_decl
%type <var_decl_t> var_decl
%type <varlist_t> func_args

//%type <decl_expr_t> decl_call
%type <call_expr_t> func_call
%type <expr_list_t> expr_list
// TODO: add some more %type's

// TODO: precedence rules
// 3.2.1 OPERATORS
// hoe lager in deze lijst, hoe hoger de associativiteit
%nonassoc EQUAL
%nonassoc CEQ CNE CLT CLE CGT CGE
%left PLUS MINUS
%left MUL DIV MOD
%nonassoc UMINUS
// unary operators??
%right EXP
// x = -5

%start program
%%

program:
  stmts {
    driver.setProgram($1);
  };


////////////////////////////////////////////////////////////////////////////////
// Statements
//

stmt:
  ';' {
    $$ = nullptr;  
  } |
  expr ';' {
    $$ = $1;
  } |
  decl {
    $$ = new AST::DeclStmt($1);
    $$->location = @$;
  } |
  IF '(' expr ')' block {
    $$ = new AST::IfStmt($3, $5);
    $$->location = @$;
  } |
  IF '(' expr ')' block ELSE block {
    $$ = new AST::IfStmt($3, $5, $7);
    $$->location = @$;
  } |
  IF '(' expr ')' stmt {
    $$ = new AST::IfStmt($3, $5);
  } |
  IF '(' expr ')' stmt ELSE stmt {
    $$ = new AST::IfStmt($3, $5, $7);
  } |
  WHILE '(' expr ')' block {
    $$ = new AST::WhileStmt($3, $5);
    $$->location = @$;
  } |
  FOR '(' stmt expr ';' expr  ')' block {
    $$ = new AST::ForStmt($3, $4, $6, $8);
    $$->location = @$;
  } |
  RETURN {
    $$ = new AST::ReturnStmt();
    $$->location = @$;
  } |
  RETURN expr {
    $$ = new AST::ReturnStmt($2);
    $$->location = @$;
  }
  ;

stmts:
  stmt {
    $$ = sema.ParseCompoundStmt(@$, $1);
  } | 
  stmts stmt {
    $$ = sema.ParseCompoundStmt(@$, $2, $1);
  };

block:
  '{' '}' {
    $$ = sema.ParseCompoundStmt(@$);
  } | 
  '{' stmts '}' {
    $$ = $2;
    $$->location = @$;
  };



////////////////////////////////////////////////////////////////////////////////
// Expressions
//

expr:
  decl_expr {
    $$ = $1;
  } |

  decl_expr EQUAL expr {
    $$ = new AST::Assignment($<decl_expr_t>1, $3);
    $$->location = @$;
  } |

  '(' expr ')' {
    $$ = $2;
  } |

  func_call {
    $$ = $1;
  } |

  STRING {
    std::string tekst = yytext(lexer);
    for(int i = 1; i < tekst.size(); i++){
      tekst[i - 1] = tekst[i];
    }
    tekst.resize(tekst.size() - 2); // remove start " en einde"
    StringLiteral *StringLiteral = new AST::StringLiteral(tekst);
    StringLiteral->location = @$;
    $$ = StringLiteral;
  } | 

  FLOAT {
    $$ = sema.ParseFloatLiteral(@$, yytext(lexer));
  } |

  INTEGER {
    $$ = sema.ParseIntLiteral(@$, yytext(lexer));
  } |

  expr CEQ expr {
    $$ = new AST::BinaryOp($1, Operator::CEQ, $3);
    $$->location = @$;
  } |

  expr CNE expr {
    $$ = new AST::BinaryOp($1, Operator::CNE, $3);
    $$->location = @$;
  } |

  expr CLT expr {
    $$ = new AST::BinaryOp($1, Operator::CLT, $3);
    $$->location = @$;
  } |
  
  expr CLE expr {
    $$ = new AST::BinaryOp($1, Operator::CLE, $3);
    $$->location = @$;
  } |
  
  expr CGT expr {
    $$ = new AST::BinaryOp($1, Operator::CGT, $3);
    $$->location = @$;
  } |
  
  expr CGE expr {
    $$ = new AST::BinaryOp($1, Operator::CGE, $3);
    $$->location = @$;
  } |

  expr PLUS expr {
    $$ = new AST::BinaryOp($1, Operator::PLUS, $3);
    $$->location = @$;
  } |
  
  expr MINUS expr {
    $$ = new AST::BinaryOp($1, Operator::MINUS, $3);
    $$->location = @$;
  } |
  
  expr MUL expr {
    $$ = new AST::BinaryOp($1, Operator::MUL, $3);
    $$->location = @$;
  } |
  
  expr DIV expr {
    $$ = new AST::BinaryOp($1, Operator::DIV, $3);
    $$->location = @$;
  } |
  
  expr MOD expr {
    $$ = new AST::BinaryOp($1, Operator::MOD, $3);
    $$->location = @$;
  } |
  
  expr EXP expr {
    $$ = new AST::BinaryOp($1, Operator::EXP, $3);
    $$->location = @$;
  } |
  
  PLUS expr %prec UMINUS {
    $$ = new AST::UnaryOp(Operator::PLUS, $2);
    $$->location = @$;
  } |

  MINUS expr %prec UMINUS {
    $$ = new AST::UnaryOp(Operator::MINUS, $2);
    $$->location = @$;
  };

decl_expr:
  ident {
    $$ = new AST::DeclRefExpr($1);
    $$->location = @$;
  } | 
  
  ident '[' expr ']' {
    $$ = new AST::DeclRefExpr($1, $3);
    $$->location = @$;
  };



////////////////////////////////////////////////////////////////////////////////
// Declarations
//

ident:
  IDENTIFIER {
    $$ = new AST::Identifier(yytext(lexer));
    $$->location = @$;
  };

decl:
  var_decl ';' {
    $$ = $1;
  } | 
  
  func_decl {
    $$ = $1;
  };


//
// Variables
//
var_decl:
  ident ident {
    auto type = sema.ParseTypeName($1);
    delete $1;

    $$ = new AST::VarDecl($2, type);
    $$->location = @$;
  } | 
  
  ident ident EQUAL expr {
    auto type = sema.ParseTypeName($1);
    delete $1;

    $$ = new AST::VarDecl($2, type, $4);
    $$->location = @$;
  };

//
// Functions
//
func_call:
  ident '(' ')' { // functie zonder parameters: foo();
    $$ = new AST::CallExpr($1);
    $$->location = @$;
  } | 
  
  ident '(' expr_list ')' { // functie met oneindig veel parameters: foo(x, bar(zoo()), y, z, ...)
    $$ = new AST::CallExpr($1, *$3); // pointer naar $3
    $$->location = @$;
  };

expr_list:
  %empty {
    $$ = sema.ParseExprList();
  } | 
  expr {
    $$ = sema.ParseExprList($1);
  } |
  expr_list ',' expr {
    $$ = sema.ParseExprList($3, $1);
  };

func_decl:
  ident ident '(' func_args ')' block {
    auto type = sema.ParseTypeName($1);
    delete $1;
    $$ = new AST::FuncDecl($2, type, *$4, $6);
    $$->location = @$;
    delete $4;
  };

func_args:
  %empty {
    $$ = sema.ParseVariableList();
  } |
  
  var_decl {
    $$ = sema.ParseVariableList($1);
  } | 
  
  func_args ',' var_decl {
    $$ = sema.ParseVariableList($3, $1);
  };
%%

// We have to implement the error function
void Parser::error(const Parser::location_type &loc,
                   const std::string &err) {
  parser_error(err, loc.begin.filename, loc.begin.line, loc.begin.column);
}

// Now that we have the Parser declared, we can declare the Lexer and implement
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
