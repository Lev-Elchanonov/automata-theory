#include "dialogue.hpp"

#include <algorithm>
#include <fstream>
#include <iostream>


dialogue::dialogue(std::unique_ptr<i_recognizer> recognizer) {
    recognizer_ = std::move(recognizer);
}




std::string dialogue::input_selection() {
    std::string choice;

    while (true) {
        std::cout << "### Enter terminal, file, info or exit: ";
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            if (std::cin.eof())
                return "exit";
            std::cout << "Unknown command\n\n";
            continue;
        }

        if (choice == "info" || choice == "terminal" || choice == "file" || choice == "exit") {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return choice;
        }
        else
            std::cout << "Unknown command\n\n";
    }
}

void dialogue::main_dialogue() {
    try {
        while (true) {
            auto choice = input_selection();
            if (choice == "info")
                show_info();
            if (choice == "terminal") {
                terminal_input();
            }
            if (choice == "file") {
                file_input();
            }
            if (choice == "exit")
                return;
        }
    } catch (int e) {
        return;
    }
}


void dialogue::terminal_input() {
    while (true) {
        std::string user_input;
        std::cout << "Enter command: ";
        std::getline(std::cin, user_input);
        if (user_input == "info") {
            show_info();
            continue;
        }
        if (user_input == "file") {
            file_input();
            continue;
        }
        if (user_input == "exit")
            throw 0;
        recognizer_->terminal_parser(user_input);
        if (recognizer_->get_parser_state() == true)
            std::cout << "\t  Success" << std::endl;
        else
            std::cout << "\t  Failed" << std::endl;
    }
}

void dialogue::file_input() {
    std::string filename;
    std::cout << "Enter file name: ";
    std::getline(std::cin, filename);
    if (filename == "terminal") {
        terminal_input();
        return;
    }
    if (filename == "info") {
        show_info();
        return;
    }
    if (filename == "exit")
        throw 0;
    try {
        recognizer_->file_parser(filename);
        if (recognizer_->get_parser_state() == true)
            std::cout << "\t  Success" << std::endl;
        else
            std::cout << "\t  Failed" << std::endl;
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
    }
}

void dialogue::show_info() {
    std::string choice;
    std::cout << "terminal/file: ";
    std::getline(std::cin, choice);
    std::ofstream file;
    if (choice == "f" || choice == "file") {
        std::string filename;
        std::cout << "Enter file name: ";
        std::getline(std::cin, filename);
        file.open(filename);
        if (!file.is_open())
            std::cerr << "Error opening file " << filename << std::endl;
    }
    std::ostream& out = file.is_open() ? static_cast<std::ostream&>(file) : std::cout;

    out << "\tCurrent state: " << recognizer_->get_parser_state() << std::endl;
    auto res_map = recognizer_->get_parser_info();
    std::ranges::for_each(res_map, [&](auto& iter) {
        out << "\t\t" << iter.first << ": ";
        for (auto& att : iter.second)
            out << att << " ";
        out << std::endl;
    });
}


