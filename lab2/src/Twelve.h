#pragma once
#include <iostream>
#include <stdexcept>
#include <string>
#include "TwelveExceptions.h"

class Twelve {
public:
    Twelve();
    explicit Twelve(const unsigned char* digits, size_t size);
    explicit Twelve(const std::string& hexStr);
    Twelve(const Twelve& other);
    Twelve(Twelve&& other) noexcept;
    ~Twelve();

    Twelve& operator=(const Twelve& other);
    Twelve& operator=(Twelve&& other) noexcept;

    Twelve& operator+=(const Twelve& other);
    Twelve& operator-=(const Twelve& other);
    Twelve& operator*=(const Twelve& other);

    Twelve operator+(const Twelve& other) const;
    Twelve operator-(const Twelve& other) const;
    Twelve operator*(const Twelve& other) const;

    bool operator==(const Twelve& other) const;
    bool operator!=(const Twelve& other) const;
    bool operator<(const Twelve& other) const;
    bool operator>(const Twelve& other) const;
    bool operator<=(const Twelve& other) const;
    bool operator>=(const Twelve& other) const;

    void print() const;
    size_t size() const;
    std::string toString() const;

    static bool validateInput(const std::string& input);
    bool isZero() const;

    static Twelve fromDecimal(unsigned long long decimal);
    unsigned long long toDecimal() const;

    friend std::ostream& operator<<(std::ostream& os, const Twelve& num);

private:
    unsigned char* digits;
    size_t length;
    void normalize();
    void resize(size_t newSize);
    void deepCopy(const Twelve& other);
    void clear();
};
