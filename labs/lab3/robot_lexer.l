%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "robot.tab.h"

int line_num = 1;
int error_count = 0;
%}

DIGIT [0-9]
LETTER [a-zA-Z]
WHITESPACE [ \t\r]+
NEWLINE \n

%%

<PROGRAM>                   {return TOKEN_PROGRAM_OPEN;}
</PROGRAM>                  {return TOKEN_PROGRAM_CLOSE;}

<VARDECLARATION>            {return TOKEN_VARDECL_OPEN;}
</VARDECLARATION>           {return TOKEN_VARDECL_CLOSE;}

<VAR                        {return TOKEN_VAR_OPEN;}
</VAR>                      {return TOKEN_VAR_CLOSE;}

<FUNC                       {return TOKEN_FUNC_OPEN;}
</FUNC>                     {return TOKEN_FUNC_CLOSE;}
    "main"                  {yylval.sval = strdup("main"); return TOKEN_MAIN;}

<CALL>                      {return TOKEN_CALL_OPEN;}
</CALL>                     {return TOKEN_CALL_CLOSE;}



name=                       {return TOKEN_NAME_ATTR;}
CONST=                      {return TOKEN_CONST;}
count=                      {return TOKEN_COUNT;}

\"[^\"]*\"                  {
                                yytext[strlen(yytext)-1] = '\0';
                                yylval.sval = strdup(yytext + 1);
                                return TOKEN_STRING;
                            }
TRUE                        {yylval.ival = 1; return TOKEN_BOOL;}
FALSE                       {yylval.ival = 0; return TOKEN_BOOL;}


<TYPE>                      {return TOKEN_TYPE_OPEN;}
</TYPE>                     {return TOKEN_TYPE_CLOSE;}

INT                         {return TOKEN_TYPE_INT;}
BOOL                        {return TOKEN_TYPE_BOOL;}
CELL                        {return TOKEN_TYPE_CELL;}
    EMPTY                       {yylval.ival = 0; return TOKEN_CELL_EMPTY;}
    WALL                        {yylval.ival = 1; return TOKEN_CELL_WALL;}
    EXIT                        {yylval.ival = 2; return TOKEN_CELL_EXIT;}
    UNDEF                       {yylval.ival = 3; return TOKEN_CELL_UNDEF;}



<DIMENSIONS                 {return TOKEN_DIMENSIONS_OPEN;}
</DIMENSIONS>               {return TOKEN_DIMENSIONS_CLOSE;}

<DIMENSION>                 {return TOKEN_DIMENSION_OPEN;}
</DIMENSION>                {return TOKEN_DIMENSION_CLOSE;}

<VALUES>                    {return TOKEN_VALUES_OPEN;}
</VALUES>                   {return TOKEN_VALUES_CLOSE;}

<VALUE>                     {return TOKEN_VALUE_OPEN;}
</VALUE>                    {return TOKEN_VALUE_CLOSE;}

<DIM>                       {return TOKEN_DIM_OPEN;}
</DIM>                      {return TOKEN_DIM_CLOSE;}

<INDEX>                     {return TOKEN_INDEX_OPEN;}
</INDEX>                    {return TOKEN_INDEX_CLOSE;}




<ASSIGN>                    {return TOKEN_ASSIGN_OPEN;}
</ASSIGN>                   {return TOKEN_ASSIGN_CLOSE;}

<TO>                        {return TOKEN_TO_OPEN;}
</TO>                       {return TOKEN_TO_CLOSE;}





<WHILE>                     {return TOKEN_WHILE_OPEN;}
</WHILE>                    {return TOKEN_WHILE_CLOSE;}

<CHECK>                     {return TOKEN_CHECK_OPEN;}
</CHECK>                    {return TOKEN_CHECK_CLOSE;}

<DO>                        {return TOKEN_DO_OPEN;}
</DO>                       {return TOKEN_DO_CLOSE;}

<SWITCH>                    {return TOKEN_SWITCH_OPEN;}
</SWITCH>                   {return TOKEN_SWITCH_CLOSE;}

<CONDITION>                 {return TOKEN_CONDITION_OPEN;}
</CONDITION>                {return TOKEN_CONDITION_CLOSE;}







<LEFT>                      {return TOKEN_LEFT_OPEN;}
</LEFT>                     {return TOKEN_LEFT_CLOSE;}

<RIGHT>                     {return TOKEN_RIGHT_OPEN;}
</RIGHT>                    {return TOKEN_RIGHT_CLOSE;}

<UP>                        {return TOKEN_UP_OPEN;}
</UP>                       {return TOKEN_UP_CLOSE;}

<DOWN>                      {return TOKEN_DOWN_OPEN;}
</DOWN>                     {return TOKEN_DOWN_CLOSE;}

<SENDDRONS>                 {return TOKEN_SENDDRONS_OPEN;}
</SENDDRONS>                {return TOKEN_SENDDRONS_CLOSE;}

<GETDRONSCOUNT>             {return TOKEN_GETDRONSCOUNT_OPEN;}
</GETDRONSCOUNT>            {return TOKEN_GETDRONSCOUNT_CLOSE;}




<ADD>                       {return TOKEN_ADD_OPEN;}
</ADD>                      {return TOKEN_ADD_CLOSE;}

<MUL>                       {return TOKEN_MUL_OPEN;}
</MUL>                      {return TOKEN_MUL_CLOSE;}

<SUB>                       {return TOKEN_SUB_OPEN;}
</SUB>                      {return TOKEN_SUB_CLOSE;}

<DIV>                       {return TOKEN_DIV_OPEN;}
</DIV>                      {return TOKEN_DIV_CLOSE;}





<NOT>                       {return TOKEN_NOT_OPEN;}
</NOT>                      {return TOKEN_NOT_CLOSE;}

<OR>                        {return TOKEN_OR_OPEN;}
</OR>                       {return TOKEN_OR_END;}

<AND>                       {return TOKEN_AND_OPEN;}
</AND>                      {return TOKEN_AND_CLOSE;}




<MAX>                       {return TOKEN_MAX_OPEN;}
</MAX>                      {return TOKEN_MAX_CLOSE;}

<MIN>                       {return TOKEN_MIN_OPEN;}
</MIN>                      {return TOKEN_MIN_CLOSE;}

<EQ>                        {return TOKEN_EQ_OPEN;}
</EQ>                       {return TOKEN_EQ_CLOSE;}



true                        {yylval.ival = 1; return TOKEN_BOOL_LIT;}
false                       {yylval.ival = 0; return TOKEN_BOOL_LIT;}



"-"?{DIGIT}+                {
                                yylval.ival = atoi(yytext);
                                return TOKEN_INT_LIT;
                            }

{LETTER}[a-zA-Z-9_]*        {
                                yylval.sval = strdup(yytext);
                                return TOKEN_IDENTIFIER;
                            }



{WHITESPACE}                {    }
{NEWLINE}                   {line_num++;}




">"                         {return '>';}
"/>"                        {return TOKEN_SELFCLOSE;}




.                   {
                        fprintf(stderr, "LEXICAL ERROR (line %d): invalid character '%s'\n", line_num, yytext);
                        error_count++;
                    }

%%


void yyerror(const char* msg){
    fprintf(stderr, "SYNTAX ERROR (line %d): %s\n", line_num, msg);
}

int yywrap() {
    return 1;
}

int get_lexical_errors() {
    return error_count;
}

void reset_lexical_errors() {
    error_count = 0;
    line_num = 1;
}


