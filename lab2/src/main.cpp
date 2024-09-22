#include <iostream>
#include <string>
#include "Twelve.h"

void displayMenu() {
    std::cout << "\n--- Menu ---\n";
    std::cout << "1. Input two 12-base numbers\n";
    std::cout << "2. Add numbers\n";
    std::cout << "3. Subtract numbers\n";
    std::cout << "4. Compare numbers\n";
    std::cout << "5. Print numbers\n";
    std::cout << "6. Exit\n";
    std::cout << "Choose an option: ";
}

int main() {
    Twelve num1, num2;
    bool numbersEntered = false;
    int choice = 0;

    while (choice != 6) {
        displayMenu();
        std::cin >> choice;

        try {
            switch (choice) {
                case 1: {
                    // Ввод двух чисел
                    std::string input1, input2;
                    std::cout << "Enter first 12-base number (valid digits: 0-9, A-B): ";
                    std::cin >> input1;
                    num1 = Twelve(input1);

                    std::cout << "Enter second 12-base number (valid digits: 0-9, A-B): ";
                    std::cin >> input2;
                    num2 = Twelve(input2);

                    numbersEntered = true;
                    std::cout << "Numbers entered successfully!\n";
                    break;
                }
                case 2: {
                    // Сложение чисел
                    if (!numbersEntered) {
                        std::cout << "Please enter the numbers first (option 1).\n";
                        break;
                    }
                    Twelve result = num1 + num2;
                    std::cout << "Result of addition: " << result.toString() << "\n";
                    break;
                }
                case 3: {
                    // Вычитание чисел
                    if (!numbersEntered) {
                        std::cout << "Please enter the numbers first (option 1).\n";
                        break;
                    }
                    Twelve result = num1 - num2;
                    std::cout << "Result of subtraction: " << result.toString() << "\n";
                    break;
                }
                case 4: {
                    // Сравнение чисел
                    if (!numbersEntered) {
                        std::cout << "Please enter the numbers first (option 1).\n";
                        break;
                    }
                    std::cout << "Comparing numbers:\n";
                    if (num1 == num2) {
                        std::cout << "Numbers are equal.\n";
                    } else if (num1 > num2) {
                        std::cout << "First number is greater.\n";
                    } else {
                        std::cout << "Second number is greater.\n";
                    }
                    break;
                }
                case 5: {
                    // Печать чисел
                    if (!numbersEntered) {
                        std::cout << "Please enter the numbers first (option 1).\n";
                        break;
                    }
                    std::cout << "First number: " << num1.toString() << "\n";
                    std::cout << "Second number: " << num2.toString() << "\n";
                    break;
                }
                case 6: {
                    std::cout << "Exiting the program...\n";
                    break;
                }
                default: {
                    std::cout << "Invalid option. Please try again.\n";
                    break;
                }
            }
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << "\n";
        }
    }

    return 0;
}
