#pragma once
#include <iostream>
#include <vector>
#include <stdexcept>
#include <string>
#include "TwelveExceptions.h"

class Twelve {
public:
    Twelve();
    explicit Twelve(const std::vector<unsigned char>& digits);
    explicit Twelve(const std::string& hexStr);
    Twelve(const Twelve& other);
    Twelve(Twelve&& other) noexcept;
    ~Twelve();

    Twelve& operator=(const Twelve& other);
    Twelve& operator=(Twelve&& other) noexcept;

    Twelve operator+(const Twelve& other) const;
    Twelve operator-(const Twelve& other) const;

    Twelve& operator+=(const Twelve& other);
    Twelve& operator-=(const Twelve& other);

    bool operator==(const Twelve& other) const;
    bool operator!=(const Twelve& other) const;
    bool operator<(const Twelve& other) const;
    bool operator>(const Twelve& other) const;

    void print() const;
    size_t size() const;
    std::string toString() const;

    friend std::ostream& operator<<(std::ostream& os, const Twelve& num);

private:
    std::vector<unsigned char> digits;
    void normalize();
};
