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

#line 37 "/files/parser.cpp" // lalr1.cc:404

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

#include "parser.hpp"

// User implementation prologue.

#line 51 "/files/parser.cpp" // lalr1.cc:412
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

#line 66 "/files/parser.cpp" // lalr1.cc:413


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
#line 152 "/files/parser.cpp" // lalr1.cc:479

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

#line 534 "/files/parser.cpp" // lalr1.cc:741

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
#line 113 "src/parser.y" // lalr1.cc:859
    {
      driver.setProgram((yystack_[0].value.compoundstmt_t));
    }
#line 646 "/files/parser.cpp" // lalr1.cc:859
    break;

  case 3:
#line 125 "src/parser.y" // lalr1.cc:859
    { (yylhs.value.stmt_t) = nullptr; }
#line 652 "/files/parser.cpp" // lalr1.cc:859
    break;

  case 4:
#line 126 "src/parser.y" // lalr1.cc:859
    {
      (yylhs.value.stmt_t) = (yystack_[1].value.expr_t);
    }
#line 660 "/files/parser.cpp" // lalr1.cc:859
    break;

  case 5:
#line 129 "src/parser.y" // lalr1.cc:859
    {
      (yylhs.value.stmt_t) = new AST::DeclStmt((yystack_[0].value.decl_t));
    }
#line 668 "/files/parser.cpp" // lalr1.cc:859
    break;

  case 9:
#line 135 "src/parser.y" // lalr1.cc:859
    {
      (yylhs.value.stmt_t) = new AST::ReturnStmt((yystack_[1].value.expr_t));
    }
#line 676 "/files/parser.cpp" // lalr1.cc:859
    break;

  case 10:
#line 138 "src/parser.y" // lalr1.cc:859
    {
      (yylhs.value.stmt_t) = new AST::ReturnStmt();
    }
#line 684 "/files/parser.cpp" // lalr1.cc:859
    break;

  case 11:
#line 144 "src/parser.y" // lalr1.cc:859
    {
      (yylhs.value.compoundstmt_t) = sema.ParseCompoundStmt(yylhs.location, (yystack_[0].value.stmt_t));
    }
#line 692 "/files/parser.cpp" // lalr1.cc:859
    break;

  case 12:
#line 147 "src/parser.y" // lalr1.cc:859
    {
      (yylhs.value.compoundstmt_t) = sema.ParseCompoundStmt(yylhs.location, (yystack_[0].value.stmt_t), (yystack_[1].value.compoundstmt_t));
    }
#line 700 "/files/parser.cpp" // lalr1.cc:859
    break;

  case 13:
#line 153 "src/parser.y" // lalr1.cc:859
    {
      (yylhs.value.compoundstmt_t) = sema.ParseCompoundStmt(yylhs.location);
    }
#line 708 "/files/parser.cpp" // lalr1.cc:859
    break;

  case 14:
#line 156 "src/parser.y" // lalr1.cc:859
    {
      (yylhs.value.compoundstmt_t) = (yystack_[1].value.compoundstmt_t);
    }
#line 716 "/files/parser.cpp" // lalr1.cc:859
    break;

  case 15:
#line 167 "src/parser.y" // lalr1.cc:859
    {
      (yylhs.value.stmt_t) = new AST::IfStmt((yystack_[2].value.expr_t), (yystack_[0].value.compoundstmt_t));
    }
#line 724 "/files/parser.cpp" // lalr1.cc:859
    break;

  case 16:
#line 170 "src/parser.y" // lalr1.cc:859
    {
      (yylhs.value.stmt_t) = new AST::IfStmt((yystack_[4].value.expr_t), (yystack_[2].value.compoundstmt_t), (yystack_[0].value.compoundstmt_t));
    }
#line 732 "/files/parser.cpp" // lalr1.cc:859
    break;

  case 17:
#line 176 "src/parser.y" // lalr1.cc:859
    {
      (yylhs.value.stmt_t) = new AST::WhileStmt((yystack_[2].value.expr_t), (yystack_[0].value.compoundstmt_t));
    }
