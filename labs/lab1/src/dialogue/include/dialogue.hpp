#pragma once
#include <iostream>
#include <memory>

#include "i_recognizer.hpp"

class dialogue {
    private:
        std::unique_ptr<i_recognizer> recognizer_;
    public:
        dialogue(std::unique_ptr<i_recognizer> recognizer);
        void terminal_input();
        void file_input();
        void main_dialogue();
        void show_info();
        static std::string input_selection();
};
