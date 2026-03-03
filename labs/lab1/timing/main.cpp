#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <algorithm>
#include <memory>

#include "lexer_context.h"
#include "lex_version.hpp"
#include "regex_version.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <numeric>

class SQLGenerator {
private:
    std::mt19937 rng;
    std::string allowed_chars;
    std::string first_chars;

    // Генерирует идентификатор фиксированной длины
    std::string generateIdentifierFixed(int length) {
        if (length <= 0) return "";

        std::uniform_int_distribution<int> firstCharDist(0, first_chars.size() - 1);
        std::string result;
        result += first_chars[firstCharDist(rng)];

        if (length > 1) {
            std::uniform_int_distribution<int> charDist(0, allowed_chars.size() - 1);
            for (int i = 1; i < length; i++) {
                result += allowed_chars[charDist(rng)];
            }
        }

        return result;
    }

    // Генерирует идентификатор случайной длины в диапазоне
    std::string generateIdentifier(int minLen = 1, int maxLen = 15) {
        std::uniform_int_distribution<int> lenDist(minLen, maxLen);
        int length = lenDist(rng);
        return generateIdentifierFixed(length);
    }

    // Генерирует атрибут (просто идентификатор)
    std::string generateAttribute() {
        return generateIdentifier(1, 10);
    }

    // Генерирует список атрибутов с разделителями
    std::string generateAttributeList(int count) {
        std::vector<std::string> attrs;
        for (int i = 0; i < count; i++) {
            attrs.push_back(generateAttribute());
        }

        // Объединяем с запятыми и пробелами
        std::string result;
        for (size_t i = 0; i < attrs.size(); i++) {
            if (i > 0) result += ", ";
            result += attrs[i];
        }
        return result;
    }

    // Вычисляет длину шаблона с подстановками
    int calculatePatternLength(const std::string& pattern,
                               const std::vector<std::string>& placeholders) {
        int total = 0;
        size_t pos = 0;
        int placeholderIdx = 0;

        while (pos < pattern.length()) {
            if (pattern[pos] == '{' && pattern[pos+1] == '}') {
                // Нашли placeholder {}
                if (placeholderIdx < placeholders.size()) {
                    total += placeholders[placeholderIdx].length();
                    placeholderIdx++;
                }
                pos += 2;
            } else {
                total++;
                pos++;
            }
        }
        return total;
    }

    // Заполняет шаблон значениями
    std::string fillPattern(const std::string& pattern,
                            const std::vector<std::string>& placeholders) {
        std::string result;
        size_t pos = 0;
        int placeholderIdx = 0;

        while (pos < pattern.length()) {
            if (pattern[pos] == '{' && pattern[pos+1] == '}') {
                if (placeholderIdx < placeholders.size()) {
                    result += placeholders[placeholderIdx];
                    placeholderIdx++;
                }
                pos += 2;
            } else {
                result += pattern[pos];
                pos++;
            }
        }
        return result;
    }

public:
    SQLGenerator() : rng(std::random_device{}()) {
        allowed_chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_.";
        first_chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_.";
    }

