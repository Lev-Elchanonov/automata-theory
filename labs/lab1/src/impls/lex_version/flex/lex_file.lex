%{
#include <string>
#include <vector>
#include <iostream>
#include "../include/lex_version.hpp"


std::string current_token;
LexState current_state_ = LexState::INITIAL;
std::vector<std::string> attributes;
STATE predicted_state_ = STATE::NO;
std::string exp_name_;

void set_token(const char* text) {
    current_token = text;
}
%}

%option noyywrap
%x St_CREATE St_NAME St_AS St_JOIN St_LPAREN St_ATTR St_COMMA St_RPAREN St_R_ATTR
%%


<INITIAL>{
    (?i:create)[ \t]+    {
        set_token(yytext);
        current_state_ = LexState::CREATE;
        BEGIN(St_CREATE);
        return 1;
    }
    (?i:create)    {
            set_token(yytext);
            current_state_ = LexState::ERROR;
            BEGIN(INITIAL);
            return 0;
    }

    [ \t]+         { /* ignore */ }
    \n             { /* ignore */ }
    .              {
        set_token(yytext);
        current_state_ = LexState::ERROR;
        BEGIN(INITIAL);
        return 0;
    }
}

<St_CREATE>{
    [ \t]+         { /* ignore */ }
    [a-zA-Z._][a-zA-Z0-9._]* {
        set_token(yytext);
        current_state_ = LexState::NAME;
        exp_name_ = yytext;
        BEGIN(St_NAME);
        return 1;
    }
    .              {

        set_token(yytext);
        current_state_ = LexState::ERROR;
        BEGIN(INITIAL);
        return 0;
    }
}

<St_NAME>{
    [ \t]+         { /* ignore */ }
    "("            {
        set_token(yytext);
        current_state_ = LexState::LPAREN;
        predicted_state_ = STATE::NEW_EXP;
        BEGIN(St_LPAREN);
        return 1;
    }
    (?i:as)[ \t]        {
        set_token(yytext);
        current_state_ = LexState::AS;
        predicted_state_ = STATE::COMBINE_EXP;
        BEGIN(St_AS);
        return 1;
    }
    .              {
        set_token(yytext);
        current_state_ = LexState::ERROR;
        BEGIN(INITIAL);
        return 0;
    }
}

<St_LPAREN>{
    [ \t]+         { /* ignore */ }
    [a-zA-Z._][a-zA-Z0-9._]* {
        set_token(yytext);
        attributes.push_back(yytext);
        current_state_ = LexState::ATTR;
        BEGIN(St_ATTR);
        return 1;
    }
    .              {
        set_token(yytext);
        current_state_ = LexState::ERROR;
        BEGIN(INITIAL);
        return 0;
    }
}

<St_ATTR>{
    [ \t]+         { /* ignore */ }
    ","            {
        set_token(yytext);
        current_state_ = LexState::COMMA;
        BEGIN(St_COMMA);
        return 1;
    }
    ")"            {
        set_token(yytext);
        current_state_ = LexState::RPAREN;
        BEGIN(St_RPAREN);
        return 1;
    }
    .              {
        set_token(yytext);
        current_state_ = LexState::ERROR;
        BEGIN(INITIAL);
        return 0;
    }
}

<St_COMMA>{
    [ \t]+         { /* ignore */ }
    [a-zA-Z._][a-zA-Z0-9._]* {
        set_token(yytext);
        attributes.push_back(yytext);
        current_state_ = LexState::ATTR;
        BEGIN(St_ATTR);
        return 1;
    }
    .              {
        set_token(yytext);
        current_state_ = LexState::ERROR;
        BEGIN(INITIAL);
        return 0;
    }
}


<St_RPAREN>{
        [ \t]+         {}
        \n             {
            set_token("COMPLETE");
            current_state_ = LexState::SUCCESS;
            BEGIN(INITIAL);
            return 1;
        }
        <<EOF>>        {
            set_token("COMPLETE");
            current_state_ = LexState::SUCCESS;
            BEGIN(INITIAL);
            return 1;
        }
        .              {
            set_token(yytext);
            current_state_ = LexState::ERROR;
            BEGIN(INITIAL);
            return 0;
        }
}


<St_AS>{
    [ \t]+         {}
    [a-zA-Z._][a-zA-Z0-9._]* {
        set_token(yytext);
        attributes.push_back(yytext);
        current_state_ = LexState::JOIN;
        BEGIN(St_JOIN);
        return 1;
    }
    .              {
        set_token(yytext);
        current_state_ = LexState::ERROR;
        BEGIN(INITIAL);
        return 0;
    }
}

<St_JOIN>{
    [ \t]+         {}
    (?i:join)[ \t]      {
        set_token(yytext);
        current_state_ = LexState::ATTR;
        BEGIN(St_R_ATTR);
        return 1;
    }
    .              {
        set_token(yytext);
        current_state_ = LexState::ERROR;
        BEGIN(INITIAL);
        return 0;
    }
}

<St_R_ATTR>{
    [ \t]+         {}
    [a-zA-Z._][a-zA-Z0-9._]* {
        set_token(yytext);
        attributes.push_back(yytext);
        current_state_ = LexState::AFT_REXP;
        BEGIN(St_RPAREN);
        return 1;
    }
    .              {
        set_token(yytext);
        current_state_ = LexState::ERROR;
        BEGIN(INITIAL);
        return 0;
    }
}

%%
