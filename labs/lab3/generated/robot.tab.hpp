// A Bison parser, made by GNU Bison 3.8.2.

// Skeleton interface for Bison LALR(1) parsers in C++

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


/**
 ** \file generated/robot.tab.hpp
 ** Define the  yy ::parser class.
 */

// C++ LALR(1) parser skeleton written by Akim Demaille.

// DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
// especially those whose name start with YY_ or yy_.  They are
// private implementation details that can be changed or removed.

#ifndef YY_YY_GENERATED_ROBOT_TAB_HPP_INCLUDED
# define YY_YY_GENERATED_ROBOT_TAB_HPP_INCLUDED
// "%code requires" blocks.
#line 8 "robot.ypp"

    #include <iostream>
    #include <string>
    #include <vector>
    #include <memory>
    #include "ast.hpp"
    namespace yy {
        class RobotLexer;
    }

#line 60 "generated/robot.tab.hpp"


# include <cstdlib> // std::abort
# include <iostream>
# include <stdexcept>
# include <string>
# include <vector>

#if defined __cplusplus
# define YY_CPLUSPLUS __cplusplus
#else
# define YY_CPLUSPLUS 199711L
#endif

// Support move semantics when possible.
#if 201103L <= YY_CPLUSPLUS
# define YY_MOVE           std::move
# define YY_MOVE_OR_COPY   move
# define YY_MOVE_REF(Type) Type&&
# define YY_RVREF(Type)    Type&&
# define YY_COPY(Type)     Type
#else
# define YY_MOVE
# define YY_MOVE_OR_COPY   copy
# define YY_MOVE_REF(Type) Type&
# define YY_RVREF(Type)    const Type&
# define YY_COPY(Type)     const Type&
#endif

// Support noexcept when possible.
#if 201103L <= YY_CPLUSPLUS
# define YY_NOEXCEPT noexcept
# define YY_NOTHROW
#else
# define YY_NOEXCEPT
# define YY_NOTHROW throw ()
#endif

// Support constexpr when possible.
#if 201703 <= YY_CPLUSPLUS
# define YY_CONSTEXPR constexpr
#else
# define YY_CONSTEXPR
#endif
# include "location.hh"


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif

#line 91 "robot.ypp"
namespace  yy  {
#line 196 "generated/robot.tab.hpp"




  /// A Bison parser.
  class  RobotParser 
  {
  public:
#ifdef YYSTYPE
# ifdef __GNUC__
#  pragma GCC message "bison: do not #define YYSTYPE in C++, use %define api.value.type"
# endif
    typedef YYSTYPE value_type;
#else
  /// A buffer to store and retrieve objects.
  ///
  /// Sort of a variant, but does not keep track of the nature
  /// of the stored data, since that knowledge is available
  /// via the current parser state.
  class value_type
  {
  public:
    /// Type of *this.
    typedef value_type self_type;

    /// Empty construction.
    value_type () YY_NOEXCEPT
      : yyraw_ ()
    {}

    /// Construct and fill.
    template <typename T>
    value_type (YY_RVREF (T) t)
    {
      new (yyas_<T> ()) T (YY_MOVE (t));
    }

#if 201103L <= YY_CPLUSPLUS
    /// Non copyable.
    value_type (const self_type&) = delete;
    /// Non copyable.
    self_type& operator= (const self_type&) = delete;
#endif

    /// Destruction, allowed only if empty.
    ~value_type () YY_NOEXCEPT
    {}

# if 201103L <= YY_CPLUSPLUS
    /// Instantiate a \a T in here from \a t.
    template <typename T, typename... U>
    T&
    emplace (U&&... u)
    {
      return *new (yyas_<T> ()) T (std::forward <U>(u)...);
    }
# else
    /// Instantiate an empty \a T in here.
    template <typename T>
    T&
    emplace ()
    {
      return *new (yyas_<T> ()) T ();
    }

    /// Instantiate a \a T in here from \a t.
    template <typename T>
    T&
    emplace (const T& t)
    {
      return *new (yyas_<T> ()) T (t);
    }
# endif

    /// Instantiate an empty \a T in here.
    /// Obsolete, use emplace.
    template <typename T>
    T&
    build ()
    {
      return emplace<T> ();
    }

    /// Instantiate a \a T in here from \a t.
    /// Obsolete, use emplace.
    template <typename T>
    T&
    build (const T& t)
    {
      return emplace<T> (t);
    }

    /// Accessor to a built \a T.
    template <typename T>
    T&
    as () YY_NOEXCEPT
    {
      return *yyas_<T> ();
    }

    /// Const accessor to a built \a T (for %printer).
    template <typename T>
    const T&
    as () const YY_NOEXCEPT
    {
      return *yyas_<T> ();
    }

    /// Swap the content with \a that, of same type.
    ///
    /// Both variants must be built beforehand, because swapping the actual
    /// data requires reading it (with as()), and this is not possible on
    /// unconstructed variants: it would require some dynamic testing, which
    /// should not be the variant's responsibility.
    /// Swapping between built and (possibly) non-built is done with
    /// self_type::move ().
    template <typename T>
    void
    swap (self_type& that) YY_NOEXCEPT
    {
      std::swap (as<T> (), that.as<T> ());
    }

    /// Move the content of \a that to this.
    ///
    /// Destroys \a that.
    template <typename T>
    void
    move (self_type& that)
    {
# if 201103L <= YY_CPLUSPLUS
      emplace<T> (std::move (that.as<T> ()));
# else
      emplace<T> ();
      swap<T> (that);
# endif
      that.destroy<T> ();
    }

# if 201103L <= YY_CPLUSPLUS
    /// Move the content of \a that to this.
    template <typename T>
    void
    move (self_type&& that)
    {
      emplace<T> (std::move (that.as<T> ()));
      that.destroy<T> ();
    }
#endif

    /// Copy the content of \a that to this.
    template <typename T>
    void
    copy (const self_type& that)
    {
      emplace<T> (that.as<T> ());
    }

    /// Destroy the stored \a T.
    template <typename T>
    void
    destroy ()
    {
      as<T> ().~T ();
    }

  private:
#if YY_CPLUSPLUS < 201103L
    /// Non copyable.
    value_type (const self_type&);
    /// Non copyable.
    self_type& operator= (const self_type&);
#endif

    /// Accessor to raw memory as \a T.
    template <typename T>
    T*
    yyas_ () YY_NOEXCEPT
    {
      void *yyp = yyraw_;
      return static_cast<T*> (yyp);
     }

    /// Const accessor to raw memory as \a T.
    template <typename T>
    const T*
    yyas_ () const YY_NOEXCEPT
    {
      const void *yyp = yyraw_;
      return static_cast<const T*> (yyp);
     }

    /// An auxiliary type to compute the largest semantic type.
    union union_type
    {
      // TOKEN_CELL_VALUE
      char dummy1[sizeof (CellValue)];

      // cond_branch
      char dummy2[sizeof (ConditionBranch)];

      // func_def
      // func_header
      char dummy3[sizeof (FuncDecl)];

      // var_item
      char dummy4[sizeof (VarDecl)];

      // type_spec
      char dummy5[sizeof (VarDecl::VarType)];

      // TOKEN_BOOL
      // TOKEN_BOOL_LIT
      // opt_const
      char dummy6[sizeof (bool)];

      // expr
      // primary_expr
      // var_ref
      char dummy7[sizeof (expr_ptr)];

      // TOKEN_INT_LIT
      char dummy8[sizeof (int)];

      // TOKEN_MAIN
      // TOKEN_STRING
      // TOKEN_IDENTIFIER
      char dummy9[sizeof (std::string)];

      // cond_list
      char dummy10[sizeof (std::vector<ConditionBranch>)];

      // var_list
      char dummy11[sizeof (std::vector<VarDecl>)];

      // opt_init_values
      // value_list
      // var_ref_list
      // opt_expr_list
      // expr_list
      // dim_ref_list
      char dummy12[sizeof (std::vector<expr_ptr>)];

      // opt_dimensions
      // dims_list
      char dummy13[sizeof (std::vector<int>)];

      // stmt_list
      char dummy14[sizeof (std::vector<stmt_ptr>)];

      // stmt
      // vardecl_stmt
      // expr_stmt
      // assign_stmt
      // while_stmt
      // switch_stmt
      // move_stmt
      // call_stmt
      // getdrons_stmt
      char dummy15[sizeof (stmt_ptr)];
    };

    /// The size of the largest semantic type.
    enum { size = sizeof (union_type) };

    /// A buffer to store semantic values.
    union
    {
      /// Strongest alignment constraints.
      long double yyalign_me_;
      /// A buffer large enough to store any of the semantic values.
      char yyraw_[size];
    };
  };

#endif
    /// Backward compatibility (Bison 3.8).
    typedef value_type semantic_type;

    /// Symbol locations.
    typedef location location_type;

    /// Syntax errors thrown from user actions.
    struct syntax_error : std::runtime_error
    {
      syntax_error (const location_type& l, const std::string& m)
        : std::runtime_error (m)
        , location (l)
      {}

      syntax_error (const syntax_error& s)
        : std::runtime_error (s.what ())
        , location (s.location)
      {}

      ~syntax_error () YY_NOEXCEPT YY_NOTHROW;

      location_type location;
    };

