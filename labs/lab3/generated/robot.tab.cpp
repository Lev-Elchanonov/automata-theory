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
#line 25 "robot.ypp"

    #include <cstdio>
    #include <map>
    #include <stack>
    #include "RobotLexer.h"

    yy::RobotLexer* THE_LEXER = nullptr;


    std::map<std::string, SymbolInfo> global_symbols_;
    std::map<std::string, FuncDecl> functions_;
    bool has_main_ = false;
    std::vector<std::map<std::string, SymbolInfo>> local_scopes_;

    SymbolInfo* find_variable_in_scopes(const std::string& name) {
            for (auto it = local_scopes_.rbegin(); it != local_scopes_.rend(); ++it) {
                auto found = it->find(name);
                if (found != it->end()) {
                    return &found->second;
                }
            }
            auto found = global_symbols_.find(name);
            if (found != global_symbols_.end()) {
                return &found->second;
            }
            return nullptr;
        }


    static int yylex(yy::RobotParser::semantic_type* yylval, yy::location* loc, yy::RobotLexer& lexer) {
        return lexer.yylex(yylval, loc);
    }

    static int product(const std::vector<int>& dims){ // для вычисления общего количества элементов в многомерном массиве
        int p = 1;
        for (int d : dims) p *= d;
        return p;
    }

    int syntax_errors_ = 0;
    struct ErrorInfo{
        int line_;
        int column_;
        std::string msg_;
        std::string type_; // syntax или semantic
    };
    std::vector<ErrorInfo> errors_;
    void add_syntax_error(int line, int col, const std::string& error_msg){
        errors_.push_back({line, col, error_msg, "syntax"});
        syntax_errors_++;
    }
    void add_semantic_error(int line, int col, const std::string& error_msg){
        errors_.push_back({line, col, error_msg, "semantic"});
    }
    void print_all_errors() {
        if (!errors_.empty()) {
            std::cerr << "\n=== ERRORS FOUND: " << errors_.size() << " ===\n";
                for (const auto& e : errors_) {
                    std::cerr << "  [" << e.type_ << "] line " << e.line_ << ":" << e.column_ << " - " << e.msg_ << std::endl;
                }
                std::cerr << "=== END OF ERRORS ===\n\n";
        }
    }

#line 111 "generated/robot.tab.cpp"


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

#line 91 "robot.ypp"
namespace  yy  {
#line 204 "generated/robot.tab.cpp"

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

  // basic_symbol.
  template <typename Base>
   RobotParser ::basic_symbol<Base>::basic_symbol (const basic_symbol& that)
    : Base (that)
    , value ()
    , location (that.location)
  {
    switch (this->kind ())
    {
      case symbol_kind::S_TOKEN_CELL_VALUE: // TOKEN_CELL_VALUE
        value.copy< CellValue > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_cond_branch: // cond_branch
        value.copy< ConditionBranch > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_func_def: // func_def
      case symbol_kind::S_func_header: // func_header
        value.copy< FuncDecl > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_var_item: // var_item
        value.copy< VarDecl > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_type_spec: // type_spec
        value.copy< VarDecl::VarType > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_TOKEN_BOOL: // TOKEN_BOOL
      case symbol_kind::S_TOKEN_BOOL_LIT: // TOKEN_BOOL_LIT
      case symbol_kind::S_opt_const: // opt_const
        value.copy< bool > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr: // expr
      case symbol_kind::S_primary_expr: // primary_expr
      case symbol_kind::S_var_ref: // var_ref
        value.copy< expr_ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_TOKEN_INT_LIT: // TOKEN_INT_LIT
        value.copy< int > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_TOKEN_MAIN: // TOKEN_MAIN
      case symbol_kind::S_TOKEN_STRING: // TOKEN_STRING
      case symbol_kind::S_TOKEN_IDENTIFIER: // TOKEN_IDENTIFIER
        value.copy< std::string > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_cond_list: // cond_list
        value.copy< std::vector<ConditionBranch> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_var_list: // var_list
        value.copy< std::vector<VarDecl> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_opt_init_values: // opt_init_values
      case symbol_kind::S_value_list: // value_list
      case symbol_kind::S_var_ref_list: // var_ref_list
      case symbol_kind::S_opt_expr_list: // opt_expr_list
      case symbol_kind::S_expr_list: // expr_list
      case symbol_kind::S_dim_ref_list: // dim_ref_list
        value.copy< std::vector<expr_ptr> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_opt_dimensions: // opt_dimensions
      case symbol_kind::S_dims_list: // dims_list
        value.copy< std::vector<int> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_list: // stmt_list
        value.copy< std::vector<stmt_ptr> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt: // stmt
      case symbol_kind::S_vardecl_stmt: // vardecl_stmt
      case symbol_kind::S_expr_stmt: // expr_stmt
      case symbol_kind::S_assign_stmt: // assign_stmt
      case symbol_kind::S_while_stmt: // while_stmt
      case symbol_kind::S_switch_stmt: // switch_stmt
      case symbol_kind::S_move_stmt: // move_stmt
      case symbol_kind::S_call_stmt: // call_stmt
      case symbol_kind::S_getdrons_stmt: // getdrons_stmt
      case symbol_kind::S_get_x_stmt: // get_x_stmt
      case symbol_kind::S_get_y_stmt: // get_y_stmt
        value.copy< stmt_ptr > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

  }




  template <typename Base>
   RobotParser ::symbol_kind_type
   RobotParser ::basic_symbol<Base>::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }


  template <typename Base>
  bool
   RobotParser ::basic_symbol<Base>::empty () const YY_NOEXCEPT
  {
    return this->kind () == symbol_kind::S_YYEMPTY;
  }

  template <typename Base>
  void
   RobotParser ::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move (s);
    switch (this->kind ())
    {
      case symbol_kind::S_TOKEN_CELL_VALUE: // TOKEN_CELL_VALUE
        value.move< CellValue > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_cond_branch: // cond_branch
        value.move< ConditionBranch > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_func_def: // func_def
      case symbol_kind::S_func_header: // func_header
        value.move< FuncDecl > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_var_item: // var_item
        value.move< VarDecl > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_type_spec: // type_spec
        value.move< VarDecl::VarType > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_TOKEN_BOOL: // TOKEN_BOOL
      case symbol_kind::S_TOKEN_BOOL_LIT: // TOKEN_BOOL_LIT
      case symbol_kind::S_opt_const: // opt_const
        value.move< bool > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_expr: // expr
      case symbol_kind::S_primary_expr: // primary_expr
      case symbol_kind::S_var_ref: // var_ref
        value.move< expr_ptr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_TOKEN_INT_LIT: // TOKEN_INT_LIT
        value.move< int > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_TOKEN_MAIN: // TOKEN_MAIN
      case symbol_kind::S_TOKEN_STRING: // TOKEN_STRING
      case symbol_kind::S_TOKEN_IDENTIFIER: // TOKEN_IDENTIFIER
        value.move< std::string > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_cond_list: // cond_list
        value.move< std::vector<ConditionBranch> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_var_list: // var_list
        value.move< std::vector<VarDecl> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_opt_init_values: // opt_init_values
      case symbol_kind::S_value_list: // value_list
      case symbol_kind::S_var_ref_list: // var_ref_list
      case symbol_kind::S_opt_expr_list: // opt_expr_list
      case symbol_kind::S_expr_list: // expr_list
      case symbol_kind::S_dim_ref_list: // dim_ref_list
        value.move< std::vector<expr_ptr> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_opt_dimensions: // opt_dimensions
      case symbol_kind::S_dims_list: // dims_list
        value.move< std::vector<int> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_stmt_list: // stmt_list
        value.move< std::vector<stmt_ptr> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_stmt: // stmt
      case symbol_kind::S_vardecl_stmt: // vardecl_stmt
      case symbol_kind::S_expr_stmt: // expr_stmt
      case symbol_kind::S_assign_stmt: // assign_stmt
      case symbol_kind::S_while_stmt: // while_stmt
      case symbol_kind::S_switch_stmt: // switch_stmt
      case symbol_kind::S_move_stmt: // move_stmt
      case symbol_kind::S_call_stmt: // call_stmt
      case symbol_kind::S_getdrons_stmt: // getdrons_stmt
      case symbol_kind::S_get_x_stmt: // get_x_stmt
      case symbol_kind::S_get_y_stmt: // get_y_stmt
        value.move< stmt_ptr > (YY_MOVE (s.value));
        break;

      default:
        break;
    }

    location = YY_MOVE (s.location);
  }

  // by_kind.
   RobotParser ::by_kind::by_kind () YY_NOEXCEPT
    : kind_ (symbol_kind::S_YYEMPTY)
  {}

#if 201103L <= YY_CPLUSPLUS
   RobotParser ::by_kind::by_kind (by_kind&& that) YY_NOEXCEPT
    : kind_ (that.kind_)
  {
    that.clear ();
  }
