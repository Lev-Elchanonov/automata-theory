#include <iostream>
#include <fstream>
#include <cstdio>
#include <string>
#include "RobotLexer.h"
#include "robot.tab.hpp"
#include "interpreter.cpp"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file> [--map <map_file>] [--vis <go_visualizer>]" << std::endl;
        return 1;
    }

    std::string input_file = argv[1];
    std::string map_file = "map.txt";
    std::string go_visualizer;
    FILE* go_pipe = nullptr;

    for (int i = 2; i < argc; i++) {
        std::string arg = argv[i];
        if (arg == "--map" && i + 1 < argc) {
            map_file = argv[i + 1];  // ← сохраняем путь к карте
            i++;
        } else if (arg == "--vis" && i + 1 < argc) {
            go_visualizer = argv[i + 1];
            i++;
        }
    }

    if (!go_visualizer.empty()) {
        go_pipe = popen(go_visualizer.c_str(), "w");
    }

    std::ifstream file(input_file);

    yy::RobotLexer lexer(file);
    yy::RobotParser parser(lexer);
    THE_LEXER = &lexer;

    int result = parser.parse();

    if (result == 0) {
        std::cout << "Parsing successful!" << std::endl;

        try {
            Interpreter interpreter(go_pipe, map_file);
            interpreter.initialize_variables();
            interpreter.run();
        } catch (const std::exception& e) {
            std::cerr << "Runtime error: " << e.what() << std::endl;
        }
    } else {
        std::cerr << "Parsing failed!" << std::endl;
    }

    if (go_pipe) {
        fprintf(go_pipe, "{\"command\":\"exit\"}\n");
        fflush(go_pipe);
        pclose(go_pipe);
    }

    return result;
}