    /// Token kinds.
    struct token
    {
      enum token_kind_type
      {
        YYEMPTY = -2,
    YYEOF = 0,                     // "end of file"
    YYerror = 256,                 // error
    YYUNDEF = 257,                 // "invalid token"
    TOKEN_PROGRAM_OPEN = 258,      // TOKEN_PROGRAM_OPEN
    TOKEN_PROGRAM_CLOSE = 259,     // TOKEN_PROGRAM_CLOSE
    TOKEN_VARDECL_OPEN = 260,      // TOKEN_VARDECL_OPEN
    TOKEN_VARDECL_CLOSE = 261,     // TOKEN_VARDECL_CLOSE
    TOKEN_VAR_OPEN = 262,          // TOKEN_VAR_OPEN
    TOKEN_VAR_CLOSE = 263,         // TOKEN_VAR_CLOSE
    TOKEN_FUNC_OPEN = 264,         // TOKEN_FUNC_OPEN
    TOKEN_FUNC_CLOSE = 265,        // TOKEN_FUNC_CLOSE
    TOKEN_MAIN = 266,              // TOKEN_MAIN
    TOKEN_CALL_OPEN = 267,         // TOKEN_CALL_OPEN
    TOKEN_CALL_CLOSE = 268,        // TOKEN_CALL_CLOSE
    TOKEN_NAME_ATTR = 269,         // TOKEN_NAME_ATTR
    TOKEN_CONST = 270,             // TOKEN_CONST
    TOKEN_COUNT = 271,             // TOKEN_COUNT
    TOKEN_STRING = 272,            // TOKEN_STRING
    TOKEN_BOOL = 273,              // TOKEN_BOOL
    TOKEN_TYPE_OPEN = 274,         // TOKEN_TYPE_OPEN
    TOKEN_TYPE_CLOSE = 275,        // TOKEN_TYPE_CLOSE
    TOKEN_TYPE_INT = 276,          // TOKEN_TYPE_INT
    TOKEN_TYPE_BOOL = 277,         // TOKEN_TYPE_BOOL
    TOKEN_TYPE_CELL = 278,         // TOKEN_TYPE_CELL
    TOKEN_CELL_VALUE = 279,        // TOKEN_CELL_VALUE
    TOKEN_DIMENSIONS_OPEN = 280,   // TOKEN_DIMENSIONS_OPEN
    TOKEN_DIMENSIONS_CLOSE = 281,  // TOKEN_DIMENSIONS_CLOSE
    TOKEN_DIMENSION_OPEN = 282,    // TOKEN_DIMENSION_OPEN
    TOKEN_DIMENSION_CLOSE = 283,   // TOKEN_DIMENSION_CLOSE
    TOKEN_VALUES_OPEN = 284,       // TOKEN_VALUES_OPEN
    TOKEN_VALUES_CLOSE = 285,      // TOKEN_VALUES_CLOSE
    TOKEN_VALUE_OPEN = 286,        // TOKEN_VALUE_OPEN
    TOKEN_VALUE_CLOSE = 287,       // TOKEN_VALUE_CLOSE
    TOKEN_DIM_OPEN = 288,          // TOKEN_DIM_OPEN
    TOKEN_DIM_CLOSE = 289,         // TOKEN_DIM_CLOSE
    TOKEN_INDEX_OPEN = 290,        // TOKEN_INDEX_OPEN
    TOKEN_INDEX_CLOSE = 291,       // TOKEN_INDEX_CLOSE
    TOKEN_ASSIGN_OPEN = 292,       // TOKEN_ASSIGN_OPEN
    TOKEN_ASSIGN_CLOSE = 293,      // TOKEN_ASSIGN_CLOSE
    TOKEN_TO_OPEN = 294,           // TOKEN_TO_OPEN
    TOKEN_TO_CLOSE = 295,          // TOKEN_TO_CLOSE
    TOKEN_WHILE_OPEN = 296,        // TOKEN_WHILE_OPEN
    TOKEN_WHILE_CLOSE = 297,       // TOKEN_WHILE_CLOSE
    TOKEN_DO_OPEN = 298,           // TOKEN_DO_OPEN
    TOKEN_DO_CLOSE = 299,          // TOKEN_DO_CLOSE
    TOKEN_CHECK_OPEN = 300,        // TOKEN_CHECK_OPEN
    TOKEN_CHECK_CLOSE = 301,       // TOKEN_CHECK_CLOSE
    TOKEN_SWITCH_OPEN = 302,       // TOKEN_SWITCH_OPEN
    TOKEN_SWITCH_CLOSE = 303,      // TOKEN_SWITCH_CLOSE
    TOKEN_CONDITION_OPEN = 304,    // TOKEN_CONDITION_OPEN
    TOKEN_CONDITION_CLOSE = 305,   // TOKEN_CONDITION_CLOSE
    TOKEN_LEFT_OPEN = 306,         // TOKEN_LEFT_OPEN
    TOKEN_LEFT_CLOSE = 307,        // TOKEN_LEFT_CLOSE
    TOKEN_RIGHT_OPEN = 308,        // TOKEN_RIGHT_OPEN
    TOKEN_RIGHT_CLOSE = 309,       // TOKEN_RIGHT_CLOSE
    TOKEN_UP_OPEN = 310,           // TOKEN_UP_OPEN
    TOKEN_UP_CLOSE = 311,          // TOKEN_UP_CLOSE
    TOKEN_DOWN_OPEN = 312,         // TOKEN_DOWN_OPEN
    TOKEN_DOWN_CLOSE = 313,        // TOKEN_DOWN_CLOSE
    TOKEN_SENDDRONS_OPEN = 314,    // TOKEN_SENDDRONS_OPEN
    TOKEN_SENDDRONS_CLOSE = 315,   // TOKEN_SENDDRONS_CLOSE
    TOKEN_GETDRONSCOUNT_OPEN = 316, // TOKEN_GETDRONSCOUNT_OPEN
    TOKEN_GETDRONSCOUNT_CLOSE = 317, // TOKEN_GETDRONSCOUNT_CLOSE
    TOKEN_ADD_OPEN = 318,          // TOKEN_ADD_OPEN
    TOKEN_ADD_CLOSE = 319,         // TOKEN_ADD_CLOSE
    TOKEN_MUL_OPEN = 320,          // TOKEN_MUL_OPEN
    TOKEN_MUL_CLOSE = 321,         // TOKEN_MUL_CLOSE
    TOKEN_SUB_OPEN = 322,          // TOKEN_SUB_OPEN
    TOKEN_SUB_CLOSE = 323,         // TOKEN_SUB_CLOSE
    TOKEN_DIV_OPEN = 324,          // TOKEN_DIV_OPEN
    TOKEN_DIV_CLOSE = 325,         // TOKEN_DIV_CLOSE
    TOKEN_NOT_OPEN = 326,          // TOKEN_NOT_OPEN
    TOKEN_NOT_CLOSE = 327,         // TOKEN_NOT_CLOSE
    TOKEN_OR_OPEN = 328,           // TOKEN_OR_OPEN
    TOKEN_OR_CLOSE = 329,          // TOKEN_OR_CLOSE
    TOKEN_AND_OPEN = 330,          // TOKEN_AND_OPEN
    TOKEN_AND_CLOSE = 331,         // TOKEN_AND_CLOSE
    TOKEN_MAX_OPEN = 332,          // TOKEN_MAX_OPEN
    TOKEN_MAX_CLOSE = 333,         // TOKEN_MAX_CLOSE
    TOKEN_MIN_OPEN = 334,          // TOKEN_MIN_OPEN
    TOKEN_MIN_CLOSE = 335,         // TOKEN_MIN_CLOSE
    TOKEN_EQ_OPEN = 336,           // TOKEN_EQ_OPEN
    TOKEN_EQ_CLOSE = 337,          // TOKEN_EQ_CLOSE
    TOKEN_BOOL_LIT = 338,          // TOKEN_BOOL_LIT
    TOKEN_INT_LIT = 339,           // TOKEN_INT_LIT
    TOKEN_IDENTIFIER = 340,        // TOKEN_IDENTIFIER
    TOKEN_SELFCLOSE = 341          // TOKEN_SELFCLOSE
      };
      /// Backward compatibility alias (Bison 3.6).
      typedef token_kind_type yytokentype;
    };

    /// Token kind, as returned by yylex.
    typedef token::token_kind_type token_kind_type;

    /// Backward compatibility alias (Bison 3.6).
    typedef token_kind_type token_type;

