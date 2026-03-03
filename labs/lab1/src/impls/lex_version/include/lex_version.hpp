#pragma once
#include "i_lexer.hpp"
#include <string>
#include <vector>
#include <utility>
#include <memory>


struct yy_buffer_state;

enum class LexState {
    INITIAL,
    CREATE,
    NAME,
    AS,
    JOIN,
    LPAREN,
    ATTR,
    COMMA,
    RPAREN,
    AFT_REXP,
    ERROR,
    SUCCESS
};


extern int yylex();
extern void yy_switch_to_buffer(yy_buffer_state*);
extern yy_buffer_state* yy_scan_string(const char*);
extern void yy_delete_buffer(yy_buffer_state*);

extern std::string current_token;
extern LexState current_state_;
extern std::vector<std::string> attributes;
extern STATE predicted_state_;
extern std::string exp_name_;

class lex_version : public i_lexer {
private:
    static void reset() {
        current_token.clear();
        current_state_ = LexState::INITIAL;
        attributes.clear();
        predicted_state_ = STATE::NO;
        exp_name_.clear();
    }

public:
    lex_version() = default;

    std::pair<STATE, std::pair<std::string, std::vector<std::string>>>
    lexline(const std::string& line) override {

        reset();
        yy_buffer_state* buffer = yy_scan_string(line.c_str());

        int res;
        int token_count = 0;
        while ((res = yylex()) > 0) {
            token_count++;
        }

        yy_delete_buffer(buffer);

        std::pair<std::string, std::vector<std::string>> result_data;

        if (current_state_ == LexState::SUCCESS) {
            result_data.first = exp_name_;
            result_data.second = attributes;


        } else {
            result_data.first = "";
            result_data.second = {};
            predicted_state_ = STATE::NO;

            current_state_ = LexState::INITIAL;
            current_token.clear();
            attributes.clear();
            exp_name_.clear();
        }


        return {predicted_state_, result_data};
    }
};
