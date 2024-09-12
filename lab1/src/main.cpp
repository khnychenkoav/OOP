#include <iostream>
#include <cctype>
#include "vowel_counter.h"

std::string getInput() {
    std::string input;
    while (true) {
        std::cout << "Enter a string: ";
        std::getline(std::cin, input);
        
        if (input.empty()) {
            std::cerr << "Input cannot be empty! Please try again." << std::endl;
        } else {
            break;
        }
    }

    return input;
}

void validateInput(const std::string& input) {
    for (char ch : input) {
        if (!std::isalpha(ch) && !isspace(ch)) {
            throw std::invalid_argument("Only alphabetic characters and spaces are allowed");
        }
    }
}

void displayResult(int vowelCount) {
    std::cout << "Number of vowels: " << vowelCount << std::endl;
}

bool exitProgram() {
    char exitChar;
    std::cout << "Press 'q' to exit, or any other key to continue..." << std::endl;
    std::cin >> exitChar;
    std::cin.ignore();
    return exitChar == 'q';
}

int main() {
    while (true) {
        try {
            std::string input = getInput();

            validateInput(input);

            int vowelCount = countVowels(input);
            displayResult(vowelCount);

            if (exitProgram()) {
                std::cout << "Exiting program..." << std::endl;
                break;
            }
        } catch (const std::invalid_argument& e) {
            std::cerr << "Invalid input: " << e.what() << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "An error occurred: " << e.what() << std::endl;
        }
    }

    return 0;
}
