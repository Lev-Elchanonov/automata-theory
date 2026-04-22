// A Bison parser, made by GNU Bison 3.8.2.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2021 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

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

// DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
// especially those whose name start with YY_ or yy_.  They are
// private implementation details that can be changed or removed.





#include "robot.tab.hpp"


// Unqualified %code blocks.
#line 23 "robot.ypp"

    #include "RobotLexer.h"
    #include <cstdio>
    #include <map>
    #include <stack>

    bool has_main = false;

    // таблица символов
    struct SymbolInfo{
        VarDecl decl_;
        std::vector<int> array_values_;
        bool initialized_ = false;
    };
    std::map<std::string, SymbolInfo> global_symbols;
    std::map<std::string, FuncDecl> functions;

    void yyerror(const std::string& msg){
        std::cerr << "SYNTAX ERROR: " << msg << std::endl;
    }

#line 68 "robot.tab.cpp"


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


// Whether we are compiled with exception support.
#ifndef YY_EXCEPTIONS
# if defined __GNUC__ && !defined __EXCEPTIONS
#  define YY_EXCEPTIONS 0
# else
#  define YY_EXCEPTIONS 1
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
    while (false)
# endif


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
      *yycdebug_ << '\n';                       \
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
      yy_stack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YY_USE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 47 "robot.ypp"
namespace  yy  {
#line 161 "robot.tab.cpp"

  /// Build a parser object.
   RobotParser :: RobotParser  (yy::RobotLexer& lexer_yyarg)
#if YYDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
#else
    :
#endif
      lexer (lexer_yyarg)
  {}

   RobotParser ::~ RobotParser  ()
  {}

   RobotParser ::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------.
  | symbol.  |
  `---------*/



  // by_state.
   RobotParser ::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

   RobotParser ::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
   RobotParser ::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
   RobotParser ::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

   RobotParser ::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

   RobotParser ::symbol_kind_type
   RobotParser ::by_state::kind () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return symbol_kind::S_YYEMPTY;
    else
      return YY_CAST (symbol_kind_type, yystos_[+state]);
  }

   RobotParser ::stack_symbol_type::stack_symbol_type ()
  {}

   RobotParser ::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state), YY_MOVE (that.location))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_TOKEN_CELL_VALUE: // TOKEN_CELL_VALUE
        value.YY_MOVE_OR_COPY< CellValue > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_cond_branch: // cond_branch
        value.YY_MOVE_OR_COPY< ConditionBranch > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_func_def: // func_def
        value.YY_MOVE_OR_COPY< FuncDecl > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_var_item: // var_item
        value.YY_MOVE_OR_COPY< VarDecl > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_type_spec: // type_spec
        value.YY_MOVE_OR_COPY< VarDecl::VarType > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_TOKEN_BOOL: // TOKEN_BOOL
      case symbol_kind::S_TOKEN_BOOL_LIT: // TOKEN_BOOL_LIT
      case symbol_kind::S_opt_const: // opt_const
        value.YY_MOVE_OR_COPY< bool > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr: // expr
      case symbol_kind::S_primary_expr: // primary_expr
      case symbol_kind::S_var_ref: // var_ref
        value.YY_MOVE_OR_COPY< expr_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_TOKEN_INT_LIT: // TOKEN_INT_LIT
        value.YY_MOVE_OR_COPY< int > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_TOKEN_MAIN: // TOKEN_MAIN
      case symbol_kind::S_TOKEN_STRING: // TOKEN_STRING
      case symbol_kind::S_TOKEN_IDENTIFIER: // TOKEN_IDENTIFIER
        value.YY_MOVE_OR_COPY< std::string > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_cond_list: // cond_list
        value.YY_MOVE_OR_COPY< std::vector<ConditionBranch> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_var_list: // var_list
        value.YY_MOVE_OR_COPY< std::vector<VarDecl> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_opt_init_values: // opt_init_values
      case symbol_kind::S_value_list: // value_list
      case symbol_kind::S_var_ref_list: // var_ref_list
      case symbol_kind::S_opt_expr_list: // opt_expr_list
      case symbol_kind::S_expr_list: // expr_list
      case symbol_kind::S_dim_ref_list: // dim_ref_list
        value.YY_MOVE_OR_COPY< std::vector<expr_ptr> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_opt_dimensions: // opt_dimensions
      case symbol_kind::S_dims_list: // dims_list
        value.YY_MOVE_OR_COPY< std::vector<int> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_list: // stmt_list
        value.YY_MOVE_OR_COPY< std::vector<stmt_ptr> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt: // stmt
      case symbol_kind::S_expr_stmt: // expr_stmt
      case symbol_kind::S_assign_stmt: // assign_stmt
      case symbol_kind::S_while_stmt: // while_stmt
      case symbol_kind::S_switch_stmt: // switch_stmt
      case symbol_kind::S_move_stmt: // move_stmt
      case symbol_kind::S_call_stmt: // call_stmt
      case symbol_kind::S_getdrons_stmt: // getdrons_stmt
        value.YY_MOVE_OR_COPY< stmt_ptr > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

   RobotParser ::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s, YY_MOVE (that.location))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_TOKEN_CELL_VALUE: // TOKEN_CELL_VALUE
        value.move< CellValue > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_cond_branch: // cond_branch
        value.move< ConditionBranch > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_func_def: // func_def
        value.move< FuncDecl > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_var_item: // var_item
        value.move< VarDecl > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_type_spec: // type_spec
        value.move< VarDecl::VarType > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_TOKEN_BOOL: // TOKEN_BOOL
      case symbol_kind::S_TOKEN_BOOL_LIT: // TOKEN_BOOL_LIT
      case symbol_kind::S_opt_const: // opt_const
        value.move< bool > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr: // expr
      case symbol_kind::S_primary_expr: // primary_expr
      case symbol_kind::S_var_ref: // var_ref
        value.move< expr_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_TOKEN_INT_LIT: // TOKEN_INT_LIT
        value.move< int > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_TOKEN_MAIN: // TOKEN_MAIN
      case symbol_kind::S_TOKEN_STRING: // TOKEN_STRING
      case symbol_kind::S_TOKEN_IDENTIFIER: // TOKEN_IDENTIFIER
        value.move< std::string > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_cond_list: // cond_list
        value.move< std::vector<ConditionBranch> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_var_list: // var_list
        value.move< std::vector<VarDecl> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_opt_init_values: // opt_init_values
      case symbol_kind::S_value_list: // value_list
      case symbol_kind::S_var_ref_list: // var_ref_list
      case symbol_kind::S_opt_expr_list: // opt_expr_list
      case symbol_kind::S_expr_list: // expr_list
      case symbol_kind::S_dim_ref_list: // dim_ref_list
        value.move< std::vector<expr_ptr> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_opt_dimensions: // opt_dimensions
      case symbol_kind::S_dims_list: // dims_list
        value.move< std::vector<int> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_list: // stmt_list
        value.move< std::vector<stmt_ptr> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt: // stmt
      case symbol_kind::S_expr_stmt: // expr_stmt
      case symbol_kind::S_assign_stmt: // assign_stmt
      case symbol_kind::S_while_stmt: // while_stmt
      case symbol_kind::S_switch_stmt: // switch_stmt
      case symbol_kind::S_move_stmt: // move_stmt
      case symbol_kind::S_call_stmt: // call_stmt
      case symbol_kind::S_getdrons_stmt: // getdrons_stmt
        value.move< stmt_ptr > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

    // that is emptied.
    that.kind_ = symbol_kind::S_YYEMPTY;
  }

#if YY_CPLUSPLUS < 201103L
   RobotParser ::stack_symbol_type&
   RobotParser ::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_TOKEN_CELL_VALUE: // TOKEN_CELL_VALUE
        value.copy< CellValue > (that.value);
        break;

      case symbol_kind::S_cond_branch: // cond_branch
        value.copy< ConditionBranch > (that.value);
        break;

      case symbol_kind::S_func_def: // func_def
        value.copy< FuncDecl > (that.value);
        break;

      case symbol_kind::S_var_item: // var_item
        value.copy< VarDecl > (that.value);
        break;

      case symbol_kind::S_type_spec: // type_spec
        value.copy< VarDecl::VarType > (that.value);
        break;

      case symbol_kind::S_TOKEN_BOOL: // TOKEN_BOOL
      case symbol_kind::S_TOKEN_BOOL_LIT: // TOKEN_BOOL_LIT
      case symbol_kind::S_opt_const: // opt_const
        value.copy< bool > (that.value);
        break;

      case symbol_kind::S_expr: // expr
      case symbol_kind::S_primary_expr: // primary_expr
      case symbol_kind::S_var_ref: // var_ref
        value.copy< expr_ptr > (that.value);
        break;

      case symbol_kind::S_TOKEN_INT_LIT: // TOKEN_INT_LIT
        value.copy< int > (that.value);
        break;

      case symbol_kind::S_TOKEN_MAIN: // TOKEN_MAIN
      case symbol_kind::S_TOKEN_STRING: // TOKEN_STRING
      case symbol_kind::S_TOKEN_IDENTIFIER: // TOKEN_IDENTIFIER
        value.copy< std::string > (that.value);
        break;

      case symbol_kind::S_cond_list: // cond_list
        value.copy< std::vector<ConditionBranch> > (that.value);
        break;

      case symbol_kind::S_var_list: // var_list
        value.copy< std::vector<VarDecl> > (that.value);
        break;

      case symbol_kind::S_opt_init_values: // opt_init_values
      case symbol_kind::S_value_list: // value_list
      case symbol_kind::S_var_ref_list: // var_ref_list
      case symbol_kind::S_opt_expr_list: // opt_expr_list
      case symbol_kind::S_expr_list: // expr_list
      case symbol_kind::S_dim_ref_list: // dim_ref_list
        value.copy< std::vector<expr_ptr> > (that.value);
        break;

      case symbol_kind::S_opt_dimensions: // opt_dimensions
      case symbol_kind::S_dims_list: // dims_list
        value.copy< std::vector<int> > (that.value);
        break;

      case symbol_kind::S_stmt_list: // stmt_list
        value.copy< std::vector<stmt_ptr> > (that.value);
        break;

      case symbol_kind::S_stmt: // stmt
      case symbol_kind::S_expr_stmt: // expr_stmt
      case symbol_kind::S_assign_stmt: // assign_stmt
      case symbol_kind::S_while_stmt: // while_stmt
      case symbol_kind::S_switch_stmt: // switch_stmt
      case symbol_kind::S_move_stmt: // move_stmt
      case symbol_kind::S_call_stmt: // call_stmt
      case symbol_kind::S_getdrons_stmt: // getdrons_stmt
        value.copy< stmt_ptr > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    return *this;
  }

   RobotParser ::stack_symbol_type&
   RobotParser ::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_TOKEN_CELL_VALUE: // TOKEN_CELL_VALUE
        value.move< CellValue > (that.value);
        break;

      case symbol_kind::S_cond_branch: // cond_branch
        value.move< ConditionBranch > (that.value);
        break;

      case symbol_kind::S_func_def: // func_def
        value.move< FuncDecl > (that.value);
        break;

      case symbol_kind::S_var_item: // var_item
        value.move< VarDecl > (that.value);
        break;

      case symbol_kind::S_type_spec: // type_spec
        value.move< VarDecl::VarType > (that.value);
        break;

      case symbol_kind::S_TOKEN_BOOL: // TOKEN_BOOL
      case symbol_kind::S_TOKEN_BOOL_LIT: // TOKEN_BOOL_LIT
      case symbol_kind::S_opt_const: // opt_const
        value.move< bool > (that.value);
        break;

      case symbol_kind::S_expr: // expr
      case symbol_kind::S_primary_expr: // primary_expr
      case symbol_kind::S_var_ref: // var_ref
        value.move< expr_ptr > (that.value);
        break;

      case symbol_kind::S_TOKEN_INT_LIT: // TOKEN_INT_LIT
        value.move< int > (that.value);
        break;

      case symbol_kind::S_TOKEN_MAIN: // TOKEN_MAIN
      case symbol_kind::S_TOKEN_STRING: // TOKEN_STRING
      case symbol_kind::S_TOKEN_IDENTIFIER: // TOKEN_IDENTIFIER
        value.move< std::string > (that.value);
        break;

      case symbol_kind::S_cond_list: // cond_list
        value.move< std::vector<ConditionBranch> > (that.value);
        break;

      case symbol_kind::S_var_list: // var_list
        value.move< std::vector<VarDecl> > (that.value);
        break;

      case symbol_kind::S_opt_init_values: // opt_init_values
      case symbol_kind::S_value_list: // value_list
      case symbol_kind::S_var_ref_list: // var_ref_list
      case symbol_kind::S_opt_expr_list: // opt_expr_list
      case symbol_kind::S_expr_list: // expr_list
      case symbol_kind::S_dim_ref_list: // dim_ref_list
        value.move< std::vector<expr_ptr> > (that.value);
        break;

      case symbol_kind::S_opt_dimensions: // opt_dimensions
      case symbol_kind::S_dims_list: // dims_list
        value.move< std::vector<int> > (that.value);
        break;

      case symbol_kind::S_stmt_list: // stmt_list
        value.move< std::vector<stmt_ptr> > (that.value);
        break;

      case symbol_kind::S_stmt: // stmt
      case symbol_kind::S_expr_stmt: // expr_stmt
      case symbol_kind::S_assign_stmt: // assign_stmt
      case symbol_kind::S_while_stmt: // while_stmt
      case symbol_kind::S_switch_stmt: // switch_stmt
      case symbol_kind::S_move_stmt: // move_stmt
      case symbol_kind::S_call_stmt: // call_stmt
      case symbol_kind::S_getdrons_stmt: // getdrons_stmt
        value.move< stmt_ptr > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    // that is emptied.
    that.state = empty_state;
    return *this;
  }
#endif

  template <typename Base>
  void
   RobotParser ::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
   RobotParser ::yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YY_USE (yyoutput);
    if (yysym.empty ())
      yyo << "empty symbol";
    else
      {
        symbol_kind_type yykind = yysym.kind ();
        yyo << (yykind < YYNTOKENS ? "token" : "nterm")
            << ' ' << yysym.name () << " ("
            << yysym.location << ": ";
        YY_USE (yykind);
        yyo << ')';
      }
  }
#endif

  void
   RobotParser ::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
   RobotParser ::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
   RobotParser ::yypop_ (int n) YY_NOEXCEPT
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
   RobotParser ::debug_stream () const
  {
    return *yycdebug_;
  }

  void
   RobotParser ::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


   RobotParser ::debug_level_type
   RobotParser ::debug_level () const
  {
    return yydebug_;
  }

  void
   RobotParser ::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

   RobotParser ::state_type
   RobotParser ::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - YYNTOKENS] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - YYNTOKENS];
  }

  bool
   RobotParser ::yy_pact_value_is_default_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yypact_ninf_;
  }

  bool
   RobotParser ::yy_table_value_is_error_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yytable_ninf_;
  }

  int
   RobotParser ::operator() ()
  {
    return parse ();
  }

  int
   RobotParser ::parse ()
  {
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

#if YY_EXCEPTIONS
    try
#endif // YY_EXCEPTIONS
      {
    YYCDEBUG << "Starting parse\n";


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, YY_MOVE (yyla));

  /*-----------------------------------------------.
  | yynewstate -- push a new symbol on the stack.  |
  `-----------------------------------------------*/
  yynewstate:
    YYCDEBUG << "Entering state " << int (yystack_[0].state) << '\n';
    YY_STACK_PRINT ();

