#ifndef LEXER_CONTEXT_H
#define LEXER_CONTEXT_H

#include <string>
#include <iostream>
#include <functional>
#include "parser_sm.h"
#include "statemap.h"
#include "i_lexer.hpp"



class lexer_context : public i_lexer {
private:
    // Состояние автомата
    std::string current_name_;      // текущее имя выражения
    std::string current_attribute_; // текущий атрибут
    std::vector<std::string> attributes_; // все атрибуты

    // Для накопления 'create"
    std::string create_accumulator_;
    bool name_started_;
    bool attribute_started_;

    STATE current_state_;
    std::string result_name_;
    std::vector<std::string> result_attributes_;

    // Callback для результата
    std::pair<STATE, std::pair<std::string, std::vector<std::string>>> on_success_;

    STATE state_;
    char saved_char_;
    bool has_saved_char_;

public:
    lexer_context() : name_started_(false), attribute_started_(false) {}

    // Методы для create_accumulator
    void start_create_accum(char c) {
        create_accumulator_ = std::string(1, c);
        std::cout << "Start create: " << c << std::endl;
    }

    bool is_accumulating_create() const {
        return true; // всегда true, когда в этом состоянии
    }

    bool create_is_accumulated() const {
        bool exp = create_accumulator_ == "create";
        if (exp)
            std::cout << "Create accumulated: " << create_accumulator_ << std::endl;
        return exp;
    }

    bool create_mismatch() const {
        // Проверяем, что накопленная строка не является началом "create"
        std::string target = "create";
        for (size_t i = 0; i < create_accumulator_.size(); ++i) {
            if (create_accumulator_[i] != target[i]) {
                return true;
            }
        }
        return false;
    }

    void save_next_char(char c) {
        saved_char_ = c;
        has_saved_char_ = true;
        std::cout << "Saved char: '" << c << "' for next state" << std::endl;
    }
    void accumulate_create(char c) {
        create_accumulator_ += c;
        std::cout << "Accumulate create: " << create_accumulator_ << std::endl;
    }


    bool has_saved_char() const {
        return has_saved_char_;
    }

    char get_saved_char() {
        has_saved_char_ = false;
        return saved_char_;
    }


    // Методы для имени
    bool name_started() const { return name_started_; }


    void add_to_name(char c) {
        current_name_ += c;
        std::cout << "Add to name: " << current_name_ << std::endl;
        name_started_ = true;
    }

    // Методы для атрибутов
    bool attribute_started() const { return attribute_started_; }

    void start_attribute(char c) {
        attribute_started_ = true;
        current_attribute_ = std::string(1, c);
        std::cout << "Start attribute: " << current_attribute_ << std::endl;
    }

    void add_to_attribute(char c) {
        current_attribute_ += c;
        std::cout << "Add to attribute: " << current_attribute_ << std::endl;
    }

    void save_attribute(char c) {
        // Сохраняем атрибут при встрече ',' или ')'
        if (!current_attribute_.empty()) {
            attributes_.push_back(current_attribute_);
            current_attribute_.clear();
            attribute_started_ = false;
        }
        std::cout << "Save attribute with char: " << c << std::endl;
    }

    void save_attribute() {
        // Сохраняем атрибут при пробеле
        if (!current_attribute_.empty()) {
            attributes_.push_back(current_attribute_);
            current_attribute_.clear();
            attribute_started_ = false;
        }
        std::cout << "Save attribute with space" << std::endl;
    }



    // Метод для конца строки
    void end_line() {
        if (!current_name_.empty() && !attributes_.empty()) {
            std::cout << "END LINE - Success! Name: " << current_name_
                     << ", Attributes: " << attributes_.size() << std::endl;

            // Вызываем callback, если он установлен
            on_success_.first = STATE::NEW_EXP;
            on_success_.second.first = current_name_;
            on_success_.second.second = attributes_;
        }

        // Сброс состояния для новой строки
        reset_for_new_line();
    }

    // Проверка конца строки (нужно реализовать в зависимости от вашего ввода)
    bool is_end_of_line(char c) const {
        return c == '\n' || c == '\r' || c == '\0';
    }

    // Проверка символов
    bool isalpha(char c) const { return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'); }
    bool isalnum(char c) const { return isalpha(c) || (c >= '0' && c <= '9'); }
    bool is_space(char c) const { return c == ' ' || c == '\t'; }

    // Методы для ошибок
    void set_state(STATE code) {
        state_ = code;
    }

    void report_failure() {
        std::cerr << "Line parsing FAILED" << std::endl;
    }

    void reset_error() {
        std::cout << "Reset error" << std::endl;
        reset_for_new_line();
    }

    void reset_state() {
        std::cout << "Reset state" << std::endl;
        reset_for_new_line();
    }

    // Сброс для новой строки
    void reset_for_new_line() {
        create_accumulator_.clear();
        current_name_.clear();
        current_attribute_.clear();
        attributes_.clear();
        name_started_ = false;
        attribute_started_ = false;
    }

    std::pair<STATE, std::pair<std::string, std::vector<std::string>>> lexline(const std::string& line) override {
        reset_for_new_line();

        // Создаем FSM автомат - используем parserContext, а не LexerFSM!
        parserContext fsm(*this);  // передаем ссылку на lexer_context

        fsm.enterStartState();

        for (char c : line) {
            std::cout << "--> " <<  c << std::endl;
            fsm.next_char(c);
        }
        fsm.next_char('\n');  // конец строки

        std::cout << "----" << attributes_.size() << std::endl;
        // Формируем результат
        for (auto& attr : attributes_)
            std::cout  << "attribute: " << attr << std::endl;
        if (on_success_.first != STATE::NO && !on_success_.second.first.empty() && !on_success_.second.second.empty()) {
            return on_success_;
        }
        return {STATE::NO, {"", {}}};
    }
};

#endif // LEXER_CONTEXT_H