    /// Symbol kinds.
    struct symbol_kind
    {
      enum symbol_kind_type
      {
        YYNTOKENS = 88, ///< Number of tokens.
        S_YYEMPTY = -2,
        S_YYEOF = 0,                             // "end of file"
        S_YYerror = 1,                           // error
        S_YYUNDEF = 2,                           // "invalid token"
        S_TOKEN_PROGRAM_OPEN = 3,                // TOKEN_PROGRAM_OPEN
        S_TOKEN_PROGRAM_CLOSE = 4,               // TOKEN_PROGRAM_CLOSE
        S_TOKEN_VARDECL_OPEN = 5,                // TOKEN_VARDECL_OPEN
        S_TOKEN_VARDECL_CLOSE = 6,               // TOKEN_VARDECL_CLOSE
        S_TOKEN_VAR_OPEN = 7,                    // TOKEN_VAR_OPEN
        S_TOKEN_VAR_CLOSE = 8,                   // TOKEN_VAR_CLOSE
        S_TOKEN_FUNC_OPEN = 9,                   // TOKEN_FUNC_OPEN
        S_TOKEN_FUNC_CLOSE = 10,                 // TOKEN_FUNC_CLOSE
        S_TOKEN_MAIN = 11,                       // TOKEN_MAIN
        S_TOKEN_CALL_OPEN = 12,                  // TOKEN_CALL_OPEN
        S_TOKEN_CALL_CLOSE = 13,                 // TOKEN_CALL_CLOSE
        S_TOKEN_NAME_ATTR = 14,                  // TOKEN_NAME_ATTR
        S_TOKEN_CONST = 15,                      // TOKEN_CONST
        S_TOKEN_COUNT = 16,                      // TOKEN_COUNT
        S_TOKEN_STRING = 17,                     // TOKEN_STRING
        S_TOKEN_BOOL = 18,                       // TOKEN_BOOL
        S_TOKEN_TYPE_OPEN = 19,                  // TOKEN_TYPE_OPEN
        S_TOKEN_TYPE_CLOSE = 20,                 // TOKEN_TYPE_CLOSE
        S_TOKEN_TYPE_INT = 21,                   // TOKEN_TYPE_INT
        S_TOKEN_TYPE_BOOL = 22,                  // TOKEN_TYPE_BOOL
        S_TOKEN_TYPE_CELL = 23,                  // TOKEN_TYPE_CELL
        S_TOKEN_CELL_VALUE = 24,                 // TOKEN_CELL_VALUE
        S_TOKEN_DIMENSIONS_OPEN = 25,            // TOKEN_DIMENSIONS_OPEN
        S_TOKEN_DIMENSIONS_CLOSE = 26,           // TOKEN_DIMENSIONS_CLOSE
        S_TOKEN_DIMENSION_OPEN = 27,             // TOKEN_DIMENSION_OPEN
        S_TOKEN_DIMENSION_CLOSE = 28,            // TOKEN_DIMENSION_CLOSE
        S_TOKEN_VALUES_OPEN = 29,                // TOKEN_VALUES_OPEN
        S_TOKEN_VALUES_CLOSE = 30,               // TOKEN_VALUES_CLOSE
        S_TOKEN_VALUE_OPEN = 31,                 // TOKEN_VALUE_OPEN
        S_TOKEN_VALUE_CLOSE = 32,                // TOKEN_VALUE_CLOSE
        S_TOKEN_DIM_OPEN = 33,                   // TOKEN_DIM_OPEN
        S_TOKEN_DIM_CLOSE = 34,                  // TOKEN_DIM_CLOSE
        S_TOKEN_INDEX_OPEN = 35,                 // TOKEN_INDEX_OPEN
        S_TOKEN_INDEX_CLOSE = 36,                // TOKEN_INDEX_CLOSE
        S_TOKEN_ASSIGN_OPEN = 37,                // TOKEN_ASSIGN_OPEN
        S_TOKEN_ASSIGN_CLOSE = 38,               // TOKEN_ASSIGN_CLOSE
        S_TOKEN_TO_OPEN = 39,                    // TOKEN_TO_OPEN
        S_TOKEN_TO_CLOSE = 40,                   // TOKEN_TO_CLOSE
        S_TOKEN_WHILE_OPEN = 41,                 // TOKEN_WHILE_OPEN
        S_TOKEN_WHILE_CLOSE = 42,                // TOKEN_WHILE_CLOSE
        S_TOKEN_DO_OPEN = 43,                    // TOKEN_DO_OPEN
        S_TOKEN_DO_CLOSE = 44,                   // TOKEN_DO_CLOSE
        S_TOKEN_CHECK_OPEN = 45,                 // TOKEN_CHECK_OPEN
        S_TOKEN_CHECK_CLOSE = 46,                // TOKEN_CHECK_CLOSE
        S_TOKEN_SWITCH_OPEN = 47,                // TOKEN_SWITCH_OPEN
        S_TOKEN_SWITCH_CLOSE = 48,               // TOKEN_SWITCH_CLOSE
        S_TOKEN_CONDITION_OPEN = 49,             // TOKEN_CONDITION_OPEN
        S_TOKEN_CONDITION_CLOSE = 50,            // TOKEN_CONDITION_CLOSE
        S_TOKEN_LEFT_OPEN = 51,                  // TOKEN_LEFT_OPEN
        S_TOKEN_LEFT_CLOSE = 52,                 // TOKEN_LEFT_CLOSE
        S_TOKEN_RIGHT_OPEN = 53,                 // TOKEN_RIGHT_OPEN
        S_TOKEN_RIGHT_CLOSE = 54,                // TOKEN_RIGHT_CLOSE
        S_TOKEN_UP_OPEN = 55,                    // TOKEN_UP_OPEN
        S_TOKEN_UP_CLOSE = 56,                   // TOKEN_UP_CLOSE
        S_TOKEN_DOWN_OPEN = 57,                  // TOKEN_DOWN_OPEN
        S_TOKEN_DOWN_CLOSE = 58,                 // TOKEN_DOWN_CLOSE
        S_TOKEN_SENDDRONS_OPEN = 59,             // TOKEN_SENDDRONS_OPEN
        S_TOKEN_SENDDRONS_CLOSE = 60,            // TOKEN_SENDDRONS_CLOSE
        S_TOKEN_GETDRONSCOUNT_OPEN = 61,         // TOKEN_GETDRONSCOUNT_OPEN
        S_TOKEN_GETDRONSCOUNT_CLOSE = 62,        // TOKEN_GETDRONSCOUNT_CLOSE
        S_TOKEN_ADD_OPEN = 63,                   // TOKEN_ADD_OPEN
        S_TOKEN_ADD_CLOSE = 64,                  // TOKEN_ADD_CLOSE
        S_TOKEN_MUL_OPEN = 65,                   // TOKEN_MUL_OPEN
        S_TOKEN_MUL_CLOSE = 66,                  // TOKEN_MUL_CLOSE
        S_TOKEN_SUB_OPEN = 67,                   // TOKEN_SUB_OPEN
        S_TOKEN_SUB_CLOSE = 68,                  // TOKEN_SUB_CLOSE
        S_TOKEN_DIV_OPEN = 69,                   // TOKEN_DIV_OPEN
        S_TOKEN_DIV_CLOSE = 70,                  // TOKEN_DIV_CLOSE
        S_TOKEN_NOT_OPEN = 71,                   // TOKEN_NOT_OPEN
        S_TOKEN_NOT_CLOSE = 72,                  // TOKEN_NOT_CLOSE
        S_TOKEN_OR_OPEN = 73,                    // TOKEN_OR_OPEN
        S_TOKEN_OR_CLOSE = 74,                   // TOKEN_OR_CLOSE
        S_TOKEN_AND_OPEN = 75,                   // TOKEN_AND_OPEN
        S_TOKEN_AND_CLOSE = 76,                  // TOKEN_AND_CLOSE
        S_TOKEN_MAX_OPEN = 77,                   // TOKEN_MAX_OPEN
        S_TOKEN_MAX_CLOSE = 78,                  // TOKEN_MAX_CLOSE
        S_TOKEN_MIN_OPEN = 79,                   // TOKEN_MIN_OPEN
        S_TOKEN_MIN_CLOSE = 80,                  // TOKEN_MIN_CLOSE
        S_TOKEN_EQ_OPEN = 81,                    // TOKEN_EQ_OPEN
        S_TOKEN_EQ_CLOSE = 82,                   // TOKEN_EQ_CLOSE
        S_TOKEN_BOOL_LIT = 83,                   // TOKEN_BOOL_LIT
        S_TOKEN_INT_LIT = 84,                    // TOKEN_INT_LIT
        S_TOKEN_IDENTIFIER = 85,                 // TOKEN_IDENTIFIER
        S_TOKEN_SELFCLOSE = 86,                  // TOKEN_SELFCLOSE
        S_87_ = 87,                              // '>'
        S_YYACCEPT = 88,                         // $accept
        S_program = 89,                          // program
        S_program_items = 90,                    // program_items
        S_vardecl_block = 91,                    // vardecl_block
        S_var_list = 92,                         // var_list
        S_var_item = 93,                         // var_item
        S_opt_const = 94,                        // opt_const
        S_type_spec = 95,                        // type_spec
        S_opt_dimensions = 96,                   // opt_dimensions
        S_dims_list = 97,                        // dims_list
        S_opt_init_values = 98,                  // opt_init_values
        S_value_list = 99,                       // value_list
        S_func_def = 100,                        // func_def
        S_func_header = 101,                     // func_header
        S_stmt_list = 102,                       // stmt_list
        S_stmt = 103,                            // stmt
        S_vardecl_stmt = 104,                    // vardecl_stmt
        S_expr_stmt = 105,                       // expr_stmt
        S_assign_stmt = 106,                     // assign_stmt
        S_var_ref_list = 107,                    // var_ref_list
        S_while_stmt = 108,                      // while_stmt
        S_switch_stmt = 109,                     // switch_stmt
        S_cond_list = 110,                       // cond_list
        S_cond_branch = 111,                     // cond_branch
        S_move_stmt = 112,                       // move_stmt
        S_call_stmt = 113,                       // call_stmt
        S_getdrons_stmt = 114,                   // getdrons_stmt
        S_expr = 115,                            // expr
        S_opt_expr_list = 116,                   // opt_expr_list
        S_expr_list = 117,                       // expr_list
        S_primary_expr = 118,                    // primary_expr
        S_var_ref = 119,                         // var_ref
        S_dim_ref_list = 120                     // dim_ref_list
      };
    };

    /// (Internal) symbol kind.
    typedef symbol_kind::symbol_kind_type symbol_kind_type;

    /// The number of tokens.
    static const symbol_kind_type YYNTOKENS = symbol_kind::YYNTOKENS;

    /// A complete symbol.
    ///
    /// Expects its Base type to provide access to the symbol kind
    /// via kind ().
    ///
    /// Provide access to semantic value and location.
    template <typename Base>
    struct basic_symbol : Base
    {
      /// Alias to Base.
      typedef Base super_type;

