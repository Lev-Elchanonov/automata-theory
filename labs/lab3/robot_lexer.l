%option c++
%option yyclass="yy::RobotLexer"
%option noyywrap
%option batch
%option never-interactive
%option yylineno
%option noinput
%option nounput

%{
#include <iostream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <sstream>

#include "robot.tab.hpp"
#include "ast.hpp"
#include "RobotLexer.h"

int error_count = 0;

void yyerror(const std::string* msg);
using Token = yy::RobotParser::token;

#undef YY_DECL
#define YY_DECL int yy::RobotLexer::yylex(yy::RobotParser::semantic_type* yylval, yy::location* loc)

%}

DIGIT [0-9]
LETTER [a-zA-Z]
WHITESPACE [ \t\r\n]+

%%

"<PROGRAM>"                   {std::cout << "<PROGRAM>" << std::endl; return Token::TOKEN_PROGRAM_OPEN;}
"</PROGRAM>"                  {std::cout << "</PROGRAM>" << std::endl; return Token::TOKEN_PROGRAM_CLOSE;}

"<VARDECLARATION>"            {std::cout << "<VARDECL>" << std::endl; return Token::TOKEN_VARDECL_OPEN;}
"</VARDECLARATION>"           {std::cout << "</VARDECL>" << std::endl; return Token::TOKEN_VARDECL_CLOSE;}

"<VAR"                        {std::cout << "VAR" << std::endl; return Token::TOKEN_VAR_OPEN;}
"</VAR>"                      {std::cout << "/VAR" << std::endl; return Token::TOKEN_VAR_CLOSE;}

"<FUNC"                       {return Token::TOKEN_FUNC_OPEN;}
"</FUNC>"                     {return Token::TOKEN_FUNC_CLOSE;}
"main"                        {yylval->build<std::string>("main"); return Token::TOKEN_MAIN;}

"<CALL>"                      {return Token::TOKEN_CALL_OPEN;}
"</CALL>"                     {return Token::TOKEN_CALL_CLOSE;}



name=                       {std::cout << "name=" << std::endl; return Token::TOKEN_NAME_ATTR;}
CONST=                      {return Token::TOKEN_CONST;}
count=                      {return Token::TOKEN_COUNT;}




\"[^\">]*\"                  {
                                std::string str(yytext + 1, yyleng - 2);
                                std::cout << str << std::endl;
                                yylval->build<std::string>(str);
                                return Token::TOKEN_STRING;
                            }
TRUE                        {yylval->build<bool>(true); return Token::TOKEN_BOOL;}
FALSE                       {yylval->build<bool>(false); return Token::TOKEN_BOOL;}


"<TYPE>"                      {std::cout << "TYPE" << std::endl; return Token::TOKEN_TYPE_OPEN;}
"</TYPE>"                     {std::cout << "/TYPE" << std::endl;return Token::TOKEN_TYPE_CLOSE;}

INT                         {return Token::TOKEN_TYPE_INT;}
BOOL                        {return Token::TOKEN_TYPE_BOOL;}
CELL                        {return Token::TOKEN_TYPE_CELL;}
    EMPTY                       {yylval->build<CellValue>(CellValue::EMPTY); return Token::TOKEN_CELL_VALUE;}
    WALL                        {yylval->build<CellValue>(CellValue::WALL); return Token::TOKEN_CELL_VALUE;}
    EXIT                        {yylval->build<CellValue>(CellValue::EXIT); return Token::TOKEN_CELL_VALUE;}
    UNDEF                       {yylval->build<CellValue>(CellValue::UNDEF); return Token::TOKEN_CELL_VALUE;}



"<DIMENSIONS"                 {return Token::TOKEN_DIMENSIONS_OPEN;}
"</DIMENSIONS>"               {return Token::TOKEN_DIMENSIONS_CLOSE;}

"<DIMENSION>"                 {return Token::TOKEN_DIMENSION_OPEN;}
"</DIMENSION>"                {return Token::TOKEN_DIMENSION_CLOSE;}

"<VALUES>"                    {return Token::TOKEN_VALUES_OPEN;}
"</VALUES>"                   {return Token::TOKEN_VALUES_CLOSE;}

"<VALUE>"                     {std::cout << "VALUE" << std::endl; return Token::TOKEN_VALUE_OPEN;}
"</VALUE>"                    {std::cout << "/VALUE" << std::endl; return Token::TOKEN_VALUE_CLOSE;}

"<DIM>"                       {return Token::TOKEN_DIM_OPEN;}
"</DIM>"                      {return Token::TOKEN_DIM_CLOSE;}

"<INDEX>"                     {return Token::TOKEN_INDEX_OPEN;}
"</INDEX>"                    {return Token::TOKEN_INDEX_CLOSE;}




