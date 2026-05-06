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
#line 207 "robot.ypp"
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
#line 1273 "generated/robot.tab.cpp"
    break;

  case 5: // program_items: program_items func_def
#line 227 "robot.ypp"
    {
        if (!yystack_[0].value.as < FuncDecl > ().name_.empty()){
            if (yystack_[0].value.as < FuncDecl > ().is_main_ || yystack_[0].value.as < FuncDecl > ().name_ == "main") {
                has_main_ = true;
            }
            functions_[yystack_[0].value.as < FuncDecl > ().name_] = yystack_[0].value.as < FuncDecl > ();
        }
    }
#line 1286 "generated/robot.tab.cpp"
    break;

  case 6: // program_items: program_items error
#line 236 "robot.ypp"
    {
        add_syntax_error(yystack_[0].location.begin.line, yystack_[0].location.begin.column, "syntax error in global scope");
        yyerrok;
        yyclearin;
    }
#line 1296 "generated/robot.tab.cpp"
    break;

  case 7: // vardecl_block: TOKEN_VARDECL_OPEN var_list TOKEN_VARDECL_CLOSE
#line 245 "robot.ypp"
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
#line 1313 "generated/robot.tab.cpp"
    break;

  case 8: // var_list: var_item
#line 261 "robot.ypp"
    {
        yylhs.value.as < std::vector<VarDecl> > ().push_back(yystack_[0].value.as < VarDecl > ());
    }
#line 1321 "generated/robot.tab.cpp"
    break;

  case 9: // var_list: var_list var_item
#line 265 "robot.ypp"
    {
        yystack_[1].value.as < std::vector<VarDecl> > ().push_back(yystack_[0].value.as < VarDecl > ());
        yylhs.value.as < std::vector<VarDecl> > () = yystack_[1].value.as < std::vector<VarDecl> > ();
    }
#line 1330 "generated/robot.tab.cpp"
    break;

  case 10: // var_item: TOKEN_VAR_OPEN TOKEN_NAME_ATTR TOKEN_STRING opt_const '>' type_spec opt_dimensions opt_init_values TOKEN_VAR_CLOSE
#line 287 "robot.ypp"
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
#line 1349 "generated/robot.tab.cpp"
    break;

  case 11: // opt_const: TOKEN_CONST TOKEN_STRING
#line 304 "robot.ypp"
    {
        yylhs.value.as < bool > () = (yystack_[0].value.as < std::string > () == "true");
    }
#line 1357 "generated/robot.tab.cpp"
    break;

  case 12: // opt_const: %empty
#line 308 "robot.ypp"
    {
        yylhs.value.as < bool > () = false; // по умолчанию ставлю false
    }
#line 1365 "generated/robot.tab.cpp"
    break;

  case 13: // type_spec: TOKEN_TYPE_OPEN TOKEN_TYPE_INT TOKEN_TYPE_CLOSE
#line 315 "robot.ypp"
    {
        yylhs.value.as < VarDecl::VarType > () = VarDecl::INT;
    }
#line 1373 "generated/robot.tab.cpp"
    break;

  case 14: // type_spec: TOKEN_TYPE_OPEN TOKEN_TYPE_BOOL TOKEN_TYPE_CLOSE
#line 319 "robot.ypp"
    {
        yylhs.value.as < VarDecl::VarType > () = VarDecl::BOOL;
    }
#line 1381 "generated/robot.tab.cpp"
    break;

  case 15: // type_spec: TOKEN_TYPE_OPEN TOKEN_TYPE_CELL TOKEN_TYPE_CLOSE
#line 323 "robot.ypp"
    {
        yylhs.value.as < VarDecl::VarType > () = VarDecl::CELL;
    }
#line 1389 "generated/robot.tab.cpp"
    break;

  case 16: // opt_dimensions: %empty
#line 330 "robot.ypp"
    {
        yylhs.value.as < std::vector<int> > () = std::vector<int>();
    }
#line 1397 "generated/robot.tab.cpp"
    break;

  case 17: // opt_dimensions: TOKEN_DIMENSIONS_OPEN TOKEN_COUNT TOKEN_STRING '>' dims_list TOKEN_DIMENSIONS_CLOSE
#line 334 "robot.ypp"
    {
        int value = atoi(yystack_[3].value.as < std::string > ().c_str());
        if (value != (int)yystack_[1].value.as < std::vector<int> > ().size()){ // несовпадение count и сколько объявлено измерений
            add_semantic_error(yystack_[4].location.begin.line, yystack_[4].location.begin.column, "dimension count mismatch: expected " + yystack_[3].value.as < std::string > () + ", got " +  std::to_string(yystack_[1].value.as < std::vector<int> > ().size()));
        } else {
            yylhs.value.as < std::vector<int> > () = yystack_[1].value.as < std::vector<int> > ();
        }

    }
#line 1411 "generated/robot.tab.cpp"
    break;

  case 18: // dims_list: TOKEN_DIMENSION_OPEN TOKEN_INT_LIT TOKEN_DIMENSION_CLOSE
