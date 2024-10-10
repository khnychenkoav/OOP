#define _USE_MATH_DEFINES
#include "Triangle.hpp"
#include <cmath>
#include <iostream>

Triangle::Triangle() : points_{} {}

Triangle::Triangle(const std::array<std::pair<double, double>, 3>& points) : points_(points) {}

Triangle::Triangle(const Triangle& other) : points_(other.points_) {}

Triangle::Triangle(Triangle&& other) noexcept : points_(std::move(other.points_)) {}

std::pair<double, double> Triangle::GeometricCenter() const {
    double x = 0, y = 0;
    for (const auto& point : points_) {
        x += point.first;
        y += point.second;
    }
    return { x / 3, y / 3 };
}

void Triangle::Print(std::ostream& os) const {
    os << "Triangle vertices:\n";
    for (const auto& point : points_) {
        os << "(" << point.first << ", " << point.second << ")\n";
    }
}

void Triangle::Read(std::istream& is) {
    while (true) {
        for (auto& point : points_) {
            std::cout << "Enter point (x y): ";
            is >> point.first >> point.second;
        }

        if (ValidateTriangle()) {
            std::cout << "The triangle is valid.\n";
            break;
        } else {
            std::cout << "The points do not form a valid equilateral triangle. Please re-enter points.\n";
            SuggestCorrectPoints();
        }
    }
}

bool Triangle::ValidateTriangle() const {
    const double tolerance = 1e-3;
    double side1 = std::hypot(points_[1].first - points_[0].first, points_[1].second - points_[0].second);
    double side2 = std::hypot(points_[2].first - points_[1].first, points_[2].second - points_[1].second);
    double side3 = std::hypot(points_[2].first - points_[0].first, points_[2].second - points_[0].second);

    return (std::abs(side1 - side2) < tolerance) && (std::abs(side2 - side3) < tolerance);
}

void Triangle::SuggestCorrectPoints() const {
    auto [centerX, centerY] = GeometricCenter();
    double radius = std::hypot(points_[0].first - centerX, points_[0].second - centerY);
    const double angleStep = 2 * M_PI / 3;

    std::cout << "Suggested correct points for an equilateral triangle:\n";
    for (size_t i = 0; i < 3; ++i) {
        double angle = i * angleStep;
        double x = centerX + radius * std::cos(angle);
        double y = centerY + radius * std::sin(angle);
        std::cout << "(" << x << ", " << y << ")\n";
    }
}
Triangle::operator double() const {
    double x1 = points_[0].first, y1 = points_[0].second;
    double x2 = points_[1].first, y2 = points_[1].second;
    double x3 = points_[2].first, y3 = points_[2].second;
    return std::abs((x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2)) / 2.0);
}

Triangle& Triangle::operator=(const Triangle& other) {
    if (this != &other) {
        points_ = other.points_;
    }
    return *this;
}

Triangle& Triangle::operator=(Triangle&& other) noexcept {
    if (this != &other) {
        points_ = std::move(other.points_);
    }
    return *this;
}

bool Triangle::operator==(const Figure& other) const {
    const Triangle* otherTriangle = dynamic_cast<const Triangle*>(&other);
    if (!otherTriangle) return false;
    return points_ == otherTriangle->points_;
}

void Triangle::Draw(sf::RenderWindow& window) const {
    sf::ConvexShape triangleShape;
    triangleShape.setPointCount(3);
    for (size_t i = 0; i < 3; ++i) {
        triangleShape.setPoint(i, sf::Vector2f(points_[i].first, points_[i].second));
    }
    triangleShape.setFillColor(sf::Color::Green);
    window.draw(triangleShape);
}

std::ostream& operator<<(std::ostream& os, const Triangle& triangle) {
    triangle.Print(os);
    return os;
}

std::istream& operator>>(std::istream& is, Triangle& triangle) {
    triangle.Read(is);
    return is;
}