"<ASSIGN>"                    {std::cout << "ASSIGN" << std::endl; return Token::TOKEN_ASSIGN_OPEN;}
"</ASSIGN>"                   {std::cout << "/ASSIGN" << std::endl; return Token::TOKEN_ASSIGN_CLOSE;}

"<TO>"                        {return Token::TOKEN_TO_OPEN;}
"</TO>"                       {return Token::TOKEN_TO_CLOSE;}





"<WHILE>"                     {std::cout << "тутаwhiile" << std::endl; return Token::TOKEN_WHILE_OPEN;}
"</WHILE>"                    {return Token::TOKEN_WHILE_CLOSE;}

"<CHECK>"                     {return Token::TOKEN_CHECK_OPEN;}
"</CHECK>"                    {return Token::TOKEN_CHECK_CLOSE;}

"<DO>"                        {return Token::TOKEN_DO_OPEN;}
"</DO>"                       {return Token::TOKEN_DO_CLOSE;}

"<SWITCH>"                    {return Token::TOKEN_SWITCH_OPEN;}
"</SWITCH>"                   {return Token::TOKEN_SWITCH_CLOSE;}

"<CONDITION>"                 {return Token::TOKEN_CONDITION_OPEN;}
"</CONDITION>"                {return Token::TOKEN_CONDITION_CLOSE;}







"<LEFT>"                      {return Token::TOKEN_LEFT_OPEN;}
"</LEFT>"                     {return Token::TOKEN_LEFT_CLOSE;}

"<RIGHT>"                     {return Token::TOKEN_RIGHT_OPEN;}
"</RIGHT>"                    {return Token::TOKEN_RIGHT_CLOSE;}

"<UP>"                        {return Token::TOKEN_UP_OPEN;}
"</UP>"                       {return Token::TOKEN_UP_CLOSE;}

"<DOWN>"                      {return Token::TOKEN_DOWN_OPEN;}
"</DOWN>"                     {return Token::TOKEN_DOWN_CLOSE;}

"<SENDDRONS>"                 {return Token::TOKEN_SENDDRONS_OPEN;}
"</SENDDRONS>"                {return Token::TOKEN_SENDDRONS_CLOSE;}

"<GETDRONSCOUNT>"             {return Token::TOKEN_GETDRONSCOUNT_OPEN;}
"</GETDRONSCOUNT>"            {return Token::TOKEN_GETDRONSCOUNT_CLOSE;}




"<ADD>"                       {return Token::TOKEN_ADD_OPEN;}
"</ADD>"                      {return Token::TOKEN_ADD_CLOSE;}

"<MUL>"                       {std::cout << "MUL" << std::endl; return Token::TOKEN_MUL_OPEN;}
"</MUL>"                      {std::cout << "/MUL" << std::endl; return Token::TOKEN_MUL_CLOSE;}

"<SUB>"                       {return Token::TOKEN_SUB_OPEN;}
"</SUB>"                      {return Token::TOKEN_SUB_CLOSE;}

"<DIV>"                       {return Token::TOKEN_DIV_OPEN;}
"</DIV>"                      {return Token::TOKEN_DIV_CLOSE;}





"<NOT>"                       {return Token::TOKEN_NOT_OPEN;}
"</NOT>"                      {return Token::TOKEN_NOT_CLOSE;}

"<OR>"                        {return Token::TOKEN_OR_OPEN;}
"</OR>"                       {return Token::TOKEN_OR_CLOSE;}

"<AND>"                       {return Token::TOKEN_AND_OPEN;}
"</AND>"                      {return Token::TOKEN_AND_CLOSE;}




"<MAX>"                       {return Token::TOKEN_MAX_OPEN;}
"</MAX>"                      {return Token::TOKEN_MAX_CLOSE;}

"<MIN>"                       {return Token::TOKEN_MIN_OPEN;}
"</MIN>"                      {return Token::TOKEN_MIN_CLOSE;}

"<EQ>"                        {return Token::TOKEN_EQ_OPEN;}
"</EQ>"                       {return Token::TOKEN_EQ_CLOSE;}



true                        {yylval->build<bool>(true); return Token::TOKEN_BOOL_LIT;}
false                       {yylval->build<bool>(false); return Token::TOKEN_BOOL_LIT;}



"-"?{DIGIT}+                {
                                int val = std::atoi(yytext);
                                std::cout << val << std::endl;
                                yylval->build<int>(val);
                                return Token::TOKEN_INT_LIT;
                            }

{LETTER}[a-zA-Z0-9_]*        {
                                yylval->build<std::string>(yytext);
                                return Token::TOKEN_IDENTIFIER;
                            }



{WHITESPACE}                {    }



">"                         {std::cout << ">" << std::endl; return '>';}
"/>"                        {return Token::TOKEN_SELFCLOSE;}




.                   {
                        std::cerr << "LEXICAL ERROR (line " << yylineno << "): invalid character '" << yytext << "'" << std::endl;
                        error_count++;
                    }

%%