#endif

   RobotParser ::by_kind::by_kind (const by_kind& that) YY_NOEXCEPT
    : kind_ (that.kind_)
  {}

   RobotParser ::by_kind::by_kind (token_kind_type t) YY_NOEXCEPT
    : kind_ (yytranslate_ (t))
  {}



  void
   RobotParser ::by_kind::clear () YY_NOEXCEPT
  {
    kind_ = symbol_kind::S_YYEMPTY;
  }

  void
   RobotParser ::by_kind::move (by_kind& that)
  {
    kind_ = that.kind_;
    that.clear ();
  }

   RobotParser ::symbol_kind_type
   RobotParser ::by_kind::kind () const YY_NOEXCEPT
  {
    return kind_;
  }


   RobotParser ::symbol_kind_type
   RobotParser ::by_kind::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }



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
      case symbol_kind::S_func_header: // func_header
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
      case symbol_kind::S_vardecl_stmt: // vardecl_stmt
      case symbol_kind::S_expr_stmt: // expr_stmt
      case symbol_kind::S_assign_stmt: // assign_stmt
      case symbol_kind::S_while_stmt: // while_stmt
      case symbol_kind::S_switch_stmt: // switch_stmt
      case symbol_kind::S_move_stmt: // move_stmt
      case symbol_kind::S_call_stmt: // call_stmt
      case symbol_kind::S_getdrons_stmt: // getdrons_stmt
      case symbol_kind::S_get_x_stmt: // get_x_stmt
      case symbol_kind::S_get_y_stmt: // get_y_stmt
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
      case symbol_kind::S_func_header: // func_header
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
      case symbol_kind::S_vardecl_stmt: // vardecl_stmt
      case symbol_kind::S_expr_stmt: // expr_stmt
      case symbol_kind::S_assign_stmt: // assign_stmt
      case symbol_kind::S_while_stmt: // while_stmt
      case symbol_kind::S_switch_stmt: // switch_stmt
      case symbol_kind::S_move_stmt: // move_stmt
      case symbol_kind::S_call_stmt: // call_stmt
      case symbol_kind::S_getdrons_stmt: // getdrons_stmt
      case symbol_kind::S_get_x_stmt: // get_x_stmt
      case symbol_kind::S_get_y_stmt: // get_y_stmt
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
      case symbol_kind::S_func_header: // func_header
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
      case symbol_kind::S_vardecl_stmt: // vardecl_stmt
      case symbol_kind::S_expr_stmt: // expr_stmt
      case symbol_kind::S_assign_stmt: // assign_stmt
      case symbol_kind::S_while_stmt: // while_stmt
      case symbol_kind::S_switch_stmt: // switch_stmt
      case symbol_kind::S_move_stmt: // move_stmt
      case symbol_kind::S_call_stmt: // call_stmt
      case symbol_kind::S_getdrons_stmt: // getdrons_stmt
      case symbol_kind::S_get_x_stmt: // get_x_stmt
      case symbol_kind::S_get_y_stmt: // get_y_stmt
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
      case symbol_kind::S_func_header: // func_header
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
      case symbol_kind::S_vardecl_stmt: // vardecl_stmt
      case symbol_kind::S_expr_stmt: // expr_stmt
      case symbol_kind::S_assign_stmt: // assign_stmt
      case symbol_kind::S_while_stmt: // while_stmt
      case symbol_kind::S_switch_stmt: // switch_stmt
      case symbol_kind::S_move_stmt: // move_stmt
      case symbol_kind::S_call_stmt: // call_stmt
      case symbol_kind::S_getdrons_stmt: // getdrons_stmt
      case symbol_kind::S_get_x_stmt: // get_x_stmt
      case symbol_kind::S_get_y_stmt: // get_y_stmt
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
            yyla.kind_ = yytranslate_ (yylex (&yyla.value, &yyla.location, lexer));
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
      case symbol_kind::S_func_header: // func_header
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
      case symbol_kind::S_vardecl_stmt: // vardecl_stmt
      case symbol_kind::S_expr_stmt: // expr_stmt
      case symbol_kind::S_assign_stmt: // assign_stmt
      case symbol_kind::S_while_stmt: // while_stmt
      case symbol_kind::S_switch_stmt: // switch_stmt
      case symbol_kind::S_move_stmt: // move_stmt
      case symbol_kind::S_call_stmt: // call_stmt
      case symbol_kind::S_getdrons_stmt: // getdrons_stmt
      case symbol_kind::S_get_x_stmt: // get_x_stmt
      case symbol_kind::S_get_y_stmt: // get_y_stmt
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
#line 210 "robot.ypp"
    {
        print_all_errors();
            if (!errors_.empty()) {
                std::cerr << "Parsing failed with " << errors_.size() << " errors" << std::endl;
                exit(1);
            }
        if (!has_main_){
            std::cerr << "SEMANTIC ERROR: function 'main' not found" << std::endl;
            exit(1);
        }
        std::cout << "=== PARSING COMPLETED SUCCESSFULLY ===" << std::endl;
        std::cout << "Global variables: " << global_symbols_.size() << std::endl;
        std::cout << "Functions: " << functions_.size() << std::endl;
    }
#line 1287 "generated/robot.tab.cpp"
    break;

  case 5: // program_items: program_items func_def
#line 230 "robot.ypp"
    {
        if (!yystack_[0].value.as < FuncDecl > ().name_.empty()){
            if (yystack_[0].value.as < FuncDecl > ().is_main_ || yystack_[0].value.as < FuncDecl > ().name_ == "main") {
                has_main_ = true;
            }
            functions_[yystack_[0].value.as < FuncDecl > ().name_] = yystack_[0].value.as < FuncDecl > ();
        }
    }
#line 1300 "generated/robot.tab.cpp"
    break;

  case 6: // program_items: program_items error
#line 239 "robot.ypp"
    {
        add_syntax_error(yystack_[0].location.begin.line, yystack_[0].location.begin.column, "syntax error in global scope");
        yyerrok;
        yyclearin;
    }
#line 1310 "generated/robot.tab.cpp"
    break;

  case 7: // vardecl_block: TOKEN_VARDECL_OPEN var_list TOKEN_VARDECL_CLOSE
#line 248 "robot.ypp"
    {
        auto& target_scope = local_scopes_.empty() ? global_symbols_ : local_scopes_.back();
        for (const auto& decl : yystack_[1].value.as < std::vector<VarDecl> > ()){
            if (target_scope.find(decl.name_) != target_scope.end()){
                add_semantic_error(yystack_[2].location.begin.line, yystack_[2].location.begin.column, "variable '" + decl.name_ + "' already declared");
                continue;
            }
            SymbolInfo info;
            info.decl_ = decl;
            target_scope[decl.name_] = info;
        }
    }
#line 1327 "generated/robot.tab.cpp"
    break;

  case 8: // var_list: var_item
#line 264 "robot.ypp"
    {
        yylhs.value.as < std::vector<VarDecl> > ().push_back(yystack_[0].value.as < VarDecl > ());
    }
#line 1335 "generated/robot.tab.cpp"
    break;

  case 9: // var_list: var_list var_item
#line 268 "robot.ypp"
    {
        yystack_[1].value.as < std::vector<VarDecl> > ().push_back(yystack_[0].value.as < VarDecl > ());
        yylhs.value.as < std::vector<VarDecl> > () = yystack_[1].value.as < std::vector<VarDecl> > ();
    }
#line 1344 "generated/robot.tab.cpp"
    break;

  case 10: // var_item: TOKEN_VAR_OPEN TOKEN_NAME_ATTR TOKEN_STRING opt_const '>' type_spec opt_dimensions opt_init_values TOKEN_VAR_CLOSE
#line 290 "robot.ypp"
    {
        yylhs.value.as < VarDecl > ().name_ = yystack_[6].value.as < std::string > ();
        yylhs.value.as < VarDecl > ().is_const_ = yystack_[5].value.as < bool > ();
        yylhs.value.as < VarDecl > ().type_ = yystack_[3].value.as < VarDecl::VarType > ();
        yylhs.value.as < VarDecl > ().dimensions_ = yystack_[2].value.as < std::vector<int> > ();
        yylhs.value.as < VarDecl > ().init_values_ = yystack_[1].value.as < std::vector<expr_ptr> > ();

        if (!yylhs.value.as < VarDecl > ().dimensions_.empty() && !yylhs.value.as < VarDecl > ().init_values_.empty()){ // если инициализированы не все переменные в массиве
            int expected = product(yylhs.value.as < VarDecl > ().dimensions_);
            if ((int)yylhs.value.as < VarDecl > ().init_values_.size() != expected){
                add_semantic_error(yystack_[6].location.begin.line, yystack_[6].location.begin.column, "wrong number of initial values for '" + yylhs.value.as < VarDecl > ().name_ + "'");
            }
        }
    }
