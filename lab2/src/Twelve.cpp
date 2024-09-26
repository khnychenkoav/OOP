#include "Twelve.h"
#include <algorithm>
#include <stdexcept>
#include <cstring>
#include "./TwelveExceptions.h"

Twelve::Twelve() : digits(nullptr), length(0) {}

Twelve::Twelve(const unsigned char* digitsArray, size_t size) : digits(new unsigned char[size]), length(size) {
    std::copy(digitsArray, digitsArray + size, digits);
    normalize();
}

Twelve::Twelve(const std::string& hexStr) {
    if (!validateInput(hexStr)) {
        throw std::invalid_argument("Invalid input.");
    }

    length = hexStr.size();
    digits = new unsigned char[length];

    for (size_t i = 0; i < length; ++i) {
        char c = hexStr[i];
        if (c >= '0' && c <= '9') {
            digits[length - i - 1] = c - '0';
        } else if (c >= 'A' && c <= 'B') {
            digits[length - i - 1] = c - 'A' + 10;
        }
    }
    normalize();
}

Twelve::Twelve(const Twelve& other) {
    deepCopy(other);
}

Twelve::Twelve(Twelve&& other) noexcept : digits(other.digits), length(other.length) {
    other.digits = nullptr;
    other.length = 0;
}

void Twelve::clear() {
    delete[] digits;
    digits = nullptr;
    length = 0;
}

Twelve::~Twelve() {
    clear();
}

Twelve& Twelve::operator=(const Twelve& other) {
    if (this != &other) {
        clear();
        deepCopy(other);
    }
    return *this;
}

Twelve& Twelve::operator=(Twelve&& other) noexcept {
    if (this != &other) {
        delete[] digits;
        digits = other.digits;
        length = other.length;
        other.digits = nullptr;
        other.length = 0;
    }
    return *this;
}

Twelve& Twelve::operator+=(const Twelve& other) {
    *this = *this + other;
    return *this;
}

Twelve& Twelve::operator-=(const Twelve& other) {
    *this = *this - other;
    return *this;
}

Twelve& Twelve::operator*=(const Twelve& other) {
    *this = *this * other;
    return *this;
}

Twelve Twelve::operator+(const Twelve& other) const {
    size_t maxSize = std::max(length, other.length);
    Twelve result;
    result.resize(maxSize + 1);

    unsigned char carry = 0;
    for (size_t i = 0; i < maxSize || carry; ++i) {
        unsigned char a = (i < length) ? digits[i] : 0;
        unsigned char b = (i < other.length) ? other.digits[i] : 0;
        unsigned char sum = a + b + carry;
        carry = sum / 12;
        result.digits[i] = sum % 12;
    }

    if (carry > 0) {
        result.digits[maxSize] = carry;
    }

    result.normalize();
    return result;
}

Twelve Twelve::operator-(const Twelve& other) const {
    if (*this < other) {
        throw NegativeResultException();
    }

    size_t maxSize = length;
    Twelve result;
    result.resize(maxSize);

    unsigned char borrow = 0;
    for (size_t i = 0; i < maxSize; ++i) {
        char a = digits[i];
        char b = (i < other.length) ? other.digits[i] : 0;
        char diff = a - b - borrow;
        if (diff < 0) {
            diff += 12;
            borrow = 1;
        } else {
            borrow = 0;
        }
        result.digits[i] = diff;
    }

    result.normalize();
    return result;
}

Twelve Twelve::operator*(const Twelve& other) const {
    size_t resultSize = length + other.length;
    Twelve result;
    result.resize(resultSize);

    for (size_t i = 0; i < length; ++i) {
        unsigned char carry = 0;
        for (size_t j = 0; j < other.length; ++j) {
            unsigned char product = digits[i] * other.digits[j] + result.digits[i + j] + carry;
            carry = product / 12;
            result.digits[i + j] = product % 12;
        }
        if (carry > 0) {
            result.digits[i + other.length] = carry;
        }
    }

    result.normalize();
    return result;
}

bool Twelve::operator==(const Twelve& other) const {
    if (length != other.length) return false;
    for (size_t i = 0; i < length; ++i) {
        if (digits[i] != other.digits[i]) return false;
    }
    return true;
}

bool Twelve::operator!=(const Twelve& other) const {
    return !(*this == other);
}

bool Twelve::operator<(const Twelve& other) const {
    if (length != other.length) return length < other.length;
    for (size_t i = length; i > 0; --i) {
        if (digits[i - 1] != other.digits[i - 1]) return digits[i - 1] < other.digits[i - 1];
    }
    return false;
}

bool Twelve::operator>(const Twelve& other) const {
    return other < *this;
}

bool Twelve::operator<=(const Twelve& other) const {
    return !(other < *this);
}

bool Twelve::operator>=(const Twelve& other) const {
    return !(*this < other);
}

unsigned long long Twelve::toDecimal() const {
    unsigned long long decimal = 0;
    unsigned long long power = 1;
    for (size_t i = 0; i < length; ++i) {
        decimal += digits[i] * power;
        power *= 12;
    }
    return decimal;
}

Twelve Twelve::fromDecimal(unsigned long long decimal) {
    if (decimal == 0) return Twelve();

    Twelve result;
    while (decimal > 0) {
        unsigned long long remainder = decimal % 12;
        result.resize(result.size() + 1);
        result.digits[result.size() - 1] = remainder;
        decimal /= 12;
    }
    result.normalize();
    return result;
}

std::ostream& operator<<(std::ostream& os, const Twelve& num) {
    return os << num.toString();
}

bool Twelve::isZero() const {
    for (size_t i = 0; i < length; ++i) {
        if (digits[i] != 0) return false;
    }
    return true;
}

size_t Twelve::size() const {
    return length;
}

void Twelve::print() const {
    std::cout << toString() << std::endl;
}

std::string Twelve::toString() const {
    std::string str;
    for (size_t i = 0; i < length; ++i) {
        char c = digits[length - i - 1];
        str += (c < 10) ? '0' + c : 'A' + (c - 10);
    }
    return str;
}

bool Twelve::validateInput(const std::string& input) {
    for (char c : input) {
        if (!((c >= '0' && c <= '9') || (c >= 'A' && c <= 'B'))) {
            return false;
        }
    }
    return true;
}

void Twelve::normalize() {
    while (length > 1 && digits[length - 1] == 0) {
        --length;
    }
}

void Twelve::resize(size_t newSize) {
    unsigned char* newDigits = new unsigned char[newSize]();
    std::copy(digits, digits + std::min(length, newSize), newDigits);
    delete[] digits;
    digits = newDigits;
    length = newSize;
}

void Twelve::deepCopy(const Twelve& other) {
    digits = new unsigned char[other.length];
    length = other.length;
    std::copy(other.digits, other.digits + other.length, digits);
}