      /// Default constructor.
      basic_symbol () YY_NOEXCEPT
        : value ()
        , location ()
      {}

#if 201103L <= YY_CPLUSPLUS
      /// Move constructor.
      basic_symbol (basic_symbol&& that)
        : Base (std::move (that))
        , value ()
        , location (std::move (that.location))
      {
        switch (this->kind ())
    {
      case symbol_kind::S_TOKEN_CELL_VALUE: // TOKEN_CELL_VALUE
        value.move< CellValue > (std::move (that.value));
        break;

      case symbol_kind::S_cond_branch: // cond_branch
        value.move< ConditionBranch > (std::move (that.value));
        break;

      case symbol_kind::S_func_def: // func_def
      case symbol_kind::S_func_header: // func_header
        value.move< FuncDecl > (std::move (that.value));
        break;

      case symbol_kind::S_var_item: // var_item
        value.move< VarDecl > (std::move (that.value));
        break;

      case symbol_kind::S_type_spec: // type_spec
        value.move< VarDecl::VarType > (std::move (that.value));
        break;

      case symbol_kind::S_TOKEN_BOOL: // TOKEN_BOOL
      case symbol_kind::S_TOKEN_BOOL_LIT: // TOKEN_BOOL_LIT
      case symbol_kind::S_opt_const: // opt_const
        value.move< bool > (std::move (that.value));
        break;

      case symbol_kind::S_expr: // expr
      case symbol_kind::S_primary_expr: // primary_expr
      case symbol_kind::S_var_ref: // var_ref
        value.move< expr_ptr > (std::move (that.value));
        break;

      case symbol_kind::S_TOKEN_INT_LIT: // TOKEN_INT_LIT
        value.move< int > (std::move (that.value));
        break;

      case symbol_kind::S_TOKEN_MAIN: // TOKEN_MAIN
      case symbol_kind::S_TOKEN_STRING: // TOKEN_STRING
      case symbol_kind::S_TOKEN_IDENTIFIER: // TOKEN_IDENTIFIER
        value.move< std::string > (std::move (that.value));
        break;

      case symbol_kind::S_cond_list: // cond_list
        value.move< std::vector<ConditionBranch> > (std::move (that.value));
        break;

      case symbol_kind::S_var_list: // var_list
        value.move< std::vector<VarDecl> > (std::move (that.value));
        break;

      case symbol_kind::S_opt_init_values: // opt_init_values
      case symbol_kind::S_value_list: // value_list
      case symbol_kind::S_var_ref_list: // var_ref_list
      case symbol_kind::S_opt_expr_list: // opt_expr_list
      case symbol_kind::S_expr_list: // expr_list
      case symbol_kind::S_dim_ref_list: // dim_ref_list
        value.move< std::vector<expr_ptr> > (std::move (that.value));
        break;

      case symbol_kind::S_opt_dimensions: // opt_dimensions
      case symbol_kind::S_dims_list: // dims_list
        value.move< std::vector<int> > (std::move (that.value));
        break;

      case symbol_kind::S_stmt_list: // stmt_list
        value.move< std::vector<stmt_ptr> > (std::move (that.value));
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
        value.move< stmt_ptr > (std::move (that.value));
        break;

      default:
        break;
    }

      }
#endif

      /// Copy constructor.
      basic_symbol (const basic_symbol& that);

      /// Constructors for typed symbols.
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, location_type&& l)
        : Base (t)
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const location_type& l)
        : Base (t)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, CellValue&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const CellValue& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, ConditionBranch&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const ConditionBranch& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, FuncDecl&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const FuncDecl& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, VarDecl&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const VarDecl& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, VarDecl::VarType&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const VarDecl::VarType& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, bool&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const bool& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, expr_ptr&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const expr_ptr& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, int&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const int& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::string&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::string& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::vector<ConditionBranch>&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::vector<ConditionBranch>& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::vector<VarDecl>&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::vector<VarDecl>& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::vector<expr_ptr>&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::vector<expr_ptr>& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::vector<int>&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::vector<int>& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::vector<stmt_ptr>&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::vector<stmt_ptr>& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, stmt_ptr&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const stmt_ptr& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

      /// Destroy the symbol.
      ~basic_symbol ()
      {
        clear ();
      }



      /// Destroy contents, and record that is empty.
      void clear () YY_NOEXCEPT
      {
        // User destructor.
        symbol_kind_type yykind = this->kind ();
        basic_symbol<Base>& yysym = *this;
        (void) yysym;
        switch (yykind)
        {
       default:
          break;
        }

        // Value type destructor.
switch (yykind)
    {
      case symbol_kind::S_TOKEN_CELL_VALUE: // TOKEN_CELL_VALUE
        value.template destroy< CellValue > ();
        break;

      case symbol_kind::S_cond_branch: // cond_branch
        value.template destroy< ConditionBranch > ();
        break;

      case symbol_kind::S_func_def: // func_def
      case symbol_kind::S_func_header: // func_header
        value.template destroy< FuncDecl > ();
        break;

      case symbol_kind::S_var_item: // var_item
        value.template destroy< VarDecl > ();
        break;

      case symbol_kind::S_type_spec: // type_spec
        value.template destroy< VarDecl::VarType > ();
        break;

      case symbol_kind::S_TOKEN_BOOL: // TOKEN_BOOL
      case symbol_kind::S_TOKEN_BOOL_LIT: // TOKEN_BOOL_LIT
      case symbol_kind::S_opt_const: // opt_const
        value.template destroy< bool > ();
        break;

      case symbol_kind::S_expr: // expr
      case symbol_kind::S_primary_expr: // primary_expr
      case symbol_kind::S_var_ref: // var_ref
        value.template destroy< expr_ptr > ();
        break;

      case symbol_kind::S_TOKEN_INT_LIT: // TOKEN_INT_LIT
        value.template destroy< int > ();
        break;

      case symbol_kind::S_TOKEN_MAIN: // TOKEN_MAIN
      case symbol_kind::S_TOKEN_STRING: // TOKEN_STRING
      case symbol_kind::S_TOKEN_IDENTIFIER: // TOKEN_IDENTIFIER
        value.template destroy< std::string > ();
        break;

      case symbol_kind::S_cond_list: // cond_list
        value.template destroy< std::vector<ConditionBranch> > ();
        break;

      case symbol_kind::S_var_list: // var_list
        value.template destroy< std::vector<VarDecl> > ();
        break;

      case symbol_kind::S_opt_init_values: // opt_init_values
      case symbol_kind::S_value_list: // value_list
      case symbol_kind::S_var_ref_list: // var_ref_list
      case symbol_kind::S_opt_expr_list: // opt_expr_list
      case symbol_kind::S_expr_list: // expr_list
      case symbol_kind::S_dim_ref_list: // dim_ref_list
        value.template destroy< std::vector<expr_ptr> > ();
        break;

      case symbol_kind::S_opt_dimensions: // opt_dimensions
      case symbol_kind::S_dims_list: // dims_list
        value.template destroy< std::vector<int> > ();
        break;

      case symbol_kind::S_stmt_list: // stmt_list
        value.template destroy< std::vector<stmt_ptr> > ();
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
        value.template destroy< stmt_ptr > ();
        break;

      default:
        break;
    }

        Base::clear ();
      }

      /// The user-facing name of this symbol.
      std::string name () const YY_NOEXCEPT
      {
        return  RobotParser ::symbol_name (this->kind ());
      }

      /// Backward compatibility (Bison 3.6).
      symbol_kind_type type_get () const YY_NOEXCEPT;

      /// Whether empty.
      bool empty () const YY_NOEXCEPT;

      /// Destructive move, \a s is emptied into this.
      void move (basic_symbol& s);

      /// The semantic value.
      value_type value;

      /// The location.
      location_type location;

    private:
#if YY_CPLUSPLUS < 201103L
      /// Assignment operator.
      basic_symbol& operator= (const basic_symbol& that);
#endif
    };

    /// Type access provider for token (enum) based symbols.
    struct by_kind
    {
      /// The symbol kind as needed by the constructor.
      typedef token_kind_type kind_type;

      /// Default constructor.
      by_kind () YY_NOEXCEPT;

#if 201103L <= YY_CPLUSPLUS
      /// Move constructor.
      by_kind (by_kind&& that) YY_NOEXCEPT;
#endif

      /// Copy constructor.
      by_kind (const by_kind& that) YY_NOEXCEPT;

      /// Constructor from (external) token numbers.
      by_kind (kind_type t) YY_NOEXCEPT;



      /// Record that this symbol is empty.
      void clear () YY_NOEXCEPT;

      /// Steal the symbol kind from \a that.
      void move (by_kind& that);

      /// The (internal) type number (corresponding to \a type).
      /// \a empty when empty.
      symbol_kind_type kind () const YY_NOEXCEPT;

      /// Backward compatibility (Bison 3.6).
      symbol_kind_type type_get () const YY_NOEXCEPT;

      /// The symbol kind.
      /// \a S_YYEMPTY when empty.
      symbol_kind_type kind_;
    };

    /// Backward compatibility for a private implementation detail (Bison 3.6).
    typedef by_kind by_type;

    /// "External" symbols: returned by the scanner.
    struct symbol_type : basic_symbol<by_kind>
    {
      /// Superclass.
      typedef basic_symbol<by_kind> super_type;

      /// Empty symbol.
      symbol_type () YY_NOEXCEPT {}

      /// Constructor for valueless symbols, and symbols from each type.
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, location_type l)
        : super_type (token_kind_type (tok), std::move (l))
#else
      symbol_type (int tok, const location_type& l)
        : super_type (token_kind_type (tok), l)
#endif
      {}
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, CellValue v, location_type l)
        : super_type (token_kind_type (tok), std::move (v), std::move (l))
#else
      symbol_type (int tok, const CellValue& v, const location_type& l)
        : super_type (token_kind_type (tok), v, l)
#endif
      {}
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, bool v, location_type l)
        : super_type (token_kind_type (tok), std::move (v), std::move (l))
#else
      symbol_type (int tok, const bool& v, const location_type& l)
        : super_type (token_kind_type (tok), v, l)
#endif
      {}
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, int v, location_type l)
        : super_type (token_kind_type (tok), std::move (v), std::move (l))