#line 1363 "generated/robot.tab.cpp"
    break;

  case 11: // opt_const: TOKEN_CONST TOKEN_STRING
#line 307 "robot.ypp"
    {
        yylhs.value.as < bool > () = (yystack_[0].value.as < std::string > () == "true");
    }
#line 1371 "generated/robot.tab.cpp"
    break;

  case 12: // opt_const: %empty
#line 311 "robot.ypp"
    {
        yylhs.value.as < bool > () = false; // по умолчанию ставлю false
    }
#line 1379 "generated/robot.tab.cpp"
    break;

  case 13: // type_spec: TOKEN_TYPE_OPEN TOKEN_TYPE_INT TOKEN_TYPE_CLOSE
#line 318 "robot.ypp"
    {
        yylhs.value.as < VarDecl::VarType > () = VarDecl::INT;
    }
#line 1387 "generated/robot.tab.cpp"
    break;

  case 14: // type_spec: TOKEN_TYPE_OPEN TOKEN_TYPE_BOOL TOKEN_TYPE_CLOSE
#line 322 "robot.ypp"
    {
        yylhs.value.as < VarDecl::VarType > () = VarDecl::BOOL;
    }
#line 1395 "generated/robot.tab.cpp"
    break;

  case 15: // type_spec: TOKEN_TYPE_OPEN TOKEN_TYPE_CELL TOKEN_TYPE_CLOSE
#line 326 "robot.ypp"
    {
        yylhs.value.as < VarDecl::VarType > () = VarDecl::CELL;
    }
#line 1403 "generated/robot.tab.cpp"
    break;

  case 16: // opt_dimensions: %empty
#line 333 "robot.ypp"
    {
        yylhs.value.as < std::vector<int> > () = std::vector<int>();
    }
#line 1411 "generated/robot.tab.cpp"
    break;

  case 17: // opt_dimensions: TOKEN_DIMENSIONS_OPEN TOKEN_COUNT TOKEN_STRING '>' dims_list TOKEN_DIMENSIONS_CLOSE
#line 337 "robot.ypp"
    {
        int value = atoi(yystack_[3].value.as < std::string > ().c_str());
        if (value != (int)yystack_[1].value.as < std::vector<int> > ().size()){ // несовпадение count и сколько объявлено измерений
            add_semantic_error(yystack_[4].location.begin.line, yystack_[4].location.begin.column, "dimension count mismatch: expected " + yystack_[3].value.as < std::string > () + ", got " +  std::to_string(yystack_[1].value.as < std::vector<int> > ().size()));
        } else {
            yylhs.value.as < std::vector<int> > () = yystack_[1].value.as < std::vector<int> > ();
        }

    }
#line 1425 "generated/robot.tab.cpp"
    break;

  case 18: // dims_list: TOKEN_DIMENSION_OPEN TOKEN_INT_LIT TOKEN_DIMENSION_CLOSE
#line 350 "robot.ypp"
    {
        yylhs.value.as < std::vector<int> > ().push_back(yystack_[1].value.as < int > ());
    }
#line 1433 "generated/robot.tab.cpp"
    break;

  case 19: // dims_list: dims_list TOKEN_DIMENSION_OPEN TOKEN_INT_LIT TOKEN_DIMENSION_CLOSE
#line 354 "robot.ypp"
    {
        yystack_[3].value.as < std::vector<int> > ().push_back(yystack_[1].value.as < int > ());
        yylhs.value.as < std::vector<int> > () = yystack_[3].value.as < std::vector<int> > ();
    }
#line 1442 "generated/robot.tab.cpp"
    break;

  case 20: // opt_init_values: %empty
#line 362 "robot.ypp"
    {
        yylhs.value.as < std::vector<expr_ptr> > () = std::vector<expr_ptr>();
    }
#line 1450 "generated/robot.tab.cpp"
    break;

  case 21: // opt_init_values: TOKEN_VALUES_OPEN value_list TOKEN_VALUES_CLOSE
#line 366 "robot.ypp"
    {
        yylhs.value.as < std::vector<expr_ptr> > () = yystack_[1].value.as < std::vector<expr_ptr> > ();
    }
#line 1458 "generated/robot.tab.cpp"
    break;

  case 22: // value_list: TOKEN_VALUE_OPEN expr TOKEN_VALUE_CLOSE
#line 373 "robot.ypp"
    {
        yylhs.value.as < std::vector<expr_ptr> > ().push_back(yystack_[1].value.as < expr_ptr > ());
    }
#line 1466 "generated/robot.tab.cpp"
    break;

  case 23: // value_list: value_list TOKEN_VALUE_OPEN expr TOKEN_VALUE_CLOSE
#line 377 "robot.ypp"
    {
        yystack_[3].value.as < std::vector<expr_ptr> > ().push_back(yystack_[1].value.as < expr_ptr > ());
        yylhs.value.as < std::vector<expr_ptr> > () = yystack_[3].value.as < std::vector<expr_ptr> > ();
    }
#line 1475 "generated/robot.tab.cpp"
    break;

  case 24: // func_def: func_header stmt_list TOKEN_FUNC_CLOSE
#line 397 "robot.ypp"
    {
        yylhs.value.as < FuncDecl > () = yystack_[2].value.as < FuncDecl > ();
        yylhs.value.as < FuncDecl > ().body_ = yystack_[1].value.as < std::vector<stmt_ptr> > ();
        local_scopes_.pop_back();
    }
#line 1485 "generated/robot.tab.cpp"
    break;

  case 25: // func_header: TOKEN_FUNC_OPEN TOKEN_NAME_ATTR TOKEN_MAIN '>'
#line 406 "robot.ypp"
    {
        local_scopes_.push_back({});
        if (has_main_){
            add_semantic_error(yystack_[1].location.begin.line, yystack_[1].location.begin.column, "multiple definitions of 'main'");
        } else{
            yylhs.value.as < FuncDecl > ().name_ = "main";
            yylhs.value.as < FuncDecl > ().is_main_ = true;
            has_main_ = true;
            functions_["main"] = yylhs.value.as < FuncDecl > ();
        }
    }
#line 1501 "generated/robot.tab.cpp"
    break;

  case 26: // func_header: TOKEN_FUNC_OPEN TOKEN_NAME_ATTR TOKEN_STRING '>'
#line 418 "robot.ypp"
    {
        local_scopes_.push_back({});
        yylhs.value.as < FuncDecl > ().name_ = yystack_[1].value.as < std::string > ();
        yylhs.value.as < FuncDecl > ().is_main_ = false;
        functions_[yystack_[1].value.as < std::string > ()] = yylhs.value.as < FuncDecl > ();
    }
#line 1512 "generated/robot.tab.cpp"
    break;

  case 27: // stmt_list: %empty
#line 427 "robot.ypp"
           { yylhs.value.as < std::vector<stmt_ptr> > () = std::vector<stmt_ptr>(); }
#line 1518 "generated/robot.tab.cpp"
    break;

  case 28: // stmt_list: stmt_list stmt
#line 429 "robot.ypp"
    {
        yystack_[1].value.as < std::vector<stmt_ptr> > ().push_back(yystack_[0].value.as < stmt_ptr > ());
        yylhs.value.as < std::vector<stmt_ptr> > () = yystack_[1].value.as < std::vector<stmt_ptr> > ();
    }
#line 1527 "generated/robot.tab.cpp"
    break;

  case 29: // stmt_list: stmt_list error
#line 434 "robot.ypp"
    {
        add_syntax_error(yystack_[0].location.begin.line, yystack_[0].location.begin.column, "Syntax error in statement list");
        yyerrok;
        yyclearin;
        yylhs.value.as < std::vector<stmt_ptr> > () = yystack_[1].value.as < std::vector<stmt_ptr> > ();
    }
#line 1538 "generated/robot.tab.cpp"
    break;

  case 30: // stmt: assign_stmt
#line 443 "robot.ypp"
                { yylhs.value.as < stmt_ptr > () = yystack_[0].value.as < stmt_ptr > (); }
#line 1544 "generated/robot.tab.cpp"
    break;

  case 31: // stmt: while_stmt
#line 444 "robot.ypp"
                 { yylhs.value.as < stmt_ptr > () = yystack_[0].value.as < stmt_ptr > (); }
#line 1550 "generated/robot.tab.cpp"
    break;

  case 32: // stmt: switch_stmt
#line 445 "robot.ypp"
                  { yylhs.value.as < stmt_ptr > () = yystack_[0].value.as < stmt_ptr > (); }
#line 1556 "generated/robot.tab.cpp"
    break;

  case 33: // stmt: move_stmt
#line 446 "robot.ypp"
                { yylhs.value.as < stmt_ptr > () = yystack_[0].value.as < stmt_ptr > (); }
