#include <iostream>
#include <cctype>
#include "vowel_counter.h"

// Функция для получения строки от пользователя с проверкой на пустую строку
std::string getInput() {
    std::string input;
    std::cout << "Enter a string: ";
    std::getline(std::cin, input);
    
    if (input.empty()) {
        throw std::invalid_argument("Input cannot be empty!");
    }

    return input;
}

// Функция для проверки строки на наличие недопустимых символов
void validateInput(const std::string& input) {
    for (char ch : input) {
        if (!std::isalpha(ch) && !isspace(ch)) {
            throw std::invalid_argument("Only alphabetic characters and spaces are allowed");
        }
    }
}

// Функция для отображения результата
void displayResult(int vowelCount) {
    std::cout << "Number of vowels: " << vowelCount << std::endl;
}

// Функция для завершения программы
void exitProgram() {
    char exitChar;
    std::cout << "Press 'q' to exit, or any other key to continue..." << std::endl;
    std::cin >> exitChar;
    if (exitChar == 'q') {
        std::cout << "Exiting program..." << std::endl;
    }
}

int main() {
    try {
        std::string input = getInput();

        // Проверка допустимости символов
        validateInput(input);

        int vowelCount = countVowels(input);
        displayResult(vowelCount);

        exitProgram();
    } catch (const std::invalid_argument& e) {
        std::cerr << "Invalid input: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "An error occurred: " << e.what() << std::endl;
    }

    return 0;
}