#else
      symbol_type (int tok, const int& v, const location_type& l)
        : super_type (token_kind_type (tok), v, l)
#endif
      {}
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, std::string v, location_type l)
        : super_type (token_kind_type (tok), std::move (v), std::move (l))
#else
      symbol_type (int tok, const std::string& v, const location_type& l)
        : super_type (token_kind_type (tok), v, l)
#endif
      {}
    };

    /// Build a parser object.
     RobotParser  (yy::RobotLexer& lexer_yyarg);
    virtual ~ RobotParser  ();

#if 201103L <= YY_CPLUSPLUS
    /// Non copyable.
     RobotParser  (const  RobotParser &) = delete;
    /// Non copyable.
     RobotParser & operator= (const  RobotParser &) = delete;
#endif

    /// Parse.  An alias for parse ().
    /// \returns  0 iff parsing succeeded.
    int operator() ();

    /// Parse.
    /// \returns  0 iff parsing succeeded.
    virtual int parse ();

#if YYDEBUG
    /// The current debugging stream.
    std::ostream& debug_stream () const YY_ATTRIBUTE_PURE;
    /// Set the current debugging stream.
    void set_debug_stream (std::ostream &);

    /// Type for debugging levels.
    typedef int debug_level_type;
    /// The current debugging level.
    debug_level_type debug_level () const YY_ATTRIBUTE_PURE;
    /// Set the current debugging level.
    void set_debug_level (debug_level_type l);
#endif

    /// Report a syntax error.
    /// \param loc    where the syntax error is found.
    /// \param msg    a description of the syntax error.
    virtual void error (const location_type& loc, const std::string& msg);

    /// Report a syntax error.
    void error (const syntax_error& err);

    /// The user-facing name of the symbol whose (internal) number is
    /// YYSYMBOL.  No bounds checking.
    static std::string symbol_name (symbol_kind_type yysymbol);

    // Implementation of make_symbol for each token kind.
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_YYEOF (location_type l)
      {
        return symbol_type (token::YYEOF, std::move (l));
      }
