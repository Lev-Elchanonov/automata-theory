#include "service.hpp"

#include <algorithm>
#include <unordered_map>

#include "i_lexer.hpp"

std::vector<std::string> service::get_attribute(const std::string& expression_name) const noexcept {
    std::vector<std::string> res = {};
    auto iter = expression_to_attribute_.find(expression_name);
    if (iter != expression_to_attribute_.end())
       res = iter->second;
    return res;
}

std::vector<std::string> service::get_expression(const std::string& attribute_name) const noexcept {
    std::vector<std::string> res = {};
    auto iter = attribute_to_expression_.find(attribute_name);
    if (iter != attribute_to_expression_.end())
        res = iter->second;
    return res;
}


bool service::add_expression(const std::string& expression_name, std::vector<std::string>& attributes) {
    if (expression_to_attribute_.contains(expression_name)) {
        state_ = false;
        return false;
    }
    std::ranges::for_each(attributes, [&](const std::string& attr){
        auto vec = get_expression(attr);

        if (!vec.empty()) {
            auto& expression_vector = attribute_to_expression_.find(attr)->second;
            expression_vector.push_back(expression_name);
        }
        else {
            std::vector new_vec = {expression_name};
            attribute_to_expression_.emplace(attr, new_vec);
        }
    });
    expression_to_attribute_.insert({expression_name, attributes});
    state_ = true;
    return true;
}


bool service::combine_expressions(const std::string& expression_1, const std::string& expression_2, const std::string& new_expression) {
    if (!expression_to_attribute_.contains(expression_1) ||
        !expression_to_attribute_.contains(expression_2) ||
        expression_1 == expression_2                     ||
        expression_to_attribute_.contains(new_expression)) {
        state_ = false;
        return false;
    }
    auto attributes_1 = get_attribute(expression_1);
    auto attributes_2 = get_attribute(expression_2);
    std::vector<std::string> summary_vector;
    summary_vector.reserve(attributes_1.size() + attributes_2.size());

    std::unordered_map<std::string, std::vector<size_t>> map_2;
    for (size_t i = 0; i < attributes_2.size(); ++i)
        map_2[attributes_2[i]].push_back(i);

    for (size_t i = 0; i < attributes_1.size(); ++i) {
        auto it = map_2.find(attributes_1[i]);
        if (it != map_2.end()) {
            attributes_1[i] = attributes_1[i] + "." + expression_1;
            if (!it->second.empty()) {
                for (size_t index : it->second)
                    attributes_2[index] = attributes_2[index] + "." + expression_2;
                it->second.clear();
            }
        }
    }


    summary_vector.insert(summary_vector.end(), attributes_1.begin(), attributes_1.end());
    summary_vector.insert(summary_vector.end(), attributes_2.begin(), attributes_2.end());
    bool res = add_expression(new_expression, summary_vector);
    return res;
}


void service::get_line(const std::string& line) {
    auto result = lexer_.lexline(line);
    if (result.first == STATE::NEW_EXP)
        state_ = add_expression(result.second.first, result.second.second);
    else if (result.first == STATE::COMBINE_EXP)
        state_ = combine_expressions(result.second.second[0], result.second.second[1], result.second.first);
    else
        state_ = false;
}
