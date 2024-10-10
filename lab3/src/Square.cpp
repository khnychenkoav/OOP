#define _USE_MATH_DEFINES
#include "Square.hpp"
#include <cmath>
#include <iostream>

Square::Square() : points_{} {}

Square::Square(const std::array<std::pair<double, double>, 4>& points) : points_(points) {}

Square::Square(const Square& other) : points_(other.points_) {}

Square::Square(Square&& other) noexcept : points_(std::move(other.points_)) {}

std::pair<double, double> Square::GeometricCenter() const {
    double x = 0, y = 0;
    for (const auto& point : points_) {
        x += point.first;
        y += point.second;
    }
    return { x / 4, y / 4 };
}

void Square::Print(std::ostream& os) const {
    os << "Square vertices:\n";
    for (const auto& point : points_) {
        os << "(" << point.first << ", " << point.second << ")\n";
    }
}

void Square::Read(std::istream& is) {
    while (true) {
        for (auto& point : points_) {
            std::cout << "Enter point (x y): ";
            is >> point.first >> point.second;
        }

        if (ValidateSquare()) {
            std::cout << "The square is valid.\n";
            break;
        } else {
            std::cout << "The points do not form a valid square. Please re-enter points.\n";
            SuggestCorrectPoints();
        }
    }
}

bool Square::ValidateSquare() const {
    const double tolerance = 1e-3;
    double side1 = std::hypot(points_[1].first - points_[0].first, points_[1].second - points_[0].second);
    double side2 = std::hypot(points_[2].first - points_[1].first, points_[2].second - points_[1].second);
    double side3 = std::hypot(points_[3].first - points_[2].first, points_[3].second - points_[2].second);
    double side4 = std::hypot(points_[0].first - points_[3].first, points_[0].second - points_[3].second);

    return (std::abs(side1 - side2) < tolerance) && (std::abs(side2 - side3) < tolerance) && (std::abs(side3 - side4) < tolerance);
}

void Square::SuggestCorrectPoints() const {
    auto [centerX, centerY] = GeometricCenter();
    double radius = std::hypot(points_[0].first - centerX, points_[0].second - centerY);
    const double angleStep = M_PI / 2; // Угол между вершинами квадрата (90 градусов)

    std::cout << "Suggested correct points for a square:\n";
    for (size_t i = 0; i < 4; ++i) {
        double angle = i * angleStep;
        double x = centerX + radius * std::cos(angle);
        double y = centerY + radius * std::sin(angle);
        std::cout << "(" << x << ", " << y << ")\n";
    }
}

Square::operator double() const {
    double side = std::hypot(points_[0].first - points_[1].first, points_[0].second - points_[1].second);
    return side * side;
}

Square& Square::operator=(const Square& other) {
    if (this != &other) {
        points_ = other.points_;
    }
    return *this;
}

Square& Square::operator=(Square&& other) noexcept {
    if (this != &other) {
        points_ = std::move(other.points_);
    }
    return *this;
}

bool Square::operator==(const Figure& other) const {
    const Square* otherSquare = dynamic_cast<const Square*>(&other);
    if (!otherSquare) return false;
    return points_ == otherSquare->points_;
}

void Square::Draw(sf::RenderWindow& window) const {
    sf::ConvexShape squareShape;
    squareShape.setPointCount(4);
    for (size_t i = 0; i < 4; ++i) {
        squareShape.setPoint(i, sf::Vector2f(points_[i].first, points_[i].second));
    }
    squareShape.setFillColor(sf::Color::Blue);
    window.draw(squareShape);
}

std::ostream& operator<<(std::ostream& os, const Square& square) {
    square.Print(os);
    return os;
}

std::istream& operator>>(std::istream& is, Square& square) {
    square.Read(is);
    return is;
}
