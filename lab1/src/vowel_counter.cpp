#include <string>
#include <stdexcept>
#include <algorithm>
#include <cctype>

int countVowels(const std::string& input) {
    if (input.empty()) {
        throw std::invalid_argument("Input string is empty");
    }

    const std::string vowels = "aeiou";
    int count = 0;

    for (char ch : input) {
        if (!std::islower(ch) && !std::isspace(ch)) {
            // Проверяем только строчные латинские буквы, а также пробелы
            throw std::invalid_argument("Input contains invalid characters (must be lowercase Latin letters or spaces)");
        }
        // Проверяем только латинские гласные
        if (vowels.find(ch) != std::string::npos) {
            count++;
        }
    }

    return count;
}