#line 347 "robot.ypp"
    {
        yylhs.value.as < std::vector<int> > ().push_back(yystack_[1].value.as < int > ());
    }
#line 1419 "generated/robot.tab.cpp"
    break;

  case 19: // dims_list: dims_list TOKEN_DIMENSION_OPEN TOKEN_INT_LIT TOKEN_DIMENSION_CLOSE
#line 351 "robot.ypp"
    {
        yystack_[3].value.as < std::vector<int> > ().push_back(yystack_[1].value.as < int > ());
        yylhs.value.as < std::vector<int> > () = yystack_[3].value.as < std::vector<int> > ();
    }
#line 1428 "generated/robot.tab.cpp"
    break;

  case 20: // opt_init_values: %empty
#line 359 "robot.ypp"
    {
        yylhs.value.as < std::vector<expr_ptr> > () = std::vector<expr_ptr>();
    }
#line 1436 "generated/robot.tab.cpp"
    break;

  case 21: // opt_init_values: TOKEN_VALUES_OPEN value_list TOKEN_VALUES_CLOSE
#line 363 "robot.ypp"
    {
        yylhs.value.as < std::vector<expr_ptr> > () = yystack_[1].value.as < std::vector<expr_ptr> > ();
    }
#line 1444 "generated/robot.tab.cpp"
    break;

  case 22: // value_list: TOKEN_VALUE_OPEN expr TOKEN_VALUE_CLOSE
#line 370 "robot.ypp"
    {
        yylhs.value.as < std::vector<expr_ptr> > ().push_back(yystack_[1].value.as < expr_ptr > ());
    }
#line 1452 "generated/robot.tab.cpp"
    break;

  case 23: // value_list: value_list TOKEN_VALUE_OPEN expr TOKEN_VALUE_CLOSE
#line 374 "robot.ypp"
    {
        yystack_[3].value.as < std::vector<expr_ptr> > ().push_back(yystack_[1].value.as < expr_ptr > ());
        yylhs.value.as < std::vector<expr_ptr> > () = yystack_[3].value.as < std::vector<expr_ptr> > ();
    }
#line 1461 "generated/robot.tab.cpp"
    break;

  case 24: // func_def: func_header stmt_list TOKEN_FUNC_CLOSE
#line 394 "robot.ypp"
    {
        yylhs.value.as < FuncDecl > () = yystack_[2].value.as < FuncDecl > ();
        yylhs.value.as < FuncDecl > ().body_ = yystack_[1].value.as < std::vector<stmt_ptr> > ();
        local_scopes_.pop_back();
    }
#line 1471 "generated/robot.tab.cpp"
    break;

  case 25: // func_header: TOKEN_FUNC_OPEN TOKEN_NAME_ATTR TOKEN_MAIN '>'
#line 403 "robot.ypp"
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
#line 1487 "generated/robot.tab.cpp"
    break;

  case 26: // func_header: TOKEN_FUNC_OPEN TOKEN_NAME_ATTR TOKEN_STRING '>'
#line 415 "robot.ypp"
    {
        local_scopes_.push_back({});
        yylhs.value.as < FuncDecl > ().name_ = yystack_[1].value.as < std::string > ();
        yylhs.value.as < FuncDecl > ().is_main_ = false;
        functions_[yystack_[1].value.as < std::string > ()] = yylhs.value.as < FuncDecl > ();
    }
#line 1498 "generated/robot.tab.cpp"
    break;

  case 27: // stmt_list: %empty
#line 424 "robot.ypp"
           { yylhs.value.as < std::vector<stmt_ptr> > () = std::vector<stmt_ptr>(); }
#line 1504 "generated/robot.tab.cpp"
    break;

  case 28: // stmt_list: stmt_list stmt
#line 426 "robot.ypp"
    {
        yystack_[1].value.as < std::vector<stmt_ptr> > ().push_back(yystack_[0].value.as < stmt_ptr > ());
        yylhs.value.as < std::vector<stmt_ptr> > () = yystack_[1].value.as < std::vector<stmt_ptr> > ();
    }
#line 1513 "generated/robot.tab.cpp"
    break;

  case 29: // stmt_list: stmt_list error
#line 431 "robot.ypp"
    {
        add_syntax_error(yystack_[0].location.begin.line, yystack_[0].location.begin.column, "Syntax error in statement list");
        yyerrok;
        yyclearin;
        yylhs.value.as < std::vector<stmt_ptr> > () = yystack_[1].value.as < std::vector<stmt_ptr> > ();
    }
#line 1524 "generated/robot.tab.cpp"
    break;

  case 30: // stmt: assign_stmt
#line 440 "robot.ypp"
                { yylhs.value.as < stmt_ptr > () = yystack_[0].value.as < stmt_ptr > (); }
#line 1530 "generated/robot.tab.cpp"
    break;

  case 31: // stmt: while_stmt
#line 441 "robot.ypp"
                 { yylhs.value.as < stmt_ptr > () = yystack_[0].value.as < stmt_ptr > (); }