#else
      static
      symbol_type
      make_YYEOF (const location_type& l)
      {
        return symbol_type (token::YYEOF, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_YYerror (location_type l)
      {
        return symbol_type (token::YYerror, std::move (l));
      }
#else
      static
      symbol_type
      make_YYerror (const location_type& l)
      {
        return symbol_type (token::YYerror, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_YYUNDEF (location_type l)
      {
        return symbol_type (token::YYUNDEF, std::move (l));
      }
#else
      static
      symbol_type
      make_YYUNDEF (const location_type& l)
      {
        return symbol_type (token::YYUNDEF, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOKEN_PROGRAM_OPEN (location_type l)
      {
        return symbol_type (token::TOKEN_PROGRAM_OPEN, std::move (l));
      }
#else
      static
      symbol_type
      make_TOKEN_PROGRAM_OPEN (const location_type& l)
      {
        return symbol_type (token::TOKEN_PROGRAM_OPEN, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOKEN_PROGRAM_CLOSE (location_type l)
      {
        return symbol_type (token::TOKEN_PROGRAM_CLOSE, std::move (l));
      }
#else
      static
      symbol_type
      make_TOKEN_PROGRAM_CLOSE (const location_type& l)
      {
        return symbol_type (token::TOKEN_PROGRAM_CLOSE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOKEN_VARDECL_OPEN (location_type l)
      {
        return symbol_type (token::TOKEN_VARDECL_OPEN, std::move (l));
      }
#else
      static
      symbol_type
      make_TOKEN_VARDECL_OPEN (const location_type& l)
      {
        return symbol_type (token::TOKEN_VARDECL_OPEN, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOKEN_VARDECL_CLOSE (location_type l)
      {
        return symbol_type (token::TOKEN_VARDECL_CLOSE, std::move (l));
      }
#else
      static
      symbol_type
      make_TOKEN_VARDECL_CLOSE (const location_type& l)
      {
        return symbol_type (token::TOKEN_VARDECL_CLOSE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOKEN_VAR_OPEN (location_type l)
      {
        return symbol_type (token::TOKEN_VAR_OPEN, std::move (l));
      }
#else
      static
      symbol_type
      make_TOKEN_VAR_OPEN (const location_type& l)
      {
        return symbol_type (token::TOKEN_VAR_OPEN, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOKEN_VAR_CLOSE (location_type l)
      {
        return symbol_type (token::TOKEN_VAR_CLOSE, std::move (l));
      }
#else
      static
      symbol_type
      make_TOKEN_VAR_CLOSE (const location_type& l)
      {
        return symbol_type (token::TOKEN_VAR_CLOSE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOKEN_FUNC_OPEN (location_type l)
      {
        return symbol_type (token::TOKEN_FUNC_OPEN, std::move (l));
      }
#else
      static
      symbol_type
      make_TOKEN_FUNC_OPEN (const location_type& l)
      {
        return symbol_type (token::TOKEN_FUNC_OPEN, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOKEN_FUNC_CLOSE (location_type l)
      {
        return symbol_type (token::TOKEN_FUNC_CLOSE, std::move (l));
      }
#else
      static
      symbol_type
      make_TOKEN_FUNC_CLOSE (const location_type& l)
      {
        return symbol_type (token::TOKEN_FUNC_CLOSE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOKEN_MAIN (std::string v, location_type l)
      {
        return symbol_type (token::TOKEN_MAIN, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_TOKEN_MAIN (const std::string& v, const location_type& l)
      {
        return symbol_type (token::TOKEN_MAIN, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOKEN_CALL_OPEN (location_type l)
      {
        return symbol_type (token::TOKEN_CALL_OPEN, std::move (l));
      }
#else
      static
      symbol_type
      make_TOKEN_CALL_OPEN (const location_type& l)
      {
        return symbol_type (token::TOKEN_CALL_OPEN, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOKEN_CALL_CLOSE (location_type l)
      {
        return symbol_type (token::TOKEN_CALL_CLOSE, std::move (l));
      }
#else
      static
      symbol_type
      make_TOKEN_CALL_CLOSE (const location_type& l)
      {
        return symbol_type (token::TOKEN_CALL_CLOSE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOKEN_NAME_ATTR (location_type l)
      {
        return symbol_type (token::TOKEN_NAME_ATTR, std::move (l));
      }
#else
      static
      symbol_type
      make_TOKEN_NAME_ATTR (const location_type& l)
      {
        return symbol_type (token::TOKEN_NAME_ATTR, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOKEN_CONST (location_type l)
      {
        return symbol_type (token::TOKEN_CONST, std::move (l));
      }
#else
      static
      symbol_type
      make_TOKEN_CONST (const location_type& l)
      {
        return symbol_type (token::TOKEN_CONST, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOKEN_COUNT (location_type l)
      {
        return symbol_type (token::TOKEN_COUNT, std::move (l));
      }
#else
      static
      symbol_type
      make_TOKEN_COUNT (const location_type& l)
      {
        return symbol_type (token::TOKEN_COUNT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOKEN_STRING (std::string v, location_type l)
      {
        return symbol_type (token::TOKEN_STRING, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_TOKEN_STRING (const std::string& v, const location_type& l)
      {
        return symbol_type (token::TOKEN_STRING, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOKEN_BOOL (bool v, location_type l)
      {
        return symbol_type (token::TOKEN_BOOL, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_TOKEN_BOOL (const bool& v, const location_type& l)
      {
        return symbol_type (token::TOKEN_BOOL, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOKEN_TYPE_OPEN (location_type l)
      {
        return symbol_type (token::TOKEN_TYPE_OPEN, std::move (l));
      }
#else
      static
      symbol_type
      make_TOKEN_TYPE_OPEN (const location_type& l)
      {
        return symbol_type (token::TOKEN_TYPE_OPEN, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOKEN_TYPE_CLOSE (location_type l)
      {
        return symbol_type (token::TOKEN_TYPE_CLOSE, std::move (l));
      }
#else
      static
      symbol_type
      make_TOKEN_TYPE_CLOSE (const location_type& l)
      {
        return symbol_type (token::TOKEN_TYPE_CLOSE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOKEN_TYPE_INT (location_type l)
      {
        return symbol_type (token::TOKEN_TYPE_INT, std::move (l));
      }
#else
      static
      symbol_type
      make_TOKEN_TYPE_INT (const location_type& l)
      {
        return symbol_type (token::TOKEN_TYPE_INT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOKEN_TYPE_BOOL (location_type l)
      {
        return symbol_type (token::TOKEN_TYPE_BOOL, std::move (l));
      }
#else
      static
      symbol_type
      make_TOKEN_TYPE_BOOL (const location_type& l)
      {
        return symbol_type (token::TOKEN_TYPE_BOOL, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOKEN_TYPE_CELL (location_type l)
      {
        return symbol_type (token::TOKEN_TYPE_CELL, std::move (l));
      }
#else
      static
      symbol_type
      make_TOKEN_TYPE_CELL (const location_type& l)
      {
        return symbol_type (token::TOKEN_TYPE_CELL, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOKEN_CELL_VALUE (CellValue v, location_type l)
      {
        return symbol_type (token::TOKEN_CELL_VALUE, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_TOKEN_CELL_VALUE (const CellValue& v, const location_type& l)
      {
        return symbol_type (token::TOKEN_CELL_VALUE, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOKEN_DIMENSIONS_OPEN (location_type l)
      {
        return symbol_type (token::TOKEN_DIMENSIONS_OPEN, std::move (l));
      }
#else
      static
      symbol_type
      make_TOKEN_DIMENSIONS_OPEN (const location_type& l)
      {
        return symbol_type (token::TOKEN_DIMENSIONS_OPEN, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOKEN_DIMENSIONS_CLOSE (location_type l)
      {
        return symbol_type (token::TOKEN_DIMENSIONS_CLOSE, std::move (l));
      }
#else
      static
      symbol_type
      make_TOKEN_DIMENSIONS_CLOSE (const location_type& l)
      {
        return symbol_type (token::TOKEN_DIMENSIONS_CLOSE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOKEN_DIMENSION_OPEN (location_type l)
      {
        return symbol_type (token::TOKEN_DIMENSION_OPEN, std::move (l));
      }
#else
      static
      symbol_type
      make_TOKEN_DIMENSION_OPEN (const location_type& l)
      {
        return symbol_type (token::TOKEN_DIMENSION_OPEN, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOKEN_DIMENSION_CLOSE (location_type l)
      {
        return symbol_type (token::TOKEN_DIMENSION_CLOSE, std::move (l));
      }
#else
      static
      symbol_type
      make_TOKEN_DIMENSION_CLOSE (const location_type& l)
      {
        return symbol_type (token::TOKEN_DIMENSION_CLOSE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOKEN_VALUES_OPEN (location_type l)
      {
        return symbol_type (token::TOKEN_VALUES_OPEN, std::move (l));
      }
#else
      static
      symbol_type
      make_TOKEN_VALUES_OPEN (const location_type& l)
      {
        return symbol_type (token::TOKEN_VALUES_OPEN, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOKEN_VALUES_CLOSE (location_type l)
      {
        return symbol_type (token::TOKEN_VALUES_CLOSE, std::move (l));
      }
#else
      static
      symbol_type
      make_TOKEN_VALUES_CLOSE (const location_type& l)
      {
        return symbol_type (token::TOKEN_VALUES_CLOSE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOKEN_VALUE_OPEN (location_type l)
      {
        return symbol_type (token::TOKEN_VALUE_OPEN, std::move (l));
      }
#else
      static
      symbol_type
      make_TOKEN_VALUE_OPEN (const location_type& l)
      {
        return symbol_type (token::TOKEN_VALUE_OPEN, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOKEN_VALUE_CLOSE (location_type l)
      {
        return symbol_type (token::TOKEN_VALUE_CLOSE, std::move (l));
      }
#else
      static
      symbol_type
      make_TOKEN_VALUE_CLOSE (const location_type& l)
      {
        return symbol_type (token::TOKEN_VALUE_CLOSE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOKEN_DIM_OPEN (location_type l)
      {
        return symbol_type (token::TOKEN_DIM_OPEN, std::move (l));
      }
#else
      static
      symbol_type
      make_TOKEN_DIM_OPEN (const location_type& l)
      {
        return symbol_type (token::TOKEN_DIM_OPEN, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOKEN_DIM_CLOSE (location_type l)
      {
        return symbol_type (token::TOKEN_DIM_CLOSE, std::move (l));
      }
#else
      static
      symbol_type
      make_TOKEN_DIM_CLOSE (const location_type& l)
      {
        return symbol_type (token::TOKEN_DIM_CLOSE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOKEN_INDEX_OPEN (location_type l)
      {
        return symbol_type (token::TOKEN_INDEX_OPEN, std::move (l));
      }
#else
      static
      symbol_type
      make_TOKEN_INDEX_OPEN (const location_type& l)
      {
        return symbol_type (token::TOKEN_INDEX_OPEN, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOKEN_INDEX_CLOSE (location_type l)
      {
        return symbol_type (token::TOKEN_INDEX_CLOSE, std::move (l));
      }
#else
      static
      symbol_type
      make_TOKEN_INDEX_CLOSE (const location_type& l)
      {
        return symbol_type (token::TOKEN_INDEX_CLOSE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOKEN_ASSIGN_OPEN (location_type l)
      {
        return symbol_type (token::TOKEN_ASSIGN_OPEN, std::move (l));
      }
#else
      static
      symbol_type
      make_TOKEN_ASSIGN_OPEN (const location_type& l)
      {
        return symbol_type (token::TOKEN_ASSIGN_OPEN, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOKEN_ASSIGN_CLOSE (location_type l)
      {
        return symbol_type (token::TOKEN_ASSIGN_CLOSE, std::move (l));
      }
#else
      static
      symbol_type
      make_TOKEN_ASSIGN_CLOSE (const location_type& l)
      {
        return symbol_type (token::TOKEN_ASSIGN_CLOSE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOKEN_TO_OPEN (location_type l)
      {
        return symbol_type (token::TOKEN_TO_OPEN, std::move (l));
      }
#else
      static
      symbol_type
      make_TOKEN_TO_OPEN (const location_type& l)
      {
        return symbol_type (token::TOKEN_TO_OPEN, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOKEN_TO_CLOSE (location_type l)
      {
        return symbol_type (token::TOKEN_TO_CLOSE, std::move (l));
      }
#else
      static
      symbol_type
      make_TOKEN_TO_CLOSE (const location_type& l)
      {
        return symbol_type (token::TOKEN_TO_CLOSE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOKEN_WHILE_OPEN (location_type l)
      {
        return symbol_type (token::TOKEN_WHILE_OPEN, std::move (l));
      }
#else
      static
      symbol_type
      make_TOKEN_WHILE_OPEN (const location_type& l)
      {
        return symbol_type (token::TOKEN_WHILE_OPEN, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOKEN_WHILE_CLOSE (location_type l)
      {
        return symbol_type (token::TOKEN_WHILE_CLOSE, std::move (l));
      }
#else
      static
      symbol_type
      make_TOKEN_WHILE_CLOSE (const location_type& l)
      {
        return symbol_type (token::TOKEN_WHILE_CLOSE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOKEN_DO_OPEN (location_type l)
      {
        return symbol_type (token::TOKEN_DO_OPEN, std::move (l));
      }
#else
      static
      symbol_type
      make_TOKEN_DO_OPEN (const location_type& l)
      {
        return symbol_type (token::TOKEN_DO_OPEN, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOKEN_DO_CLOSE (location_type l)
      {
        return symbol_type (token::TOKEN_DO_CLOSE, std::move (l));
      }
#else
      static
      symbol_type
      make_TOKEN_DO_CLOSE (const location_type& l)
      {
        return symbol_type (token::TOKEN_DO_CLOSE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOKEN_CHECK_OPEN (location_type l)
      {
        return symbol_type (token::TOKEN_CHECK_OPEN, std::move (l));
      }
#else
      static
      symbol_type
      make_TOKEN_CHECK_OPEN (const location_type& l)
      {
        return symbol_type (token::TOKEN_CHECK_OPEN, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOKEN_CHECK_CLOSE (location_type l)
      {
        return symbol_type (token::TOKEN_CHECK_CLOSE, std::move (l));
      }
#else
      static
      symbol_type
      make_TOKEN_CHECK_CLOSE (const location_type& l)
      {
        return symbol_type (token::TOKEN_CHECK_CLOSE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOKEN_SWITCH_OPEN (location_type l)
      {
        return symbol_type (token::TOKEN_SWITCH_OPEN, std::move (l));
      }
#else
      static
      symbol_type
      make_TOKEN_SWITCH_OPEN (const location_type& l)
      {
        return symbol_type (token::TOKEN_SWITCH_OPEN, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOKEN_SWITCH_CLOSE (location_type l)
      {
        return symbol_type (token::TOKEN_SWITCH_CLOSE, std::move (l));
      }
#else
      static
      symbol_type
      make_TOKEN_SWITCH_CLOSE (const location_type& l)
      {
        return symbol_type (token::TOKEN_SWITCH_CLOSE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOKEN_CONDITION_OPEN (location_type l)
      {
        return symbol_type (token::TOKEN_CONDITION_OPEN, std::move (l));
      }
#else
      static
      symbol_type
      make_TOKEN_CONDITION_OPEN (const location_type& l)
      {
        return symbol_type (token::TOKEN_CONDITION_OPEN, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOKEN_CONDITION_CLOSE (location_type l)
      {
        return symbol_type (token::TOKEN_CONDITION_CLOSE, std::move (l));
      }
#else
      static
      symbol_type
      make_TOKEN_CONDITION_CLOSE (const location_type& l)
      {
        return symbol_type (token::TOKEN_CONDITION_CLOSE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOKEN_LEFT_OPEN (location_type l)
      {
        return symbol_type (token::TOKEN_LEFT_OPEN, std::move (l));
      }
#else
      static
      symbol_type
      make_TOKEN_LEFT_OPEN (const location_type& l)
      {
        return symbol_type (token::TOKEN_LEFT_OPEN, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOKEN_LEFT_CLOSE (location_type l)
      {
        return symbol_type (token::TOKEN_LEFT_CLOSE, std::move (l));
      }
#else
      static
      symbol_type
      make_TOKEN_LEFT_CLOSE (const location_type& l)
      {
        return symbol_type (token::TOKEN_LEFT_CLOSE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOKEN_RIGHT_OPEN (location_type l)
      {
        return symbol_type (token::TOKEN_RIGHT_OPEN, std::move (l));
      }
#else
      static
      symbol_type
      make_TOKEN_RIGHT_OPEN (const location_type& l)
      {
        return symbol_type (token::TOKEN_RIGHT_OPEN, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOKEN_RIGHT_CLOSE (location_type l)
      {
        return symbol_type (token::TOKEN_RIGHT_CLOSE, std::move (l));
      }
#else
      static
      symbol_type
      make_TOKEN_RIGHT_CLOSE (const location_type& l)
      {
        return symbol_type (token::TOKEN_RIGHT_CLOSE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOKEN_UP_OPEN (location_type l)
      {
        return symbol_type (token::TOKEN_UP_OPEN, std::move (l));
      }
#else
      static
      symbol_type
      make_TOKEN_UP_OPEN (const location_type& l)
      {
        return symbol_type (token::TOKEN_UP_OPEN, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOKEN_UP_CLOSE (location_type l)
      {
        return symbol_type (token::TOKEN_UP_CLOSE, std::move (l));
      }
#else
      static
      symbol_type
      make_TOKEN_UP_CLOSE (const location_type& l)
      {
        return symbol_type (token::TOKEN_UP_CLOSE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOKEN_DOWN_OPEN (location_type l)
      {
        return symbol_type (token::TOKEN_DOWN_OPEN, std::move (l));
      }
#else
      static
      symbol_type
      make_TOKEN_DOWN_OPEN (const location_type& l)
      {
        return symbol_type (token::TOKEN_DOWN_OPEN, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOKEN_DOWN_CLOSE (location_type l)
      {
        return symbol_type (token::TOKEN_DOWN_CLOSE, std::move (l));
      }
#else
      static
      symbol_type
      make_TOKEN_DOWN_CLOSE (const location_type& l)
      {
        return symbol_type (token::TOKEN_DOWN_CLOSE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOKEN_SENDDRONS_OPEN (location_type l)
      {
        return symbol_type (token::TOKEN_SENDDRONS_OPEN, std::move (l));
      }
#else
      static
      symbol_type
      make_TOKEN_SENDDRONS_OPEN (const location_type& l)
      {
        return symbol_type (token::TOKEN_SENDDRONS_OPEN, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOKEN_SENDDRONS_CLOSE (location_type l)
      {
        return symbol_type (token::TOKEN_SENDDRONS_CLOSE, std::move (l));
      }
#else
      static
      symbol_type
      make_TOKEN_SENDDRONS_CLOSE (const location_type& l)
      {
        return symbol_type (token::TOKEN_SENDDRONS_CLOSE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOKEN_GETDRONSCOUNT_OPEN (location_type l)
      {
        return symbol_type (token::TOKEN_GETDRONSCOUNT_OPEN, std::move (l));
      }
#else
      static
      symbol_type
      make_TOKEN_GETDRONSCOUNT_OPEN (const location_type& l)
      {
        return symbol_type (token::TOKEN_GETDRONSCOUNT_OPEN, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOKEN_GETDRONSCOUNT_CLOSE (location_type l)
      {
        return symbol_type (token::TOKEN_GETDRONSCOUNT_CLOSE, std::move (l));
      }
#else
      static
      symbol_type
      make_TOKEN_GETDRONSCOUNT_CLOSE (const location_type& l)
      {
        return symbol_type (token::TOKEN_GETDRONSCOUNT_CLOSE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOKEN_ADD_OPEN (location_type l)
      {
        return symbol_type (token::TOKEN_ADD_OPEN, std::move (l));
      }
#else
      static
      symbol_type
      make_TOKEN_ADD_OPEN (const location_type& l)
      {
        return symbol_type (token::TOKEN_ADD_OPEN, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOKEN_ADD_CLOSE (location_type l)
      {
        return symbol_type (token::TOKEN_ADD_CLOSE, std::move (l));
      }
#else
      static
      symbol_type
      make_TOKEN_ADD_CLOSE (const location_type& l)
      {
        return symbol_type (token::TOKEN_ADD_CLOSE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOKEN_MUL_OPEN (location_type l)
      {
        return symbol_type (token::TOKEN_MUL_OPEN, std::move (l));
      }
#else
      static
      symbol_type
      make_TOKEN_MUL_OPEN (const location_type& l)
      {
        return symbol_type (token::TOKEN_MUL_OPEN, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOKEN_MUL_CLOSE (location_type l)
      {
        return symbol_type (token::TOKEN_MUL_CLOSE, std::move (l));
      }
#else
      static
      symbol_type
      make_TOKEN_MUL_CLOSE (const location_type& l)
      {
        return symbol_type (token::TOKEN_MUL_CLOSE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOKEN_SUB_OPEN (location_type l)
      {
        return symbol_type (token::TOKEN_SUB_OPEN, std::move (l));
      }
#else
      static
      symbol_type
      make_TOKEN_SUB_OPEN (const location_type& l)
      {
        return symbol_type (token::TOKEN_SUB_OPEN, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOKEN_SUB_CLOSE (location_type l)
      {
        return symbol_type (token::TOKEN_SUB_CLOSE, std::move (l));
      }
#else
      static
      symbol_type
      make_TOKEN_SUB_CLOSE (const location_type& l)
      {
        return symbol_type (token::TOKEN_SUB_CLOSE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOKEN_DIV_OPEN (location_type l)
      {
        return symbol_type (token::TOKEN_DIV_OPEN, std::move (l));
      }
#else
      static
      symbol_type
      make_TOKEN_DIV_OPEN (const location_type& l)
      {
        return symbol_type (token::TOKEN_DIV_OPEN, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOKEN_DIV_CLOSE (location_type l)
      {
        return symbol_type (token::TOKEN_DIV_CLOSE, std::move (l));
      }
#else
      static
      symbol_type
      make_TOKEN_DIV_CLOSE (const location_type& l)
      {
        return symbol_type (token::TOKEN_DIV_CLOSE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOKEN_NOT_OPEN (location_type l)
      {
        return symbol_type (token::TOKEN_NOT_OPEN, std::move (l));
      }
#else
      static
      symbol_type
      make_TOKEN_NOT_OPEN (const location_type& l)
      {
        return symbol_type (token::TOKEN_NOT_OPEN, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOKEN_NOT_CLOSE (location_type l)
      {
        return symbol_type (token::TOKEN_NOT_CLOSE, std::move (l));
      }
#else
      static
      symbol_type
      make_TOKEN_NOT_CLOSE (const location_type& l)
      {
        return symbol_type (token::TOKEN_NOT_CLOSE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOKEN_OR_OPEN (location_type l)
      {
        return symbol_type (token::TOKEN_OR_OPEN, std::move (l));
      }
#else
      static
      symbol_type
      make_TOKEN_OR_OPEN (const location_type& l)
      {
        return symbol_type (token::TOKEN_OR_OPEN, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOKEN_OR_CLOSE (location_type l)
      {
        return symbol_type (token::TOKEN_OR_CLOSE, std::move (l));
      }
#else
      static
      symbol_type
      make_TOKEN_OR_CLOSE (const location_type& l)
      {
        return symbol_type (token::TOKEN_OR_CLOSE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOKEN_AND_OPEN (location_type l)
      {
        return symbol_type (token::TOKEN_AND_OPEN, std::move (l));
      }
#else
      static
      symbol_type
      make_TOKEN_AND_OPEN (const location_type& l)
      {
        return symbol_type (token::TOKEN_AND_OPEN, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOKEN_AND_CLOSE (location_type l)
      {
        return symbol_type (token::TOKEN_AND_CLOSE, std::move (l));
      }
#else
      static
      symbol_type
      make_TOKEN_AND_CLOSE (const location_type& l)
      {
        return symbol_type (token::TOKEN_AND_CLOSE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOKEN_MAX_OPEN (location_type l)
      {
        return symbol_type (token::TOKEN_MAX_OPEN, std::move (l));
      }
#else
      static
      symbol_type
      make_TOKEN_MAX_OPEN (const location_type& l)
      {
        return symbol_type (token::TOKEN_MAX_OPEN, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOKEN_MAX_CLOSE (location_type l)
      {
        return symbol_type (token::TOKEN_MAX_CLOSE, std::move (l));
      }
#else
      static
      symbol_type
      make_TOKEN_MAX_CLOSE (const location_type& l)
      {
        return symbol_type (token::TOKEN_MAX_CLOSE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOKEN_MIN_OPEN (location_type l)
      {
        return symbol_type (token::TOKEN_MIN_OPEN, std::move (l));
      }
#else
      static
      symbol_type
      make_TOKEN_MIN_OPEN (const location_type& l)
      {
        return symbol_type (token::TOKEN_MIN_OPEN, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOKEN_MIN_CLOSE (location_type l)
      {
        return symbol_type (token::TOKEN_MIN_CLOSE, std::move (l));
      }
#else
      static
      symbol_type
      make_TOKEN_MIN_CLOSE (const location_type& l)
      {
        return symbol_type (token::TOKEN_MIN_CLOSE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOKEN_EQ_OPEN (location_type l)
      {
        return symbol_type (token::TOKEN_EQ_OPEN, std::move (l));
      }
#else
      static
      symbol_type
      make_TOKEN_EQ_OPEN (const location_type& l)
      {
        return symbol_type (token::TOKEN_EQ_OPEN, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOKEN_EQ_CLOSE (location_type l)
      {
        return symbol_type (token::TOKEN_EQ_CLOSE, std::move (l));
      }
#else
      static
      symbol_type
      make_TOKEN_EQ_CLOSE (const location_type& l)
      {
        return symbol_type (token::TOKEN_EQ_CLOSE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOKEN_BOOL_LIT (bool v, location_type l)
      {
        return symbol_type (token::TOKEN_BOOL_LIT, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_TOKEN_BOOL_LIT (const bool& v, const location_type& l)
      {
        return symbol_type (token::TOKEN_BOOL_LIT, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOKEN_INT_LIT (int v, location_type l)
      {
        return symbol_type (token::TOKEN_INT_LIT, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_TOKEN_INT_LIT (const int& v, const location_type& l)
      {
        return symbol_type (token::TOKEN_INT_LIT, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOKEN_IDENTIFIER (std::string v, location_type l)
      {
        return symbol_type (token::TOKEN_IDENTIFIER, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_TOKEN_IDENTIFIER (const std::string& v, const location_type& l)
      {
        return symbol_type (token::TOKEN_IDENTIFIER, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOKEN_SELFCLOSE (location_type l)
      {
        return symbol_type (token::TOKEN_SELFCLOSE, std::move (l));
      }
#else
      static
      symbol_type
      make_TOKEN_SELFCLOSE (const location_type& l)
      {
        return symbol_type (token::TOKEN_SELFCLOSE, l);
      }
#endif


    class context
    {
    public:
      context (const  RobotParser & yyparser, const symbol_type& yyla);
      const symbol_type& lookahead () const YY_NOEXCEPT { return yyla_; }
      symbol_kind_type token () const YY_NOEXCEPT { return yyla_.kind (); }
      const location_type& location () const YY_NOEXCEPT { return yyla_.location; }

      /// Put in YYARG at most YYARGN of the expected tokens, and return the
      /// number of tokens stored in YYARG.  If YYARG is null, return the
      /// number of expected tokens (guaranteed to be less than YYNTOKENS).
      int expected_tokens (symbol_kind_type yyarg[], int yyargn) const;

    private:
      const  RobotParser & yyparser_;
      const symbol_type& yyla_;
    };

  private:
#if YY_CPLUSPLUS < 201103L
    /// Non copyable.
     RobotParser  (const  RobotParser &);
    /// Non copyable.
     RobotParser & operator= (const  RobotParser &);
#endif


    /// Stored state numbers (used for stacks).
    typedef unsigned char state_type;

    /// The arguments of the error message.
    int yy_syntax_error_arguments_ (const context& yyctx,
                                    symbol_kind_type yyarg[], int yyargn) const;

    /// Generate an error message.
    /// \param yyctx     the context in which the error occurred.
    virtual std::string yysyntax_error_ (const context& yyctx) const;
    /// Compute post-reduction state.
    /// \param yystate   the current state
    /// \param yysym     the nonterminal to push on the stack
    static state_type yy_lr_goto_state_ (state_type yystate, int yysym);

    /// Whether the given \c yypact_ value indicates a defaulted state.
    /// \param yyvalue   the value to check
    static bool yy_pact_value_is_default_ (int yyvalue) YY_NOEXCEPT;

    /// Whether the given \c yytable_ value indicates a syntax error.
    /// \param yyvalue   the value to check
    static bool yy_table_value_is_error_ (int yyvalue) YY_NOEXCEPT;

    static const signed char yypact_ninf_;
    static const signed char yytable_ninf_;

    /// Convert a scanner token kind \a t to a symbol kind.
    /// In theory \a t should be a token_kind_type, but character literals
    /// are valid, yet not members of the token_kind_type enum.
    static symbol_kind_type yytranslate_ (int t) YY_NOEXCEPT;

    /// Convert the symbol name \a n to a form suitable for a diagnostic.
    static std::string yytnamerr_ (const char *yystr);

    /// For a symbol, its name in clear.
    static const char* const yytname_[];


    // Tables.
    // YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
    // STATE-NUM.
    static const short yypact_[];

    // YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
    // Performed when YYTABLE does not specify something else to do.  Zero
    // means the default is an error.
    static const signed char yydefact_[];

    // YYPGOTO[NTERM-NUM].
    static const short yypgoto_[];

    // YYDEFGOTO[NTERM-NUM].
    static const unsigned char yydefgoto_[];

    // YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
    // positive, shift that token.  If negative, reduce the rule whose
    // number is the opposite.  If YYTABLE_NINF, syntax error.
    static const unsigned char yytable_[];

    static const short yycheck_[];

    // YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
    // state STATE-NUM.
    static const signed char yystos_[];

    // YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.
    static const signed char yyr1_[];

    // YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.
    static const signed char yyr2_[];


#if YYDEBUG
    // YYRLINE[YYN] -- Source line where rule number YYN was defined.
    static const short yyrline_[];
    /// Report on the debug stream that the rule \a r is going to be reduced.
    virtual void yy_reduce_print_ (int r) const;
    /// Print the state stack on the debug stream.
    virtual void yy_stack_print_ () const;

    /// Debugging level.
    int yydebug_;
    /// Debug stream.
    std::ostream* yycdebug_;

    /// \brief Display a symbol kind, value and location.
    /// \param yyo    The output stream.
    /// \param yysym  The symbol.
    template <typename Base>
    void yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const;
#endif

    /// \brief Reclaim the memory associated to a symbol.
    /// \param yymsg     Why this token is reclaimed.
    ///                  If null, print nothing.
    /// \param yysym     The symbol.
    template <typename Base>
    void yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const;

  private:
    /// Type access provider for state based symbols.
    struct by_state
    {
      /// Default constructor.
      by_state () YY_NOEXCEPT;

      /// The symbol kind as needed by the constructor.
      typedef state_type kind_type;

      /// Constructor.
      by_state (kind_type s) YY_NOEXCEPT;

      /// Copy constructor.
      by_state (const by_state& that) YY_NOEXCEPT;

      /// Record that this symbol is empty.
      void clear () YY_NOEXCEPT;

      /// Steal the symbol kind from \a that.
      void move (by_state& that);

      /// The symbol kind (corresponding to \a state).
      /// \a symbol_kind::S_YYEMPTY when empty.
      symbol_kind_type kind () const YY_NOEXCEPT;

      /// The state number used to denote an empty symbol.
      /// We use the initial state, as it does not have a value.
      enum { empty_state = 0 };

      /// The state.
      /// \a empty when empty.
      state_type state;
    };

    /// "Internal" symbol: element of the stack.
    struct stack_symbol_type : basic_symbol<by_state>
    {
      /// Superclass.
      typedef basic_symbol<by_state> super_type;
      /// Construct an empty symbol.
      stack_symbol_type ();
      /// Move or copy construction.
      stack_symbol_type (YY_RVREF (stack_symbol_type) that);
      /// Steal the contents from \a sym to build this.
      stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) sym);
#if YY_CPLUSPLUS < 201103L
      /// Assignment, needed by push_back by some old implementations.
      /// Moves the contents of that.
      stack_symbol_type& operator= (stack_symbol_type& that);

      /// Assignment, needed by push_back by other implementations.
      /// Needed by some other old implementations.
      stack_symbol_type& operator= (const stack_symbol_type& that);
#endif
    };

    /// A stack with random access from its top.
    template <typename T, typename S = std::vector<T> >
    class stack
    {
    public:
      // Hide our reversed order.
      typedef typename S::iterator iterator;
      typedef typename S::const_iterator const_iterator;
      typedef typename S::size_type size_type;
      typedef typename std::ptrdiff_t index_type;

      stack (size_type n = 200) YY_NOEXCEPT
        : seq_ (n)
      {}

#if 201103L <= YY_CPLUSPLUS
      /// Non copyable.
      stack (const stack&) = delete;
      /// Non copyable.
      stack& operator= (const stack&) = delete;
#endif

      /// Random access.
      ///
      /// Index 0 returns the topmost element.
      const T&
      operator[] (index_type i) const
      {
        return seq_[size_type (size () - 1 - i)];
      }

      /// Random access.
      ///
      /// Index 0 returns the topmost element.
      T&
      operator[] (index_type i)
      {
        return seq_[size_type (size () - 1 - i)];
      }

      /// Steal the contents of \a t.
      ///
      /// Close to move-semantics.
      void
      push (YY_MOVE_REF (T) t)
      {
        seq_.push_back (T ());
        operator[] (0).move (t);
      }

      /// Pop elements from the stack.
      void
      pop (std::ptrdiff_t n = 1) YY_NOEXCEPT
      {
        for (; 0 < n; --n)
          seq_.pop_back ();
      }

      /// Pop all elements from the stack.
      void
      clear () YY_NOEXCEPT
      {
        seq_.clear ();
      }

      /// Number of elements on the stack.
      index_type
      size () const YY_NOEXCEPT
      {
        return index_type (seq_.size ());
      }

      /// Iterator on top of the stack (going downwards).
      const_iterator
      begin () const YY_NOEXCEPT
      {
        return seq_.begin ();
      }

      /// Bottom of the stack.
      const_iterator
      end () const YY_NOEXCEPT
      {
        return seq_.end ();
      }

      /// Present a slice of the top of a stack.
      class slice
      {
      public:
        slice (const stack& stack, index_type range) YY_NOEXCEPT
          : stack_ (stack)
          , range_ (range)
        {}

        const T&
        operator[] (index_type i) const
        {
          return stack_[range_ - i];
        }

      private:
        const stack& stack_;
        index_type range_;
      };

    private:
#if YY_CPLUSPLUS < 201103L
      /// Non copyable.
      stack (const stack&);
      /// Non copyable.
      stack& operator= (const stack&);
#endif
      /// The wrapped container.
      S seq_;
    };


    /// Stack type.
    typedef stack<stack_symbol_type> stack_type;

    /// The stack.
    stack_type yystack_;

    /// Push a new state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param sym  the symbol
    /// \warning the contents of \a s.value is stolen.
    void yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym);

    /// Push a new look ahead token on the state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param s    the state
    /// \param sym  the symbol (for its value and location).
    /// \warning the contents of \a sym.value is stolen.
    void yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym);

    /// Pop \a n symbols from the stack.
    void yypop_ (int n = 1) YY_NOEXCEPT;

    /// Constants.
    enum
    {
      yylast_ = 335,     ///< Last index in yytable_.
      yynnts_ = 33,  ///< Number of nonterminal symbols.
      yyfinal_ = 4 ///< Termination state number.
    };


    // User arguments.
    yy::RobotLexer& lexer;

  };


#line 91 "robot.ypp"
} //  yy 
#line 3009 "generated/robot.tab.hpp"


// "%code provides" blocks.
#line 19 "robot.ypp"
             // код доступен другим файлам
    void yyerror(const std::string& msg);
    extern yy::RobotLexer* THE_LEXER;

#line 3018 "generated/robot.tab.hpp"


#endif // !YY_YY_GENERATED_ROBOT_TAB_HPP_INCLUDED
