// A Bison parser, made by GNU Bison 3.0.4.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.


// First part of user declarations.

#line 37 "/pract/parser.cpp" // lalr1.cc:404

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

#include "parser.hpp"

// User implementation prologue.

#line 51 "/pract/parser.cpp" // lalr1.cc:412
// Unqualified %code blocks.
#line 53 "src/parser.y" // lalr1.cc:413

  #include "driver.hpp"
  #include "sema.hpp"

  using namespace cheetah;

  // forward declaration of the Flex interface
  static int yylex(Parser::semantic_type *value,
                   Parser::location_type *location,
                   Lexer &lexer, Driver &driver);
  static std::string yytext(Lexer &lexer);

#line 66 "/pract/parser.cpp" // lalr1.cc:413


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (/*CONSTCOND*/ false)
# endif


// Suppress unused-variable warnings by "using" E.
#define YYUSE(E) ((void) (E))

// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << std::endl;                  \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yystack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE(Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void>(0)
# define YY_STACK_PRINT()                static_cast<void>(0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 7 "src/parser.y" // lalr1.cc:479
namespace cheetah {
#line 152 "/pract/parser.cpp" // lalr1.cc:479

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  Parser::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr = "";
        char const *yyp = yystr;

        for (;;)
          switch (*++yyp)
            {
            case '\'':
            case ',':
              goto do_not_strip_quotes;

            case '\\':
              if (*++yyp != '\\')
                goto do_not_strip_quotes;
              // Fall through.
            default:
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }


  /// Build a parser object.
  Parser::Parser (Lexer &lexer_yyarg, Sema &sema_yyarg, Driver &driver_yyarg)
    :
#if YYDEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      lexer (lexer_yyarg),
      sema (sema_yyarg),
      driver (driver_yyarg)
  {}

  Parser::~Parser ()
  {}


  /*---------------.
  | Symbol types.  |
  `---------------*/

  inline
  Parser::syntax_error::syntax_error (const location_type& l, const std::string& m)
    : std::runtime_error (m)
    , location (l)
  {}

  // basic_symbol.
  template <typename Base>
  inline
  Parser::basic_symbol<Base>::basic_symbol ()
    : value ()
  {}

  template <typename Base>
  inline
  Parser::basic_symbol<Base>::basic_symbol (const basic_symbol& other)
    : Base (other)
    , value ()
    , location (other.location)
  {
    value = other.value;
  }


  template <typename Base>
  inline
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const semantic_type& v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}


  /// Constructor for valueless symbols.
  template <typename Base>
  inline
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const location_type& l)
    : Base (t)
    , value ()
    , location (l)
  {}

  template <typename Base>
  inline
  Parser::basic_symbol<Base>::~basic_symbol ()
  {
    clear ();
  }

  template <typename Base>
  inline
  void
  Parser::basic_symbol<Base>::clear ()
  {
    Base::clear ();
  }

  template <typename Base>
  inline
  bool
  Parser::basic_symbol<Base>::empty () const
  {
    return Base::type_get () == empty_symbol;
  }

  template <typename Base>
  inline
  void
  Parser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move(s);
    value = s.value;
    location = s.location;
  }

  // by_type.
  inline
  Parser::by_type::by_type ()
    : type (empty_symbol)
  {}

  inline
  Parser::by_type::by_type (const by_type& other)
    : type (other.type)
  {}

  inline
  Parser::by_type::by_type (token_type t)
    : type (yytranslate_ (t))
  {}

  inline
  void
  Parser::by_type::clear ()
  {
    type = empty_symbol;
  }

  inline
  void
  Parser::by_type::move (by_type& that)
  {
    type = that.type;
    that.clear ();
  }

  inline
  int
  Parser::by_type::type_get () const
  {
    return type;
  }


  // by_state.
  inline
  Parser::by_state::by_state ()
    : state (empty_state)
  {}

  inline
  Parser::by_state::by_state (const by_state& other)
    : state (other.state)
  {}

  inline
  void
  Parser::by_state::clear ()
  {
    state = empty_state;
  }

  inline
  void
  Parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  inline
  Parser::by_state::by_state (state_type s)
    : state (s)
  {}

  inline
  Parser::symbol_number_type
  Parser::by_state::type_get () const
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[state];
  }

  inline
  Parser::stack_symbol_type::stack_symbol_type ()
  {}


  inline
  Parser::stack_symbol_type::stack_symbol_type (state_type s, symbol_type& that)
    : super_type (s, that.location)
  {
    value = that.value;
    // that is emptied.
    that.type = empty_symbol;
  }

  inline
  Parser::stack_symbol_type&
  Parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    value = that.value;
    location = that.location;
    return *this;
  }


  template <typename Base>
  inline
  void
  Parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);

    // User destructor.
    YYUSE (yysym.type_get ());
  }