#line 1536 "generated/robot.tab.cpp"
    break;

  case 32: // stmt: switch_stmt
#line 442 "robot.ypp"
                  { yylhs.value.as < stmt_ptr > () = yystack_[0].value.as < stmt_ptr > (); }
#line 1542 "generated/robot.tab.cpp"
    break;

  case 33: // stmt: move_stmt
#line 443 "robot.ypp"
                { yylhs.value.as < stmt_ptr > () = yystack_[0].value.as < stmt_ptr > (); }
#line 1548 "generated/robot.tab.cpp"
    break;

  case 34: // stmt: call_stmt
#line 444 "robot.ypp"
                { yylhs.value.as < stmt_ptr > () = yystack_[0].value.as < stmt_ptr > (); }
#line 1554 "generated/robot.tab.cpp"
    break;

  case 35: // stmt: getdrons_stmt
#line 445 "robot.ypp"
                    { yylhs.value.as < stmt_ptr > () = yystack_[0].value.as < stmt_ptr > (); }
#line 1560 "generated/robot.tab.cpp"
    break;

  case 36: // stmt: expr_stmt
#line 446 "robot.ypp"
                { yylhs.value.as < stmt_ptr > () = yystack_[0].value.as < stmt_ptr > (); }
#line 1566 "generated/robot.tab.cpp"
    break;

  case 37: // stmt: vardecl_stmt
#line 447 "robot.ypp"
                   { yylhs.value.as < stmt_ptr > () = yystack_[0].value.as < stmt_ptr > (); }
#line 1572 "generated/robot.tab.cpp"
    break;

  case 38: // vardecl_stmt: TOKEN_VARDECL_OPEN var_list TOKEN_VARDECL_CLOSE
#line 453 "robot.ypp"
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
#line 1592 "generated/robot.tab.cpp"
    break;

  case 39: // expr_stmt: expr
#line 473 "robot.ypp"
    {
        auto statement = std::make_shared<StmtNode>(StmtNode::EXPR);
        statement->expr_val_ = yystack_[0].value.as < expr_ptr > ();
        yylhs.value.as < stmt_ptr > () = statement;
    }
#line 1602 "generated/robot.tab.cpp"
    break;

  case 40: // assign_stmt: TOKEN_ASSIGN_OPEN TOKEN_VALUE_OPEN expr TOKEN_VALUE_CLOSE TOKEN_TO_OPEN var_ref_list TOKEN_TO_CLOSE TOKEN_ASSIGN_CLOSE
#line 488 "robot.ypp"
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
#line 1637 "generated/robot.tab.cpp"
    break;

  case 41: // var_ref_list: var_ref
#line 522 "robot.ypp"
    {
        yylhs.value.as < std::vector<expr_ptr> > ().push_back(yystack_[0].value.as < expr_ptr > ());
    }
#line 1645 "generated/robot.tab.cpp"
    break;

  case 42: // var_ref_list: var_ref_list var_ref
#line 526 "robot.ypp"
    {
        yystack_[1].value.as < std::vector<expr_ptr> > ().push_back(yystack_[0].value.as < expr_ptr > ());
        yylhs.value.as < std::vector<expr_ptr> > () = yystack_[1].value.as < std::vector<expr_ptr> > ();
    }
#line 1654 "generated/robot.tab.cpp"
    break;

  case 43: // while_stmt: TOKEN_WHILE_OPEN TOKEN_CHECK_OPEN expr TOKEN_CHECK_CLOSE TOKEN_DO_OPEN stmt_list TOKEN_DO_CLOSE TOKEN_WHILE_CLOSE
#line 544 "robot.ypp"
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
#line 1669 "generated/robot.tab.cpp"
    break;

  case 44: // switch_stmt: TOKEN_SWITCH_OPEN cond_list TOKEN_SWITCH_CLOSE
#line 579 "robot.ypp"
    {
        auto st = std::make_shared<StmtNode>(StmtNode::SWITCH);
        st->switch_cases_ = yystack_[1].value.as < std::vector<ConditionBranch> > ();
        yylhs.value.as < stmt_ptr > () = st;
    }
#line 1679 "generated/robot.tab.cpp"
    break;

  case 45: // cond_list: cond_branch
#line 588 "robot.ypp"
    {
        yylhs.value.as < std::vector<ConditionBranch> > ().push_back(yystack_[0].value.as < ConditionBranch > ());
    }
#line 1687 "generated/robot.tab.cpp"
    break;

  case 46: // cond_list: cond_list cond_branch
#line 592 "robot.ypp"
    {
        yystack_[1].value.as < std::vector<ConditionBranch> > ().push_back(yystack_[0].value.as < ConditionBranch > ());
        yylhs.value.as < std::vector<ConditionBranch> > () = yystack_[1].value.as < std::vector<ConditionBranch> > ();
    }
#line 1696 "generated/robot.tab.cpp"
    break;

  case 47: // cond_branch: TOKEN_CONDITION_OPEN TOKEN_CHECK_OPEN expr TOKEN_CHECK_CLOSE TOKEN_DO_OPEN stmt_list TOKEN_DO_CLOSE TOKEN_CONDITION_CLOSE
