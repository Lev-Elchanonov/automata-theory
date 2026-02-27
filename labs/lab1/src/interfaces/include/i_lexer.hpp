#pragma once
#include <string>
#include <vector>


enum class STATE {
    NO,
    NEW_EXP,
    COMBINE_EXP
};
class i_lexer {
    private:

    public:
        virtual ~i_lexer() = default;

        virtual std::pair<STATE, std::pair<std::string, std::vector<std::string>>> lexline(const std::string& line) = 0;
};