#line 1562 "generated/robot.tab.cpp"
    break;

  case 34: // stmt: call_stmt
#line 447 "robot.ypp"
                { yylhs.value.as < stmt_ptr > () = yystack_[0].value.as < stmt_ptr > (); }
#line 1568 "generated/robot.tab.cpp"
    break;

  case 35: // stmt: getdrons_stmt
#line 448 "robot.ypp"
                    { yylhs.value.as < stmt_ptr > () = yystack_[0].value.as < stmt_ptr > (); }
#line 1574 "generated/robot.tab.cpp"
    break;

  case 36: // stmt: expr_stmt
#line 449 "robot.ypp"
                { yylhs.value.as < stmt_ptr > () = yystack_[0].value.as < stmt_ptr > (); }
#line 1580 "generated/robot.tab.cpp"
    break;

  case 37: // stmt: vardecl_stmt
#line 450 "robot.ypp"
                   { yylhs.value.as < stmt_ptr > () = yystack_[0].value.as < stmt_ptr > (); }
#line 1586 "generated/robot.tab.cpp"
    break;

  case 38: // stmt: get_x_stmt
#line 451 "robot.ypp"
                 { yylhs.value.as < stmt_ptr > () = yystack_[0].value.as < stmt_ptr > (); }
#line 1592 "generated/robot.tab.cpp"
    break;

  case 39: // stmt: get_y_stmt
#line 452 "robot.ypp"
                 { yylhs.value.as < stmt_ptr > () = yystack_[0].value.as < stmt_ptr > (); }
#line 1598 "generated/robot.tab.cpp"
    break;

  case 40: // vardecl_stmt: TOKEN_VARDECL_OPEN var_list TOKEN_VARDECL_CLOSE
#line 458 "robot.ypp"
    {
        auto& target_scope = local_scopes_.empty() ? global_symbols_ : local_scopes_.back();
        for (const auto& decl : yystack_[1].value.as < std::vector<VarDecl> > ()){
            if (target_scope.find(decl.name_) != target_scope.end()){
                add_semantic_error(yystack_[2].location.begin.line, yystack_[2].location.begin.column, "variable '" + decl.name_ + "' already declared");
                continue;
            }
            SymbolInfo info;
            info.decl_ = decl;
            target_scope[decl.name_] = info;
        }
        auto st = std::make_shared<StmtNode>(StmtNode::VARDECL);
        st->var_decls_ = yystack_[1].value.as < std::vector<VarDecl> > ();
        yylhs.value.as < stmt_ptr > () = st;
    }
#line 1618 "generated/robot.tab.cpp"
    break;

  case 41: // expr_stmt: expr
#line 478 "robot.ypp"
    {
        auto statement = std::make_shared<StmtNode>(StmtNode::EXPR);
        statement->expr_val_ = yystack_[0].value.as < expr_ptr > ();
        yylhs.value.as < stmt_ptr > () = statement;
    }
#line 1628 "generated/robot.tab.cpp"
    break;

  case 42: // assign_stmt: TOKEN_ASSIGN_OPEN TOKEN_VALUE_OPEN expr TOKEN_VALUE_CLOSE TOKEN_TO_OPEN var_ref_list TOKEN_TO_CLOSE TOKEN_ASSIGN_CLOSE
#line 493 "robot.ypp"
    {
        for (auto& var : yystack_[2].value.as < std::vector<expr_ptr> > ()){
            auto* sym = find_variable_in_scopes(var->var_name_);
            if (!sym){
                add_semantic_error(yystack_[2].location.begin.line, yystack_[2].location.begin.column, "assignment to undeclared variable '" + var->var_name_ + "'");
                continue;
            }
            if (sym->decl_.is_const_){
                add_semantic_error(yystack_[2].location.begin.line, yystack_[2].location.begin.column, "assignment to const variable '" + var->var_name_ + "'");
                continue;
            }
            VarDecl::VarType var_type = sym->decl_.type_;
            ExprNode::ValueType expr_type = yystack_[5].value.as < expr_ptr > ()->value_type_;

             if (var_type == VarDecl::INT && expr_type != ExprNode::TYPE_INT){
                add_semantic_error(yystack_[2].location.begin.line, yystack_[2].location.begin.column, "type mismatch: cannot assign non-INT to INT variable '" + var->var_name_ + "'");
             }
             else if (var_type == VarDecl::BOOL && expr_type != ExprNode::TYPE_BOOL){
                add_semantic_error(yystack_[2].location.begin.line, yystack_[2].location.begin.column, "type mismatch: cannot assign non-BOOL to BOOL variable '" + var->var_name_ + "'");
             }
             else if (var_type == VarDecl::CELL && expr_type != ExprNode::TYPE_CELL){
                add_semantic_error(yystack_[2].location.begin.line, yystack_[2].location.begin.column, "type mismatch: cannot assign non-CELL to CELL variable '" + var->var_name_ + "'");
             }
        }

        auto st = std::make_shared<StmtNode>(StmtNode::ASSIGN);
        st->value_ = yystack_[5].value.as < expr_ptr > ();
        st->targets_ = yystack_[2].value.as < std::vector<expr_ptr> > ();
        yylhs.value.as < stmt_ptr > () = st;
    }
#line 1663 "generated/robot.tab.cpp"
    break;

  case 43: // var_ref_list: var_ref
#line 527 "robot.ypp"
    {
        yylhs.value.as < std::vector<expr_ptr> > ().push_back(yystack_[0].value.as < expr_ptr > ());
    }
#line 1671 "generated/robot.tab.cpp"
    break;

  case 44: // var_ref_list: var_ref_list var_ref
#line 531 "robot.ypp"
    {
        yystack_[1].value.as < std::vector<expr_ptr> > ().push_back(yystack_[0].value.as < expr_ptr > ());
        yylhs.value.as < std::vector<expr_ptr> > () = yystack_[1].value.as < std::vector<expr_ptr> > ();
    }
#line 1680 "generated/robot.tab.cpp"
    break;

  case 45: // while_stmt: TOKEN_WHILE_OPEN TOKEN_CHECK_OPEN expr TOKEN_CHECK_CLOSE TOKEN_DO_OPEN stmt_list TOKEN_DO_CLOSE TOKEN_WHILE_CLOSE
#line 549 "robot.ypp"
    {
        if (yystack_[5].value.as < expr_ptr > ()->value_type_ != ExprNode::TYPE_BOOL){
            add_semantic_error(yystack_[5].location.begin.line, yystack_[5].location.begin.column, "while condition must be boolean");
        } else {
            auto st = std::make_shared<StmtNode>(StmtNode::WHILE);
            st->while_cond_ = yystack_[5].value.as < expr_ptr > ();
            st->while_body_ = yystack_[2].value.as < std::vector<stmt_ptr> > ();
            yylhs.value.as < stmt_ptr > () = st;
        }
    }
#line 1695 "generated/robot.tab.cpp"
    break;

  case 46: // switch_stmt: TOKEN_SWITCH_OPEN cond_list TOKEN_SWITCH_CLOSE
#line 584 "robot.ypp"
    {
        auto st = std::make_shared<StmtNode>(StmtNode::SWITCH);
        st->switch_cases_ = yystack_[1].value.as < std::vector<ConditionBranch> > ();
        yylhs.value.as < stmt_ptr > () = st;
    }
#line 1705 "generated/robot.tab.cpp"
    break;

  case 47: // cond_list: cond_branch
#line 593 "robot.ypp"
    {
        yylhs.value.as < std::vector<ConditionBranch> > ().push_back(yystack_[0].value.as < ConditionBranch > ());
    }
#line 1713 "generated/robot.tab.cpp"
    break;

  case 48: // cond_list: cond_list cond_branch
#line 597 "robot.ypp"
    {
        yystack_[1].value.as < std::vector<ConditionBranch> > ().push_back(yystack_[0].value.as < ConditionBranch > ());
        yylhs.value.as < std::vector<ConditionBranch> > () = yystack_[1].value.as < std::vector<ConditionBranch> > ();
    }
#line 1722 "generated/robot.tab.cpp"
    break;

  case 49: // cond_branch: TOKEN_CONDITION_OPEN TOKEN_CHECK_OPEN expr TOKEN_CHECK_CLOSE TOKEN_DO_OPEN stmt_list TOKEN_DO_CLOSE TOKEN_CONDITION_CLOSE
#line 605 "robot.ypp"
    {
        if (yystack_[5].value.as < expr_ptr > ()->value_type_ != ExprNode::TYPE_BOOL){
            add_semantic_error(yystack_[5].location.begin.line, yystack_[5].location.begin.column, "condition must be boolean");
        } else {
            yylhs.value.as < ConditionBranch > ().condition_ = yystack_[5].value.as < expr_ptr > ();
            yylhs.value.as < ConditionBranch > ().body_ = yystack_[2].value.as < std::vector<stmt_ptr> > ();
        }
    }
