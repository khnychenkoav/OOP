#include <iostream>
#include <string>
#include <limits>
#include "Twelve.h"
#include "TwelveExceptions.h"

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
        if (!(std::cin >> choice)) {
            std::cerr << "Invalid input. Please enter a number.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        try {
            switch (choice) {
                case 1: {
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
                    if (!numbersEntered) {
                        std::cout << "Please enter the numbers first (option 1).\n";
                        break;
                    }
                    Twelve result = num1 + num2;
                    std::cout << "Result of addition: " << result.toString() << "\n";
                    break;
                }
                case 3: {
                    if (!numbersEntered) {
                        std::cout << "Please enter the numbers first (option 1).\n";
                        break;
                    }
                    Twelve result = num1 - num2;
                    std::cout << "Result of subtraction: " << result.toString() << "\n";
                    break;
                }
                case 4: {
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
        } catch (const NegativeResultException& e) {
            std::cerr << "Error: Subtraction result is negative. " << e.what() << "\n";
        } catch (const std::exception& e) {
            std::cerr << "An error occurred: " << e.what() << "\n";
        }
    }

    return 0;
}