#if YYDEBUG
  template <typename Base>
  void
  Parser::yy_print_ (std::ostream& yyo,
                                     const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    symbol_number_type yytype = yysym.type_get ();
    // Avoid a (spurious) G++ 4.8 warning about "array subscript is
    // below array bounds".
    if (yysym.empty ())
      std::abort ();
    yyo << (yytype < yyntokens_ ? "token" : "nterm")
        << ' ' << yytname_[yytype] << " ("
        << yysym.location << ": ";
    YYUSE (yytype);
    yyo << ')';
  }
#endif

  inline
  void
  Parser::yypush_ (const char* m, state_type s, symbol_type& sym)
  {
    stack_symbol_type t (s, sym);
    yypush_ (m, t);
  }

  inline
  void
  Parser::yypush_ (const char* m, stack_symbol_type& s)
  {
    if (m)
      YY_SYMBOL_PRINT (m, s);
    yystack_.push (s);
  }

  inline
  void
  Parser::yypop_ (unsigned int n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  Parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  Parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  Parser::debug_level_type
  Parser::debug_level () const
  {
    return yydebug_;
  }

  void
  Parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  inline Parser::state_type
  Parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  inline bool
  Parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  inline bool
  Parser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  Parser::parse ()
  {
    // State.
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

    /// The return value of parse ().
    int yyresult;

    // FIXME: This shoud be completely indented.  It is not yet to
    // avoid gratuitous conflicts when merging into the master branch.
    try
      {
    YYCDEBUG << "Starting parse" << std::endl;


    // User initialization code.
    #line 47 "src/parser.y" // lalr1.cc:741
{
  // Initialize the initial location.
  yyla.location.begin.filename = yyla.location.end.filename = &driver.filename();
  yyla.location.end.line = yyla.location.end.column = 1;
}

#line 534 "/pract/parser.cpp" // lalr1.cc:741

    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, yyla);

    // A new symbol was pushed on the stack.
  yynewstate:
    YYCDEBUG << "Entering state " << yystack_[0].state << std::endl;

    // Accept?
    if (yystack_[0].state == yyfinal_)
      goto yyacceptlab;

    goto yybackup;

    // Backup.
  yybackup:

    // Try to take a decision without lookahead.
    yyn = yypact_[yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token: ";
        try
          {
            yyla.type = yytranslate_ (yylex (&yyla.value, &yyla.location, lexer, driver));
          }
        catch (const syntax_error& yyexc)
          {
            error (yyexc);
            goto yyerrlab1;
          }
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.type_get ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.type_get ())
      goto yydefault;

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", yyn, yyla);
    goto yynewstate;

  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;

  /*-----------------------------.
  | yyreduce -- Do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_(yystack_[yylen].state, yyr1_[yyn]);
      /* If YYLEN is nonzero, implement the default value of the
         action: '$$ = $1'.  Otherwise, use the top of the stack.

         Otherwise, the following line sets YYLHS.VALUE to garbage.
         This behavior is undocumented and Bison users should not rely
         upon it.  */
      if (yylen)
        yylhs.value = yystack_[yylen - 1].value;
      else
        yylhs.value = yystack_[0].value;

      // Compute the default @$.
      {
        slice<stack_symbol_type, stack_type> slice (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, slice, yylen);
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
      try
        {
          switch (yyn)
            {
  case 2:
#line 123 "src/parser.y" // lalr1.cc:859
    {
    driver.setProgram((yystack_[0].value.compoundstmt_t));
  }
#line 646 "/pract/parser.cpp" // lalr1.cc:859
    break;

  case 3:
#line 134 "src/parser.y" // lalr1.cc:859
    {
    (yylhs.value.stmt_t) = nullptr;  
  }
#line 654 "/pract/parser.cpp" // lalr1.cc:859
    break;

  case 4:
#line 137 "src/parser.y" // lalr1.cc:859
    {
    (yylhs.value.stmt_t) = (yystack_[1].value.expr_t);
  }
#line 662 "/pract/parser.cpp" // lalr1.cc:859
    break;

  case 5:
#line 140 "src/parser.y" // lalr1.cc:859
    {
    (yylhs.value.stmt_t) = new AST::DeclStmt((yystack_[0].value.decl_t));
    (yylhs.value.stmt_t)->location = yylhs.location;
  }
#line 671 "/pract/parser.cpp" // lalr1.cc:859
    break;

  case 6:
#line 146 "src/parser.y" // lalr1.cc:859
    {
    (yylhs.value.compoundstmt_t) = sema.ParseCompoundStmt(yylhs.location, (yystack_[0].value.stmt_t));
  }
#line 679 "/pract/parser.cpp" // lalr1.cc:859
    break;

  case 7:
#line 149 "src/parser.y" // lalr1.cc:859
    {
    (yylhs.value.compoundstmt_t) = sema.ParseCompoundStmt(yylhs.location, (yystack_[0].value.stmt_t), (yystack_[1].value.compoundstmt_t));
  }
#line 687 "/pract/parser.cpp" // lalr1.cc:859
    break;

  case 8:
#line 154 "src/parser.y" // lalr1.cc:859
    {
    (yylhs.value.compoundstmt_t) = sema.ParseCompoundStmt(yylhs.location);
  }
#line 695 "/pract/parser.cpp" // lalr1.cc:859
    break;

  case 9:
#line 157 "src/parser.y" // lalr1.cc:859
    {
    (yylhs.value.compoundstmt_t) = (yystack_[1].value.compoundstmt_t);
    (yylhs.value.compoundstmt_t)->location = yylhs.location;
  }
#line 704 "/pract/parser.cpp" // lalr1.cc:859
    break;

  case 10:
#line 169 "src/parser.y" // lalr1.cc:859
    {
    (yylhs.value.expr_t) = (yystack_[0].value.expr_t);
  }
#line 712 "/pract/parser.cpp" // lalr1.cc:859
    break;

  case 11:
#line 173 "src/parser.y" // lalr1.cc:859
    {
    (yylhs.value.expr_t) = new AST::Assignment((yystack_[2].value.decl_expr_t), (yystack_[0].value.expr_t));
    (yylhs.value.expr_t)->location = yylhs.location;
  }
#line 721 "/pract/parser.cpp" // lalr1.cc:859
    break;

  case 12:
#line 178 "src/parser.y" // lalr1.cc:859
    {
    (yylhs.value.expr_t) = (yystack_[1].value.expr_t);
  }
#line 729 "/pract/parser.cpp" // lalr1.cc:859
    break;

  case 13:
#line 182 "src/parser.y" // lalr1.cc:859
    {
    (yylhs.value.expr_t) = (yystack_[0].value.call_expr_t);
  }
#line 737 "/pract/parser.cpp" // lalr1.cc:859
    break;

  case 14:
#line 186 "src/parser.y" // lalr1.cc:859
    {
    StringLiteral *StringLiteral = new AST::StringLiteral(yytext(lexer));
    StringLiteral->location = yylhs.location;
    (yylhs.value.expr_t) = StringLiteral;
    //$$ = new AST::StringLiteral(yytext(lexer));
    //$$->location = @$;
  }
#line 749 "/pract/parser.cpp" // lalr1.cc:859
    break;

  case 15:
#line 194 "src/parser.y" // lalr1.cc:859
    {
    (yylhs.value.expr_t) = sema.ParseFloatLiteral(yylhs.location, yytext(lexer));
  }
#line 757 "/pract/parser.cpp" // lalr1.cc:859
    break;

  case 16:
#line 198 "src/parser.y" // lalr1.cc:859
    {
    (yylhs.value.expr_t) = sema.ParseIntLiteral(yylhs.location, yytext(lexer));
  }
#line 765 "/pract/parser.cpp" // lalr1.cc:859
    break;

  case 17:
#line 202 "src/parser.y" // lalr1.cc:859
    {
    (yylhs.value.expr_t) = new AST::BinaryOp((yystack_[2].value.expr_t), Operator::CEQ, (yystack_[0].value.expr_t));
    (yylhs.value.expr_t)->location = yylhs.location;
  }
#line 774 "/pract/parser.cpp" // lalr1.cc:859
    break;

  case 18:
#line 207 "src/parser.y" // lalr1.cc:859
    {
    (yylhs.value.expr_t) = new AST::BinaryOp((yystack_[2].value.expr_t), Operator::CNE, (yystack_[0].value.expr_t));
    (yylhs.value.expr_t)->location = yylhs.location;
  }
#line 783 "/pract/parser.cpp" // lalr1.cc:859
    break;

  case 19:
#line 212 "src/parser.y" // lalr1.cc:859
    {
    (yylhs.value.expr_t) = new AST::BinaryOp((yystack_[2].value.expr_t), Operator::CLT, (yystack_[0].value.expr_t));
    (yylhs.value.expr_t)->location = yylhs.location;
  }
#line 792 "/pract/parser.cpp" // lalr1.cc:859
    break;

  case 20:
#line 217 "src/parser.y" // lalr1.cc:859
    {
    (yylhs.value.expr_t) = new AST::BinaryOp((yystack_[2].value.expr_t), Operator::CLE, (yystack_[0].value.expr_t));
    (yylhs.value.expr_t)->location = yylhs.location;
  }
#line 801 "/pract/parser.cpp" // lalr1.cc:859
    break;

  case 21:
#line 222 "src/parser.y" // lalr1.cc:859
    {
    (yylhs.value.expr_t) = new AST::BinaryOp((yystack_[2].value.expr_t), Operator::CGT, (yystack_[0].value.expr_t));
    (yylhs.value.expr_t)->location = yylhs.location;
  }
#line 810 "/pract/parser.cpp" // lalr1.cc:859
    break;

  case 22:
#line 227 "src/parser.y" // lalr1.cc:859
    {
    (yylhs.value.expr_t) = new AST::BinaryOp((yystack_[2].value.expr_t), Operator::CGE, (yystack_[0].value.expr_t));
    (yylhs.value.expr_t)->location = yylhs.location;
  }
#line 819 "/pract/parser.cpp" // lalr1.cc:859
    break;

  case 23:
#line 232 "src/parser.y" // lalr1.cc:859
    {
    (yylhs.value.expr_t) = new AST::BinaryOp((yystack_[2].value.expr_t), Operator::PLUS, (yystack_[0].value.expr_t));
    (yylhs.value.expr_t)->location = yylhs.location;
  }
#line 828 "/pract/parser.cpp" // lalr1.cc:859
    break;

  case 24:
#line 237 "src/parser.y" // lalr1.cc:859
    {
    (yylhs.value.expr_t) = new AST::BinaryOp((yystack_[2].value.expr_t), Operator::MINUS, (yystack_[0].value.expr_t));
    (yylhs.value.expr_t)->location = yylhs.location;
  }
#line 837 "/pract/parser.cpp" // lalr1.cc:859
    break;

  case 25:
#line 242 "src/parser.y" // lalr1.cc:859
    {
    (yylhs.value.expr_t) = new AST::BinaryOp((yystack_[2].value.expr_t), Operator::MUL, (yystack_[0].value.expr_t));
    (yylhs.value.expr_t)->location = yylhs.location;
  }
#line 846 "/pract/parser.cpp" // lalr1.cc:859
    break;

  case 26:
#line 247 "src/parser.y" // lalr1.cc:859
    {
    (yylhs.value.expr_t) = new AST::BinaryOp((yystack_[2].value.expr_t), Operator::DIV, (yystack_[0].value.expr_t));
    (yylhs.value.expr_t)->location = yylhs.location;
  }
#line 855 "/pract/parser.cpp" // lalr1.cc:859
    break;

  case 27:
#line 252 "src/parser.y" // lalr1.cc:859
    {
    (yylhs.value.expr_t) = new AST::BinaryOp((yystack_[2].value.expr_t), Operator::MOD, (yystack_[0].value.expr_t));
    (yylhs.value.expr_t)->location = yylhs.location;
  }
#line 864 "/pract/parser.cpp" // lalr1.cc:859
    break;

  case 28:
#line 257 "src/parser.y" // lalr1.cc:859
    {
    (yylhs.value.expr_t) = new AST::BinaryOp((yystack_[2].value.expr_t), Operator::EXP, (yystack_[0].value.expr_t));
    (yylhs.value.expr_t)->location = yylhs.location;
  }
#line 873 "/pract/parser.cpp" // lalr1.cc:859
    break;

  case 29:
#line 262 "src/parser.y" // lalr1.cc:859
    {
    (yylhs.value.expr_t) = new AST::UnaryOp(Operator::PLUS, (yystack_[0].value.expr_t));
    (yylhs.value.expr_t)->location = yylhs.location;
  }
#line 882 "/pract/parser.cpp" // lalr1.cc:859
    break;

  case 30:
#line 267 "src/parser.y" // lalr1.cc:859
    {
    (yylhs.value.expr_t) = new AST::UnaryOp(Operator::MINUS, (yystack_[0].value.expr_t));
    (yylhs.value.expr_t)->location = yylhs.location;
  }
#line 891 "/pract/parser.cpp" // lalr1.cc:859
    break;

  case 31:
#line 273 "src/parser.y" // lalr1.cc:859
    {
    (yylhs.value.expr_t) = new AST::DeclRefExpr((yystack_[0].value.ident_t));
    (yylhs.value.expr_t)->location = yylhs.location;
  }
#line 900 "/pract/parser.cpp" // lalr1.cc:859
    break;

  case 32:
#line 278 "src/parser.y" // lalr1.cc:859
    {
    (yylhs.value.expr_t) = new AST::DeclRefExpr((yystack_[3].value.ident_t), (yystack_[1].value.expr_t));
    (yylhs.value.expr_t)->location = yylhs.location;
  }
#line 909 "/pract/parser.cpp" // lalr1.cc:859
    break;

  case 33:
#line 290 "src/parser.y" // lalr1.cc:859
    {
    (yylhs.value.ident_t) = new AST::Identifier(yytext(lexer));
    (yylhs.value.ident_t)->location = yylhs.location;
  }
#line 918 "/pract/parser.cpp" // lalr1.cc:859
    break;

  case 34:
#line 296 "src/parser.y" // lalr1.cc:859
    {
    (yylhs.value.decl_t) = (yystack_[1].value.var_decl_t);
  }
#line 926 "/pract/parser.cpp" // lalr1.cc:859
    break;

  case 35:
#line 300 "src/parser.y" // lalr1.cc:859
    {
    (yylhs.value.decl_t) = (yystack_[0].value.decl_t);
  }
#line 934 "/pract/parser.cpp" // lalr1.cc:859
    break;

  case 36:
#line 309 "src/parser.y" // lalr1.cc:859
    {
    auto type = sema.ParseTypeName((yystack_[1].value.ident_t));
    delete (yystack_[1].value.ident_t);

    (yylhs.value.var_decl_t) = new AST::VarDecl((yystack_[0].value.ident_t), type);
    (yylhs.value.var_decl_t)->location = yylhs.location;
  }
#line 946 "/pract/parser.cpp" // lalr1.cc:859
    break;

  case 37:
#line 317 "src/parser.y" // lalr1.cc:859
    {
    auto type = sema.ParseTypeName((yystack_[3].value.ident_t));
    delete (yystack_[3].value.ident_t);

    (yylhs.value.var_decl_t) = new AST::VarDecl((yystack_[2].value.ident_t), type, (yystack_[0].value.expr_t));
    (yylhs.value.var_decl_t)->location = yylhs.location;
  }
#line 958 "/pract/parser.cpp" // lalr1.cc:859
    break;

  case 38:
#line 329 "src/parser.y" // lalr1.cc:859
    { // functie zonder parameters: foo();
    (yylhs.value.call_expr_t) = new AST::CallExpr((yystack_[2].value.ident_t));
    (yylhs.value.call_expr_t)->location = yylhs.location;
  }
#line 967 "/pract/parser.cpp" // lalr1.cc:859
    break;

  case 39:
#line 334 "src/parser.y" // lalr1.cc:859
    { // functie met oneindig veel parameters: foo(x, bar(zoo()), y, z, ...)
    (yylhs.value.call_expr_t) = new AST::CallExpr((yystack_[3].value.ident_t), *(yystack_[1].value.expr_list_t)); // pointer naar $3
    (yylhs.value.call_expr_t)->location = yylhs.location;
  }
#line 976 "/pract/parser.cpp" // lalr1.cc:859
    break;

  case 40:
#line 340 "src/parser.y" // lalr1.cc:859
    {
    (yylhs.value.expr_list_t) = sema.ParseExprList();
  }
#line 984 "/pract/parser.cpp" // lalr1.cc:859
    break;

  case 41:
#line 343 "src/parser.y" // lalr1.cc:859
    {
    (yylhs.value.expr_list_t) = sema.ParseExprList((yystack_[0].value.expr_t));
  }
#line 992 "/pract/parser.cpp" // lalr1.cc:859
    break;

  case 42:
#line 346 "src/parser.y" // lalr1.cc:859
    {
    (yylhs.value.expr_list_t) = sema.ParseExprList((yystack_[0].value.expr_t), (yystack_[2].value.expr_list_t));
  }
#line 1000 "/pract/parser.cpp" // lalr1.cc:859
    break;

  case 43:
#line 351 "src/parser.y" // lalr1.cc:859
    {
    auto type = sema.ParseTypeName((yystack_[5].value.ident_t));
    delete (yystack_[5].value.ident_t);
    (yylhs.value.decl_t) = new AST::FuncDecl((yystack_[4].value.ident_t), type, *(yystack_[2].value.varlist_t), (yystack_[0].value.compoundstmt_t));
    (yylhs.value.decl_t)->location = yylhs.location;
    delete (yystack_[2].value.varlist_t);
  }
#line 1012 "/pract/parser.cpp" // lalr1.cc:859
    break;

  case 44:
#line 360 "src/parser.y" // lalr1.cc:859
    {
    (yylhs.value.varlist_t) = sema.ParseVariableList();
  }
#line 1020 "/pract/parser.cpp" // lalr1.cc:859
    break;

  case 45:
#line 364 "src/parser.y" // lalr1.cc:859
    {
    (yylhs.value.varlist_t) = sema.ParseVariableList((yystack_[0].value.var_decl_t));
  }
#line 1028 "/pract/parser.cpp" // lalr1.cc:859
    break;

  case 46:
#line 368 "src/parser.y" // lalr1.cc:859
    {
    (yylhs.value.varlist_t) = sema.ParseVariableList((yystack_[0].value.var_decl_t), (yystack_[2].value.varlist_t));
  }
#line 1036 "/pract/parser.cpp" // lalr1.cc:859
    break;


#line 1040 "/pract/parser.cpp" // lalr1.cc:859
            default:
              break;
            }
        }
      catch (const syntax_error& yyexc)
        {
          error (yyexc);
          YYERROR;
        }
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;
      YY_STACK_PRINT ();

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, yylhs);
    }
    goto yynewstate;

  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        error (yyla.location, yysyntax_error_ (yystack_[0].state, yyla));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.type_get () == yyeof_)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:

    /* Pacify compilers like GCC when the user code never invokes
       YYERROR and the label yyerrorlab therefore never appears in user
       code.  */
    if (false)
      goto yyerrorlab;
    yyerror_range[1].location = yystack_[yylen - 1].location;
    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    goto yyerrlab1;

  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    {
      stack_symbol_type error_token;
      for (;;)
        {
          yyn = yypact_[yystack_[0].state];
          if (!yy_pact_value_is_default_ (yyn))
            {
              yyn += yyterror_;
              if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yyterror_)
                {
                  yyn = yytable_[yyn];
                  if (0 < yyn)
                    break;
                }
            }

          // Pop the current state because it cannot handle the error token.
          if (yystack_.size () == 1)
            YYABORT;

          yyerror_range[1].location = yystack_[0].location;
          yy_destroy_ ("Error: popping", yystack_[0]);
          yypop_ ();
          YY_STACK_PRINT ();
        }

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      error_token.state = yyn;
      yypush_ ("Shifting", error_token);
    }
    goto yynewstate;

    // Accept.
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;

    // Abort.
  yyabortlab:
    yyresult = 1;
    goto yyreturn;

  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack"
                 << std::endl;
        // Do not try to display the values of the reclaimed symbols,
        // as their printer might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
  }

  void
  Parser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what());
  }

  // Generate an error message.
  std::string
  Parser::yysyntax_error_ (state_type yystate, const symbol_type& yyla) const
  {
    // Number of reported tokens (one for the "unexpected", one per
    // "expected").
    size_t yycount = 0;
    // Its maximum.
    enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
    // Arguments of yyformat.
    char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];

    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yyla) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yyla.  (However, yyla is currently not documented for users.)
       - Of course, the expected token list depends on states to have
         correct lookahead information, and it depends on the parser not
         to perform extra reductions after fetching a lookahead from the
         scanner and before detecting a syntax error.  Thus, state
         merging (from LALR or IELR) and default reductions corrupt the
         expected token list.  However, the list is correct for
         canonical LR with one exception: it will still contain any
         token that will not be accepted due to an error action in a
         later state.
    */
    if (!yyla.empty ())
      {
        int yytoken = yyla.type_get ();
        yyarg[yycount++] = yytname_[yytoken];
        int yyn = yypact_[yystate];
        if (!yy_pact_value_is_default_ (yyn))
          {
            /* Start YYX at -YYN if negative to avoid negative indexes in
               YYCHECK.  In other words, skip the first -YYN actions for
               this state because they are default actions.  */
            int yyxbegin = yyn < 0 ? -yyn : 0;
            // Stay within bounds of both yycheck and yytname.
            int yychecklim = yylast_ - yyn + 1;
            int yyxend = yychecklim < yyntokens_ ? yychecklim : yyntokens_;
            for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
              if (yycheck_[yyx + yyn] == yyx && yyx != yyterror_
                  && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
                {
                  if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                    {
                      yycount = 1;
                      break;
                    }
                  else
                    yyarg[yycount++] = yytname_[yyx];
                }
          }
      }

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
        YYCASE_(0, YY_("syntax error"));
        YYCASE_(1, YY_("syntax error, unexpected %s"));
        YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    std::string yyres;
    // Argument number.
    size_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += yytnamerr_ (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const signed char Parser::yypact_ninf_ = -57;

  const signed char Parser::yytable_ninf_ = -1;

  const short int
  Parser::yypact_[] =
  {
      87,   -57,   -57,   -57,   -57,   100,   100,   -57,   100,    34,
     -57,    87,   152,    27,    10,   -57,    16,   -57,   -57,   -14,
      -9,   -14,   135,   -57,   -57,   100,   100,   100,   100,   100,
     100,   100,   100,   100,   100,   100,   100,   -57,   100,    35,
     100,    -8,   -57,   -57,   165,   165,   165,   165,   165,   165,
     -14,   -14,    19,    19,    19,    19,   177,   -57,   177,   -17,
     116,   100,    39,   -57,   100,   -57,   177,    39,   -57,   -16,
     177,    36,    23,    39,    61,   -57,   -57,   -57,    74,   -57
  };

  const unsigned char
  Parser::yydefact_[] =
  {
       0,    33,    16,    15,    14,     0,     0,     3,     0,     0,
       6,     2,     0,    10,    31,     5,     0,    13,    35,    29,
      31,    30,     0,     1,     7,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     4,     0,    40,
       0,    36,    34,    12,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    28,    27,    11,    38,    41,     0,
       0,     0,    44,    39,     0,    32,    37,     0,    45,     0,
      42,    36,     0,     0,     0,    43,    46,     8,     0,     9
  };

  const signed char
  Parser::yypgoto_[] =
  {
     -57,   -57,   -10,   -24,   -57,    -3,   -57,     0,   -57,   -56,
     -57,   -57,   -57,   -57
  };

  const signed char
  Parser::yydefgoto_[] =
  {
      -1,     9,    10,    11,    75,    12,    13,    20,    15,    16,
      17,    59,    18,    69
  };

  const signed char
  Parser::yytable_[] =
  {
      14,    24,    19,    21,    61,    22,    68,    33,    34,    35,
      36,    14,    63,    72,    41,    64,    73,    76,     1,    39,
      62,    40,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    23,    56,    58,    60,    39,    38,
      40,    42,    35,     1,     2,     3,     4,     1,    61,    74,
      78,     0,     0,     0,     5,     6,     0,     0,    66,     0,
       0,    70,    67,     8,    57,     0,     0,    71,    24,     1,
       2,     3,     4,    67,    14,     0,     0,     0,    14,     0,
       5,     6,     1,     2,     3,     4,     7,     0,    77,     8,
       0,     0,     0,     5,     6,     1,     2,     3,     4,     7,
       0,    79,     8,     0,     0,     0,     5,     6,     1,     2,
       3,     4,     7,     0,     0,     8,     0,     0,     0,     5,
       6,     0,     0,     0,     0,     0,     0,     0,     8,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,     0,     0,     0,     0,     0,     0,    65,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
       0,     0,     0,     0,    43,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    -1,    -1,
      -1,    -1,    -1,    -1,    31,    32,    33,    34,    35,    36,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36
  };

  const signed char
  Parser::yycheck_[] =
  {
       0,    11,     5,     6,    12,     8,    62,    21,    22,    23,
      24,    11,    29,    29,    14,    32,    32,    73,     8,    28,
      28,    30,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,     0,    38,    39,    40,    28,    12,
      30,    25,    23,     8,     9,    10,    11,     8,    12,    26,
      74,    -1,    -1,    -1,    19,    20,    -1,    -1,    61,    -1,
      -1,    64,    62,    28,    29,    -1,    -1,    67,    78,     8,
       9,    10,    11,    73,    74,    -1,    -1,    -1,    78,    -1,
      19,    20,     8,     9,    10,    11,    25,    -1,    27,    28,
      -1,    -1,    -1,    19,    20,     8,     9,    10,    11,    25,
      -1,    27,    28,    -1,    -1,    -1,    19,    20,     8,     9,
      10,    11,    25,    -1,    -1,    28,    -1,    -1,    -1,    19,
      20,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    28,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    -1,    -1,    -1,    -1,    -1,    -1,    31,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      -1,    -1,    -1,    -1,    29,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24
  };

  const unsigned char
  Parser::yystos_[] =
  {
       0,     8,     9,    10,    11,    19,    20,    25,    28,    34,
      35,    36,    38,    39,    40,    41,    42,    43,    45,    38,
      40,    38,    38,     0,    35,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    12,    28,
      30,    40,    25,    29,    38,    38,    38,    38,    38,    38,
      38,    38,    38,    38,    38,    38,    38,    29,    38,    44,
      38,    12,    28,    29,    32,    31,    38,    40,    42,    46,
      38,    40,    29,    32,    26,    37,    42,    27,    36,    27
  };

  const unsigned char
  Parser::yyr1_[] =
  {
       0,    33,    34,    35,    35,    35,    36,    36,    37,    37,
      38,    38,    38,    38,    38,    38,    38,    38,    38,    38,
      38,    38,    38,    38,    38,    38,    38,    38,    38,    38,
      38,    39,    39,    40,    41,    41,    42,    42,    43,    43,
      44,    44,    44,    45,    46,    46,    46
  };

  const unsigned char
  Parser::yyr2_[] =
  {
       0,     2,     1,     1,     2,     1,     1,     2,     2,     3,
       1,     3,     3,     1,     1,     1,     1,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     2,
       2,     1,     4,     1,     2,     1,     2,     4,     3,     4,
       0,     1,     3,     6,     0,     1,     3
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const Parser::yytname_[] =
  {
  "$end", "error", "$undefined", "RETURN", "IF", "ELSE", "WHILE", "FOR",
  "IDENTIFIER", "INTEGER", "FLOAT", "STRING", "EQUAL", "CEQ", "CNE", "CLT",
  "CLE", "CGT", "CGE", "PLUS", "MINUS", "MUL", "DIV", "EXP", "MOD", "';'",
  "'{'", "'}'", "'('", "')'", "'['", "']'", "','", "$accept", "program",
  "stmt", "stmts", "block", "expr", "decl_expr", "ident", "decl",
  "var_decl", "func_call", "expr_list", "func_decl", "func_args", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned short int
  Parser::yyrline_[] =
  {
       0,   123,   123,   134,   137,   140,   146,   149,   154,   157,
     169,   173,   178,   182,   186,   194,   198,   202,   207,   212,
     217,   222,   227,   232,   237,   242,   247,   252,   257,   262,
     267,   273,   278,   290,   296,   300,   309,   317,   329,   334,
     340,   343,   346,   351,   360,   364,   368
  };

  // Print the state stack on the debug stream.
  void
  Parser::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << i->state;
    *yycdebug_ << std::endl;
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  Parser::yy_reduce_print_ (int yyrule)
  {
    unsigned int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):" << std::endl;
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG

  // Symbol number corresponding to token number t.
  inline
  Parser::token_number_type
  Parser::yytranslate_ (int t)
  {
    static
    const token_number_type
    translate_table[] =
    {
     0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      28,    29,     2,     2,    32,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    25,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    30,     2,    31,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    26,     2,    27,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24
    };
    const unsigned int user_token_number_max_ = 279;
    const token_number_type undef_token_ = 2;

    if (static_cast<int>(t) <= yyeof_)
      return yyeof_;
    else if (static_cast<unsigned int> (t) <= user_token_number_max_)
      return translate_table[t];
    else
      return undef_token_;
  }

#line 7 "src/parser.y" // lalr1.cc:1167
} // cheetah
#line 1530 "/pract/parser.cpp" // lalr1.cc:1167
#line 371 "src/parser.y" // lalr1.cc:1168


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
