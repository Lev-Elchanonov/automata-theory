#include "regex_version.hpp"
#include <fstream>
#include <iostream>
#include <regex>

bool regex_version::create_new_expression(const std::string& str) {
    std::smatch matches;
    std::string name_attr_pattern = "[a-zA-Z_.,][a-zA-Z0-9_.,]*";
    std::regex attribute_list_regex("\\s*(create\\s+)"
                                        "(" + name_attr_pattern + ")"
                                        "(\\s+)"
                                        "(\\(\\s*" + "(" + name_attr_pattern + "\\s*)+" + "\\))"
                                        "$"
                                        );


    if (std::regex_search(str, matches, attribute_list_regex)) {
        std::vector<std::string> final_attributes;
        std::regex single_attribute_regex(name_attr_pattern);
        std::string name = matches[2];
        std::string attribs = matches[4];

        auto w_begin = std::sregex_iterator(attribs.begin(), attribs.end(), single_attribute_regex);
        auto w_end = std::sregex_iterator(); // по умолчанию в конце

        for (std::sregex_iterator i = w_begin; i != w_end; ++i) {
            std::string token = i->str();

            auto iter = i;
            if (++iter != w_end && !token.empty()) {
                if (token.back() == ',') {
                    token.pop_back();
                }
                else {
                    parser_.set_condition(false);
                    return false;
                }
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
    std::string name_pattern = "[a-zA-Z_.,][a-zA-Z0-9_.,]*";
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


