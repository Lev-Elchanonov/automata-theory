#ifndef ROBOTLEXER_H
#define ROBOTLEXER_H

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>



namespace yy {
    class RobotParser;
    class location;

    class RobotLexer {
    public:
        RobotLexer(std::istream& input);
        RobotLexer(const std::string& input);
        ~RobotLexer();

        int yylex(RobotParser::semantic_type* yylval, location* loc);
    };
}
#endif