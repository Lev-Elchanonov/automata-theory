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

        std::string current_name_;
        std::string current_attribute_;
        std::vector<std::string> attributes_;


        std::string create_accumulator_;
        std::string join_accumulator_;
        bool name_started_;
        bool attribute_started_;

        STATE current_state_;


        std::pair<STATE, std::pair<std::string, std::vector<std::string>>> on_success_;

        STATE state_;
        char saved_char_{};
        bool has_saved_char_{};
        bool exit_ = false;
        bool create_accumulating_;
        bool join_accumulating_;

    public:
        lexer_context() : name_started_(false), attribute_started_(false) {}


        void start_create_accum(char c) {
            create_accumulating_ = true;
            create_accumulator_ = std::string(1, c);
        }

        [[nodiscard]] bool is_accumulating_create() const {return create_accumulating_;}

        [[nodiscard]] bool is_accumulating_join() const {return join_accumulating_;}

        [[nodiscard]] bool create_is_accumulated() const {
            bool exp = create_accumulator_ == "create";
            return exp;
        }

        [[nodiscard]] bool join_is_accumulated() const {
            bool exp = join_accumulator_ == "join";
            return exp;
        }


        [[nodiscard]] bool join_mismatch() const {
            std::string target = "join";
            for (size_t i = 0; i < join_accumulator_.size(); ++i) {
                if (join_accumulator_[i] != target[i]) {
                    return true;
                }
            }
            return false;
        }

        [[nodiscard]] bool create_mismatch() const {
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
        }

        void accumulate_create(char c) {create_accumulator_ += c;}
        void accumulate_join(char c) {
            join_accumulating_ = true;
            join_accumulator_ += c;
        }

        [[nodiscard]] bool has_saved_char() const {return has_saved_char_;}

        char get_saved_char() {
            has_saved_char_ = false;
            return saved_char_;
        }


        [[nodiscard]] bool name_started() const { return name_started_; }


        void add_to_name(char c) {
            current_name_ += c;
            name_started_ = true;
        }

        [[nodiscard]] bool attribute_started() const { return attribute_started_; }

        void start_attribute(char c) {
            attribute_started_ = true;
            current_attribute_ = std::string(1, c);
        }

        void add_to_attribute(char c) {current_attribute_ += c;}


        void save_attribute() {
            if (!current_attribute_.empty()) {
                attributes_.push_back(current_attribute_);
                current_attribute_.clear();
                attribute_started_ = false;
            }
        }



        void end_line() {
            if (!current_name_.empty() && !attributes_.empty()) {
                on_success_.first = state_;
                on_success_.second.first = current_name_;
            on_success_.second.second = attributes_;
            }
            reset_for_new_line();
        }

        static bool is_end_of_line(char c) {return c == '\n' || c == '\r' || c == '\0';}

        static bool isalpha(char c) { return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'); }
        static bool isalnum(char c) { return isalpha(c) || (c >= '0' && c <= '9'); }
        static bool is_space(char c) { return c == ' ' || c == '\t'; }


        void set_state(STATE code) {state_ = code;}

        void reset_for_new_line() {
            create_accumulator_.clear();
            join_accumulator_.clear();
            current_name_.clear();
            current_attribute_.clear();
            attributes_.clear();
            name_started_ = false;
            attribute_started_ = false;
            create_accumulating_ = false;
            join_accumulating_ = false;
        }

        void set_exit_state() {exit_ = true;}

        std::pair<STATE, std::pair<std::string, std::vector<std::string>>> lexline(const std::string& line) override {
            reset_for_new_line();

            parserContext fsm(*this);

            fsm.enterStartState();

            auto c_line = line.c_str();
            for (size_t i = 0; i <= line.size(); i++) {
                fsm.next_char(c_line[i]);
                if (exit_) {
                    exit_ = false;
                    return {STATE::NO, {"", {}}};
                }
            }

            if (on_success_.first != STATE::NO && !on_success_.second.first.empty() && !on_success_.second.second.empty()) {
                return on_success_;
            }
            return {STATE::NO, {"", {}}};
        }
};

#endif