#ifndef TRIANGLE_TPP
#define TRIANGLE_TPP

#include "Triangle.hpp"
#include <cmath>
#include <iostream>

template <Scalar T>
Triangle<T>::Triangle() {
    for (auto& point : points_) {
        point = std::make_unique<Point<T>>();
    }
}

template <Scalar T>
Triangle<T>::Triangle(const std::array<Point<T>, 3>& points) {
    for (size_t i = 0; i < 3; ++i) {
        points_[i] = std::make_unique<Point<T>>(points[i]);
    }
}

template <Scalar T>
Triangle<T>::Triangle(const Triangle<T>& other) {
    for (size_t i = 0; i < 3; ++i) {
        points_[i] = std::make_unique<Point<T>>(*other.points_[i]);
    }
}

template <Scalar T>
Triangle<T>::Triangle(Triangle<T>&& other) noexcept : points_(std::move(other.points_)) {}

template <Scalar T>
Point<T> Triangle<T>::GeometricCenter() const {
    T x = T(), y = T();
    for (const auto& point : points_) {
        x += point->x();
        y += point->y();
    }
    return Point<T>(x / 3, y / 3);
}

template <Scalar T>
void Triangle<T>::Print(std::ostream& os) const {
    os << "Triangle vertices:\n";
    for (const auto& point : points_) {
        os << *point << "\n";
    }
}

template <Scalar T>
void Triangle<T>::Read(std::istream& is) {
    while (true) {
        for (auto& point : points_) {
            std::cout << "Enter point (x y): ";
            is >> *point;
        }

        if (ValidateTriangle()) {
            std::cout << "The triangle is valid.\n";
            break;
        } else {
            std::cout << "The points do not form a valid equilateral triangle. Please re-enter points.\n";
            SuggestCorrectPoints();
            UseSuggestedPoints();
            break; // Для простоты используем предложенные точки
        }
    }
}

template <Scalar T>
bool Triangle<T>::ValidateTriangle() const {
    const double tolerance = 1e-3;
    double side1 = std::hypot(static_cast<double>(points_[1]->x() - points_[0]->x()), static_cast<double>(points_[1]->y() - points_[0]->y()));
    double side2 = std::hypot(static_cast<double>(points_[2]->x() - points_[1]->x()), static_cast<double>(points_[2]->y() - points_[1]->y()));
    double side3 = std::hypot(static_cast<double>(points_[2]->x() - points_[0]->x()), static_cast<double>(points_[2]->y() - points_[0]->y()));

    return (std::abs(side1 - side2) < tolerance) && (std::abs(side2 - side3) < tolerance);
}

template <Scalar T>
void Triangle<T>::SuggestCorrectPoints() const {
    auto center = GeometricCenter();
    double radius = std::hypot(static_cast<double>(points_[0]->x() - center.x()), static_cast<double>(points_[0]->y() - center.y()));
    const double angleStep = 2 * M_PI / 3;

    std::cout << "Suggested correct points for an equilateral triangle:\n";
    for (size_t i = 0; i < 3; ++i) {
        double angle = i * angleStep;
        T x = static_cast<T>(center.x() + radius * std::cos(angle));
        T y = static_cast<T>(center.y() + radius * std::sin(angle));
        std::cout << "(" << x << ", " << y << ")\n";
    }
}

template <Scalar T>
void Triangle<T>::UseSuggestedPoints() {
    auto center = GeometricCenter();
    double radius = std::hypot(static_cast<double>(points_[0]->x() - center.x()), static_cast<double>(points_[0]->y() - center.y()));
    const double angleStep = 2 * M_PI / 3;

    for (size_t i = 0; i < 3; ++i) {
        double angle = i * angleStep;
        T x = static_cast<T>(center.x() + radius * std::cos(angle));
        T y = static_cast<T>(center.y() + radius * std::sin(angle));
        points_[i]->x(x);
        points_[i]->y(y);
    }
}

template <Scalar T>
Triangle<T>::operator double() const {
    double x1 = static_cast<double>(points_[0]->x());
    double y1 = static_cast<double>(points_[0]->y());
    double x2 = static_cast<double>(points_[1]->x());
    double y2 = static_cast<double>(points_[1]->y());
    double x3 = static_cast<double>(points_[2]->x());
    double y3 = static_cast<double>(points_[2]->y());
    return std::abs((x1*(y2 - y3) + x2*(y3 - y1) + x3*(y1 - y2)) / 2.0);
}

template <Scalar T>
Triangle<T>& Triangle<T>::operator=(const Triangle<T>& other) {
    if (this != &other) {
        for (size_t i = 0; i < 3; ++i) {
            points_[i] = std::make_unique<Point<T>>(*other.points_[i]);
        }
    }
    return *this;
}

template <Scalar T>
Triangle<T>& Triangle<T>::operator=(Triangle<T>&& other) noexcept {
    if (this != &other) {
        points_ = std::move(other.points_);
    }
    return *this;
}

template <Scalar T>
bool Triangle<T>::operator==(const Figure<T>& other) const {
    const Triangle<T>* otherTriangle = dynamic_cast<const Triangle<T>*>(&other);
    if (!otherTriangle) return false;
    for (size_t i = 0; i < 3; ++i) {
        if (!(*points_[i] == *otherTriangle->points_[i])) {
            return false;
        }
    }
    return true;
}

template <Scalar T>
void Triangle<T>::Draw(sf::RenderWindow& window) const {
    sf::ConvexShape triangleShape;
    triangleShape.setPointCount(3);
    for (size_t i = 0; i < 3; ++i) {
        triangleShape.setPoint(i, sf::Vector2f(static_cast<float>(points_[i]->x()), static_cast<float>(points_[i]->y())));
    }
    triangleShape.setFillColor(sf::Color::Green);
    window.draw(triangleShape);
}

template <Scalar T>
std::ostream& operator<<(std::ostream& os, const Triangle<T>& triangle) {
    triangle.Print(os);
    return os;
}

template <Scalar T>
std::istream& operator>>(std::istream& is, Triangle<T>& triangle) {
    triangle.Read(is);
    return is;
}

#endif