    std::string generateString(int targetLength) {
        // Два основных шаблона
        const std::string pattern1 = "create {} ( {} )";
        const std::string pattern2 = "create {} as {} join {}";

        const int MAX_ATTEMPTS = 10000;

        for (int attempt = 0; attempt < MAX_ATTEMPTS; attempt++) {
            std::uniform_int_distribution<int> typeDist(0, 1);
            bool usePattern1 = (typeDist(rng) == 0);

            if (usePattern1) {
                // Пробуем разные длины идентификаторов
                int relNameLen = std::uniform_int_distribution<int>(3, 20)(rng);
                int attrCount = std::uniform_int_distribution<int>(2, 50)(rng);

                std::string relName = generateIdentifierFixed(relNameLen);

                // Генерируем атрибуты
                std::vector<std::string> attrs;
                int totalAttrsLength = 0;

                // Примерно распределяем длину под атрибуты
                // Формула: общая длина = длина relName + длина всех атрибутов + (attrCount-1)*2 (запятые) + 13 (служебные символы)
                int availableForAttrs = targetLength - relNameLen - 13 - (attrCount - 1) * 2;

                if (availableForAttrs <= 0) continue;

                // Генерируем атрибуты так, чтобы их суммарная длина была примерно availableForAttrs
                int remainingLength = availableForAttrs;
                for (int i = 0; i < attrCount; i++) {
                    int maxAttrLen = std::min(20, remainingLength - (attrCount - i - 1));
                    if (maxAttrLen < 1) break;

                    int attrLen = std::uniform_int_distribution<int>(1, maxAttrLen)(rng);
                    attrs.push_back(generateIdentifierFixed(attrLen));
                    remainingLength -= attrLen;
                }

                if (attrs.size() < 2) continue;

                // Формируем список атрибутов
                std::string attrList;
                for (size_t i = 0; i < attrs.size(); i++) {
                    if (i > 0) attrList += ", ";
                    attrList += attrs[i];
                }

                // Финальная строка
                std::string result = "create " + relName + " ( " + attrList + " )";

                if (result.length() == targetLength) {
                    return result;
                }
                // Если немного короче, добавляем пробелы внутри (но не в конец)
                else if (result.length() < targetLength) {
                    int diff = targetLength - result.length();

                    // Вставляем пробелы в случайные места
                    std::vector<size_t> insertPositions;
                    for (size_t i = 0; i < result.length(); i++) {
                        if (result[i] == ' ') {
                            insertPositions.push_back(i);
                        }
                    }

                    if (!insertPositions.empty()) {
                        std::string modified = result;
                        int inserted = 0;
                        while (inserted < diff && !insertPositions.empty()) {
                            size_t pos = insertPositions[inserted % insertPositions.size()];
                            modified.insert(pos, " ");
                            inserted++;
                            // Корректируем последующие позиции
                            for (auto& p : insertPositions) {
                                if (p > pos) p++;
                            }
                        }
                        if (modified.length() == targetLength) {
                            return modified;
                        }
                    }
                }
            } else {
                // Паттерн 2: create {} as {} join {}
                int len1 = std::uniform_int_distribution<int>(3, 30)(rng);
                int len2 = std::uniform_int_distribution<int>(3, 30)(rng);
                int len3 = std::uniform_int_distribution<int>(3, 30)(rng);

                std::string name1 = generateIdentifierFixed(len1);
                std::string name2 = generateIdentifierFixed(len2);
                std::string name3 = generateIdentifierFixed(len3);

                // Базовая строка без идентификаторов: "create  as  join "
                int baseLength = 15; // "create  as  join " без учета идентификаторов
                int totalLength = baseLength + len1 + len2 + len3;

                if (totalLength == targetLength) {
                    return "create " + name1 + " as " + name2 + " join " + name3;
                }
                else if (totalLength < targetLength) {
                    int diff = targetLength - totalLength;

                    // Распределяем дополнительные пробелы между словами
                    std::vector<std::string> parts = {"create", name1, "as", name2, "join", name3};
                    std::vector<int> spaces(parts.size() - 1, 1); // минимум 1 пробел между частями

                    // Распределяем оставшиеся пробелы
                    for (int i = 0; i < diff; i++) {
                        spaces[i % spaces.size()]++;
                    }

                    // Собираем результат
                    std::string result;
                    for (size_t i = 0; i < parts.size(); i++) {
                        result += parts[i];
                        if (i < spaces.size()) {
                            result += std::string(spaces[i], ' ');
                        }
                    }

                    if (result.length() == targetLength) {
                        return result;
                    }
                }
            }
        }

        // Если не получилось после всех попыток, генерируем простую строку с пробелами
        // но стараемся распределить пробелы равномерно
        return generateBalancedString(targetLength);
    }

    // Запасной метод - генерирует сбалансированную строку
    std::string generateBalancedString(int targetLength) {
        // Берем простой шаблон и равномерно распределяем пробелы
        std::string relName = generateIdentifierFixed(8);
        std::string attr1 = generateIdentifierFixed(5);
        std::string attr2 = generateIdentifierFixed(5);
        std::string attr3 = generateIdentifierFixed(5);

        std::string base = "create " + relName + " ( " + attr1 + ", " + attr2 + ", " + attr3 + " )";
        int baseLen = base.length();

        if (baseLen <= targetLength) {
            int diff = targetLength - baseLen;

            // Находим все пробелы
            std::vector<size_t> spacePos;
            for (size_t i = 0; i < base.length(); i++) {
                if (base[i] == ' ') spacePos.push_back(i);
            }

            if (!spacePos.empty()) {
                std::string result = base;
                int spacesPerPosition = diff / spacePos.size();
                int extraSpaces = diff % spacePos.size();

                // Добавляем пробелы в обратном порядке, чтобы не сбивать индексы
                for (int i = spacePos.size() - 1; i >= 0; i--) {
                    int spacesToAdd = spacesPerPosition + (i < extraSpaces ? 1 : 0);
                    if (spacesToAdd > 0) {
                        result.insert(spacePos[i], std::string(spacesToAdd, ' '));
                    }
                }

                if (result.length() == targetLength) {
                    return result;
                }
            }
        }

        // Если все сломалось, возвращаем что-то базовое
        return "create test_table ( id, name, age )" +
               std::string(targetLength - 33, ' ');
    }