#line 600 "robot.ypp"
    {
        if (yystack_[5].value.as < expr_ptr > ()->value_type_ != ExprNode::TYPE_BOOL){
            add_semantic_error(yystack_[5].location.begin.line, yystack_[5].location.begin.column, "condition must be boolean");
        } else {
            yylhs.value.as < ConditionBranch > ().condition_ = yystack_[5].value.as < expr_ptr > ();
            yylhs.value.as < ConditionBranch > ().body_ = yystack_[2].value.as < std::vector<stmt_ptr> > ();
        }
    }
#line 1709 "generated/robot.tab.cpp"
    break;

  case 48: // move_stmt: TOKEN_LEFT_OPEN expr TOKEN_LEFT_CLOSE
#line 622 "robot.ypp"
    {
        auto st = std::make_shared<StmtNode>(StmtNode::MOVE);
        st->direction_ = StmtNode::LEFT;
        st->distance_ = yystack_[1].value.as < expr_ptr > ();
        yylhs.value.as < stmt_ptr > () = st;
    }
#line 1720 "generated/robot.tab.cpp"
    break;

  case 49: // move_stmt: TOKEN_RIGHT_OPEN expr TOKEN_RIGHT_CLOSE
#line 629 "robot.ypp"
    {
        auto st = std::make_shared<StmtNode>(StmtNode::MOVE);
        st->direction_ = StmtNode::RIGHT;
        st->distance_ = yystack_[1].value.as < expr_ptr > ();
        yylhs.value.as < stmt_ptr > () = st;
    }
#line 1731 "generated/robot.tab.cpp"
    break;

  case 50: // move_stmt: TOKEN_UP_OPEN expr TOKEN_UP_CLOSE
#line 636 "robot.ypp"
    {
        auto st = std::make_shared<StmtNode>(StmtNode::MOVE);
        st->direction_ = StmtNode::UP;
        st->distance_ = yystack_[1].value.as < expr_ptr > ();
        yylhs.value.as < stmt_ptr > () = st;
    }
#line 1742 "generated/robot.tab.cpp"
    break;

  case 51: // move_stmt: TOKEN_DOWN_OPEN expr TOKEN_DOWN_CLOSE
#line 643 "robot.ypp"
    {
        auto st = std::make_shared<StmtNode>(StmtNode::MOVE);
        st->direction_ = StmtNode::DOWN;
        st->distance_ = yystack_[1].value.as < expr_ptr > ();
        yylhs.value.as < stmt_ptr > () = st;
    }
#line 1753 "generated/robot.tab.cpp"
    break;

  case 52: // call_stmt: TOKEN_CALL_OPEN TOKEN_IDENTIFIER TOKEN_CALL_CLOSE
#line 656 "robot.ypp"
    {
        if (functions_.find(yystack_[1].value.as < std::string > ()) == functions_.end()){
            add_semantic_error(yystack_[1].location.begin.line, yystack_[1].location.begin.column, "function '" + yystack_[1].value.as < std::string > () + "' not defined");
        } else {
            auto st = std::make_shared<StmtNode>(StmtNode::CALL);
            st->call_name_ = yystack_[1].value.as < std::string > ();
            yylhs.value.as < stmt_ptr > () = st;
        }
    }
#line 1767 "generated/robot.tab.cpp"
    break;

  case 53: // getdrons_stmt: TOKEN_GETDRONSCOUNT_OPEN var_ref TOKEN_GETDRONSCOUNT_CLOSE
#line 672 "robot.ypp"
    {
        auto st = std::make_shared<StmtNode>(StmtNode::GETDRONSCOUNT);
        st->dron_target_ = yystack_[1].value.as < expr_ptr > ();
        yylhs.value.as < stmt_ptr > () = st;
    }
#line 1777 "generated/robot.tab.cpp"
    break;

  case 54: // expr: primary_expr
#line 687 "robot.ypp"
    {
        yylhs.value.as < expr_ptr > () = yystack_[0].value.as < expr_ptr > ();
    }
#line 1785 "generated/robot.tab.cpp"
    break;

  case 55: // expr: TOKEN_VALUE_OPEN expr TOKEN_VALUE_CLOSE
#line 691 "robot.ypp"
    {
        yylhs.value.as < expr_ptr > () = yystack_[1].value.as < expr_ptr > ();
    }
#line 1793 "generated/robot.tab.cpp"
    break;

  case 56: // expr: TOKEN_ADD_OPEN opt_expr_list TOKEN_ADD_CLOSE
#line 695 "robot.ypp"
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
#line 1810 "generated/robot.tab.cpp"
    break;

  case 57: // expr: TOKEN_MUL_OPEN opt_expr_list TOKEN_MUL_CLOSE
#line 708 "robot.ypp"
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
#line 1827 "generated/robot.tab.cpp"
    break;

  case 58: // expr: TOKEN_SUB_OPEN expr expr TOKEN_SUB_CLOSE
