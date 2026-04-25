#include <iostream>
#include <fstream>
#include "RobotLexer.h"
#include "robot.tab.hpp"
#include "interpreter.cpp"

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

    yy::RobotLexer lexer(file);
    yy::RobotParser parser(lexer);  // Конструктор с параметром теперь существует

    // Устанавливаем глобальный указатель для доступа из парсера
    THE_LEXER = &lexer;

    int result = parser.parse();

    if (result == 0) {
        std::cout << "Parsing successful!" << std::endl;
    } else {
        std::cerr << "Parsing failed with " << result << " errors." << std::endl;
    }

    Interpreter interpreter(nullptr);
    interpreter.initialize_variables();
    interpreter.run();
    return result;
}