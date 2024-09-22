#include "Twelve.h"
#include <algorithm>
#include <sstream>

// Конструктор по умолчанию
Twelve::Twelve() : digits(1, 0) {}

// Конструктор из вектора цифр
Twelve::Twelve(const std::vector<unsigned char>& digits) : digits(digits) {
    if (digits.empty()) {
        throw std::invalid_argument("Digits vector cannot be empty");
    }
    normalize();
}

size_t Twelve::size() const {
    return digits.size();
}

// Конструктор из строки (предполагается, что строка содержит двенадцатиричные цифры)
Twelve::Twelve(const std::string& hexStr) {
    if (hexStr.empty()) {
        throw std::invalid_argument("String cannot be empty");
    }
    for (char c : hexStr) {
        if (c >= '0' && c <= '9') {
            digits.push_back(c - '0');
        } else if (c >= 'A' && c <= 'B') {
            digits.push_back(c - 'A' + 10);
        } else {
            throw InvalidCharacterException(c); // Используем пользовательское исключение
        }
    }
    std::reverse(digits.begin(), digits.end()); // Младшая цифра первой
    normalize();
}

// Конструктор копирования
Twelve::Twelve(const Twelve& other) : digits(other.digits) {}

// Перемещающий конструктор
Twelve::Twelve(Twelve&& other) noexcept : digits(std::move(other.digits)) {
    if (digits.empty()) {
        digits.push_back(0); // Устанавливаем объект в "0"
    }
    other.digits.clear();
    other.digits.push_back(0);
}

// Деструктор
Twelve::~Twelve() {}

// Оператор присваивания копированием
Twelve& Twelve::operator=(const Twelve& other) {
    if (this != &other) {
        digits = other.digits;
    }
    return *this;
}

// Оператор присваивания перемещением
Twelve& Twelve::operator=(Twelve&& other) noexcept {
    if (this != &other) {
        digits = std::move(other.digits);
        if (digits.empty()) {
            digits.push_back(0); // Устанавливаем объект в "0"
        }
        other.digits.clear();
        other.digits.push_back(0);
    }
    return *this;
}

// Оператор сложения
Twelve Twelve::operator+(const Twelve& other) const {
    Twelve result;
    size_t maxSize = std::max(digits.size(), other.digits.size());
    result.digits.resize(maxSize);

    unsigned char carry = 0;
    for (size_t i = 0; i < maxSize; ++i) {
        unsigned char a = (i < digits.size()) ? digits[i] : 0;
        unsigned char b = (i < other.digits.size()) ? other.digits[i] : 0;
        unsigned char sum = a + b + carry;
        carry = sum / 12;
        result.digits[i] = sum % 12;

        if (carry > 0 && i == maxSize - 1) {
            if (carry > 12) {
                throw OverflowException(); // Проверка на переполнение
            }
            result.digits.push_back(carry);
        }
    }

    return result;
}

// Оператор вычитания
Twelve Twelve::operator-(const Twelve& other) const {
    if (*this < other) {
        throw NegativeResultException(); // Проверка на отрицательный результат
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

// Оператор присваивающего сложения
Twelve& Twelve::operator+=(const Twelve& other) {
    *this = *this + other;
    return *this;
}

// Оператор присваивающего вычитания
Twelve& Twelve::operator-=(const Twelve& other) {
    *this = *this - other;
    return *this;
}

// Оператор сравнения ==
bool Twelve::operator==(const Twelve& other) const {
    return digits == other.digits;
}

// Оператор сравнения !=
bool Twelve::operator!=(const Twelve& other) const {
    return !(*this == other);
}

// Оператор сравнения <
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

// Оператор сравнения >
bool Twelve::operator>(const Twelve& other) const {
    return other < *this;
}

// Вывод числа
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

// Нормализация числа (удаление ведущих нулей)
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