#line 721 "robot.ypp"
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
#line 1843 "generated/robot.tab.cpp"
    break;

  case 59: // expr: TOKEN_DIV_OPEN expr expr TOKEN_DIV_CLOSE
#line 733 "robot.ypp"
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
#line 1861 "generated/robot.tab.cpp"
    break;

  case 60: // expr: TOKEN_AND_OPEN opt_expr_list TOKEN_AND_CLOSE
#line 747 "robot.ypp"
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
#line 1878 "generated/robot.tab.cpp"
    break;

  case 61: // expr: TOKEN_OR_OPEN opt_expr_list TOKEN_OR_CLOSE
#line 760 "robot.ypp"
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
#line 1895 "generated/robot.tab.cpp"
    break;

  case 62: // expr: TOKEN_NOT_OPEN expr TOKEN_NOT_CLOSE
#line 773 "robot.ypp"
    {
        if (yystack_[1].value.as < expr_ptr > ()->value_type_ != ExprNode::TYPE_BOOL){
            add_semantic_error(yystack_[2].location.begin.line, yystack_[2].location.begin.column, "NOT expects boolean");
        }

        auto n = std::make_shared<ExprNode>(ExprNode::NOT);
        n->args_.push_back(yystack_[1].value.as < expr_ptr > ());
        n->value_type_ = ExprNode::TYPE_BOOL;
        yylhs.value.as < expr_ptr > () = n;
    }
#line 1910 "generated/robot.tab.cpp"
    break;

  case 63: // expr: TOKEN_EQ_OPEN opt_expr_list TOKEN_EQ_CLOSE
#line 784 "robot.ypp"
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
#line 1927 "generated/robot.tab.cpp"
    break;

  case 64: // expr: TOKEN_MAX_OPEN opt_expr_list TOKEN_MAX_CLOSE
#line 797 "robot.ypp"
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
#line 1944 "generated/robot.tab.cpp"
    break;

  case 65: // expr: TOKEN_MIN_OPEN opt_expr_list TOKEN_MIN_CLOSE
#line 810 "robot.ypp"
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
#line 1961 "generated/robot.tab.cpp"
    break;

  case 66: // expr: TOKEN_SENDDRONS_OPEN expr TOKEN_SENDDRONS_CLOSE
#line 823 "robot.ypp"
    {
        auto drons = std::make_shared<ExprNode>(ExprNode::SENDDRONS);
        drons->args_.push_back(yystack_[1].value.as < expr_ptr > ());
        drons->value_type_ = ExprNode::TYPE_CELL;
        yylhs.value.as < expr_ptr > () = drons;
    }
#line 1972 "generated/robot.tab.cpp"
    break;

  case 67: // opt_expr_list: %empty
#line 833 "robot.ypp"
    {
        yylhs.value.as < std::vector<expr_ptr> > () = std::vector<expr_ptr>();
    }
#line 1980 "generated/robot.tab.cpp"
    break;

  case 68: // opt_expr_list: expr_list
#line 837 "robot.ypp"
    {
        yylhs.value.as < std::vector<expr_ptr> > () = yystack_[0].value.as < std::vector<expr_ptr> > ();
    }
#line 1988 "generated/robot.tab.cpp"
    break;

  case 69: // expr_list: expr
#line 844 "robot.ypp"
    {
        yylhs.value.as < std::vector<expr_ptr> > ().push_back(yystack_[0].value.as < expr_ptr > ());
    }
#line 1996 "generated/robot.tab.cpp"
    break;

  case 70: // expr_list: expr_list expr
#line 848 "robot.ypp"
    {
        yystack_[1].value.as < std::vector<expr_ptr> > ().push_back(yystack_[0].value.as < expr_ptr > ());
        yylhs.value.as < std::vector<expr_ptr> > () = yystack_[1].value.as < std::vector<expr_ptr> > ();
    }
#line 2005 "generated/robot.tab.cpp"
    break;

  case 71: // primary_expr: TOKEN_INT_LIT
#line 856 "robot.ypp"
    {
        yylhs.value.as < expr_ptr > () = ExprNode::make_int(yystack_[0].value.as < int > ());
    }
#line 2013 "generated/robot.tab.cpp"
    break;

  case 72: // primary_expr: TOKEN_BOOL_LIT
#line 860 "robot.ypp"
    {
        yylhs.value.as < expr_ptr > () = ExprNode::make_bool(yystack_[0].value.as < bool > ());
    }
#line 2021 "generated/robot.tab.cpp"
    break;

  case 73: // primary_expr: TOKEN_CELL_VALUE
#line 864 "robot.ypp"
    {
        yylhs.value.as < expr_ptr > () = ExprNode::make_cell(yystack_[0].value.as < CellValue > ());
    }
#line 2029 "generated/robot.tab.cpp"
    break;

  case 74: // primary_expr: var_ref
#line 868 "robot.ypp"
    {
        yylhs.value.as < expr_ptr > () = yystack_[0].value.as < expr_ptr > ();
    }
