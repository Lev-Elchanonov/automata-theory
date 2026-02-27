#include "regex_version.hpp"
#include <fstream>
#include <iostream>
#include <regex>
/*
bool regex_version::create_new_expression(const std::string& str) {
    std::smatch matches;
    std::string name_attr_pattern = "[a-zA-Z_.][a-zA-Z0-9_.]*";
    std::regex attribute_list_regex("\\s*(create\\s+)"
                                        "(" + name_attr_pattern + ")"
                                        "(\\s*)"
                                        "(\\(\\s*)"
                                        "(" + name_attr_pattern + ")"
                                        "((\\s*,\\s*" + name_attr_pattern + ")*)"
                                        "(\\))"
                                        "$"
                                        );


    if (std::regex_search(str, matches, attribute_list_regex)) {
        std::vector<std::string> final_attributes;
        std::regex single_attribute_regex(name_attr_pattern);
        std::string name = matches[2];
        final_attributes.push_back(matches[5]);
        std::string attribs = matches[6];
        auto w_begin = std::sregex_iterator(attribs.begin(), attribs.end(), single_attribute_regex);
        auto w_end = std::sregex_iterator(); // по умолчанию в конце

        for (std::sregex_iterator i = w_begin; i != w_end; ++i) {
            std::string token = i->str();

            token.erase(0, token.find_first_not_of(" "));
            token.erase((token.find_last_not_of(" ") + 1));
            if (token.empty()) {
                parser_.set_condition(false);
                return false;
            }
            final_attributes.push_back(token);
        }
        bool res = parser_.add_expression(name, final_attributes);
        return res;
    }
    parser_.set_condition(false);
    return false;
}

bool regex_version::combine_expressions(const std::string& str) {
    std::smatch matches;
    std::string name_pattern = "[a-zA-Z_.][a-zA-Z0-9_.]*";
    std::regex combine_regex("\\s*(create\\s+)"
                                "(" + name_pattern + ")"
                                "(\\s+)"
                                "(as\\s+)"
                                "(" + name_pattern + ")"
                                "(\\s+join\\s+)"
                                "(" + name_pattern + ")"
                                "\\s*$"
    );
    if (std::regex_search(str, matches, combine_regex)) {
        std::string new_expression = matches[2];
        std::string expression_1 = matches[5];
        std::string expression_2 = matches[7];
        bool res = parser_.combine_expressions(expression_1, expression_2, new_expression);
        return res;
    }
    parser_.set_condition(false);
    return false;
}


void regex_version::terminal_parser(const std::string& str) {
    if (create_new_expression(str) || combine_expressions(str))
        parser_.set_condition(true);
    else
        parser_.set_condition(false);
}

const std::map<std::string, std::vector<std::string>>& regex_version::get_parser_info() const noexcept {
    return parser_.get_map();
}

void regex_version::file_parser(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open())
        throw std::runtime_error("File not found: " + path);
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty())
            continue;
        terminal_parser(line);
    }
    file.close();
}
*/

std::pair<STATE, std::pair<std::string, std::vector<std::string>>>
regex_version::lexline(const std::string& line) {

    std::smatch matches;
    std::string name_attr_pattern = "[a-zA-Z_.][a-zA-Z0-9_.]*";

    std::regex combined_regex(
        "\\s*create\\s+"
        "(" + name_attr_pattern + ")"
        "(?:"
            "\\s*\\(\\s*"
            "(" + name_attr_pattern + ")"
            "((?:\\s*,\\s*" + name_attr_pattern + ")*)"
            "\\s*\\)"
            "|"
            "\\s+as\\s+"
            "(" + name_attr_pattern + ")"
            "\\s+join\\s+"
            "(" + name_attr_pattern + ")"
        ")"
        "\\s*$"
    );

    if (std::regex_search(line, matches, combined_regex)) {
        std::string name = matches[1];
        if (matches[2].matched) {
            std::vector<std::string> attributes;
            attributes.push_back(matches[2]);

            if (matches[3].matched) {
                std::regex single_attribute_regex(name_attr_pattern);
                std::string attribs = matches[3];

                auto w_begin = std::sregex_iterator(attribs.begin(), attribs.end(),
                                                    single_attribute_regex);
                auto w_end = std::sregex_iterator();

                for (std::sregex_iterator i = w_begin; i != w_end; ++i) {
                    std::string token = i->str();

                    token.erase(0, token.find_first_not_of(" "));
                    token.erase(token.find_last_not_of(" ") + 1);

                    if (token.empty()) {
                        return {STATE::NO, {"", {}}};
                    }
                    attributes.push_back(token);
                }
            }
            return {STATE::NEW_EXP, {name, attributes}};
        }
        else if (matches[4].matched) {
            std::vector<std::string> expressions;
            expressions.push_back(matches[4]);  // первое выражение
            expressions.push_back(matches[5]);  // второе выражение


            return {STATE::COMBINE_EXP, {name, expressions}};
        }
    }
    return {STATE::NO, {"", {}}};
}
