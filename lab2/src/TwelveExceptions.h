#pragma once
#include <stdexcept>
#include <string>

class TwelveException : public std::runtime_error {
public:
    explicit TwelveException(const std::string& message) 
        : std::runtime_error("TwelveException: " + message) {}

    virtual std::string details() const {
        return what();
    }
};

class InvalidCharacterException : public TwelveException {
private:
    char invalidChar;
    size_t position;

public:
    InvalidCharacterException(char invalidChar, size_t pos = 0) 
        : TwelveException("Invalid character '" + std::string(1, invalidChar) + "' at position " + std::to_string(pos)),
          invalidChar(invalidChar), position(pos) {}

    char getInvalidChar() const {
        return invalidChar;
    }

    std::string details() const override {
        return "Character '" + std::string(1, invalidChar) + "' is not valid at position " + std::to_string(position);
    }
};

class NegativeResultException : public TwelveException {
public:
    NegativeResultException() 
        : TwelveException("Result cannot be negative") {}

    std::string details() const override {
        return "Negative result exception occurred: result of subtraction is less than zero.";
    }
};

class OverflowException : public TwelveException {
private:
    unsigned char carryValue;

public:
    OverflowException(unsigned char carry = 0) 
        : TwelveException("Overflow occurred during arithmetic operation, carry: " + std::to_string(carry)),
          carryValue(carry) {}

    unsigned char getCarryValue() const {
        return carryValue;
    }

    std::string details() const override {
        return "Overflow with carry value: " + std::to_string(carryValue);
    }
};

class DivisionByZeroException : public std::runtime_error {
public:
    DivisionByZeroException() : std::runtime_error("Division by zero is not allowed") {}
};