    std::vector<std::string> generateAllLengths() {
        std::vector<int> lengths = {1000, 5000, 10000, 20000, 30000, 40000,
                                     50000, 60000, 70000, 80000, 90000, 100000};

        std::vector<std::string> res;
        for (int len : lengths) {
            std::string generated = generateString(len);
            res.push_back(generated);

        }
        return res;
    }
};





int main() {
    SQLGenerator generator;

    // Пример генерации одной строки длиной 1000 символов
    std::string result = generator.generateString(1000);
    //std::cout << "Example string (1000 chars):\n" << result << "\n\n";

    auto v_regex = std::make_unique<regex_version>();
    auto v_smc = std::make_unique<lexer_context>();
    auto v_lex = std::make_unique<lex_version>();

    // Генерация для всех указанных длин
    /*
    auto all_strings = generator.generateAllLengths();
    for (auto& string : all_strings) {
        std::ofstream file("../files/" + std::to_string(string.size()) + ".txt");
        file << string;
        file.close();
    }
    */
    std::ofstream file_out_reg("../time_results/regex.txt");
    for (int i = 0; i < 12; i++) {
        std::vector<std::string> strings = {100, ""};
        for (auto& str : strings) {
            if (i == 0)
                str = generator.generateString(1000);
            else if (i == 1)
                str = generator.generateString(5000);
            else
                str = generator.generateString((i-1)*10000);
        }

        std::pair<STATE, std::pair<std::string, std::vector<std::string>>> res;
        auto start = std::chrono::high_resolution_clock::now();
        for (auto& str : strings) {
            res = v_regex->lexline(str);
        }
        auto end = std::chrono::high_resolution_clock::now();

        auto duration = end - start;
        auto time = std::chrono::duration_cast<std::chrono::microseconds>(duration).count();
        double avg_time = time / 100;
        if (res.first != STATE::NO)
            std::cout << "SUCCESS" << std::endl;

        file_out_reg << avg_time << std::endl;
        strings.clear();
    }
    file_out_reg.close();


    std::ofstream file_out_smc("../time_results/smc.txt");
    for (int i = 0; i < 12; i++) {
        std::pair<STATE, std::pair<std::string, std::vector<std::string>>> res;

        std::vector<std::string> strings = {100, ""};
        for (auto& str : strings) {
            if (i == 0)
                str = generator.generateString(1000);
            else if (i == 1)
                str = generator.generateString(5000);
            else
                str = generator.generateString((i-1)*10000);
        }

        auto start = std::chrono::high_resolution_clock::now();
        for (auto& str : strings)
            res= v_smc->lexline(str);
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = end - start;
        auto time = std::chrono::duration_cast<std::chrono::microseconds>(duration).count();
        double avg_time = time / 100;
        if (res.first != STATE::NO)
            std::cout << "SUCCESS" << std::endl;


        file_out_smc<< avg_time << std::endl;
        strings.clear();
    }
    file_out_smc.close();



    std::ofstream file_out_lex("../time_results/lex.txt");
    for (int i = 0; i < 12; i++) {
        std::pair<STATE, std::pair<std::string, std::vector<std::string>>> res;
        std::vector<std::string> strings = {100, ""};
        for (auto& str : strings) {
            if (i == 0)
                str = generator.generateString(1000);
            else if (i == 1)
                str = generator.generateString(5000);
            else
                str = generator.generateString((i-1)*10000);
        }


        auto start = std::chrono::high_resolution_clock::now();
        for (auto& str : strings) {
            res= v_lex->lexline(str);
        }
        auto end = std::chrono::high_resolution_clock::now();

        auto duration = end - start;
        auto time = std::chrono::duration_cast<std::chrono::microseconds>(duration).count();
        if (res.first != STATE::NO)
            std::cout << "SUCCESS" << std::endl;
        double avg_time = time / 100;
        file_out_lex << avg_time << std::endl;
        strings.clear();
    }
    file_out_lex.close();
    return 0;
}