#line 2037 "generated/robot.tab.cpp"
    break;

  case 75: // var_ref: TOKEN_IDENTIFIER
#line 882 "robot.ypp"
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
#line 2067 "generated/robot.tab.cpp"
    break;

  case 76: // var_ref: TOKEN_IDENTIFIER dim_ref_list
#line 908 "robot.ypp"
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
#line 2107 "generated/robot.tab.cpp"
    break;

  case 77: // dim_ref_list: TOKEN_DIM_OPEN TOKEN_INDEX_OPEN expr TOKEN_INDEX_CLOSE TOKEN_DIM_CLOSE
#line 947 "robot.ypp"
    {
        yylhs.value.as < std::vector<expr_ptr> > () = std::vector<expr_ptr>();
        yylhs.value.as < std::vector<expr_ptr> > ().push_back(yystack_[2].value.as < expr_ptr > ());
    }
#line 2116 "generated/robot.tab.cpp"
    break;

  case 78: // dim_ref_list: dim_ref_list TOKEN_DIM_OPEN TOKEN_INDEX_OPEN expr TOKEN_INDEX_CLOSE TOKEN_DIM_CLOSE
#line 952 "robot.ypp"
    {
        yystack_[5].value.as < std::vector<expr_ptr> > ().push_back(yystack_[2].value.as < expr_ptr > ());
        yylhs.value.as < std::vector<expr_ptr> > () = yystack_[5].value.as < std::vector<expr_ptr> > ();
    }
#line 2125 "generated/robot.tab.cpp"
    break;


