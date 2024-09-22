#pragma once
#include <stdexcept>
#include <string>

// Базовый класс для исключений, связанных с классом Twelve
class TwelveException : public std::runtime_error {
public:
    explicit TwelveException(const std::string& message) : std::runtime_error(message) {}
};

// Исключение для некорректных символов в строке
class InvalidCharacterException : public TwelveException {
public:
    InvalidCharacterException(char invalidChar) 
        : TwelveException("Invalid character in string: " + std::string(1, invalidChar)) {}
};

// Исключение для отрицательного результата при вычитании
class NegativeResultException : public TwelveException {
public:
    NegativeResultException() : TwelveException("Result cannot be negative") {}
};

// Исключение для переполнения при сложении
class OverflowException : public TwelveException {
public:
    OverflowException() : TwelveException("Overflow occurred during arithmetic operation") {}
};
