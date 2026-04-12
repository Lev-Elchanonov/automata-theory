%{
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void yyerror(const char* msg);
int yylex(void);

extern int line_num;
extern int error_count;
extern FILE *yyin;
int has_main = 0;

/* int RobotLexer::yylex(yy::RobotParser::semantic_type* yylval) */

typedef enum {
    TYPE_INT,
    TYPE_BOOL,
    TYPE_CELL
} DataType;

typedef enum {
    CELL_EMPTY = 0,
    CELL_WALL = 1,
    CELL_EXIT = 2,
    CELL_UNDEF = 3
} CellValue;

typedef struct Dimension{
    int max_index;
    struct Dimension* next;
} Dimension;

typedef struct Dimensions{
    int count;
    Dimension* dims;
} Dimensions;

typedef struct InitValue{
    InitValue* values;
} InitValue;

typedef struct VarDecl{
    char* name;
    int is_const;
    DataType type;
    Dimensions* dimensions;
    InitValues* init_values;
    struct VarDecl* next;
} VarDecl;

typedef struct VarRef{
    char* name;
    int* indices;
    int indices_count;
} VarRef;


%}


%union{ // yylval
    int ival;
    char* sval;
}


%token  TOKEN_PROGRAM_OPEN TOKEN_PROGRAM_CLOSE
%token  TOKEN_VARDECL_OPEN TOKEN_VARDECL_CLOSE
%token  TOKEN_VAR_OPEN TOKEN_VAR_CLOSE
%token  TOKEN_FUNC_OPEN TOKEN_FUNC_CLOSE
    %token <sval> TOKEN_MAIN
%token  TOKEN_CALL_OPEN TOKEN_CALL_CLOSE


%token  TOKEN_NAME_ATTR
%token  TOKEN_CONST
%token  TOKEN_COUNT

%token <sval> TOKEN_STRING
%token <ival> TOKEN_BOOL

%token  TOKEN_TYPE_OPEN TOKEN_TYPE_CLOSE

%token  TOKEN_TYPE_INT
%token  TOKEN_TYPE_BOOL
%token  TOKEN_TYPE_CELL
    %token <ival> TOKEN_CELL_EMPTY
    %token <ival> TOKEN_CELL_WALL
    %token <ival> TOKEN_CELL_EXIT
    %token <ival> TOKEN_CELL_UNDEF

%token  TOKEN_DIMENSIONS_OPEN TOKEN_DIMENSIONS_CLOSE
%token  TOKEN_DIMENSION_OPEN TOKEN_DIMENSION_CLOSE

%token  TOKEN_VALUES_OPEN TOKEN_VALUES_CLOSE
%token  TOKEN_VALUE_OPEN TOKEN_VALUE_CLOSE

%token  TOKEN_DIM_OPEN TOKEN_DIM_CLOSE
%token  TOKEN_INDEX_OPEN TOKEN_INDEX_CLOSE

%token  TOKEN_ASSIGN_OPEN TOKEN_ASSIGN_CLOSE

%token  TOKEN_TO_OPEN TOKEN_TO_CLOSE

%token  TOKEN_WHILE_OPEN TOKEN_WHILE_CLOSE
%token  TOKEN_DO_OPEN TOKEN_DO_CLOSE

%token  TOKEN_CHECK_OPEN TOKEN_CHECK_CLOSE

%token  TOKEN_SWITCH_OPEN TOKEN_SWITCH_CLOSE
%token  TOKEN_CONDITION_OPEN TOKEN_CONDITION_CLOSE

%token  TOKEN_LEFT_OPEN TOKEN_LEFT_CLOSE
%token  TOKEN_RIGHT_OPEN TOKEN_RIGHT_CLOSE
%token  TOKEN_UP_OPEN TOKEN_UP_CLOSE
%token  TOKEN_DOWN_OPEN TOKEN_DOWN_CLOSE

%token  TOKEN_SENDDRONS_OPEN TOKEN_SENDDRONS_CLOSE
%token  TOKEN_GETDRONSCOUNT_OPEN TOKEN_GETDRONSCOUNT_CLOSE

%token  TOKEN_ADD_OPEN TOKEN_ADD_CLOSE
%token  TOKEN_MUL_OPEN TOKEN_MUL_CLOSE
%token  TOKEN_SUB_OPEN TOKEN_SUB_CLOSE
%token  TOKEN_DIV_OPEN TOKEN_DIV_CLOSE

%token  TOKEN_NOT_OPEN TOKEN_NOT_CLOSE
%token  TOKEN_OR_OPEN TOKEN_OR_CLOSE
%token  TOKEN_AND_OPEN TOKEN_AND_CLOSE

%token  TOKEN_MAX_OPEN TOKEN_MAX_CLOSE
%token  TOKEN_MIN_OPEN TOKEN_MIN_CLOSE

%token  TOKEN_EQ_OPEN TOKEN_EQ_CLOSE

%token <ival> TOKEN_BOOL_LIT
%token <ival> TOKEN_INT_LIT
%token <sval> TOKEN_IDENTIFIER

%token TOKEN_SELFCLOSE

%left TOKEN_OR_OPEN
%left TOKEN_AND_OPEN
%right TOKEN_NOT_OPEN
%left TOKEN_EQ_OPEN
%left TOKEN_ADD_OPEN TOKEN_SUB_OPEN
%left TOKEN_MUL_OPEN TOKEN_DIV_OPEN

%%

program:
    TOKEN_PROGRAM_OPEN global_items TOKEN_PROGRAM_CLOSE
    {
        printf("PROGRAM PARSED SUCCESSFULLY\n");
        if (!has_main){
            fprintf(stderr, "SEMANTIC ERROR: function 'main' not found\n");
            exit(1);
        }
    }
;

global_items:
    | global_items vardecl_block
    | global_items func_def
;

vardecl_block:
    TOKEN_VARDECL_OPEN var_list TOKEN_VARDECL_CLOSE
    {
        prinf("Var declaration block\n");
    }
;

var_list:
    TOKEN_VAR_OPEN var_attrs '>' var_body TOKEN_VAR_CLOSE
    {
        printf("\tПеременная: %s\n", $2);
    }
;

var_attrs:
    TOKEN_NAME_ATTR TOKEN_STRING opt_const
    {
        printf("\tname = %s\n", $2);
        $$ = $2;
    }
;

opt_const:
    TOKEN_CONST TOKEN_BOOL
    {
        printf("\tconst = %s\n", $2 ? "TRUE" : "FALSE");
        $$ = $2;
    }
    |
    {
        $$ = 0; //false
    }
;

var_body:
    type opt_dimensions opt_values
    {
        printf("в var_body\n");
    }
;

type:
    TOKEN_TYPE_OPEN type_name TOKEN_TYPE_CLOSE
    {
        printf("поиск типа\n");
        $$ =
    }
;

type_name:
    TOKEN_TYPE_INT {printf("\tТип INT"); $$ = $1;}
    | TOKEN_TYPE_BOOL {printf("\tТип BOOL"); $$ = $1;}
    | TOKEN_TYPE_CELL {printf("\tТип CELL"); $$ = $1;}
;

opt_dimensions:
    {
        $$ = NULL
    }
    | TOKEN_DIMENSIONS_OPEN dims_attrs '>' TOKEN_DIMENSIONS_CLOSE
    {

    }
;

dims_attrs:
    TOKEN_COUNT TOKEN_INT_LIT
    {
        printf("\t размерность: %d\n", $2);
        $$ = $2;
    }
;