#line 2129 "generated/robot.tab.cpp"

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


  const signed char  RobotParser ::yypact_ninf_ = -127;

  const signed char  RobotParser ::yytable_ninf_ = -1;

  const short
   RobotParser ::yypact_[] =
  {
       9,  -127,    26,     5,  -127,  -127,  -127,    25,    22,  -127,
    -127,  -127,    27,    -2,  -127,    -4,    32,    23,  -127,  -127,
     -44,   -42,  -127,    25,  -127,   -39,  -127,   250,    16,    10,
       0,   250,   250,   250,   250,   250,   -34,   250,   250,   250,
     250,   250,   250,   250,   250,   250,   250,  -127,  -127,    17,
    -127,  -127,  -127,  -127,  -127,  -127,  -127,  -127,  -127,  -127,
    -127,  -127,    42,  -127,  -127,    15,    45,    28,   250,   250,
      14,   -18,  -127,    18,     7,     8,    13,     2,    19,  -127,
      11,   250,    20,   250,   250,    -6,     3,    24,    34,    -8,
      36,    39,    43,    61,    -7,  -127,  -127,  -127,    50,    44,
     250,  -127,  -127,  -127,  -127,  -127,  -127,  -127,  -127,  -127,
    -127,  -127,    38,    40,  -127,  -127,  -127,  -127,  -127,  -127,
     250,    53,  -127,    73,    55,    59,    75,  -127,  -127,    60,
     250,     6,    94,   -34,  -127,    79,    89,    91,   105,   106,
     110,   121,   109,   -37,  -127,   119,  -127,  -127,   107,  -127,
    -127,  -127,   122,   113,   132,   108,  -127,   111,   194,  -127,
      62,   250,     4,  -127,  -127,  -127,    97,   124,   116,  -127,
     250,  -127,    68,    12,  -127,   123,   129,  -127,    74,  -127,
    -127,   131,  -127
  };

  const signed char
   RobotParser ::yydefact_[] =
  {
       0,     3,     0,     0,     1,     6,     2,     0,     0,     4,
       5,    27,     0,     0,     8,     0,     0,     0,     7,     9,
       0,     0,    29,     0,    24,     0,    73,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    67,    67,     0,
       0,     0,    67,    67,    67,    67,    67,    72,    71,    75,
      28,    37,    36,    30,    31,    32,    33,    34,    35,    39,
      54,    74,    12,    25,    26,     0,     0,     0,     0,     0,
       0,     0,    45,     0,     0,     0,     0,     0,     0,    69,
       0,    68,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    76,     0,     0,    38,    52,    55,     0,     0,
       0,    44,    46,    48,    49,    50,    51,    66,    53,    56,
      70,    57,     0,     0,    62,    61,    60,    64,    65,    63,
       0,     0,    11,     0,     0,     0,     0,    58,    59,     0,
       0,     0,    16,     0,    27,     0,     0,     0,     0,     0,
       0,     0,    20,     0,    41,     0,    27,    77,     0,    13,
      14,    15,     0,     0,     0,     0,    42,     0,     0,    78,
       0,     0,     0,    10,    40,    43,     0,     0,     0,    21,
       0,    47,     0,     0,    22,     0,     0,    17,     0,    23,
      18,     0,    19
  };

  const short
   RobotParser ::yypgoto_[] =
  {
    -127,  -127,  -127,  -127,   138,   -11,  -127,  -127,  -127,  -127,
    -127,  -127,  -127,  -127,  -126,  -127,  -127,  -127,  -127,  -127,
    -127,  -127,  -127,    93,  -127,  -127,  -127,   -16,    90,  -127,
    -127,   -35,  -127
  };

  const unsigned char
   RobotParser ::yydefgoto_[] =
  {
       0,     2,     3,     9,    13,    14,    94,   132,   142,   173,
     154,   162,    10,    11,    16,    50,    51,    52,    53,   143,
      54,    55,    71,    72,    56,    57,    58,    79,    80,    81,
      60,    61,    92
  };

  const unsigned char
   RobotParser ::yytable_[] =
  {
      59,    78,    19,   155,    18,    12,     5,    20,   145,     6,
       7,    67,     1,    21,     8,    73,    74,    75,    76,    77,
     158,    95,    12,    83,    84,    85,     4,   138,   139,   140,
     101,    70,    12,    22,   169,   170,    15,    23,   177,   178,
      62,    17,    24,    63,    25,    64,    66,    68,    49,    70,
      91,    49,    98,    99,    19,    69,    26,    93,    96,   100,
      97,   104,   107,    27,   105,   110,   114,   112,   113,    28,
     103,   106,   118,    29,   120,   109,   121,   115,   122,    30,
     123,   108,   124,    31,   126,    32,   111,    33,   130,    34,
     125,    35,   131,    36,   133,    37,   136,    38,   144,    39,
     116,    40,   134,    41,   129,    42,   127,    43,   156,    44,
     128,    45,   117,    46,   137,    47,    48,    49,   119,   141,
      22,   135,   146,   147,    23,   149,   150,   148,    82,    59,
     151,    25,    86,    87,    88,    89,    90,   152,   153,   160,
     163,   159,    59,    26,   161,   168,   164,   171,   174,   167,
      27,   172,   176,   165,   175,   179,    28,   180,   181,   182,
      29,    65,     0,   157,   102,     0,    30,     0,     0,     0,
      31,     0,    32,     0,    33,     0,    34,     0,    35,     0,
      36,     0,    37,     0,    38,     0,    39,     0,    40,     0,
      41,     0,    42,     0,    43,    22,    44,     0,    45,    23,
      46,     0,    47,    48,    49,     0,    25,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    26,     0,
       0,     0,     0,     0,     0,    27,     0,     0,     0,     0,
       0,    28,     0,     0,     0,    29,     0,     0,   166,     0,
       0,    30,     0,     0,     0,    31,     0,    32,     0,    33,
       0,    34,     0,    35,     0,    36,     0,    37,     0,    38,
       0,    39,     0,    40,     0,    41,     0,    42,     0,    43,
       0,    44,     0,    45,    26,    46,     0,    47,    48,    49,
       0,    27,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    35,
       0,     0,     0,    37,     0,    38,     0,    39,     0,    40,
       0,    41,     0,    42,     0,    43,     0,    44,     0,    45,
       0,    46,     0,    47,    48,    49
  };

  const short
   RobotParser ::yycheck_[] =
  {
      16,    36,    13,    40,     6,     7,     1,    11,   134,     4,
       5,    27,     3,    17,     9,    31,    32,    33,    34,    35,
     146,     6,     7,    39,    40,    41,     0,    21,    22,    23,
      48,    49,     7,     1,    30,    31,    14,     5,    26,    27,
      17,    14,    10,    87,    12,    87,    85,    31,    85,    49,
      33,    85,    68,    69,    65,    45,    24,    15,    13,    45,
      32,    54,    60,    31,    56,    81,    72,    83,    84,    37,
      52,    58,    80,    41,    35,    64,    33,    74,    17,    47,
      87,    62,    32,    51,   100,    53,    66,    55,    35,    57,
      46,    59,    19,    61,    39,    63,    36,    65,   133,    67,
      76,    69,    43,    71,   120,    73,    68,    75,   143,    77,
      70,    79,    78,    81,   130,    83,    84,    85,    82,    25,
       1,    46,    43,    34,     5,    20,    20,    36,    38,   145,
      20,    12,    42,    43,    44,    45,    46,    16,    29,    17,
       8,    34,   158,    24,    31,   161,    38,    50,    32,    87,
      31,    27,    84,    42,   170,    32,    37,    28,    84,    28,
      41,    23,    -1,    44,    71,    -1,    47,    -1,    -1,    -1,
      51,    -1,    53,    -1,    55,    -1,    57,    -1,    59,    -1,
      61,    -1,    63,    -1,    65,    -1,    67,    -1,    69,    -1,
      71,    -1,    73,    -1,    75,     1,    77,    -1,    79,     5,
      81,    -1,    83,    84,    85,    -1,    12,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    24,    -1,
      -1,    -1,    -1,    -1,    -1,    31,    -1,    -1,    -1,    -1,
      -1,    37,    -1,    -1,    -1,    41,    -1,    -1,    44,    -1,
      -1,    47,    -1,    -1,    -1,    51,    -1,    53,    -1,    55,
      -1,    57,    -1,    59,    -1,    61,    -1,    63,    -1,    65,
      -1,    67,    -1,    69,    -1,    71,    -1,    73,    -1,    75,
      -1,    77,    -1,    79,    24,    81,    -1,    83,    84,    85,
      -1,    31,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    59,
      -1,    -1,    -1,    63,    -1,    65,    -1,    67,    -1,    69,
      -1,    71,    -1,    73,    -1,    75,    -1,    77,    -1,    79,
      -1,    81,    -1,    83,    84,    85
  };

  const signed char
   RobotParser ::yystos_[] =
  {
       0,     3,    89,    90,     0,     1,     4,     5,     9,    91,
     100,   101,     7,    92,    93,    14,   102,    14,     6,    93,
      11,    17,     1,     5,    10,    12,    24,    31,    37,    41,
      47,    51,    53,    55,    57,    59,    61,    63,    65,    67,
      69,    71,    73,    75,    77,    79,    81,    83,    84,    85,
     103,   104,   105,   106,   108,   109,   112,   113,   114,   115,
     118,   119,    17,    87,    87,    92,    85,   115,    31,    45,
      49,   110,   111,   115,   115,   115,   115,   115,   119,   115,
     116,   117,   116,   115,   115,   115,   116,   116,   116,   116,
     116,    33,   120,    15,    94,     6,    13,    32,   115,   115,
      45,    48,   111,    52,    54,    56,    58,    60,    62,    64,
     115,    66,   115,   115,    72,    74,    76,    78,    80,    82,
      35,    33,    17,    87,    32,    46,   115,    68,    70,   115,
      35,    19,    95,    39,    43,    46,    36,   115,    21,    22,
      23,    25,    96,   107,   119,   102,    43,    34,    36,    20,
      20,    20,    16,    29,    98,    40,   119,    44,   102,    34,
      17,    31,    99,     8,    38,    42,    44,    87,   115,    30,
      31,    50,    27,    97,    32,   115,    84,    26,    27,    32,
      28,    84,    28
  };

  const signed char
   RobotParser ::yyr1_[] =
  {
       0,    88,    89,    90,    90,    90,    90,    91,    92,    92,
      93,    94,    94,    95,    95,    95,    96,    96,    97,    97,
      98,    98,    99,    99,   100,   101,   101,   102,   102,   102,
     103,   103,   103,   103,   103,   103,   103,   103,   104,   105,
     106,   107,   107,   108,   109,   110,   110,   111,   112,   112,
     112,   112,   113,   114,   115,   115,   115,   115,   115,   115,
     115,   115,   115,   115,   115,   115,   115,   116,   116,   117,
     117,   118,   118,   118,   118,   119,   119,   120,   120
  };

  const signed char
   RobotParser ::yyr2_[] =
  {
       0,     2,     3,     0,     2,     2,     2,     3,     1,     2,
       9,     2,     0,     3,     3,     3,     0,     6,     3,     4,
       0,     3,     3,     4,     3,     4,     4,     0,     2,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     3,     1,
       8,     1,     2,     8,     3,     1,     2,     8,     3,     3,
       3,     3,     3,     3,     1,     3,     3,     3,     4,     4,
       3,     3,     3,     3,     3,     3,     3,     0,     1,     1,
       2,     1,     1,     1,     1,     1,     2,     5,     6
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
  "value_list", "func_def", "func_header", "stmt_list", "stmt",
  "vardecl_stmt", "expr_stmt", "assign_stmt", "var_ref_list", "while_stmt",
  "switch_stmt", "cond_list", "cond_branch", "move_stmt", "call_stmt",
  "getdrons_stmt", "expr", "opt_expr_list", "expr_list", "primary_expr",
  "var_ref", "dim_ref_list", YY_NULLPTR
  };