#line 1735 "generated/robot.tab.cpp"
    break;

  case 50: // move_stmt: TOKEN_LEFT_OPEN expr TOKEN_LEFT_CLOSE
#line 627 "robot.ypp"
    {
        auto st = std::make_shared<StmtNode>(StmtNode::MOVE);
        st->direction_ = StmtNode::LEFT;
        st->distance_ = yystack_[1].value.as < expr_ptr > ();
        yylhs.value.as < stmt_ptr > () = st;
    }
#line 1746 "generated/robot.tab.cpp"
    break;

  case 51: // move_stmt: TOKEN_RIGHT_OPEN expr TOKEN_RIGHT_CLOSE
#line 634 "robot.ypp"
    {
        auto st = std::make_shared<StmtNode>(StmtNode::MOVE);
        st->direction_ = StmtNode::RIGHT;
        st->distance_ = yystack_[1].value.as < expr_ptr > ();
        yylhs.value.as < stmt_ptr > () = st;
    }
#line 1757 "generated/robot.tab.cpp"
    break;

  case 52: // move_stmt: TOKEN_UP_OPEN expr TOKEN_UP_CLOSE
#line 641 "robot.ypp"
    {
        auto st = std::make_shared<StmtNode>(StmtNode::MOVE);
        st->direction_ = StmtNode::UP;
        st->distance_ = yystack_[1].value.as < expr_ptr > ();
        yylhs.value.as < stmt_ptr > () = st;
    }
#line 1768 "generated/robot.tab.cpp"
    break;

  case 53: // move_stmt: TOKEN_DOWN_OPEN expr TOKEN_DOWN_CLOSE
#line 648 "robot.ypp"
    {
        auto st = std::make_shared<StmtNode>(StmtNode::MOVE);
        st->direction_ = StmtNode::DOWN;
        st->distance_ = yystack_[1].value.as < expr_ptr > ();
        yylhs.value.as < stmt_ptr > () = st;
    }
#line 1779 "generated/robot.tab.cpp"
    break;

  case 54: // call_stmt: TOKEN_CALL_OPEN TOKEN_IDENTIFIER TOKEN_CALL_CLOSE
#line 661 "robot.ypp"
    {
        if (functions_.find(yystack_[1].value.as < std::string > ()) == functions_.end()){
            add_semantic_error(yystack_[1].location.begin.line, yystack_[1].location.begin.column, "function '" + yystack_[1].value.as < std::string > () + "' not defined");
        } else {
            auto st = std::make_shared<StmtNode>(StmtNode::CALL);
            st->call_name_ = yystack_[1].value.as < std::string > ();
            yylhs.value.as < stmt_ptr > () = st;
        }
    }
#line 1793 "generated/robot.tab.cpp"
    break;

  case 55: // getdrons_stmt: TOKEN_GETDRONSCOUNT_OPEN var_ref TOKEN_GETDRONSCOUNT_CLOSE
#line 677 "robot.ypp"
    {
        auto st = std::make_shared<StmtNode>(StmtNode::GETDRONSCOUNT);
        st->dron_target_ = yystack_[1].value.as < expr_ptr > ();
        yylhs.value.as < stmt_ptr > () = st;
    }
#line 1803 "generated/robot.tab.cpp"
    break;

  case 56: // get_x_stmt: TOKEN_GETX_OPEN var_ref TOKEN_GETX_CLOSE
#line 686 "robot.ypp"
    {
        auto st = std::make_shared<StmtNode>(StmtNode::GETX);
        st->x_ = yystack_[1].value.as < expr_ptr > ();
        yylhs.value.as < stmt_ptr > () = st;
    }
#line 1813 "generated/robot.tab.cpp"
    break;

  case 57: // get_y_stmt: TOKEN_GETY_OPEN var_ref TOKEN_GETY_CLOSE
#line 695 "robot.ypp"
    {
        auto st = std::make_shared<StmtNode>(StmtNode::GETY);
        st->y_ = yystack_[1].value.as < expr_ptr > ();
        yylhs.value.as < stmt_ptr > () = st;
    }
#line 1823 "generated/robot.tab.cpp"
    break;

  case 58: // expr: primary_expr
#line 709 "robot.ypp"
    {
        yylhs.value.as < expr_ptr > () = yystack_[0].value.as < expr_ptr > ();
    }
#line 1831 "generated/robot.tab.cpp"
    break;

  case 59: // expr: TOKEN_VALUE_OPEN expr TOKEN_VALUE_CLOSE
#line 713 "robot.ypp"
    {
        yylhs.value.as < expr_ptr > () = yystack_[1].value.as < expr_ptr > ();
    }
#line 1839 "generated/robot.tab.cpp"
    break;

  case 60: // expr: TOKEN_ADD_OPEN opt_expr_list TOKEN_ADD_CLOSE
#line 717 "robot.ypp"
    {
        for (auto& arg : yystack_[1].value.as < std::vector<expr_ptr> > ()){
            if (arg->value_type_ != ExprNode::TYPE_INT){
                add_semantic_error(yystack_[2].location.begin.line, yystack_[2].location.begin.column, "ADD expects integer arguments");
            }
        }

        auto ad = std::make_shared<ExprNode>(ExprNode::ADD);
        ad->args_ = yystack_[1].value.as < std::vector<expr_ptr> > ();
        ad->value_type_ = ExprNode::TYPE_INT;
        yylhs.value.as < expr_ptr > () = ad;
    }
#line 1856 "generated/robot.tab.cpp"
    break;

  case 61: // expr: TOKEN_MUL_OPEN opt_expr_list TOKEN_MUL_CLOSE
#line 730 "robot.ypp"
    {
        for (auto& arg : yystack_[1].value.as < std::vector<expr_ptr> > ()){
            if (arg->value_type_ != ExprNode::TYPE_INT){
                add_semantic_error(yystack_[2].location.begin.line, yystack_[2].location.begin.column, "MUL expects integer arguments");
            }
        }

        auto mu = std::make_shared<ExprNode>(ExprNode::MUL);
        mu->args_ = yystack_[1].value.as < std::vector<expr_ptr> > ();
        mu->value_type_ = ExprNode::TYPE_INT;
        yylhs.value.as < expr_ptr > () = mu;
    }
#line 1873 "generated/robot.tab.cpp"
    break;

  case 62: // expr: TOKEN_SUB_OPEN expr expr TOKEN_SUB_CLOSE
#line 743 "robot.ypp"
    {
        if (yystack_[2].value.as < expr_ptr > ()->value_type_ != ExprNode::TYPE_INT || yystack_[1].value.as < expr_ptr > ()->value_type_ != ExprNode::TYPE_INT){
            add_semantic_error(yystack_[3].location.begin.line, yystack_[3].location.begin.column, "SUB expects integers");
        }

        auto su = std::make_shared<ExprNode>(ExprNode::SUB);
        su->args_.push_back(yystack_[2].value.as < expr_ptr > ());
        su->args_.push_back(yystack_[1].value.as < expr_ptr > ());
        su->value_type_ = ExprNode::TYPE_INT;
        yylhs.value.as < expr_ptr > () = su;
    }
#line 1889 "generated/robot.tab.cpp"
    break;

  case 63: // expr: TOKEN_DIV_OPEN expr expr TOKEN_DIV_CLOSE
#line 755 "robot.ypp"
    {
        if (yystack_[2].value.as < expr_ptr > ()->value_type_ != ExprNode::TYPE_INT || yystack_[1].value.as < expr_ptr > ()->value_type_ != ExprNode::TYPE_INT){
            add_semantic_error(yystack_[3].location.begin.line, yystack_[3].location.begin.column, "DIV expects integers");
        }
        if (yystack_[1].value.as < expr_ptr > ()->type_ == ExprNode::INT_LIT && yystack_[1].value.as < expr_ptr > ()->int_value_ == 0){
            add_semantic_error(yystack_[3].location.begin.line, yystack_[3].location.begin.column, "division by zero");
        }
        auto di = std::make_shared<ExprNode>(ExprNode::DIV);
        di->args_.push_back(yystack_[2].value.as < expr_ptr > ());
        di->args_.push_back(yystack_[1].value.as < expr_ptr > ());
        di->value_type_ = ExprNode::TYPE_INT;
        yylhs.value.as < expr_ptr > () = di;
    }
#line 1907 "generated/robot.tab.cpp"
    break;

  case 64: // expr: TOKEN_AND_OPEN opt_expr_list TOKEN_AND_CLOSE
