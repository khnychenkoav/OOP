#define _USE_MATH_DEFINES
#include "Octagon.hpp"
#include <cmath>
#include <iostream>

Octagon::Octagon() : points_{} {}

Octagon::Octagon(const std::array<std::pair<double, double>, 8>& points) : points_(points) {}

Octagon::Octagon(const Octagon& other) : points_(other.points_) {}

Octagon::Octagon(Octagon&& other) noexcept : points_(std::move(other.points_)) {}

std::pair<double, double> Octagon::GeometricCenter() const {
    double x = 0, y = 0;
    for (const auto& point : points_) {
        x += point.first;
        y += point.second;
    }
    return { x / 8, y / 8 };
}

void Octagon::Print(std::ostream& os) const {
    os << "Octagon vertices:\n";
    for (const auto& point : points_) {
        os << "(" << point.first << ", " << point.second << ")\n";
    }
}

void Octagon::Read(std::istream& is) {
    int attempts = 0;
    while (true) {
        for (auto& point : points_) {
            std::cout << "Enter point (x y): ";
            is >> point.first >> point.second;
        }

        if (ValidateOctagon()) {
            std::cout << "The octagon is valid.\n";
            break;
        } else {
            std::cout << "The points do not form a regular octagon. Please re-enter points.\n";
            SuggestCorrectPoints();
            attempts++;

            if (attempts >= 1) {
                std::string response;
                std::cout << "Do you want to automatically use the suggested correct points? (y/n): ";
                is >> response;
                if (response == "y" || response == "Y") {
                    UseSuggestedPoints();
                    std::cout << "Using suggested points for the regular octagon.\n";
                    break;
                }
            }
        }
    }
}

void Octagon::UseSuggestedPoints() {
    auto [centerX, centerY] = GeometricCenter();
    double radius = std::hypot(points_[0].first - centerX, points_[0].second - centerY);
    const double angleStep = M_PI / 4;

    for (size_t i = 0; i < 8; ++i) {
        double angle = i * angleStep;
        points_[i].first = centerX + radius * std::cos(angle);
        points_[i].second = centerY + radius * std::sin(angle);
    }
}

void Octagon::SuggestCorrectPoints() const {
    auto [centerX, centerY] = GeometricCenter();
    double radius = std::hypot(points_[0].first - centerX, points_[0].second - centerY);
    const double angleStep = M_PI / 4;

    std::cout << "Suggested correct points for a regular octagon:\n";
    for (size_t i = 0; i < 8; ++i) {
        double angle = i * angleStep;
        double x = centerX + radius * std::cos(angle);
        double y = centerY + radius * std::sin(angle);
        std::cout << "(" << x << ", " << y << ")\n";
    }
}


bool Octagon::ValidateOctagon() const {
    const double tolerance = 1e-2;

    double side1 = std::hypot(points_[1].first - points_[0].first, points_[1].second - points_[0].second);
    for (size_t i = 1; i < 8; ++i) {
        double side2 = std::hypot(points_[(i + 1) % 8].first - points_[i].first, points_[(i + 1) % 8].second - points_[i].second);
        if (std::abs(side1 - side2) > tolerance) {
            return false;
        }
    }

    for (size_t i = 0; i < 8; ++i) {
        std::pair<double, double> vec1 = { points_[(i + 1) % 8].first - points_[i].first, points_[(i + 1) % 8].second - points_[i].second };
        std::pair<double, double> vec2 = { points_[(i + 2) % 8].first - points_[(i + 1) % 8].first, points_[(i + 2) % 8].second - points_[(i + 1) % 8].second };

        double dot = vec1.first * vec2.first + vec1.second * vec2.second;
        double len1 = std::hypot(vec1.first, vec1.second);
        double len2 = std::hypot(vec2.first, vec2.second);
        double angleCos = dot / (len1 * len2);

        if (std::abs(angleCos + std::sqrt(2) / 2) > tolerance) {
            return false;
        }
    }

    return true;
}

Octagon::operator double() const {
    double area = 0;
    for (size_t i = 0; i < 8; ++i) {
        const auto& [x1, y1] = points_[i];
        const auto& [x2, y2] = points_[(i + 1) % 8];
        area += (x1 * y2 - x2 * y1);
    }
    return std::abs(area) / 2.0;
}

Octagon& Octagon::operator=(const Octagon& other) {
    if (this != &other) {
        points_ = other.points_;
    }
    return *this;
}

Octagon& Octagon::operator=(Octagon&& other) noexcept {
    if (this != &other) {
        points_ = std::move(other.points_);
    }
    return *this;
}

bool Octagon::operator==(const Figure& other) const {
    const Octagon* otherOctagon = dynamic_cast<const Octagon*>(&other);
    if (!otherOctagon) return false;
    return points_ == otherOctagon->points_;
}

void Octagon::Draw(sf::RenderWindow& window) const {
    sf::ConvexShape octagonShape;
    octagonShape.setPointCount(8);
    for (size_t i = 0; i < 8; ++i) {
        octagonShape.setPoint(i, sf::Vector2f(points_[i].first, points_[i].second));
    }
    octagonShape.setFillColor(sf::Color::Red);
    window.draw(octagonShape);
}

std::ostream& operator<<(std::ostream& os, const Octagon& octagon) {
    octagon.Print(os);
    return os;
}

std::istream& operator>>(std::istream& is, Octagon& octagon) {
    octagon.Read(is);
    return is;
}