#endif


#if YYDEBUG
  const short
   RobotParser ::yyrline_[] =
  {
       0,   206,   206,   224,   225,   226,   235,   244,   260,   264,
     286,   303,   307,   314,   318,   322,   329,   333,   346,   350,
     358,   362,   369,   373,   393,   402,   414,   424,   425,   430,
     440,   441,   442,   443,   444,   445,   446,   447,   452,   472,
     487,   521,   525,   543,   578,   587,   591,   599,   621,   628,
     635,   642,   655,   671,   686,   690,   694,   707,   720,   732,
     746,   759,   772,   783,   796,   809,   822,   832,   836,   843,
     847,   855,   859,   863,   867,   881,   907,   946,   951
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
       2,     2,    87,     2,     2,     2,     2,     2,     2,     2,
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
      85,    86
    };
    // Last valid token kind.
    const int code_max = 341;

    if (t <= 0)
      return symbol_kind::S_YYEOF;
    else if (t <= code_max)
      return static_cast <symbol_kind_type> (translate_table[t]);
    else
      return symbol_kind::S_YYUNDEF;
  }

#line 91 "robot.ypp"
} //  yy 
#line 2823 "generated/robot.tab.cpp"

#line 958 "robot.ypp"


void yy::RobotParser::error(const location_type& loc, const std::string& msg) {
    add_syntax_error(loc.begin.line, loc.begin.column, msg);
}