    // Accept?
    if (yystack_[0].state == yyfinal_)
      YYACCEPT;

    goto yybackup;


  /*-----------.
  | yybackup.  |
  `-----------*/
  yybackup:
    // Try to take a decision without lookahead.
    yyn = yypact_[+yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token\n";
#if YY_EXCEPTIONS
        try
#endif // YY_EXCEPTIONS
          {
            symbol_type yylookahead (yylex ());
            yyla.move (yylookahead);
          }
#if YY_EXCEPTIONS
        catch (const syntax_error& yyexc)
          {
            YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
            error (yyexc);
            goto yyerrlab1;
          }
#endif // YY_EXCEPTIONS
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    if (yyla.kind () == symbol_kind::S_YYerror)
    {
      // The scanner already issued an error message, process directly
      // to error recovery.  But do not keep the error token as
      // lookahead, it is too special and may lead us to an endless
      // loop in error recovery. */
      yyla.kind_ = symbol_kind::S_YYUNDEF;
      goto yyerrlab1;
    }

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.kind ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.kind ())
      {
        goto yydefault;
      }

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
    yypush_ ("Shifting", state_type (yyn), YY_MOVE (yyla));
    goto yynewstate;


  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[+yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;


  /*-----------------------------.
  | yyreduce -- do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_ (yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
      switch (yyr1_[yyn])
    {
      case symbol_kind::S_TOKEN_CELL_VALUE: // TOKEN_CELL_VALUE
        yylhs.value.emplace< CellValue > ();
        break;

      case symbol_kind::S_cond_branch: // cond_branch
        yylhs.value.emplace< ConditionBranch > ();
        break;

      case symbol_kind::S_func_def: // func_def
        yylhs.value.emplace< FuncDecl > ();
        break;

      case symbol_kind::S_var_item: // var_item
        yylhs.value.emplace< VarDecl > ();
        break;

      case symbol_kind::S_type_spec: // type_spec
        yylhs.value.emplace< VarDecl::VarType > ();
        break;

      case symbol_kind::S_TOKEN_BOOL: // TOKEN_BOOL
      case symbol_kind::S_TOKEN_BOOL_LIT: // TOKEN_BOOL_LIT
      case symbol_kind::S_opt_const: // opt_const
        yylhs.value.emplace< bool > ();
        break;

      case symbol_kind::S_expr: // expr
      case symbol_kind::S_primary_expr: // primary_expr
      case symbol_kind::S_var_ref: // var_ref
        yylhs.value.emplace< expr_ptr > ();
        break;

      case symbol_kind::S_TOKEN_INT_LIT: // TOKEN_INT_LIT
        yylhs.value.emplace< int > ();
        break;

      case symbol_kind::S_TOKEN_MAIN: // TOKEN_MAIN
      case symbol_kind::S_TOKEN_STRING: // TOKEN_STRING
      case symbol_kind::S_TOKEN_IDENTIFIER: // TOKEN_IDENTIFIER
        yylhs.value.emplace< std::string > ();
        break;

      case symbol_kind::S_cond_list: // cond_list
        yylhs.value.emplace< std::vector<ConditionBranch> > ();
        break;

      case symbol_kind::S_var_list: // var_list
        yylhs.value.emplace< std::vector<VarDecl> > ();
        break;

      case symbol_kind::S_opt_init_values: // opt_init_values
      case symbol_kind::S_value_list: // value_list
      case symbol_kind::S_var_ref_list: // var_ref_list
      case symbol_kind::S_opt_expr_list: // opt_expr_list
      case symbol_kind::S_expr_list: // expr_list
      case symbol_kind::S_dim_ref_list: // dim_ref_list
        yylhs.value.emplace< std::vector<expr_ptr> > ();
        break;

      case symbol_kind::S_opt_dimensions: // opt_dimensions
      case symbol_kind::S_dims_list: // dims_list
        yylhs.value.emplace< std::vector<int> > ();
        break;

      case symbol_kind::S_stmt_list: // stmt_list
        yylhs.value.emplace< std::vector<stmt_ptr> > ();
        break;

      case symbol_kind::S_stmt: // stmt
      case symbol_kind::S_expr_stmt: // expr_stmt
      case symbol_kind::S_assign_stmt: // assign_stmt
      case symbol_kind::S_while_stmt: // while_stmt
      case symbol_kind::S_switch_stmt: // switch_stmt
      case symbol_kind::S_move_stmt: // move_stmt
      case symbol_kind::S_call_stmt: // call_stmt
      case symbol_kind::S_getdrons_stmt: // getdrons_stmt
        yylhs.value.emplace< stmt_ptr > ();
        break;

      default:
        break;
    }


      // Default location.
      {
        stack_type::slice range (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, range, yylen);
        yyerror_range[1].location = yylhs.location;
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
#if YY_EXCEPTIONS
      try
#endif // YY_EXCEPTIONS
        {
          switch (yyn)
            {
  case 2: // program: TOKEN_PROGRAM_OPEN program_items TOKEN_PROGRAM_CLOSE
#line 152 "robot.ypp"
    {
        if (!has_main){
            fprintf(stderr, "SEMANTIC ERROR: function 'main' not found\n");
            exit(1);
        }
        std::cout << "=== PARSING COMPLETED SUCCESSFULLY ===" << std::endl;
        std::cout << "Global variables: " << global_symbols.size() << std::endl;
        std::cout << "Functions: " << functions.size() << std::endl;
    }
#line 958 "robot.tab.cpp"
    break;

  case 5: // program_items: program_items func_def
#line 167 "robot.ypp"
    {
        if (!yystack_[0].value.as < FuncDecl > ().name_.empty()){
            if (functions.find(yystack_[0].value.as < FuncDecl > ().name_) != functions.end()){
                std::cerr << "SEMANTIC ERROR: function '" << yystack_[0].value.as < FuncDecl > ().name_ << "' already defined" << std::endl;
                exit(1);
            }
            functions[yystack_[0].value.as < FuncDecl > ().name_] = yystack_[0].value.as < FuncDecl > ();
            std::cout << "Function defined: " << yystack_[0].value.as < FuncDecl > ().name_ << std::endl;
        }
    }
#line 973 "robot.tab.cpp"
    break;

  case 6: // program_items: program_items error
#line 178 "robot.ypp"
    {
        std::cerr << "Syntax error in global scope" << std::endl;
        yyerrok;
    }
#line 982 "robot.tab.cpp"
    break;

  case 7: // vardecl_block: TOKEN_VARDECL_OPEN var_list TOKEN_VARDECL_CLOSE
#line 186 "robot.ypp"
    {
        for (const auto& decl : yystack_[1].value.as < std::vector<VarDecl> > ()){
            if (global_symbols.find(decl.name_) != global_symbols.end()){
                std::cerr << "SEMANTIC ERROR: variable '" << decl.name_ << "' already declared" << std::endl;

            }
            SymbolInfo info;
            info.decl_ = decl;
            global_symbols[decl.name_] = info;
            std::cout << "Variable declared: " << decl.name_ << "(type: " << decl.type_ << ")" << std::endl;
        }
    }
#line 999 "robot.tab.cpp"
    break;

  case 8: // var_list: var_item
#line 202 "robot.ypp"
    {
        yylhs.value.as < std::vector<VarDecl> > ().push_back(yystack_[0].value.as < VarDecl > ());
    }
#line 1007 "robot.tab.cpp"
    break;

  case 9: // var_list: var_list var_item
#line 206 "robot.ypp"
    {
        yystack_[1].value.as < std::vector<VarDecl> > ().push_back(yystack_[0].value.as < VarDecl > ());
        yylhs.value.as < std::vector<VarDecl> > () = yystack_[1].value.as < std::vector<VarDecl> > ();
    }
#line 1016 "robot.tab.cpp"
    break;

  case 10: // var_item: TOKEN_VAR_OPEN TOKEN_NAME_ATTR TOKEN_STRING opt_const '>' type_spec opt_dimensions opt_init_values TOKEN_VAR_CLOSE
#line 229 "robot.ypp"
    {
        yylhs.value.as < VarDecl > ().name_ = yystack_[6].value.as < std::string > ();
        yylhs.value.as < VarDecl > ().is_const_ = yystack_[5].value.as < bool > ();
        yylhs.value.as < VarDecl > ().type_ = yystack_[3].value.as < VarDecl::VarType > ();
        yylhs.value.as < VarDecl > ().dimensions_ = yystack_[2].value.as < std::vector<int> > ();
        yylhs.value.as < VarDecl > ().init_values_ = yystack_[1].value.as < std::vector<expr_ptr> > ();
    }
#line 1028 "robot.tab.cpp"
    break;

  case 11: // opt_const: TOKEN_CONST TOKEN_BOOL
#line 239 "robot.ypp"
    {
        yylhs.value.as < bool > () = yystack_[0].value.as < bool > ();
    }
#line 1036 "robot.tab.cpp"
    break;

  case 12: // opt_const: %empty
#line 243 "robot.ypp"
    {
        yylhs.value.as < bool > () = false;
    }
#line 1044 "robot.tab.cpp"
    break;

  case 13: // type_spec: TOKEN_TYPE_OPEN TOKEN_TYPE_INT TOKEN_TYPE_CLOSE
#line 250 "robot.ypp"
    {
        yylhs.value.as < VarDecl::VarType > () = VarDecl::INT;
    }
#line 1052 "robot.tab.cpp"
    break;

  case 14: // type_spec: TOKEN_TYPE_OPEN TOKEN_TYPE_BOOL TOKEN_TYPE_CLOSE
#line 254 "robot.ypp"
    {
        yylhs.value.as < VarDecl::VarType > () = VarDecl::BOOL;
    }
#line 1060 "robot.tab.cpp"
    break;

  case 15: // type_spec: TOKEN_TYPE_OPEN TOKEN_TYPE_CELL TOKEN_TYPE_CLOSE
#line 258 "robot.ypp"
    {
        yylhs.value.as < VarDecl::VarType > () = VarDecl::CELL;
    }
#line 1068 "robot.tab.cpp"
    break;

  case 16: // opt_dimensions: %empty
#line 265 "robot.ypp"
    {
        yylhs.value.as < std::vector<int> > () = std::vector<int>();
    }
#line 1076 "robot.tab.cpp"
    break;

  case 17: // opt_dimensions: TOKEN_DIMENSIONS_OPEN TOKEN_COUNT TOKEN_INT_LIT '>' dims_list TOKEN_DIMENSIONS_CLOSE
#line 269 "robot.ypp"
    {
        if (yystack_[3].value.as < int > () != (int)yystack_[1].value.as < std::vector<int> > ().size()){ // несовпадение count и сколько объявлено измерений
            std::cerr << "SEMANTIC ERROR: dimension count mismatch" << std::endl;
            exit(1);
        }
        yylhs.value.as < std::vector<int> > () = yystack_[1].value.as < std::vector<int> > ();
    }
#line 1088 "robot.tab.cpp"
    break;

  case 18: // dims_list: TOKEN_DIMENSION_OPEN TOKEN_INT_LIT TOKEN_DIMENSION_CLOSE
#line 280 "robot.ypp"
    {
        yylhs.value.as < std::vector<int> > ().push_back(yystack_[1].value.as < int > ());
    }
#line 1096 "robot.tab.cpp"
    break;

  case 19: // dims_list: dims_list TOKEN_DIMENSION_OPEN TOKEN_INT_LIT TOKEN_DIMENSION_CLOSE
#line 284 "robot.ypp"
    {
        yystack_[3].value.as < std::vector<int> > ().push_back(yystack_[1].value.as < int > ());
        yylhs.value.as < std::vector<int> > () = yystack_[3].value.as < std::vector<int> > ();
    }
#line 1105 "robot.tab.cpp"
    break;

  case 20: // opt_init_values: %empty
#line 292 "robot.ypp"
    {
        yylhs.value.as < std::vector<expr_ptr> > () = std::vector<expr_ptr>();
    }
#line 1113 "robot.tab.cpp"
    break;

  case 21: // opt_init_values: TOKEN_VALUES_OPEN value_list TOKEN_VALUES_CLOSE
#line 296 "robot.ypp"
    {
        yylhs.value.as < std::vector<expr_ptr> > () = yystack_[1].value.as < std::vector<expr_ptr> > ();
    }
#line 1121 "robot.tab.cpp"
    break;

  case 22: // value_list: TOKEN_VALUE_OPEN expr TOKEN_VALUE_CLOSE
#line 303 "robot.ypp"
    {
        yylhs.value.as < std::vector<expr_ptr> > ().push_back(yystack_[1].value.as < expr_ptr > ());
    }
#line 1129 "robot.tab.cpp"
    break;

  case 23: // value_list: value_list TOKEN_VALUE_OPEN expr TOKEN_VALUE_CLOSE
#line 307 "robot.ypp"
    {
        yystack_[3].value.as < std::vector<expr_ptr> > ().push_back(yystack_[1].value.as < expr_ptr > ());
        yylhs.value.as < std::vector<expr_ptr> > () = yystack_[3].value.as < std::vector<expr_ptr> > ();
    }
#line 1138 "robot.tab.cpp"
    break;

  case 24: // func_def: TOKEN_FUNC_OPEN TOKEN_NAME_ATTR TOKEN_MAIN '>' stmt_list TOKEN_FUNC_CLOSE
#line 326 "robot.ypp"
    {
        yylhs.value.as < FuncDecl > ().name_ = "main";
        yylhs.value.as < FuncDecl > ().body_ = yystack_[1].value.as < std::vector<stmt_ptr> > ();
        yylhs.value.as < FuncDecl > ().is_main_ = true;
        has_main = true;
    }
#line 1149 "robot.tab.cpp"
    break;

  case 25: // func_def: TOKEN_FUNC_OPEN TOKEN_NAME_ATTR TOKEN_STRING '>' stmt_list TOKEN_FUNC_CLOSE
#line 333 "robot.ypp"
    {
        yylhs.value.as < FuncDecl > ().name_ = yystack_[3].value.as < std::string > ();
        yylhs.value.as < FuncDecl > ().body_ = yystack_[1].value.as < std::vector<stmt_ptr> > ();
        yylhs.value.as < FuncDecl > ().is_main_ = false;
    }
#line 1159 "robot.tab.cpp"
    break;

  case 26: // stmt_list: %empty
#line 341 "robot.ypp"
           { yylhs.value.as < std::vector<stmt_ptr> > () = std::vector<stmt_ptr>(); }
#line 1165 "robot.tab.cpp"
    break;

  case 27: // stmt_list: stmt_list stmt
#line 343 "robot.ypp"
    {
        yystack_[1].value.as < std::vector<stmt_ptr> > ().push_back(yystack_[0].value.as < stmt_ptr > ());
        yylhs.value.as < std::vector<stmt_ptr> > () = yystack_[1].value.as < std::vector<stmt_ptr> > ();
    }
#line 1174 "robot.tab.cpp"
    break;

  case 28: // stmt_list: stmt_list error
#line 348 "robot.ypp"
    {
        std::cerr << "Syntax error in statement list. Skipping..." << std::endl;
        yyerrok;
        yylhs.value.as < std::vector<stmt_ptr> > () = yystack_[1].value.as < std::vector<stmt_ptr> > ();
    }
#line 1184 "robot.tab.cpp"
    break;

  case 29: // stmt: assign_stmt
#line 356 "robot.ypp"
                { yylhs.value.as < stmt_ptr > () = yystack_[0].value.as < stmt_ptr > (); }
#line 1190 "robot.tab.cpp"
    break;

  case 30: // stmt: while_stmt
#line 357 "robot.ypp"
                 { yylhs.value.as < stmt_ptr > () = yystack_[0].value.as < stmt_ptr > (); }
#line 1196 "robot.tab.cpp"
    break;

  case 31: // stmt: switch_stmt
#line 358 "robot.ypp"
                  { yylhs.value.as < stmt_ptr > () = yystack_[0].value.as < stmt_ptr > (); }
#line 1202 "robot.tab.cpp"
    break;

  case 32: // stmt: move_stmt
#line 359 "robot.ypp"
                { yylhs.value.as < stmt_ptr > () = yystack_[0].value.as < stmt_ptr > (); }
#line 1208 "robot.tab.cpp"
    break;

  case 33: // stmt: call_stmt
#line 360 "robot.ypp"
                { yylhs.value.as < stmt_ptr > () = yystack_[0].value.as < stmt_ptr > (); }
#line 1214 "robot.tab.cpp"
    break;

  case 34: // stmt: getdrons_stmt
#line 361 "robot.ypp"
                    { yylhs.value.as < stmt_ptr > () = yystack_[0].value.as < stmt_ptr > (); }
#line 1220 "robot.tab.cpp"
    break;

  case 35: // stmt: expr_stmt
#line 362 "robot.ypp"
                { yylhs.value.as < stmt_ptr > () = yystack_[0].value.as < stmt_ptr > (); }
#line 1226 "robot.tab.cpp"
    break;

  case 36: // expr_stmt: expr
#line 367 "robot.ypp"
    {
        auto statement = std::make_shared<StmtNode>(StmtNode::EXPR);
        statement->expr_val_ = yystack_[0].value.as < expr_ptr > ();
        yylhs.value.as < stmt_ptr > () = statement;
    }
#line 1236 "robot.tab.cpp"
    break;

  case 37: // assign_stmt: TOKEN_ASSIGN_OPEN TOKEN_VALUE_OPEN expr TOKEN_VALUE_CLOSE TOKEN_TO_OPEN var_ref_list TOKEN_TO_CLOSE TOKEN_ASSIGN_CLOSE
#line 382 "robot.ypp"
    {
        auto st = std::make_shared<StmtNode>(StmtNode::ASSIGN);
        st->value_ = yystack_[5].value.as < expr_ptr > ();
        st->targets_ = yystack_[2].value.as < std::vector<expr_ptr> > ();
        yylhs.value.as < stmt_ptr > () = st;
    }
#line 1247 "robot.tab.cpp"
    break;

  case 38: // var_ref_list: var_ref
#line 392 "robot.ypp"
    {
        yylhs.value.as < std::vector<expr_ptr> > ().push_back(yystack_[0].value.as < expr_ptr > ());
    }
#line 1255 "robot.tab.cpp"
    break;

  case 39: // var_ref_list: var_ref_list var_ref
#line 396 "robot.ypp"
    {
        yystack_[1].value.as < std::vector<expr_ptr> > ().push_back(yystack_[0].value.as < expr_ptr > ());
        yylhs.value.as < std::vector<expr_ptr> > () = yystack_[1].value.as < std::vector<expr_ptr> > ();
    }
#line 1264 "robot.tab.cpp"
    break;

  case 40: // while_stmt: TOKEN_WHILE_OPEN TOKEN_CHECK_OPEN expr TOKEN_CHECK_CLOSE TOKEN_DO_OPEN stmt_list TOKEN_DO_CLOSE TOKEN_WHILE_CLOSE
#line 414 "robot.ypp"
    {
        auto st = std::make_shared<StmtNode>(StmtNode::WHILE);
        st->while_cond_ = yystack_[5].value.as < expr_ptr > ();
        st->while_body_ = yystack_[2].value.as < std::vector<stmt_ptr> > ();
        yylhs.value.as < stmt_ptr > () = st;
    }
#line 1275 "robot.tab.cpp"
    break;

  case 41: // switch_stmt: TOKEN_SWITCH_OPEN cond_list TOKEN_SWITCH_CLOSE
#line 445 "robot.ypp"
    {
        auto st = std::make_shared<StmtNode>(StmtNode::SWITCH);
        st->switch_cases_ = yystack_[1].value.as < std::vector<ConditionBranch> > ();
        yylhs.value.as < stmt_ptr > () = st;
    }
#line 1285 "robot.tab.cpp"
    break;

  case 42: // cond_list: cond_branch
#line 454 "robot.ypp"
    {
        yylhs.value.as < std::vector<ConditionBranch> > ().push_back(yystack_[0].value.as < ConditionBranch > ());
    }
#line 1293 "robot.tab.cpp"
    break;

  case 43: // cond_list: cond_list cond_branch
#line 458 "robot.ypp"
    {
        yystack_[1].value.as < std::vector<ConditionBranch> > ().push_back(yystack_[0].value.as < ConditionBranch > ());
        yylhs.value.as < std::vector<ConditionBranch> > () = yystack_[1].value.as < std::vector<ConditionBranch> > ();
    }
#line 1302 "robot.tab.cpp"
    break;

  case 44: // cond_branch: TOKEN_CONDITION_OPEN TOKEN_CHECK_OPEN expr TOKEN_CHECK_CLOSE TOKEN_DO_OPEN stmt_list TOKEN_DO_CLOSE TOKEN_CONDITION_CLOSE
#line 466 "robot.ypp"
    {
        yylhs.value.as < ConditionBranch > ().condition_ = yystack_[5].value.as < expr_ptr > ();
        yylhs.value.as < ConditionBranch > ().body_ = yystack_[2].value.as < std::vector<stmt_ptr> > ();
    }
#line 1311 "robot.tab.cpp"
    break;

  case 45: // move_stmt: TOKEN_LEFT_OPEN expr TOKEN_LEFT_CLOSE
#line 484 "robot.ypp"
    {
        auto st = std::make_shared<StmtNode>(StmtNode::MOVE);
        st->direction_ = StmtNode::LEFT;
        st->distance_ = yystack_[1].value.as < expr_ptr > ();
        yylhs.value.as < stmt_ptr > () = st;
    }
#line 1322 "robot.tab.cpp"
    break;

  case 46: // move_stmt: TOKEN_RIGHT_OPEN expr TOKEN_RIGHT_CLOSE
#line 491 "robot.ypp"
    {
        auto st = std::make_shared<StmtNode>(StmtNode::MOVE);
        st->direction_ = StmtNode::RIGHT;
        st->distance_ = yystack_[1].value.as < expr_ptr > ();
        yylhs.value.as < stmt_ptr > () = st;
    }
#line 1333 "robot.tab.cpp"
    break;

  case 47: // move_stmt: TOKEN_UP_OPEN expr TOKEN_UP_CLOSE
#line 498 "robot.ypp"
    {
        auto st = std::make_shared<StmtNode>(StmtNode::MOVE);
        st->direction_ = StmtNode::UP;
        st->distance_ = yystack_[1].value.as < expr_ptr > ();
        yylhs.value.as < stmt_ptr > () = st;
    }
#line 1344 "robot.tab.cpp"
    break;

  case 48: // move_stmt: TOKEN_DOWN_OPEN expr TOKEN_DOWN_CLOSE
#line 505 "robot.ypp"
    {
        auto st = std::make_shared<StmtNode>(StmtNode::MOVE);
        st->direction_ = StmtNode::DOWN;
        st->distance_ = yystack_[1].value.as < expr_ptr > ();
        yylhs.value.as < stmt_ptr > () = st;
    }
#line 1355 "robot.tab.cpp"
    break;

  case 49: // call_stmt: TOKEN_CALL_OPEN TOKEN_STRING TOKEN_CALL_CLOSE
#line 518 "robot.ypp"
    {
        auto st = std::make_shared<StmtNode>(StmtNode::CALL);
        st->call_name_ = yystack_[1].value.as < std::string > ();
        yylhs.value.as < stmt_ptr > () = st;
    }
#line 1365 "robot.tab.cpp"
    break;

  case 50: // getdrons_stmt: TOKEN_GETDRONSCOUNT_OPEN var_ref TOKEN_GETDRONSCOUNT_CLOSE
#line 530 "robot.ypp"
    {
        auto st = std::make_shared<StmtNode>(StmtNode::GETDRONSCOUNT);
        st->dron_target_ = yystack_[1].value.as < expr_ptr > ();
        yylhs.value.as < stmt_ptr > () = st;
    }
#line 1375 "robot.tab.cpp"
    break;

  case 51: // expr: primary_expr
#line 545 "robot.ypp"
    {
        yylhs.value.as < expr_ptr > () = yystack_[0].value.as < expr_ptr > ();
    }
#line 1383 "robot.tab.cpp"
    break;

  case 52: // expr: TOKEN_ADD_OPEN opt_expr_list TOKEN_ADD_CLOSE
#line 549 "robot.ypp"
    {
        auto ad = std::make_shared<ExprNode>(ExprNode::ADD);
        ad->args_ = yystack_[1].value.as < std::vector<expr_ptr> > ();
        yylhs.value.as < expr_ptr > () = ad;
    }
#line 1393 "robot.tab.cpp"
    break;

  case 53: // expr: TOKEN_MUL_OPEN opt_expr_list TOKEN_MUL_CLOSE
#line 555 "robot.ypp"
    {
        auto mu = std::make_shared<ExprNode>(ExprNode::MUL);
        mu->args_ = yystack_[1].value.as < std::vector<expr_ptr> > ();
        yylhs.value.as < expr_ptr > () = mu;
    }
#line 1403 "robot.tab.cpp"
    break;

  case 54: // expr: TOKEN_SUB_OPEN expr expr TOKEN_SUB_CLOSE
#line 561 "robot.ypp"
    {
        auto su = std::make_shared<ExprNode>(ExprNode::SUB);
        su->args_.push_back(yystack_[2].value.as < expr_ptr > ());
        su->args_.push_back(yystack_[1].value.as < expr_ptr > ());
        yylhs.value.as < expr_ptr > () = su;
    }
#line 1414 "robot.tab.cpp"
    break;

  case 55: // expr: TOKEN_DIV_OPEN expr expr TOKEN_DIV_CLOSE
#line 568 "robot.ypp"
    {
        auto di = std::make_shared<ExprNode>(ExprNode::DIV);
        di->args_.push_back(yystack_[2].value.as < expr_ptr > ());
        di->args_.push_back(yystack_[1].value.as < expr_ptr > ());
        yylhs.value.as < expr_ptr > () = di;
    }
#line 1425 "robot.tab.cpp"
    break;

  case 56: // expr: TOKEN_AND_OPEN opt_expr_list TOKEN_AND_CLOSE
#line 575 "robot.ypp"
    {
        auto a = std::make_shared<ExprNode>(ExprNode::AND);
        a->args_ = yystack_[1].value.as < std::vector<expr_ptr> > ();
        yylhs.value.as < expr_ptr > () = a;
    }
#line 1435 "robot.tab.cpp"
    break;

  case 57: // expr: TOKEN_OR_OPEN opt_expr_list TOKEN_OR_CLOSE
#line 581 "robot.ypp"
    {
        auto o = std::make_shared<ExprNode>(ExprNode::OR);
        o->args_ = yystack_[1].value.as < std::vector<expr_ptr> > ();
        yylhs.value.as < expr_ptr > () = o;
    }
#line 1445 "robot.tab.cpp"
    break;

  case 58: // expr: TOKEN_NOT_OPEN expr TOKEN_NOT_CLOSE
#line 587 "robot.ypp"
    {
        auto n = std::make_shared<ExprNode>(ExprNode::NOT);
        n->args_.push_back(yystack_[1].value.as < expr_ptr > ());
        yylhs.value.as < expr_ptr > () = n;
    }
#line 1455 "robot.tab.cpp"
    break;

  case 59: // expr: TOKEN_EQ_OPEN opt_expr_list TOKEN_EQ_CLOSE
#line 593 "robot.ypp"
    {
        auto eq = std::make_shared<ExprNode>(ExprNode::EQ);
        eq->args_ = yystack_[1].value.as < std::vector<expr_ptr> > ();
        yylhs.value.as < expr_ptr > () = eq;
    }
#line 1465 "robot.tab.cpp"
    break;

  case 60: // expr: TOKEN_MAX_OPEN opt_expr_list TOKEN_MAX_CLOSE
#line 599 "robot.ypp"
    {
        auto ma = std::make_shared<ExprNode>(ExprNode::MAX);
        ma->args_ = yystack_[1].value.as < std::vector<expr_ptr> > ();
        yylhs.value.as < expr_ptr > () = ma;
    }
#line 1475 "robot.tab.cpp"
    break;

  case 61: // expr: TOKEN_MIN_OPEN opt_expr_list TOKEN_MIN_CLOSE
#line 605 "robot.ypp"
    {
        auto mi = std::make_shared<ExprNode>(ExprNode::MIN);
        mi->args_ = yystack_[1].value.as < std::vector<expr_ptr> > ();
        yylhs.value.as < expr_ptr > () = mi;
    }
#line 1485 "robot.tab.cpp"
    break;

  case 62: // expr: TOKEN_SENDDRONS_OPEN expr TOKEN_SENDDRONS_CLOSE
#line 611 "robot.ypp"
    {
        auto drons = std::make_shared<ExprNode>(ExprNode::SENDDRONS);
        drons->args_.push_back(yystack_[1].value.as < expr_ptr > ());
        yylhs.value.as < expr_ptr > () = drons;
    }
#line 1495 "robot.tab.cpp"
    break;

  case 63: // expr: TOKEN_CALL_OPEN TOKEN_STRING TOKEN_CALL_CLOSE
#line 617 "robot.ypp"
    {
        auto call = std::make_shared<ExprNode>(ExprNode::CALL);
        call->var_name_ = yystack_[1].value.as < std::string > ();
        yylhs.value.as < expr_ptr > () = call;
    }
#line 1505 "robot.tab.cpp"
    break;

  case 64: // opt_expr_list: %empty
#line 626 "robot.ypp"
    {
        yylhs.value.as < std::vector<expr_ptr> > () = std::vector<expr_ptr>();
    }
#line 1513 "robot.tab.cpp"
    break;

  case 65: // opt_expr_list: expr_list
#line 630 "robot.ypp"
    {
        yylhs.value.as < std::vector<expr_ptr> > () = yystack_[0].value.as < std::vector<expr_ptr> > ();
    }
#line 1521 "robot.tab.cpp"
    break;

  case 66: // expr_list: expr
#line 637 "robot.ypp"
    {
        yylhs.value.as < std::vector<expr_ptr> > ().push_back(yystack_[0].value.as < expr_ptr > ());
    }
#line 1529 "robot.tab.cpp"
    break;

  case 67: // expr_list: expr_list expr
#line 641 "robot.ypp"
    {
        yystack_[1].value.as < std::vector<expr_ptr> > ().push_back(yystack_[0].value.as < expr_ptr > ());
        yylhs.value.as < std::vector<expr_ptr> > () = yystack_[1].value.as < std::vector<expr_ptr> > ();
    }
#line 1538 "robot.tab.cpp"
    break;

  case 68: // primary_expr: TOKEN_INT_LIT
#line 649 "robot.ypp"
    {
        yylhs.value.as < expr_ptr > () = ExprNode::make_int(yystack_[0].value.as < int > ());
    }
#line 1546 "robot.tab.cpp"
    break;

  case 69: // primary_expr: TOKEN_BOOL_LIT
#line 653 "robot.ypp"
    {
        yylhs.value.as < expr_ptr > () = ExprNode::make_bool(yystack_[0].value.as < bool > ());
    }
#line 1554 "robot.tab.cpp"
    break;

  case 70: // primary_expr: TOKEN_CELL_VALUE
#line 657 "robot.ypp"
    {
        yylhs.value.as < expr_ptr > () = ExprNode::make_cell(yystack_[0].value.as < CellValue > ());
    }
#line 1562 "robot.tab.cpp"
    break;

  case 71: // primary_expr: var_ref
#line 661 "robot.ypp"
    {
        yylhs.value.as < expr_ptr > () = yystack_[0].value.as < expr_ptr > ();
    }
#line 1570 "robot.tab.cpp"
    break;

  case 72: // var_ref: TOKEN_IDENTIFIER
#line 675 "robot.ypp"
    {
        auto iden = ExprNode::make_var_ref(yystack_[0].value.as < std::string > ());
        yylhs.value.as < expr_ptr > () = iden;
    }
#line 1579 "robot.tab.cpp"
    break;

  case 73: // var_ref: TOKEN_IDENTIFIER dim_ref_list
#line 680 "robot.ypp"
    {
        auto iden = ExprNode::make_var_ref(yystack_[1].value.as < std::string > ());
        for (auto& idx : yystack_[0].value.as < std::vector<expr_ptr> > ()) {
            iden->indices_.push_back(idx);
        }
        yylhs.value.as < expr_ptr > () = iden;
    }
#line 1591 "robot.tab.cpp"
    break;

  case 74: // dim_ref_list: TOKEN_DIM_OPEN TOKEN_INDEX_OPEN expr TOKEN_INDEX_CLOSE TOKEN_DIM_CLOSE
#line 691 "robot.ypp"
    {
        yylhs.value.as < std::vector<expr_ptr> > () = std::vector<expr_ptr>();
        yylhs.value.as < std::vector<expr_ptr> > ().push_back(yystack_[2].value.as < expr_ptr > ());
    }
#line 1600 "robot.tab.cpp"
    break;

  case 75: // dim_ref_list: dim_ref_list TOKEN_DIM_OPEN TOKEN_INDEX_OPEN expr TOKEN_INDEX_CLOSE TOKEN_DIM_CLOSE
#line 696 "robot.ypp"
    {
        yystack_[5].value.as < std::vector<expr_ptr> > ().push_back(yystack_[2].value.as < expr_ptr > ());
        yylhs.value.as < std::vector<expr_ptr> > () = yystack_[5].value.as < std::vector<expr_ptr> > ();
    }
#line 1609 "robot.tab.cpp"
    break;


#line 1613 "robot.tab.cpp"

            default:
              break;
            }
        }
#if YY_EXCEPTIONS
      catch (const syntax_error& yyexc)
        {
          YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
          error (yyexc);
          YYERROR;
        }
#endif // YY_EXCEPTIONS
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, YY_MOVE (yylhs));
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
        context yyctx (*this, yyla);
        std::string msg = yysyntax_error_ (yyctx);
        error (yyla.location, YY_MOVE (msg));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.kind () == symbol_kind::S_YYEOF)
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
    /* Pacify compilers when the user code never invokes YYERROR and
       the label yyerrorlab therefore never appears in user code.  */
    if (false)
      YYERROR;

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    YY_STACK_PRINT ();
    goto yyerrlab1;


  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    // Pop stack until we find a state that shifts the error token.
    for (;;)
      {
        yyn = yypact_[+yystack_[0].state];
        if (!yy_pact_value_is_default_ (yyn))
          {
            yyn += symbol_kind::S_YYerror;
            if (0 <= yyn && yyn <= yylast_
                && yycheck_[yyn] == symbol_kind::S_YYerror)
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
    {
      stack_symbol_type error_token;

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      error_token.state = state_type (yyn);
      yypush_ ("Shifting", YY_MOVE (error_token));
    }
    goto yynewstate;


  /*-------------------------------------.
  | yyacceptlab -- YYACCEPT comes here.  |
  `-------------------------------------*/
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;


  /*-----------------------------------.
  | yyabortlab -- YYABORT comes here.  |
  `-----------------------------------*/
  yyabortlab:
    yyresult = 1;
    goto yyreturn;


  /*-----------------------------------------------------.
  | yyreturn -- parsing is finished, return the result.  |
  `-----------------------------------------------------*/
  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    YY_STACK_PRINT ();
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
#if YY_EXCEPTIONS
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack\n";
        // Do not try to display the values of the reclaimed symbols,
        // as their printers might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
#endif // YY_EXCEPTIONS
  }

  void
   RobotParser ::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what ());
  }

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
   RobotParser ::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr;
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
              else
                goto append;