#line 740 "/files/parser.cpp" // lalr1.cc:859
    break;

  case 18:
#line 182 "src/parser.y" // lalr1.cc:859
    {
      (yylhs.value.stmt_t) = new AST::ForStmt((yystack_[6].value.stmt_t), (yystack_[4].value.expr_t), (yystack_[2].value.expr_t), (yystack_[0].value.compoundstmt_t));
    }
#line 748 "/files/parser.cpp" // lalr1.cc:859
    break;

  case 19:
#line 188 "src/parser.y" // lalr1.cc:859
    {
      (yylhs.value.stmt_t) = new AST::DeclStmt((yystack_[0].value.var_decl_t));
    }
#line 756 "/files/parser.cpp" // lalr1.cc:859
    break;

  case 20:
#line 191 "src/parser.y" // lalr1.cc:859
    {
      (yylhs.value.stmt_t) = (yystack_[0].value.expr_t);
    }
#line 764 "/files/parser.cpp" // lalr1.cc:859
    break;

  case 21:
#line 203 "src/parser.y" // lalr1.cc:859
    {
      (yylhs.value.expr_t) = (yystack_[0].value.expr_t);
    }
#line 772 "/files/parser.cpp" // lalr1.cc:859
    break;

  case 22:
#line 206 "src/parser.y" // lalr1.cc:859
    {
      (yylhs.value.expr_t) = new AST::Assignment((yystack_[2].value.decl_expr_t), (yystack_[0].value.expr_t));
    }
#line 780 "/files/parser.cpp" // lalr1.cc:859
    break;

  case 23:
#line 209 "src/parser.y" // lalr1.cc:859
    {
      (yylhs.value.expr_t) = (yystack_[1].value.expr_t);
    }
#line 788 "/files/parser.cpp" // lalr1.cc:859
    break;

  case 26:
#line 214 "src/parser.y" // lalr1.cc:859
    { (yylhs.value.expr_t) = new AST::BinaryOp((yystack_[2].value.expr_t), AST::Operator::CEQ,   (yystack_[0].value.expr_t)); }
#line 794 "/files/parser.cpp" // lalr1.cc:859
    break;

  case 27:
#line 215 "src/parser.y" // lalr1.cc:859
    { (yylhs.value.expr_t) = new AST::BinaryOp((yystack_[2].value.expr_t), AST::Operator::CNE,   (yystack_[0].value.expr_t)); }
#line 800 "/files/parser.cpp" // lalr1.cc:859
    break;

  case 28:
#line 216 "src/parser.y" // lalr1.cc:859
    { (yylhs.value.expr_t) = new AST::BinaryOp((yystack_[2].value.expr_t), AST::Operator::CLT,   (yystack_[0].value.expr_t)); }
#line 806 "/files/parser.cpp" // lalr1.cc:859
    break;

  case 29:
#line 217 "src/parser.y" // lalr1.cc:859
    { (yylhs.value.expr_t) = new AST::BinaryOp((yystack_[2].value.expr_t), AST::Operator::CLE,   (yystack_[0].value.expr_t)); }
#line 812 "/files/parser.cpp" // lalr1.cc:859
    break;

  case 30:
#line 218 "src/parser.y" // lalr1.cc:859
    { (yylhs.value.expr_t) = new AST::BinaryOp((yystack_[2].value.expr_t), AST::Operator::CGT,   (yystack_[0].value.expr_t)); }
#line 818 "/files/parser.cpp" // lalr1.cc:859
    break;

  case 31:
#line 219 "src/parser.y" // lalr1.cc:859
    { (yylhs.value.expr_t) = new AST::BinaryOp((yystack_[2].value.expr_t), AST::Operator::CGE,   (yystack_[0].value.expr_t)); }
#line 824 "/files/parser.cpp" // lalr1.cc:859
    break;

  case 32:
#line 220 "src/parser.y" // lalr1.cc:859
    { (yylhs.value.expr_t) = new AST::BinaryOp((yystack_[2].value.expr_t), AST::Operator::PLUS,  (yystack_[0].value.expr_t)); }
