#ifndef SQUARE_TPP
#define SQUARE_TPP

#include "Square.hpp"
#include <cmath>
#include <iostream>

template <Scalar T>
Square<T>::Square() {
    for (auto& point : points_) {
        point = std::make_unique<Point<T>>();
    }
}

template <Scalar T>
Square<T>::Square(const std::array<Point<T>, 4>& points) {
    for (size_t i = 0; i < 4; ++i) {
        points_[i] = std::make_unique<Point<T>>(points[i]);
    }
}

template <Scalar T>
Square<T>::Square(const Square<T>& other) {
    for (size_t i = 0; i < 4; ++i) {
        points_[i] = std::make_unique<Point<T>>(*other.points_[i]);
    }
}

template <Scalar T>
Square<T>::Square(Square<T>&& other) noexcept : points_(std::move(other.points_)) {}

template <Scalar T>
Point<T> Square<T>::GeometricCenter() const {
    T x = T(), y = T();
    for (const auto& point : points_) {
        x += point->x();
        y += point->y();
    }
    return Point<T>(x / 4, y / 4);
}

template <Scalar T>
void Square<T>::Print(std::ostream& os) const {
    os << "Square vertices:\n";
    for (const auto& point : points_) {
        os << *point << "\n";
    }
}

template <Scalar T>
void Square<T>::Read(std::istream& is) {
    while (true) {
        for (auto& point : points_) {
            std::cout << "Enter point (x y): ";
            is >> *point;
        }

        if (ValidateSquare()) {
            std::cout << "The square is valid.\n";
            break;
        } else {
            std::cout << "The points do not form a valid square. Using suggested points.\n";
            SuggestCorrectPoints();
            UseSuggestedPoints();
            break; // Для простоты используем предложенные точки
        }
    }
}

template <Scalar T>
bool Square<T>::ValidateSquare() const {
    const double tolerance = 1e-3;
    double side1 = std::hypot(static_cast<double>(points_[1]->x() - points_[0]->x()), static_cast<double>(points_[1]->y() - points_[0]->y()));
    double side2 = std::hypot(static_cast<double>(points_[2]->x() - points_[1]->x()), static_cast<double>(points_[2]->y() - points_[1]->y()));
    double side3 = std::hypot(static_cast<double>(points_[3]->x() - points_[2]->x()), static_cast<double>(points_[3]->y() - points_[2]->y()));
    double side4 = std::hypot(static_cast<double>(points_[0]->x() - points_[3]->x()), static_cast<double>(points_[0]->y() - points_[3]->y()));

    return (std::abs(side1 - side2) < tolerance) && (std::abs(side2 - side3) < tolerance) && (std::abs(side3 - side4) < tolerance);
}

template <Scalar T>
void Square<T>::SuggestCorrectPoints() const {
    auto center = GeometricCenter();
    double radius = std::hypot(static_cast<double>(points_[0]->x() - center.x()), static_cast<double>(points_[0]->y() - center.y()));
    const double angleStep = M_PI / 2;

    std::cout << "Suggested correct points for a square:\n";
    for (size_t i = 0; i < 4; ++i) {
        double angle = i * angleStep;
        T x = static_cast<T>(center.x() + radius * std::cos(angle));
        T y = static_cast<T>(center.y() + radius * std::sin(angle));
        std::cout << "(" << x << ", " << y << ")\n";
    }
}

template <Scalar T>
void Square<T>::UseSuggestedPoints() {
    auto center = GeometricCenter();
    double radius = std::hypot(static_cast<double>(points_[0]->x() - center.x()), static_cast<double>(points_[0]->y() - center.y()));
    const double angleStep = M_PI / 2;

    for (size_t i = 0; i < 4; ++i) {
        double angle = i * angleStep;
        T x = static_cast<T>(center.x() + radius * std::cos(angle));
        T y = static_cast<T>(center.y() + radius * std::sin(angle));
        points_[i]->x(x);
        points_[i]->y(y);
    }
}

template <Scalar T>
Square<T>::operator double() const {
    double side = std::hypot(static_cast<double>(points_[0]->x() - points_[1]->x()), static_cast<double>(points_[0]->y() - points_[1]->y()));
    return side * side;
}

template <Scalar T>
Square<T>& Square<T>::operator=(const Square<T>& other) {
    if (this != &other) {
        for (size_t i = 0; i < 4; ++i) {
            points_[i] = std::make_unique<Point<T>>(*other.points_[i]);
        }
    }
    return *this;
}

template <Scalar T>
Square<T>& Square<T>::operator=(Square<T>&& other) noexcept {
    if (this != &other) {
        points_ = std::move(other.points_);
    }
    return *this;
}

template <Scalar T>
bool Square<T>::operator==(const Figure<T>& other) const {
    const Square<T>* otherSquare = dynamic_cast<const Square<T>*>(&other);
    if (!otherSquare) return false;
    for (size_t i = 0; i < 4; ++i) {
        if (!(*points_[i] == *otherSquare->points_[i])) {
            return false;
        }
    }
    return true;
}

template <Scalar T>
void Square<T>::Draw(sf::RenderWindow& window) const {
    sf::ConvexShape squareShape;
    squareShape.setPointCount(4);
    for (size_t i = 0; i < 4; ++i) {
        squareShape.setPoint(i, sf::Vector2f(static_cast<float>(points_[i]->x()), static_cast<float>(points_[i]->y())));
    }
    squareShape.setFillColor(sf::Color::Blue);
    window.draw(squareShape);
}

template <Scalar T>
std::ostream& operator<<(std::ostream& os, const Square<T>& square) {
    square.Print(os);
    return os;
}

template <Scalar T>
std::istream& operator>>(std::istream& is, Square<T>& square) {
    square.Read(is);
    return is;
}

#endif