#line 769 "robot.ypp"
    {
        for (auto& arg : yystack_[1].value.as < std::vector<expr_ptr> > ()){
            if (arg->value_type_ != ExprNode::TYPE_BOOL){
                add_semantic_error(yystack_[2].location.begin.line, yystack_[2].location.begin.column, "AND expects boolean arguments");
            }
        }

        auto a = std::make_shared<ExprNode>(ExprNode::AND);
        a->args_ = yystack_[1].value.as < std::vector<expr_ptr> > ();
        a->value_type_ = ExprNode::TYPE_BOOL;
        yylhs.value.as < expr_ptr > () = a;
    }
#line 1924 "generated/robot.tab.cpp"
    break;

  case 65: // expr: TOKEN_OR_OPEN opt_expr_list TOKEN_OR_CLOSE
#line 782 "robot.ypp"
    {
        for (auto& arg : yystack_[1].value.as < std::vector<expr_ptr> > ()){
            if (arg->value_type_ != ExprNode::TYPE_BOOL){
                add_semantic_error(yystack_[2].location.begin.line, yystack_[2].location.begin.column, "OR expects boolean arguments");
            }
        }

        auto o = std::make_shared<ExprNode>(ExprNode::OR);
        o->args_ = yystack_[1].value.as < std::vector<expr_ptr> > ();
        o->value_type_ = ExprNode::TYPE_BOOL;
        yylhs.value.as < expr_ptr > () = o;
    }
#line 1941 "generated/robot.tab.cpp"
    break;

  case 66: // expr: TOKEN_NOT_OPEN expr TOKEN_NOT_CLOSE
#line 795 "robot.ypp"
    {
        if (yystack_[1].value.as < expr_ptr > ()->value_type_ != ExprNode::TYPE_BOOL){
            add_semantic_error(yystack_[2].location.begin.line, yystack_[2].location.begin.column, "NOT expects boolean");
        }

        auto n = std::make_shared<ExprNode>(ExprNode::NOT);
        n->args_.push_back(yystack_[1].value.as < expr_ptr > ());
        n->value_type_ = ExprNode::TYPE_BOOL;
        yylhs.value.as < expr_ptr > () = n;
    }
#line 1956 "generated/robot.tab.cpp"
    break;

  case 67: // expr: TOKEN_EQ_OPEN opt_expr_list TOKEN_EQ_CLOSE
#line 806 "robot.ypp"
    {
        for (size_t i = 1; i < yystack_[1].value.as < std::vector<expr_ptr> > ().size(); i++){
            if (yystack_[1].value.as < std::vector<expr_ptr> > ()[i]->value_type_ != yystack_[1].value.as < std::vector<expr_ptr> > ()[0]->value_type_){
                add_semantic_error(yystack_[2].location.begin.line, yystack_[2].location.begin.column, "EQ arguments must have same type");
            }
        }

        auto eq = std::make_shared<ExprNode>(ExprNode::EQ);
        eq->args_ = yystack_[1].value.as < std::vector<expr_ptr> > ();
        eq->value_type_ = ExprNode::TYPE_BOOL;
        yylhs.value.as < expr_ptr > () = eq;
    }
#line 1973 "generated/robot.tab.cpp"
    break;

  case 68: // expr: TOKEN_MAX_OPEN opt_expr_list TOKEN_MAX_CLOSE
#line 819 "robot.ypp"
    {
        for (auto& arg : yystack_[1].value.as < std::vector<expr_ptr> > ()){
            if (arg->value_type_ != ExprNode::TYPE_INT){
                add_semantic_error(yystack_[2].location.begin.line, yystack_[2].location.begin.column, "MAX expects integer arguments");
            }
        }

        auto ma = std::make_shared<ExprNode>(ExprNode::MAX);
        ma->args_ = yystack_[1].value.as < std::vector<expr_ptr> > ();
        ma->value_type_ = ExprNode::TYPE_INT;
        yylhs.value.as < expr_ptr > () = ma;
    }
#line 1990 "generated/robot.tab.cpp"
    break;

  case 69: // expr: TOKEN_MIN_OPEN opt_expr_list TOKEN_MIN_CLOSE
#line 832 "robot.ypp"
    {
        for (auto& arg : yystack_[1].value.as < std::vector<expr_ptr> > ()){
            if (arg->value_type_ != ExprNode::TYPE_INT){
                add_semantic_error(yystack_[2].location.begin.line, yystack_[2].location.begin.column, "MIN expects integer arguments");
            }
        }

        auto mi = std::make_shared<ExprNode>(ExprNode::MIN);
        mi->args_ = yystack_[1].value.as < std::vector<expr_ptr> > ();
        mi->value_type_ = ExprNode::TYPE_INT;
        yylhs.value.as < expr_ptr > () = mi;
    }
#line 2007 "generated/robot.tab.cpp"
    break;

  case 70: // expr: TOKEN_SENDDRONS_OPEN expr TOKEN_SENDDRONS_CLOSE
#line 845 "robot.ypp"
    {
        auto drons = std::make_shared<ExprNode>(ExprNode::SENDDRONS);
        drons->args_.push_back(yystack_[1].value.as < expr_ptr > ());
        drons->value_type_ = ExprNode::TYPE_CELL;
        yylhs.value.as < expr_ptr > () = drons;
    }
#line 2018 "generated/robot.tab.cpp"
    break;

  case 71: // opt_expr_list: %empty
#line 855 "robot.ypp"
    {
        yylhs.value.as < std::vector<expr_ptr> > () = std::vector<expr_ptr>();
    }
#line 2026 "generated/robot.tab.cpp"
    break;

  case 72: // opt_expr_list: expr_list
#line 859 "robot.ypp"
    {
        yylhs.value.as < std::vector<expr_ptr> > () = yystack_[0].value.as < std::vector<expr_ptr> > ();
    }
#line 2034 "generated/robot.tab.cpp"
    break;

  case 73: // expr_list: expr
#line 866 "robot.ypp"
    {
        yylhs.value.as < std::vector<expr_ptr> > ().push_back(yystack_[0].value.as < expr_ptr > ());
    }
#line 2042 "generated/robot.tab.cpp"
    break;

  case 74: // expr_list: expr_list expr
#line 870 "robot.ypp"
    {
        yystack_[1].value.as < std::vector<expr_ptr> > ().push_back(yystack_[0].value.as < expr_ptr > ());
        yylhs.value.as < std::vector<expr_ptr> > () = yystack_[1].value.as < std::vector<expr_ptr> > ();
    }
#line 2051 "generated/robot.tab.cpp"
    break;

  case 75: // primary_expr: TOKEN_INT_LIT
#line 878 "robot.ypp"
    {
        yylhs.value.as < expr_ptr > () = ExprNode::make_int(yystack_[0].value.as < int > ());
    }
#line 2059 "generated/robot.tab.cpp"
    break;

  case 76: // primary_expr: TOKEN_BOOL_LIT
#line 882 "robot.ypp"
    {
        yylhs.value.as < expr_ptr > () = ExprNode::make_bool(yystack_[0].value.as < bool > ());
    }
#line 2067 "generated/robot.tab.cpp"
    break;

  case 77: // primary_expr: TOKEN_CELL_VALUE
#line 886 "robot.ypp"
    {
        yylhs.value.as < expr_ptr > () = ExprNode::make_cell(yystack_[0].value.as < CellValue > ());
    }
#line 2075 "generated/robot.tab.cpp"
    break;

  case 78: // primary_expr: var_ref
#line 890 "robot.ypp"
    {
        yylhs.value.as < expr_ptr > () = yystack_[0].value.as < expr_ptr > ();
    }
#line 2083 "generated/robot.tab.cpp"
    break;

  case 79: // var_ref: TOKEN_IDENTIFIER
#line 904 "robot.ypp"
    {
        auto* sym = find_variable_in_scopes(yystack_[0].value.as < std::string > ());
        if (!sym){
            add_semantic_error(yystack_[0].location.begin.line, yystack_[0].location.begin.column, "variable '" + yystack_[0].value.as < std::string > () + "' not declared");
        }

        auto iden = ExprNode::make_var_ref(yystack_[0].value.as < std::string > ());
        if (sym) {
                    switch (sym->decl_.type_) {
                        case VarDecl::INT:
                            iden->value_type_ = ExprNode::TYPE_INT;
                            break;
                        case VarDecl::BOOL:
                            iden->value_type_ = ExprNode::TYPE_BOOL;
                            break;
                        case VarDecl::CELL:
                            iden->value_type_ = ExprNode::TYPE_CELL;
                            break;
                        default: iden->value_type_ = ExprNode::TYPE_UNKNOWN;
                    }
                }

                yylhs.value.as < expr_ptr > () = iden;

    }
#line 2113 "generated/robot.tab.cpp"
    break;

  case 80: // var_ref: TOKEN_IDENTIFIER dim_ref_list
