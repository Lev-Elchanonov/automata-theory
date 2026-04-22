#include <iostream>
#include <fstream>
#include "RobotLexer.h"
#include "robot.tab.hpp"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file>" << std::endl;
        return 1;
    }

    std::ifstream file(argv[1]);
    if (!file.is_open()) {
        std::cerr << "Error: Cannot open file " << argv[1] << std::endl;
        return 1;
    }

    yy::RobotLexer lexer(file);   // ← ОБРАТИТЕ ВНИМАНИЕ: yy::RobotLexer
    yy::RobotParser parser(lexer);

    int result = parser.parse();

    if (result == 0) {
        std::cout << "Parsing successful!" << std::endl;
    } else {
        std::cout << "Parsing failed!" << std::endl;
    }

    return result;
}