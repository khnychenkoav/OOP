#include "Twelve.h"
#include <algorithm>
#include <sstream>
#include <stdexcept>

Twelve::Twelve() : digits(1, 0) {}

Twelve::Twelve(const std::vector<unsigned char>& digits) : digits(digits) {
    if (digits.empty()) {
        throw std::invalid_argument("Digits vector cannot be empty");
    }
    normalize();
}

size_t Twelve::size() const {
    return digits.size();
}

Twelve::Twelve(const std::string& hexStr) {
    if (hexStr.empty()) {
        throw std::invalid_argument("String cannot be empty");
    }
    for (char c : hexStr) {
        if (c >= '0' && c <= '9') {
            digits.push_back(c - '0');
        } else if (c >= 'A' && c <= 'B') {
            digits.push_back(c - 'A' + 10);
        } else if (c >= 'a' && c <= 'b') {
            digits.push_back(c - 'a' + 10);
        } else {
            throw InvalidCharacterException(c);
        }
    }
    std::reverse(digits.begin(), digits.end());
    normalize();
}

Twelve::Twelve(const Twelve& other) : digits(other.digits) {}

Twelve::Twelve(Twelve&& other) noexcept : digits(std::move(other.digits)) {
    if (digits.empty()) {
        digits.push_back(0);
    }
    other.digits.clear();
    other.digits.push_back(0);
}

Twelve::~Twelve() {}

Twelve& Twelve::operator=(const Twelve& other) {
    if (this != &other) {
        digits = other.digits;
    }
    return *this;
}

Twelve& Twelve::operator=(Twelve&& other) noexcept {
    if (this != &other) {
        digits = std::move(other.digits);
        if (digits.empty()) {
            digits.push_back(0);
        }
        other.digits.clear();
        other.digits.push_back(0);
    }
    return *this;
}

Twelve Twelve::operator+(const Twelve& other) const {
    Twelve result;
    size_t maxSize = std::max(digits.size(), other.digits.size());
    result.digits.resize(maxSize);

    unsigned char carry = 0;
    const size_t maxAllowedSize = 10;

    for (size_t i = 0; i < maxSize; ++i) {
        unsigned char a = (i < digits.size()) ? digits[i] : 0;
        unsigned char b = (i < other.digits.size()) ? other.digits[i] : 0;
        unsigned char sum = a + b + carry;
        carry = sum / 12;
        result.digits[i] = sum % 12;
    }

    if (carry > 0) {
        result.digits.push_back(carry);
    }

    if (result.digits.size() > maxAllowedSize) {
        throw OverflowException();
    }

    return result;
}

Twelve Twelve::operator-(const Twelve& other) const {
    if (*this < other) {
        throw NegativeResultException();
    }

    Twelve result;
    size_t maxSize = std::max(digits.size(), other.digits.size());
    result.digits.resize(maxSize);

    unsigned char borrow = 0;
    for (size_t i = 0; i < maxSize; ++i) {
        unsigned char a = (i < digits.size()) ? digits[i] : 0;
        unsigned char b = (i < other.digits.size()) ? other.digits[i] : 0;
        if (a < b + borrow) {
            result.digits[i] = (a + 12) - (b + borrow);
            borrow = 1;
        } else {
            result.digits[i] = a - (b + borrow);
            borrow = 0;
        }
    }

    result.normalize();
    return result;
}

Twelve& Twelve::operator+=(const Twelve& other) {
    *this = *this + other;
    return *this;
}

Twelve& Twelve::operator-=(const Twelve& other) {
    *this = *this - other;
    return *this;
}

bool Twelve::operator==(const Twelve& other) const {
    return digits == other.digits;
}

bool Twelve::operator!=(const Twelve& other) const {
    return !(*this == other);
}

bool Twelve::operator<(const Twelve& other) const {
    if (digits.size() != other.digits.size()) {
        return digits.size() < other.digits.size();
    }
    for (int i = digits.size() - 1; i >= 0; --i) {
        if (digits[i] != other.digits[i]) {
            return digits[i] < other.digits[i];
        }
    }
    return false;
}

bool Twelve::operator>(const Twelve& other) const {
    return other < *this;
}

void Twelve::print() const {
    for (int i = digits.size() - 1; i >= 0; --i) {
        if (digits[i] < 10) {
            std::cout << (char)('0' + digits[i]);
        } else {
            std::cout << (char)('A' + (digits[i] - 10));
        }
    }
    std::cout << std::endl;
}

void Twelve::normalize() {
    while (digits.size() > 1 && digits.back() == 0) {
        digits.pop_back();
    }
    if (digits.empty()) {
        digits.push_back(0);
    }
}

std::ostream& operator<<(std::ostream& os, const Twelve& num) {
    for (int i = num.digits.size() - 1; i >= 0; --i) {
        if (num.digits[i] < 10) {
            os << (char)('0' + num.digits[i]);
        } else {
            os << (char)('A' + (num.digits[i] - 10));
        }
    }
    return os;
}

std::string Twelve::toString() const {
    std::ostringstream oss;
    for (int i = size() - 1; i >= 0; --i) {
        if (digits[i] < 10) {
            oss << static_cast<char>('0' + digits[i]);
        } else {
            oss << static_cast<char>('A' + (digits[i] - 10));
        }
    }
    return oss.str();
}

Twelve Twelve::fromDecimal(unsigned long long decimal) {
    if (decimal == 0) {
        return Twelve();
    }

    std::vector<unsigned char> digits;
    while (decimal > 0) {
        digits.push_back(decimal % 12);
        decimal /= 12;
    }

    return Twelve(digits);
}

unsigned long long Twelve::toDecimal() const {
    unsigned long long decimal = 0;
    unsigned long long base = 1;

    for (unsigned char digit : digits) {
        decimal += digit * base;
        base *= 12;
    }

    return decimal;
}

Twelve Twelve::operator*(const Twelve& other) const {
    Twelve result = Twelve::fromDecimal(this->toDecimal() * other.toDecimal());
    if (result.digits.size() > 10) {
        throw OverflowException();
    }
    return result;
}

Twelve& Twelve::operator*=(const Twelve& other) {
    *this = *this * other;
    return *this;
}

Twelve Twelve::operator/(const Twelve& other) const {
    if (other.isZero()) {
        throw DivisionByZeroException();
    }

    Twelve result = Twelve::fromDecimal(this->toDecimal() / other.toDecimal());
    return result;
}

Twelve& Twelve::operator/=(const Twelve& other) {
    *this = *this / other;
    return *this;
}

bool Twelve::isZero() const {
    return digits.size() == 1 && digits[0] == 0;
}
