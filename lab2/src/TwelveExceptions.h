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

class NegativeResultException : public TwelveException {
public:
    NegativeResultException() 
        : TwelveException("Result cannot be negative") {}

    std::string details() const override {
        return "Negative result exception occurred: result of subtraction is less than zero.";
    }
};
