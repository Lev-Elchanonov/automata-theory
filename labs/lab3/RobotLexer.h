#ifndef ROBOTLEXER_H
#define ROBOTLEXER_H

#if !defined(yyFlexLexerOnce)
#include <FlexLexer.h>
#endif

#include <string>
#include <iostream>
#include <sstream>
#include "generated/robot.tab.hpp"


namespace yy {
    class RobotLexer : public yyFlexLexer {
    public:
        explicit RobotLexer(std::istream& input) : yyFlexLexer(&input) {}
        explicit RobotLexer(const std::string& input) : yyFlexLexer() {
            iss_ = new std::istringstream(input);
            yyFlexLexer::switch_streams(iss_);
        }
        ~RobotLexer() override {
            delete iss_;
        }
        int yylex(yy::RobotParser::semantic_type* yylval, yy::location* loc);



    private:
        std::istringstream* iss_ = nullptr;
    };

}

#endif