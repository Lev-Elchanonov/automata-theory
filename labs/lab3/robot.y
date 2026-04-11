%{
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void yyerror(const char* msg);
int yylex(void);

extern int line_num;
extern int error_count;
%}

%union{ // yylval
    int ival;
    char* sval;
}


%token  TOKEN_PROGRAMM_OPEN
%token  TOKEN_PROGRAMM_CLOSE

%token  TOKEN_VARDECL_OPEN
%token  TOKEN_VARDECL_CLOSE

%token  TOKEN_VAR_OPEN
%token  TOKEN_VAR_CLOSE

%token  TOKEN_FUNC_OPEN
%token  TOKEN_FUNC_CLOSE
    %token <sval> TOKEN_MAIN

%token  TOKEN_CALL_OPEN
%token  TOKEN_CALL_CLOSE

%token  TOKEN_NAME_ATTR
%token  TOKEN_CONST
%token  TOKEN_COUNT

%token <sval> TOKEN_STRING
%token <ival> TOKEN_BOOL

%token  TOKEN_TYPE_OPEN
%token  TOKEN_TYPE_CLOSE

%token  TOKEN_TYPE_INT
%token  TOKEN_TYPE_BOOL
%token  TOKEN_TYPE_CELL
    %token <ival> TOKEN_CELL_EMPTY
    %token <ival> TOKEN_CELL_WALL
    %token <ival> TOKEN_CELL_EXIT
    %token <ival> TOKEN_CELL_UNDEF

%token  TOKEN_DIMENSIONS_OPEN
%token  TOKEN_DIMENSIONS_CLOSE

%token  TOKEN_DIMENSION_OPEN
%token  TOKEN_DIMENSION_CLOSE

%token  TOKEN_VALUES_OPEN
%token  TOKEN_VALUES_CLOSE

%token  TOKEN_VALUE_OPEN
%token  TOKEN_VALUE_CLOSE

%token  TOKEN_DIM_OPEN
%token  TOKEN_DIM_CLOSE

%token  TOKEN_INDEX_OPEN
%token  TOKEN_INDEX_CLOSE

%token  TOKEN_ASSIGN_OPEN
%token  TOKEN_ASSIGN_CLOSE

%token  TOKEN_TO_OPEN
%token  TOKEN_TO_CLOSE

%token  TOKEN_WHILE_OPEN
%token  TOKEN_WHILE_CLOSE

%token  TOKEN_CHECK_OPEN
%token  TOKEN_CHECK_CLOSE

%token  TOKEN_DO_OPEN
%token  TOKEN_DO_CLOSE

%token  TOKEN_SWITCH_OPEN
%token  TOKEN_SWITCH_CLOSE

%token  TOKEN_CONDITION_OPEN
%token  TOKEN_CONDITION_CLOSE

%token  TOKEN_LEFT_OPEN
%token  TOKEN_LEFT_CLOSE

%token  TOKEN_RIGHT_OPEN
%token  TOKEN_RIGHT_CLOSE

%token  TOKEN_UP_OPEN
%token  TOKEN_UP_CLOSE

%token  TOKEN_DOWN_OPEN
%token  TOKEN_DOWN_CLOSE

%token  TOKEN_SENDDRONS_OPEN
%token  TOKEN_SENDDRONS_CLOSE

%token  TOKEN_GETDRONSCOUNT_OPEN
%token  TOKEN_GETDRONSCOUNT_CLOSE

%token  TOKEN_ADD_OPEN
%token  TOKEN_ADD_CLOSE

%token  TOKEN_MUL_OPEN
%token  TOKEN_MUL_CLOSE

%token  TOKEN_SUB_OPEN
%token  TOKEN_SUB_CLOSE

%token  TOKEN_DIV_OPEN
%token  TOKEN_DIV_CLOSE

%token  TOKEN_NOT_OPEN
%token  TOKEN_NOT_CLOSE

%token  TOKEN_OR_OPEN
%token  TOKEN_OR_END

%token  TOKEN_AND_OPEN
%token  TOKEN_AND_CLOSE

%token  TOKEN_MAX_OPEN
%token  TOKEN_MAX_CLOSE

%token  TOKEN_MIN_OPEN
%token  TOKEN_MIN_CLOSE

%token  TOKEN_EQ_OPEN
%token  TOKEN_EQ_CLOSE

%token <ival> TOKEN_BOOL_LIT
%token <ival> TOKEN_INT_LIT
%token <sval> TOKEN_IDENTIFIER

%token TOKEN_SELFCLOSE