#line 930 "robot.ypp"
    {
        auto* sym = find_variable_in_scopes(yystack_[1].value.as < std::string > ());
        if (!sym){
            add_semantic_error(yystack_[1].location.begin.line, yystack_[1].location.begin.column, "variable '" + yystack_[1].value.as < std::string > () + "' not declared");
        }
        if (sym) {
            if (yystack_[0].value.as < std::vector<expr_ptr> > ().size() != sym->decl_.dimensions_.size()){
                add_semantic_error(yystack_[1].location.begin.line, yystack_[1].location.begin.column, "wrong number of indices for '" + yystack_[1].value.as < std::string > () + "'");
            }
            for (auto& idx : yystack_[0].value.as < std::vector<expr_ptr> > ()) {
                if (idx->value_type_ != ExprNode::TYPE_INT){
                    add_semantic_error(yystack_[1].location.begin.line, yystack_[1].location.begin.column, "array index must be integer");
                }
            }
        }
        auto iden = ExprNode::make_var_ref(yystack_[1].value.as < std::string > ());
        if (sym) {
            switch (sym->decl_.type_) {
                case VarDecl::INT:
                    iden->value_type_ = ExprNode::TYPE_INT;
                    break;
                case VarDecl::BOOL:
                    iden->value_type_ = ExprNode::TYPE_BOOL;
                    break;
                case VarDecl::CELL:
                    iden->value_type_ = ExprNode::TYPE_CELL;
                    break;
                default: iden->value_type_ = ExprNode::TYPE_UNKNOWN;
            }
        }
        for (auto& idx : yystack_[0].value.as < std::vector<expr_ptr> > ()) {
            iden->indices_.push_back(idx);
        }
        yylhs.value.as < expr_ptr > () = iden;
    }
#line 2153 "generated/robot.tab.cpp"
    break;

  case 81: // dim_ref_list: TOKEN_DIM_OPEN TOKEN_INDEX_OPEN expr TOKEN_INDEX_CLOSE TOKEN_DIM_CLOSE
#line 969 "robot.ypp"
    {
        yylhs.value.as < std::vector<expr_ptr> > () = std::vector<expr_ptr>();
        yylhs.value.as < std::vector<expr_ptr> > ().push_back(yystack_[2].value.as < expr_ptr > ());
    }
#line 2162 "generated/robot.tab.cpp"
    break;

  case 82: // dim_ref_list: dim_ref_list TOKEN_DIM_OPEN TOKEN_INDEX_OPEN expr TOKEN_INDEX_CLOSE TOKEN_DIM_CLOSE
#line 974 "robot.ypp"
    {
        yystack_[5].value.as < std::vector<expr_ptr> > ().push_back(yystack_[2].value.as < expr_ptr > ());
        yylhs.value.as < std::vector<expr_ptr> > () = yystack_[5].value.as < std::vector<expr_ptr> > ();
    }
#line 2171 "generated/robot.tab.cpp"
    break;