            append:
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

  std::string
   RobotParser ::symbol_name (symbol_kind_type yysymbol)
  {
    return yytnamerr_ (yytname_[yysymbol]);
  }



  //  RobotParser ::context.
   RobotParser ::context::context (const  RobotParser & yyparser, const symbol_type& yyla)
    : yyparser_ (yyparser)
    , yyla_ (yyla)
  {}

  int
   RobotParser ::context::expected_tokens (symbol_kind_type yyarg[], int yyargn) const
  {
    // Actual number of expected tokens
    int yycount = 0;

    const int yyn = yypact_[+yyparser_.yystack_[0].state];
    if (!yy_pact_value_is_default_ (yyn))
      {
        /* Start YYX at -YYN if negative to avoid negative indexes in
           YYCHECK.  In other words, skip the first -YYN actions for
           this state because they are default actions.  */
        const int yyxbegin = yyn < 0 ? -yyn : 0;
        // Stay within bounds of both yycheck and yytname.
        const int yychecklim = yylast_ - yyn + 1;
        const int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
        for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
          if (yycheck_[yyx + yyn] == yyx && yyx != symbol_kind::S_YYerror
              && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
            {
              if (!yyarg)
                ++yycount;
              else if (yycount == yyargn)
                return 0;
              else
                yyarg[yycount++] = YY_CAST (symbol_kind_type, yyx);
            }
      }

    if (yyarg && yycount == 0 && 0 < yyargn)
      yyarg[0] = symbol_kind::S_YYEMPTY;
    return yycount;
  }






  int
   RobotParser ::yy_syntax_error_arguments_ (const context& yyctx,
                                                 symbol_kind_type yyarg[], int yyargn) const
  {
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
         scanner and before detecting a syntax error.  Thus, state merging
         (from LALR or IELR) and default reductions corrupt the expected
         token list.  However, the list is correct for canonical LR with
         one exception: it will still contain any token that will not be
         accepted due to an error action in a later state.
    */

    if (!yyctx.lookahead ().empty ())
      {
        if (yyarg)
          yyarg[0] = yyctx.token ();
        int yyn = yyctx.expected_tokens (yyarg ? yyarg + 1 : yyarg, yyargn - 1);
        return yyn + 1;
      }
    return 0;
  }

  // Generate an error message.
  std::string
   RobotParser ::yysyntax_error_ (const context& yyctx) const
  {
    // Its maximum.
    enum { YYARGS_MAX = 5 };
    // Arguments of yyformat.
    symbol_kind_type yyarg[YYARGS_MAX];
    int yycount = yy_syntax_error_arguments_ (yyctx, yyarg, YYARGS_MAX);

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
      default: // Avoid compiler warnings.
        YYCASE_ (0, YY_("syntax error"));
        YYCASE_ (1, YY_("syntax error, unexpected %s"));
        YYCASE_ (2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_ (3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_ (4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_ (5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    std::string yyres;
    // Argument number.
    std::ptrdiff_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += symbol_name (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const signed char  RobotParser ::yypact_ninf_ = -44;

  const signed char  RobotParser ::yytable_ninf_ = -1;

  const short
   RobotParser ::yypact_[] =
  {
      15,   -44,    36,    34,   -44,   -44,   -44,    30,    26,   -44,
     -44,    27,     2,   -44,    -1,    25,   -44,   -44,   -43,   -40,
      33,   -44,   -44,    32,   -35,    98,   175,   -44,    35,   -44,
     -44,    38,   -44,    20,     8,     7,     5,     5,     5,     5,
       5,   -28,     5,     5,     5,     5,     5,     5,     5,     5,
       5,     5,   -44,   -44,    40,   -44,   -44,   -44,   -44,   -44,
     -44,   -44,   -44,   -44,   -44,   -44,   -44,   -16,    41,    45,
       5,     5,    18,   -26,   -44,    43,    13,    17,    11,    19,
       9,    21,   -44,    23,     5,    28,     5,     5,     3,    22,
      16,    24,    29,    31,    46,    52,    71,    73,    75,    81,
      69,   -44,    72,    55,     5,   -44,   -44,    90,   -44,   -44,
     -44,   -44,   -44,   -44,   -44,   -44,   -44,    37,    42,   -44,
     -44,   -44,   -44,   -44,   -44,     5,    76,   -44,   -44,   -44,
      39,    83,   110,    67,    77,    78,   -44,   -44,   -44,    85,
       5,    47,     5,    -6,   -44,   -28,   -44,    82,    93,    94,
      92,    97,   -44,     5,   -36,   -44,   250,   -44,   -44,    99,
      48,     1,   -44,   104,   100,   -44,   101,   325,   -44,   112,
     -44,    57,   -44,   -44,   -44,    96,   -44,   116,   -44,   -44
  };

  const signed char
   RobotParser ::yydefact_[] =
  {
       0,     3,     0,     0,     1,     6,     2,     0,     0,     4,
       5,     0,     0,     8,     0,     0,     7,     9,     0,     0,
      12,    26,    26,     0,     0,     0,     0,    11,     0,    28,
      24,     0,    70,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    64,    64,     0,     0,     0,    64,    64,    64,
      64,    64,    69,    68,    72,    27,    35,    29,    30,    31,
      32,    33,    34,    36,    51,    71,    25,     0,    16,     0,
       0,     0,     0,     0,    42,     0,     0,     0,     0,     0,
       0,     0,    66,     0,    65,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    73,     0,     0,     0,     0,
      20,    49,     0,     0,     0,    41,    43,     0,    45,    46,
      47,    48,    62,    50,    52,    67,    53,     0,     0,    58,
      57,    56,    60,    61,    59,     0,     0,    13,    14,    15,
       0,     0,     0,     0,     0,     0,    63,    54,    55,     0,
       0,     0,     0,     0,    10,     0,    26,     0,     0,     0,
       0,     0,    21,     0,     0,    38,     0,    26,    74,     0,
       0,     0,    22,     0,     0,    39,     0,     0,    75,     0,
      17,     0,    23,    37,    40,     0,    18,     0,    44,    19
  };

  const short
   RobotParser ::yypgoto_[] =
  {
     -44,   -44,   -44,   -44,   -44,   135,   -44,   -44,   -44,   -44,
     -44,   -44,   -44,   -20,   -44,   -44,   -44,   -44,   -44,   -44,
     -44,    79,   -44,   -44,   -44,   -25,   -17,   -44,   -44,   -38,
     -44
  };

  const unsigned char
   RobotParser ::yydefgoto_[] =
  {
       0,     2,     3,     9,    12,    13,    24,    68,   100,   161,
     132,   143,    10,    25,    55,    56,    57,   154,    58,    59,
      73,    74,    60,    61,    62,    82,    83,    84,    64,    65,
      95
  };

  const unsigned char
   RobotParser ::yytable_[] =
  {
      63,    63,    26,    81,   164,    96,    97,    98,    16,    11,
      18,    76,    77,    78,    79,    80,    19,    75,     1,    86,
      87,    88,   105,    72,   152,   153,    85,   170,   171,    32,
      89,    90,    91,    92,    93,     5,     4,    11,     6,     7,
      14,    15,    20,     8,    21,   102,   103,    22,    23,    54,
      27,    70,    28,    71,    67,    69,    72,    54,   101,   115,
     107,   117,   118,   104,    40,   108,    99,   110,    42,   112,
      43,   109,    44,    94,    45,   119,    46,   111,    47,   135,
      48,   125,    49,   113,    50,   126,    51,   114,    52,    53,
      54,   127,   121,   128,   116,   129,   120,   130,   131,    29,
     139,   134,   122,   136,   133,   137,   145,   155,    30,   123,
      31,   140,   138,   124,   142,   149,   165,   151,   144,   160,
     146,   148,    32,   141,   147,   157,   156,   158,   163,   162,
     159,    63,   169,   168,   150,    33,   172,   167,   173,    34,
     176,   177,    63,   174,   179,    35,   178,    17,     0,    36,
       0,    37,   106,    38,     0,    39,     0,    40,     0,    41,
       0,    42,     0,    43,     0,    44,     0,    45,     0,    46,
       0,    47,     0,    48,     0,    49,    29,    50,     0,    51,
       0,    52,    53,    54,     0,    66,     0,    31,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    32,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    33,     0,     0,     0,    34,     0,     0,     0,
       0,     0,    35,     0,     0,     0,    36,     0,    37,     0,
      38,     0,    39,     0,    40,     0,    41,     0,    42,     0,
      43,     0,    44,     0,    45,     0,    46,     0,    47,     0,
      48,    29,    49,     0,    50,     0,    51,     0,    52,    53,
      54,     0,    31,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    32,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    33,     0,     0,
       0,    34,     0,     0,   166,     0,     0,    35,     0,     0,
       0,    36,     0,    37,     0,    38,     0,    39,     0,    40,
       0,    41,     0,    42,     0,    43,     0,    44,     0,    45,
       0,    46,     0,    47,     0,    48,    29,    49,     0,    50,
       0,    51,     0,    52,    53,    54,     0,    31,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    32,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    33,     0,     0,     0,    34,     0,     0,   175,
       0,     0,    35,     0,     0,     0,    36,     0,    37,     0,
      38,     0,    39,     0,    40,     0,    41,     0,    42,     0,
      43,     0,    44,     0,    45,     0,    46,     0,    47,     0,
      48,     0,    49,     0,    50,     0,    51,     0,    52,    53,
      54
  };

  const short
   RobotParser ::yycheck_[] =
  {
      25,    26,    22,    41,    40,    21,    22,    23,     6,     7,
      11,    36,    37,    38,    39,    40,    17,    12,     3,    44,
      45,    46,    48,    49,    30,    31,    43,    26,    27,    24,
      47,    48,    49,    50,    51,     1,     0,     7,     4,     5,
      14,    14,    17,     9,    87,    70,    71,    87,    15,    85,
      18,    31,    87,    45,    19,    17,    49,    85,    13,    84,
      17,    86,    87,    45,    59,    52,    25,    56,    63,    60,
      65,    54,    67,    33,    69,    72,    71,    58,    73,   104,
      75,    35,    77,    62,    79,    33,    81,    64,    83,    84,
      85,    20,    76,    20,    66,    20,    74,    16,    29,     1,
     125,    46,    78,    13,    32,    68,    39,   145,    10,    80,
      12,    35,    70,    82,    31,   140,   154,   142,     8,    27,
      43,    36,    24,    84,    46,    43,   146,    34,   153,    32,
      36,   156,    84,    34,    87,    37,    32,   157,    38,    41,
      28,    84,   167,    42,    28,    47,    50,    12,    -1,    51,
      -1,    53,    73,    55,    -1,    57,    -1,    59,    -1,    61,
      -1,    63,    -1,    65,    -1,    67,    -1,    69,    -1,    71,
      -1,    73,    -1,    75,    -1,    77,     1,    79,    -1,    81,
      -1,    83,    84,    85,    -1,    10,    -1,    12,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    24,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    37,    -1,    -1,    -1,    41,    -1,    -1,    -1,
      -1,    -1,    47,    -1,    -1,    -1,    51,    -1,    53,    -1,
      55,    -1,    57,    -1,    59,    -1,    61,    -1,    63,    -1,
      65,    -1,    67,    -1,    69,    -1,    71,    -1,    73,    -1,
      75,     1,    77,    -1,    79,    -1,    81,    -1,    83,    84,
      85,    -1,    12,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    24,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    37,    -1,    -1,
      -1,    41,    -1,    -1,    44,    -1,    -1,    47,    -1,    -1,
      -1,    51,    -1,    53,    -1,    55,    -1,    57,    -1,    59,
      -1,    61,    -1,    63,    -1,    65,    -1,    67,    -1,    69,
      -1,    71,    -1,    73,    -1,    75,     1,    77,    -1,    79,
      -1,    81,    -1,    83,    84,    85,    -1,    12,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    24,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    37,    -1,    -1,    -1,    41,    -1,    -1,    44,
      -1,    -1,    47,    -1,    -1,    -1,    51,    -1,    53,    -1,
      55,    -1,    57,    -1,    59,    -1,    61,    -1,    63,    -1,
      65,    -1,    67,    -1,    69,    -1,    71,    -1,    73,    -1,
      75,    -1,    77,    -1,    79,    -1,    81,    -1,    83,    84,
      85
  };

  const signed char
   RobotParser ::yystos_[] =
  {
       0,     3,    89,    90,     0,     1,     4,     5,     9,    91,
     100,     7,    92,    93,    14,    14,     6,    93,    11,    17,
      17,    87,    87,    15,    94,   101,   101,    18,    87,     1,
      10,    12,    24,    37,    41,    47,    51,    53,    55,    57,
      59,    61,    63,    65,    67,    69,    71,    73,    75,    77,
      79,    81,    83,    84,    85,   102,   103,   104,   106,   107,
     110,   111,   112,   113,   116,   117,    10,    19,    95,    17,
      31,    45,    49,   108,   109,    12,   113,   113,   113,   113,
     113,   117,   113,   114,   115,   114,   113,   113,   113,   114,
     114,   114,   114,   114,    33,   118,    21,    22,    23,    25,
      96,    13,   113,   113,    45,    48,   109,    17,    52,    54,
      56,    58,    60,    62,    64,   113,    66,   113,   113,    72,
      74,    76,    78,    80,    82,    35,    33,    20,    20,    20,
      16,    29,    98,    32,    46,   113,    13,    68,    70,   113,
      35,    84,    31,    99,     8,    39,    43,    46,    36,   113,
      87,   113,    30,    31,   105,   117,   101,    43,    34,    36,
      27,    97,    32,   113,    40,   117,    44,   101,    34,    84,
      26,    27,    32,    38,    42,    44,    28,    84,    50,    28
  };

  const signed char
   RobotParser ::yyr1_[] =
  {
       0,    88,    89,    90,    90,    90,    90,    91,    92,    92,
      93,    94,    94,    95,    95,    95,    96,    96,    97,    97,
      98,    98,    99,    99,   100,   100,   101,   101,   101,   102,
     102,   102,   102,   102,   102,   102,   103,   104,   105,   105,
     106,   107,   108,   108,   109,   110,   110,   110,   110,   111,
     112,   113,   113,   113,   113,   113,   113,   113,   113,   113,
     113,   113,   113,   113,   114,   114,   115,   115,   116,   116,
     116,   116,   117,   117,   118,   118
  };

  const signed char
   RobotParser ::yyr2_[] =
  {
       0,     2,     3,     0,     2,     2,     2,     3,     1,     2,
       9,     2,     0,     3,     3,     3,     0,     6,     3,     4,
       0,     3,     3,     4,     6,     6,     0,     2,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     8,     1,     2,
       8,     3,     1,     2,     8,     3,     3,     3,     3,     3,
       3,     1,     3,     3,     4,     4,     3,     3,     3,     3,
       3,     3,     3,     3,     0,     1,     1,     2,     1,     1,
       1,     1,     1,     2,     5,     6
  };


#if YYDEBUG || 1
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a YYNTOKENS, nonterminals.
  const char*
  const  RobotParser ::yytname_[] =
  {
  "\"end of file\"", "error", "\"invalid token\"", "TOKEN_PROGRAM_OPEN",
  "TOKEN_PROGRAM_CLOSE", "TOKEN_VARDECL_OPEN", "TOKEN_VARDECL_CLOSE",
  "TOKEN_VAR_OPEN", "TOKEN_VAR_CLOSE", "TOKEN_FUNC_OPEN",
  "TOKEN_FUNC_CLOSE", "TOKEN_MAIN", "TOKEN_CALL_OPEN", "TOKEN_CALL_CLOSE",
  "TOKEN_NAME_ATTR", "TOKEN_CONST", "TOKEN_COUNT", "TOKEN_STRING",
  "TOKEN_BOOL", "TOKEN_TYPE_OPEN", "TOKEN_TYPE_CLOSE", "TOKEN_TYPE_INT",
  "TOKEN_TYPE_BOOL", "TOKEN_TYPE_CELL", "TOKEN_CELL_VALUE",
  "TOKEN_DIMENSIONS_OPEN", "TOKEN_DIMENSIONS_CLOSE",
  "TOKEN_DIMENSION_OPEN", "TOKEN_DIMENSION_CLOSE", "TOKEN_VALUES_OPEN",
  "TOKEN_VALUES_CLOSE", "TOKEN_VALUE_OPEN", "TOKEN_VALUE_CLOSE",
  "TOKEN_DIM_OPEN", "TOKEN_DIM_CLOSE", "TOKEN_INDEX_OPEN",
  "TOKEN_INDEX_CLOSE", "TOKEN_ASSIGN_OPEN", "TOKEN_ASSIGN_CLOSE",
  "TOKEN_TO_OPEN", "TOKEN_TO_CLOSE", "TOKEN_WHILE_OPEN",
  "TOKEN_WHILE_CLOSE", "TOKEN_DO_OPEN", "TOKEN_DO_CLOSE",
  "TOKEN_CHECK_OPEN", "TOKEN_CHECK_CLOSE", "TOKEN_SWITCH_OPEN",
  "TOKEN_SWITCH_CLOSE", "TOKEN_CONDITION_OPEN", "TOKEN_CONDITION_CLOSE",
  "TOKEN_LEFT_OPEN", "TOKEN_LEFT_CLOSE", "TOKEN_RIGHT_OPEN",
  "TOKEN_RIGHT_CLOSE", "TOKEN_UP_OPEN", "TOKEN_UP_CLOSE",
  "TOKEN_DOWN_OPEN", "TOKEN_DOWN_CLOSE", "TOKEN_SENDDRONS_OPEN",
  "TOKEN_SENDDRONS_CLOSE", "TOKEN_GETDRONSCOUNT_OPEN",
  "TOKEN_GETDRONSCOUNT_CLOSE", "TOKEN_ADD_OPEN", "TOKEN_ADD_CLOSE",
  "TOKEN_MUL_OPEN", "TOKEN_MUL_CLOSE", "TOKEN_SUB_OPEN", "TOKEN_SUB_CLOSE",
  "TOKEN_DIV_OPEN", "TOKEN_DIV_CLOSE", "TOKEN_NOT_OPEN", "TOKEN_NOT_CLOSE",
  "TOKEN_OR_OPEN", "TOKEN_OR_CLOSE", "TOKEN_AND_OPEN", "TOKEN_AND_CLOSE",
  "TOKEN_MAX_OPEN", "TOKEN_MAX_CLOSE", "TOKEN_MIN_OPEN", "TOKEN_MIN_CLOSE",
  "TOKEN_EQ_OPEN", "TOKEN_EQ_CLOSE", "TOKEN_BOOL_LIT", "TOKEN_INT_LIT",
  "TOKEN_IDENTIFIER", "TOKEN_SELFCLOSE", "'>'", "$accept", "program",
  "program_items", "vardecl_block", "var_list", "var_item", "opt_const",
  "type_spec", "opt_dimensions", "dims_list", "opt_init_values",
  "value_list", "func_def", "stmt_list", "stmt", "expr_stmt",
  "assign_stmt", "var_ref_list", "while_stmt", "switch_stmt", "cond_list",
  "cond_branch", "move_stmt", "call_stmt", "getdrons_stmt", "expr",
  "opt_expr_list", "expr_list", "primary_expr", "var_ref", "dim_ref_list", YY_NULLPTR
  };
#endif


#if YYDEBUG
  const short
   RobotParser ::yyrline_[] =
  {
       0,   151,   151,   164,   165,   166,   177,   185,   201,   205,
     228,   238,   242,   249,   253,   257,   264,   268,   279,   283,
     291,   295,   302,   306,   325,   332,   341,   342,   347,   356,
     357,   358,   359,   360,   361,   362,   366,   381,   391,   395,
     413,   444,   453,   457,   465,   483,   490,   497,   504,   517,
     529,   544,   548,   554,   560,   567,   574,   580,   586,   592,
     598,   604,   610,   616,   625,   629,   636,   640,   648,   652,
     656,   660,   674,   679,   690,   695
  };

  void
   RobotParser ::yy_stack_print_ () const
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << int (i->state);
    *yycdebug_ << '\n';
  }

  void
   RobotParser ::yy_reduce_print_ (int yyrule) const
  {
    int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):\n";
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG


#line 47 "robot.ypp"
} //  yy 
#line 2264 "robot.tab.cpp"

#line 702 "robot.ypp"


void yy::RobotParser::error(const location_type& loc, const std::string& msg) {
    std::cerr << "Error at " << loc << ": " << msg << std::endl;
}