#line 830 "/files/parser.cpp" // lalr1.cc:859
    break;

  case 33:
#line 221 "src/parser.y" // lalr1.cc:859
    { (yylhs.value.expr_t) = new AST::BinaryOp((yystack_[2].value.expr_t), AST::Operator::MINUS, (yystack_[0].value.expr_t)); }
#line 836 "/files/parser.cpp" // lalr1.cc:859
    break;

  case 34:
#line 222 "src/parser.y" // lalr1.cc:859
    { (yylhs.value.expr_t) = new AST::BinaryOp((yystack_[2].value.expr_t), AST::Operator::MUL,   (yystack_[0].value.expr_t)); }
#line 842 "/files/parser.cpp" // lalr1.cc:859
    break;

  case 35:
#line 223 "src/parser.y" // lalr1.cc:859
    { (yylhs.value.expr_t) = new AST::BinaryOp((yystack_[2].value.expr_t), AST::Operator::DIV,   (yystack_[0].value.expr_t)); }
#line 848 "/files/parser.cpp" // lalr1.cc:859
    break;

  case 36:
#line 224 "src/parser.y" // lalr1.cc:859
    { (yylhs.value.expr_t) = new AST::BinaryOp((yystack_[2].value.expr_t), AST::Operator::MOD,   (yystack_[0].value.expr_t)); }
#line 854 "/files/parser.cpp" // lalr1.cc:859
    break;

  case 37:
#line 225 "src/parser.y" // lalr1.cc:859
    { (yylhs.value.expr_t) = new AST::UnaryOp(     AST::Operator::MINUS, (yystack_[0].value.expr_t)); }
#line 860 "/files/parser.cpp" // lalr1.cc:859
    break;

  case 38:
#line 226 "src/parser.y" // lalr1.cc:859
    { (yylhs.value.expr_t) = new AST::UnaryOp(     AST::Operator::PLUS,  (yystack_[0].value.expr_t)); }
#line 866 "/files/parser.cpp" // lalr1.cc:859
    break;

  case 39:
#line 227 "src/parser.y" // lalr1.cc:859
    { (yylhs.value.expr_t) = new AST::BinaryOp((yystack_[2].value.expr_t), AST::Operator::EXP,   (yystack_[0].value.expr_t)); }
#line 872 "/files/parser.cpp" // lalr1.cc:859
    break;

  case 40:
#line 231 "src/parser.y" // lalr1.cc:859
    {
      (yylhs.value.expr_t) = new AST::DeclRefExpr((yystack_[0].value.ident_t));
    }
#line 880 "/files/parser.cpp" // lalr1.cc:859
    break;

  case 41:
#line 234 "src/parser.y" // lalr1.cc:859
    {
      (yylhs.value.expr_t) = new AST::DeclRefExpr((yystack_[3].value.ident_t), (yystack_[1].value.expr_t));
    }
#line 888 "/files/parser.cpp" // lalr1.cc:859
    break;

  case 42:
#line 245 "src/parser.y" // lalr1.cc:859
    {
      (yylhs.value.expr_t) = sema.ParseIntLiteral(yylhs.location, yytext(lexer));
    }
#line 896 "/files/parser.cpp" // lalr1.cc:859
    break;

  case 43:
#line 256 "src/parser.y" // lalr1.cc:859
    {
      (yylhs.value.expr_t) = new AST::CallExpr((yystack_[3].value.ident_t), *(yystack_[1].value.exprlist_t));
      delete (yystack_[1].value.exprlist_t);
     }
#line 905 "/files/parser.cpp" // lalr1.cc:859
    break;

  case 44:
#line 262 "src/parser.y" // lalr1.cc:859
    {
      (yylhs.value.exprlist_t) = sema.ParseExprList();
    }
#line 913 "/files/parser.cpp" // lalr1.cc:859
    break;

  case 45:
#line 265 "src/parser.y" // lalr1.cc:859
    {
      (yylhs.value.exprlist_t) = sema.ParseExprList((yystack_[0].value.expr_t));
    }
#line 921 "/files/parser.cpp" // lalr1.cc:859
    break;

  case 46:
