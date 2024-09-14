#include <string>
#include <stdexcept>
#include <cctype>

int countVowels(const std::string& input) {
    if (input.empty()) {
        throw std::invalid_argument("Input string is empty");
    }

    const std::string vowels = "aeiouy";
    int count = 0;

    for (char ch : input) {
        if (!std::islower(ch) && !std::isspace(ch)) {
            throw std::invalid_argument("Input contains invalid characters (must be lowercase Latin letters or spaces)");
        }
        if (vowels.find(ch) != std::string::npos) {
            count++;
        }
    }

    return count;
}