#line 2175 "generated/robot.tab.cpp"

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


  const short  RobotParser ::yypact_ninf_ = -133;

  const signed char  RobotParser ::yytable_ninf_ = -1;

  const short
   RobotParser ::yypact_[] =
  {
       2,  -133,    37,     3,  -133,  -133,  -133,    40,    34,  -133,
    -133,  -133,    35,     7,  -133,    -8,   104,    33,  -133,  -133,
     -40,   -38,  -133,    40,  -133,   -33,  -133,    14,    23,    10,
      12,    14,    14,    14,    14,    14,   -26,    14,    14,    14,
      14,    14,    14,    14,    14,    14,    14,  -133,  -133,    27,
     -26,   -26,  -133,  -133,  -133,  -133,  -133,  -133,  -133,  -133,
    -133,  -133,  -133,  -133,  -133,  -133,    47,  -133,  -133,    29,
      50,    32,    14,    14,    20,    -9,  -133,    15,    16,    18,
       8,    22,    13,  -133,     4,    14,    26,    14,    14,    24,
      28,     0,    25,    -2,    19,    45,    51,    -1,     5,    71,
       9,  -133,  -133,  -133,    72,    60,    14,  -133,  -133,  -133,
    -133,  -133,  -133,  -133,  -133,  -133,  -133,  -133,    39,    38,
    -133,  -133,  -133,  -133,  -133,  -133,    14,    77,  -133,  -133,
    -133,    94,    76,    74,    73,  -133,  -133,    82,    14,     6,
      95,   -26,  -133,    80,    90,    89,   106,   107,   109,   114,
     102,   -39,  -133,   179,  -133,  -133,    98,  -133,  -133,  -133,
     116,   103,   128,   100,  -133,    97,   254,  -133,    49,    14,
      11,  -133,  -133,  -133,    92,   117,   111,  -133,    14,  -133,
      62,    17,  -133,   115,   120,  -133,    65,  -133,  -133,   124,
    -133
  };

  const signed char
   RobotParser ::yydefact_[] =
  {
       0,     3,     0,     0,     1,     6,     2,     0,     0,     4,
       5,    27,     0,     0,     8,     0,     0,     0,     7,     9,
       0,     0,    29,     0,    24,     0,    77,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    71,    71,     0,
       0,     0,    71,    71,    71,    71,    71,    76,    75,    79,
       0,     0,    28,    37,    36,    30,    31,    32,    33,    34,
      35,    38,    39,    41,    58,    78,    12,    25,    26,     0,
       0,     0,     0,     0,     0,     0,    47,     0,     0,     0,
       0,     0,     0,    73,     0,    72,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    80,     0,     0,     0,
       0,    40,    54,    59,     0,     0,     0,    46,    48,    50,
      51,    52,    53,    70,    55,    60,    74,    61,     0,     0,
      66,    65,    64,    68,    69,    67,     0,     0,    56,    57,
      11,     0,     0,     0,     0,    62,    63,     0,     0,     0,
      16,     0,    27,     0,     0,     0,     0,     0,     0,     0,
      20,     0,    43,     0,    27,    81,     0,    13,    14,    15,
       0,     0,     0,     0,    44,     0,     0,    82,     0,     0,
       0,    10,    42,    45,     0,     0,     0,    21,     0,    49,
       0,     0,    22,     0,     0,    17,     0,    23,    18,     0,
      19
  };

  const short
   RobotParser ::yypgoto_[] =
  {
    -133,  -133,  -133,  -133,   131,   -11,  -133,  -133,  -133,  -133,
    -133,  -133,  -133,  -133,  -132,  -133,  -133,  -133,  -133,  -133,
    -133,  -133,  -133,    81,  -133,  -133,  -133,  -133,  -133,   -16,
     -12,  -133,  -133,   -30,  -133
  };

  const unsigned char
   RobotParser ::yydefgoto_[] =
  {
       0,     2,     3,     9,    13,    14,   100,   140,   150,   181,
     162,   170,    10,    11,    16,    52,    53,    54,    55,   151,
      56,    57,    75,    76,    58,    59,    60,    61,    62,    83,
      84,    85,    64,    65,    96
  };

  const unsigned char
   RobotParser ::yytable_[] =
  {
      63,   163,    19,    20,     5,     1,    82,     6,     7,    21,
     153,    71,     8,    18,    12,    77,    78,    79,    80,    81,
      97,    98,   166,    87,    88,    89,    86,   146,   147,   148,
      90,    91,    92,    93,    94,   101,    12,     4,    26,   107,
      74,   177,   178,   185,   186,    27,    49,    12,    15,    17,
      66,    67,    70,    68,    72,    73,   104,   105,    19,    49,
      95,    74,    99,   102,   103,   106,   112,   109,   115,   116,
     110,   118,   119,    35,   111,   114,   122,    37,   124,    38,
     126,    39,   113,    40,   127,    41,   128,    42,   130,    43,
     134,    44,   117,    45,   129,    46,   120,    47,    48,    49,
     131,   125,   121,   123,   132,    22,   133,   135,   136,    23,
     137,   152,   138,   139,    24,   141,    25,   142,   144,   143,
     149,   164,   145,   154,   155,   156,   157,   158,    26,   159,
     160,   161,   167,   168,   169,    27,   171,    63,   172,   173,
     175,    28,   179,   182,   180,    29,   184,   187,   188,   189,
      63,    30,   190,   176,    69,    31,   108,    32,     0,    33,
       0,    34,   183,    35,     0,    36,     0,    37,     0,    38,
       0,    39,     0,    40,     0,    41,     0,    42,     0,    43,
      22,    44,     0,    45,    23,    46,     0,    47,    48,    49,
      50,    25,    51,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    26,     0,     0,     0,     0,     0,     0,
      27,     0,     0,     0,     0,     0,    28,     0,     0,     0,
      29,     0,     0,   165,     0,     0,    30,     0,     0,     0,
      31,     0,    32,     0,    33,     0,    34,     0,    35,     0,
      36,     0,    37,     0,    38,     0,    39,     0,    40,     0,
      41,     0,    42,     0,    43,    22,    44,     0,    45,    23,
      46,     0,    47,    48,    49,    50,    25,    51,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    26,     0,
       0,     0,     0,     0,     0,    27,     0,     0,     0,     0,
       0,    28,     0,     0,     0,    29,     0,     0,   174,     0,
       0,    30,     0,     0,     0,    31,     0,    32,     0,    33,
       0,    34,     0,    35,     0,    36,     0,    37,     0,    38,
       0,    39,     0,    40,     0,    41,     0,    42,     0,    43,
       0,    44,     0,    45,     0,    46,     0,    47,    48,    49,
      50,     0,    51
  };

  const short
   RobotParser ::yycheck_[] =
  {
      16,    40,    13,    11,     1,     3,    36,     4,     5,    17,
     142,    27,     9,     6,     7,    31,    32,    33,    34,    35,
      50,    51,   154,    39,    40,    41,    38,    21,    22,    23,
      42,    43,    44,    45,    46,     6,     7,     0,    24,    48,
      49,    30,    31,    26,    27,    31,    85,     7,    14,    14,
      17,    91,    85,    91,    31,    45,    72,    73,    69,    85,
      33,    49,    15,    13,    32,    45,    58,    52,    64,    85,
      54,    87,    88,    59,    56,    62,    76,    63,    80,    65,
      35,    67,    60,    69,    33,    71,    87,    73,    17,    75,
     106,    77,    66,    79,    89,    81,    72,    83,    84,    85,
      91,    82,    74,    78,    32,     1,    46,    68,    70,     5,
     126,   141,    35,    19,    10,    39,    12,    43,    36,    46,
      25,   151,   138,    43,    34,    36,    20,    20,    24,    20,
      16,    29,    34,    17,    31,    31,     8,   153,    38,    42,
      91,    37,    50,    32,    27,    41,    84,    32,    28,    84,
     166,    47,    28,   169,    23,    51,    75,    53,    -1,    55,
      -1,    57,   178,    59,    -1,    61,    -1,    63,    -1,    65,
      -1,    67,    -1,    69,    -1,    71,    -1,    73,    -1,    75,
       1,    77,    -1,    79,     5,    81,    -1,    83,    84,    85,
      86,    12,    88,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    24,    -1,    -1,    -1,    -1,    -1,    -1,
      31,    -1,    -1,    -1,    -1,    -1,    37,    -1,    -1,    -1,
      41,    -1,    -1,    44,    -1,    -1,    47,    -1,    -1,    -1,
      51,    -1,    53,    -1,    55,    -1,    57,    -1,    59,    -1,
      61,    -1,    63,    -1,    65,    -1,    67,    -1,    69,    -1,
      71,    -1,    73,    -1,    75,     1,    77,    -1,    79,     5,
      81,    -1,    83,    84,    85,    86,    12,    88,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    24,    -1,
      -1,    -1,    -1,    -1,    -1,    31,    -1,    -1,    -1,    -1,
      -1,    37,    -1,    -1,    -1,    41,    -1,    -1,    44,    -1,
      -1,    47,    -1,    -1,    -1,    51,    -1,    53,    -1,    55,
      -1,    57,    -1,    59,    -1,    61,    -1,    63,    -1,    65,
      -1,    67,    -1,    69,    -1,    71,    -1,    73,    -1,    75,
      -1,    77,    -1,    79,    -1,    81,    -1,    83,    84,    85,
      86,    -1,    88
  };

  const signed char
   RobotParser ::yystos_[] =
  {
       0,     3,    93,    94,     0,     1,     4,     5,     9,    95,
     104,   105,     7,    96,    97,    14,   106,    14,     6,    97,
      11,    17,     1,     5,    10,    12,    24,    31,    37,    41,
      47,    51,    53,    55,    57,    59,    61,    63,    65,    67,
      69,    71,    73,    75,    77,    79,    81,    83,    84,    85,
      86,    88,   107,   108,   109,   110,   112,   113,   116,   117,
     118,   119,   120,   121,   124,   125,    17,    91,    91,    96,
      85,   121,    31,    45,    49,   114,   115,   121,   121,   121,
     121,   121,   125,   121,   122,   123,   122,   121,   121,   121,
     122,   122,   122,   122,   122,    33,   126,   125,   125,    15,
      98,     6,    13,    32,   121,   121,    45,    48,   115,    52,
      54,    56,    58,    60,    62,    64,   121,    66,   121,   121,
      72,    74,    76,    78,    80,    82,    35,    33,    87,    89,
      17,    91,    32,    46,   121,    68,    70,   121,    35,    19,
      99,    39,    43,    46,    36,   121,    21,    22,    23,    25,
     100,   111,   125,   106,    43,    34,    36,    20,    20,    20,
      16,    29,   102,    40,   125,    44,   106,    34,    17,    31,
     103,     8,    38,    42,    44,    91,   121,    30,    31,    50,
      27,   101,    32,   121,    84,    26,    27,    32,    28,    84,
      28
  };

  const signed char
   RobotParser ::yyr1_[] =
  {
       0,    92,    93,    94,    94,    94,    94,    95,    96,    96,
      97,    98,    98,    99,    99,    99,   100,   100,   101,   101,
     102,   102,   103,   103,   104,   105,   105,   106,   106,   106,
     107,   107,   107,   107,   107,   107,   107,   107,   107,   107,
     108,   109,   110,   111,   111,   112,   113,   114,   114,   115,
     116,   116,   116,   116,   117,   118,   119,   120,   121,   121,
     121,   121,   121,   121,   121,   121,   121,   121,   121,   121,
     121,   122,   122,   123,   123,   124,   124,   124,   124,   125,
     125,   126,   126
  };

  const signed char
   RobotParser ::yyr2_[] =
  {
       0,     2,     3,     0,     2,     2,     2,     3,     1,     2,
       9,     2,     0,     3,     3,     3,     0,     6,     3,     4,
       0,     3,     3,     4,     3,     4,     4,     0,     2,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     1,     8,     1,     2,     8,     3,     1,     2,     8,
       3,     3,     3,     3,     3,     3,     3,     3,     1,     3,
       3,     3,     4,     4,     3,     3,     3,     3,     3,     3,
       3,     0,     1,     1,     2,     1,     1,     1,     1,     1,
       2,     5,     6
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
  "TOKEN_IDENTIFIER", "TOKEN_GETX_OPEN", "TOKEN_GETX_CLOSE",
  "TOKEN_GETY_OPEN", "TOKEN_GETY_CLOSE", "TOKEN_SELFCLOSE", "'>'",
  "$accept", "program", "program_items", "vardecl_block", "var_list",
  "var_item", "opt_const", "type_spec", "opt_dimensions", "dims_list",
  "opt_init_values", "value_list", "func_def", "func_header", "stmt_list",
  "stmt", "vardecl_stmt", "expr_stmt", "assign_stmt", "var_ref_list",
  "while_stmt", "switch_stmt", "cond_list", "cond_branch", "move_stmt",
  "call_stmt", "getdrons_stmt", "get_x_stmt", "get_y_stmt", "expr",
  "opt_expr_list", "expr_list", "primary_expr", "var_ref", "dim_ref_list", YY_NULLPTR
  };
#endif


#if YYDEBUG
  const short
   RobotParser ::yyrline_[] =
  {
       0,   209,   209,   227,   228,   229,   238,   247,   263,   267,
     289,   306,   310,   317,   321,   325,   332,   336,   349,   353,
     361,   365,   372,   376,   396,   405,   417,   427,   428,   433,
     443,   444,   445,   446,   447,   448,   449,   450,   451,   452,
     457,   477,   492,   526,   530,   548,   583,   592,   596,   604,
     626,   633,   640,   647,   660,   676,   685,   694,   708,   712,
     716,   729,   742,   754,   768,   781,   794,   805,   818,   831,
     844,   854,   858,   865,   869,   877,   881,   885,   889,   903,
     929,   968,   973
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

   RobotParser ::symbol_kind_type
   RobotParser ::yytranslate_ (int t) YY_NOEXCEPT
  {
    // YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to
    // TOKEN-NUM as returned by yylex.
    static
    const signed char
    translate_table[] =
    {
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,    91,     2,     2,     2,     2,     2,     2,     2,
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
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90
    };
    // Last valid token kind.
    const int code_max = 345;

    if (t <= 0)
      return symbol_kind::S_YYEOF;
    else if (t <= code_max)
      return static_cast <symbol_kind_type> (translate_table[t]);
    else
      return symbol_kind::S_YYUNDEF;
  }

#line 91 "robot.ypp"
} //  yy 
#line 2878 "generated/robot.tab.cpp"

#line 980 "robot.ypp"


void yy::RobotParser::error(const location_type& loc, const std::string& msg) {
    add_syntax_error(loc.begin.line, loc.begin.column, msg);
}