#line 268 "src/parser.y" // lalr1.cc:859
    {
      (yylhs.value.exprlist_t) = sema.ParseExprList((yystack_[0].value.expr_t), (yystack_[2].value.exprlist_t));
    }
#line 929 "/files/parser.cpp" // lalr1.cc:859
    break;

  case 47:
#line 280 "src/parser.y" // lalr1.cc:859
    {
      (yylhs.value.ident_t) = new AST::Identifier(yytext(lexer));
    }
#line 937 "/files/parser.cpp" // lalr1.cc:859
    break;

  case 48:
#line 286 "src/parser.y" // lalr1.cc:859
    {
      (yylhs.value.decl_t) = (yystack_[1].value.var_decl_t);
    }
#line 945 "/files/parser.cpp" // lalr1.cc:859
    break;

  case 49:
#line 289 "src/parser.y" // lalr1.cc:859
    {
      (yylhs.value.decl_t) = (yystack_[0].value.decl_t);
    }
#line 953 "/files/parser.cpp" // lalr1.cc:859
    break;

  case 50:
#line 300 "src/parser.y" // lalr1.cc:859
    {
      auto type = sema.ParseTypeName((yystack_[1].value.ident_t));
      delete (yystack_[1].value.ident_t);

      (yylhs.value.var_decl_t) = new AST::VarDecl((yystack_[0].value.ident_t), type);
    }
#line 964 "/files/parser.cpp" // lalr1.cc:859
    break;

  case 51:
#line 306 "src/parser.y" // lalr1.cc:859
    {
      auto type = sema.ParseTypeName((yystack_[3].value.ident_t));
      delete (yystack_[3].value.ident_t);

      (yylhs.value.var_decl_t) = new AST::VarDecl((yystack_[2].value.ident_t), type, (yystack_[0].value.expr_t));
    }
#line 975 "/files/parser.cpp" // lalr1.cc:859
    break;

  case 52:
#line 320 "src/parser.y" // lalr1.cc:859
    {
      auto type = sema.ParseTypeName((yystack_[5].value.ident_t));
      delete (yystack_[5].value.ident_t);

      (yylhs.value.decl_t) = new AST::FuncDecl((yystack_[4].value.ident_t), type, *(yystack_[2].value.varlist_t), (yystack_[0].value.compoundstmt_t));
      delete (yystack_[2].value.varlist_t);
    }
#line 987 "/files/parser.cpp" // lalr1.cc:859
    break;

  case 53:
#line 330 "src/parser.y" // lalr1.cc:859
    {
      (yylhs.value.varlist_t) = sema.ParseVariableList();
    }
#line 995 "/files/parser.cpp" // lalr1.cc:859
    break;

  case 54:
#line 333 "src/parser.y" // lalr1.cc:859
    {
      (yylhs.value.varlist_t) = sema.ParseVariableList((yystack_[0].value.var_decl_t));
    }
#line 1003 "/files/parser.cpp" // lalr1.cc:859
    break;

  case 55:
#line 336 "src/parser.y" // lalr1.cc:859
    {
      (yylhs.value.varlist_t) = sema.ParseVariableList((yystack_[0].value.var_decl_t), (yystack_[2].value.varlist_t));
    }
#line 1011 "/files/parser.cpp" // lalr1.cc:859
    break;


#line 1015 "/files/parser.cpp" // lalr1.cc:859
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


  const signed char Parser::yypact_ninf_ = -77;

  const signed char Parser::yytable_ninf_ = -1;

  const short int
  Parser::yypact_[] =
  {
      53,   121,   -26,   -19,   -11,   -77,   -77,    56,    56,   -77,
      56,    19,   -77,    53,   -77,   -77,   -77,   230,     9,   -77,
     -77,    24,   -77,    -4,   -77,   -77,   244,   -15,    56,    56,
      56,     0,     0,   158,   -77,   -77,    56,    56,    56,    56,
      56,    56,    56,    56,    56,    56,    56,    56,   -77,    56,
      56,    56,     1,   -77,   -77,   176,   194,     7,   272,    24,
     -77,   -77,   284,   284,   284,   284,   284,   284,    67,    67,
       0,     0,     0,     0,   272,   272,   -22,   138,    56,    18,
      20,    20,    56,    40,   -77,    56,   -77,   272,    18,   -77,
     -18,    90,    49,   -77,   258,   272,    20,    18,   -77,   117,
      20,    56,   -77,   -77,   -77,   -77,   212,    20,   -77
  };

  const unsigned char
  Parser::yydefact_[] =
  {
       0,     0,     0,     0,     0,    47,    42,     0,     0,     3,
       0,     0,    11,     2,     6,     7,     8,     0,    21,    25,
      24,    40,     5,     0,    49,    10,     0,    40,     0,     0,
       0,    38,    37,     0,     1,    12,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     4,     0,
      44,     0,    50,    48,     9,     0,     0,     0,    20,    40,
      19,    23,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    39,    36,    22,    45,     0,     0,     0,    53,
       0,     0,     0,    50,    43,     0,    41,    51,     0,    54,
       0,     0,    15,    17,     0,    46,     0,     0,    13,     0,
       0,     0,    52,    55,    14,    16,     0,     0,    18
  };

  const signed char
  Parser::yypgoto_[] =
  {
     -77,   -77,   -12,   -33,   -76,   -77,   -77,   -77,   -77,    -1,
     -77,   -77,   -77,   -77,     4,   -77,   -28,   -77,   -77
  };

  const signed char
  Parser::yydefgoto_[] =
  {
      -1,    11,    12,    13,    92,    14,    15,    16,    57,    17,
      18,    19,    20,    76,    27,    22,    23,    24,    90
  };

  const signed char
  Parser::yytable_[] =
  {
      26,    35,    60,    28,    21,    93,    31,    32,    84,    33,
      29,    85,    96,    78,    50,    97,    51,    21,    30,    34,
     102,    49,    53,    46,   105,    52,     5,    55,    56,    58,
      79,   108,     5,    82,    59,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    91,    74,    75,
      77,    89,    78,    50,   100,    51,     1,     2,    99,     3,
       4,     5,     6,    83,     5,     6,     0,     0,     0,   103,
       0,     0,     7,     8,     0,     7,     8,    87,     0,     9,
       0,    94,    10,    88,    95,    10,     0,    35,    44,    45,
      46,    47,    83,     1,     2,    21,     3,     4,     5,     6,
     106,    88,     0,    21,     0,     0,     0,     0,     0,     7,
       8,     0,     0,     0,     0,     0,     9,     0,    98,    10,
       1,     2,     0,     3,     4,     5,     6,     0,     0,     5,
       6,     0,     0,     0,     0,     0,     7,     8,     0,     0,
       7,     8,     0,     9,     0,   104,    10,    25,     0,     0,
      10,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,     0,     0,     0,     0,     0,     0,     0,
      86,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,     0,     0,     0,     0,     0,    61,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,     0,     0,     0,     0,     0,    80,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,     0,
       0,     0,     0,     0,    81,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,     0,     0,     0,
       0,     0,   107,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,     0,    48,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,     0,
      54,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,     0,   101,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    -1,    -1,    -1,
      -1,    -1,    -1,    42,    43,    44,    45,    46,    47
  };

  const signed char
  Parser::yycheck_[] =
  {
       1,    13,    30,    29,     0,    81,     7,     8,    30,    10,
      29,    33,    30,    12,    29,    33,    31,    13,    29,     0,
      96,    12,    26,    23,   100,    21,     8,    28,    29,    30,
      29,   107,     8,    26,    30,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    27,    49,    50,
      51,    79,    12,    29,     5,    31,     3,     4,    91,     6,
       7,     8,     9,    59,     8,     9,    -1,    -1,    -1,    97,
      -1,    -1,    19,    20,    -1,    19,    20,    78,    -1,    26,
      -1,    82,    29,    79,    85,    29,    -1,    99,    21,    22,
      23,    24,    88,     3,     4,    91,     6,     7,     8,     9,
     101,    97,    -1,    99,    -1,    -1,    -1,    -1,    -1,    19,
      20,    -1,    -1,    -1,    -1,    -1,    26,    -1,    28,    29,
       3,     4,    -1,     6,     7,     8,     9,    -1,    -1,     8,
       9,    -1,    -1,    -1,    -1,    -1,    19,    20,    -1,    -1,
      19,    20,    -1,    26,    -1,    28,    29,    26,    -1,    -1,
      29,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      32,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    -1,    -1,    -1,    -1,    -1,    30,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    -1,    -1,    -1,    -1,    -1,    30,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    -1,
      -1,    -1,    -1,    -1,    30,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    -1,    -1,    -1,
      -1,    -1,    30,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    -1,    26,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    -1,
      26,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    -1,    26,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24
  };

  const unsigned char
  Parser::yystos_[] =
  {
       0,     3,     4,     6,     7,     8,     9,    19,    20,    26,
      29,    35,    36,    37,    39,    40,    41,    43,    44,    45,
      46,    48,    49,    50,    51,    26,    43,    48,    29,    29,
      29,    43,    43,    43,     0,    36,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    26,    12,
      29,    31,    48,    26,    26,    43,    43,    42,    43,    48,
      50,    30,    43,    43,    43,    43,    43,    43,    43,    43,
      43,    43,    43,    43,    43,    43,    47,    43,    12,    29,
      30,    30,    26,    48,    30,    33,    32,    43,    48,    50,
      52,    27,    38,    38,    43,    43,    30,    33,    28,    37,
       5,    26,    38,    50,    28,    38,    43,    30,    38
  };

  const unsigned char
  Parser::yyr1_[] =
  {
       0,    34,    35,    36,    36,    36,    36,    36,    36,    36,
      36,    37,    37,    38,    38,    39,    39,    40,    41,    42,
      42,    43,    43,    43,    43,    43,    43,    43,    43,    43,
      43,    43,    43,    43,    43,    43,    43,    43,    43,    43,
      44,    44,    45,    46,    47,    47,    47,    48,    49,    49,
      50,    50,    51,    52,    52,    52
  };

  const unsigned char
  Parser::yyr2_[] =
  {
       0,     2,     1,     1,     2,     1,     1,     1,     1,     3,
       2,     1,     2,     2,     3,     5,     7,     5,     9,     1,
       1,     1,     3,     3,     1,     1,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     2,     2,     3,
       1,     4,     1,     4,     0,     1,     3,     1,     2,     1,
       2,     4,     6,     0,     1,     3
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const Parser::yytname_[] =
  {
  "$end", "error", "$undefined", "RETURN", "IF", "ELSE", "WHILE", "FOR",
  "IDENTIFIER", "INTEGER", "FLOAT", "STRING", "EQUAL", "CEQ", "CNE", "CLT",
  "CLE", "CGT", "CGE", "PLUS", "MINUS", "MUL", "DIV", "EXP", "MOD",
  "UNARY", "';'", "'{'", "'}'", "'('", "')'", "'['", "']'", "','",
  "$accept", "program", "stmt", "stmts", "block", "ifstmt", "whilestmt",
  "forstmt", "forinit", "expr", "decl_expr", "literal", "call",
  "call_args", "ident", "decl", "var_decl", "func_decl", "func_args", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned short int
  Parser::yyrline_[] =
  {
       0,   113,   113,   125,   126,   129,   132,   133,   134,   135,
     138,   144,   147,   153,   156,   167,   170,   176,   182,   188,
     191,   203,   206,   209,   212,   213,   214,   215,   216,   217,
     218,   219,   220,   221,   222,   223,   224,   225,   226,   227,
     231,   234,   245,   256,   262,   265,   268,   280,   286,   289,
     300,   306,   320,   330,   333,   336
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
      29,    30,     2,     2,    33,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    26,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    31,     2,    32,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    27,     2,    28,     2,     2,     2,     2,
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
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25
    };
    const unsigned int user_token_number_max_ = 280;
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
#line 1539 "/files/parser.cpp" // lalr1.cc:1167
#line 341 "src/parser.y" // lalr1.cc:1168


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
