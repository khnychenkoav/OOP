#ifndef OCTAGON_TPP
#define OCTAGON_TPP

#include "Octagon.hpp"
#include <cmath>
#include <iostream>

template <Scalar T>
Octagon<T>::Octagon() {
    for (auto& point : points_) {
        point = std::make_unique<Point<T>>();
    }
}

template <Scalar T>
Octagon<T>::Octagon(const std::array<Point<T>, 8>& points) {
    for (size_t i = 0; i < 8; ++i) {
        points_[i] = std::make_unique<Point<T>>(points[i]);
    }
}

template <Scalar T>
Octagon<T>::Octagon(const Octagon<T>& other) {
    for (size_t i = 0; i < 8; ++i) {
        points_[i] = std::make_unique<Point<T>>(*other.points_[i]);
    }
}

template <Scalar T>
Octagon<T>::Octagon(Octagon<T>&& other) noexcept : points_(std::move(other.points_)) {}

template <Scalar T>
Point<T> Octagon<T>::GeometricCenter() const {
    T x = T(), y = T();
    for (const auto& point : points_) {
        x += point->x();
        y += point->y();
    }
    return Point<T>(x / 8, y / 8);
}

template <Scalar T>
void Octagon<T>::Print(std::ostream& os) const {
    os << "Octagon vertices:\n";
    for (const auto& point : points_) {
        os << *point << "\n";
    }
}

template <Scalar T>
void Octagon<T>::Read(std::istream& is) {
    while (true) {
        for (auto& point : points_) {
            std::cout << "Enter point (x y): ";
            is >> *point;
        }

        if (ValidateOctagon()) {
            std::cout << "The octagon is valid.\n";
            break;
        } else {
            std::cout << "The points do not form a valid octagon. Using suggested points.\n";
            SuggestCorrectPoints();
            UseSuggestedPoints();
            break; // Для простоты используем предложенные точки
        }
    }
}

template <Scalar T>
bool Octagon<T>::ValidateOctagon() const {
    const double tolerance = 1e-2;

    double side1 = std::hypot(static_cast<double>(points_[1]->x() - points_[0]->x()), static_cast<double>(points_[1]->y() - points_[0]->y()));
    for (size_t i = 1; i < 8; ++i) {
        double side2 = std::hypot(static_cast<double>(points_[(i + 1) % 8]->x() - points_[i]->x()), static_cast<double>(points_[(i + 1) % 8]->y() - points_[i]->y()));
        if (std::abs(side1 - side2) > tolerance) {
            return false;
        }
    }

    // Проверка углов
    for (size_t i = 0; i < 8; ++i) {
        Point<T>& p0 = *points_[i];
        Point<T>& p1 = *points_[(i + 1) % 8];
        Point<T>& p2 = *points_[(i + 2) % 8];

        double dx1 = static_cast<double>(p1.x() - p0.x());
        double dy1 = static_cast<double>(p1.y() - p0.y());
        double dx2 = static_cast<double>(p2.x() - p1.x());
        double dy2 = static_cast<double>(p2.y() - p1.y());

        double dot = dx1 * dx2 + dy1 * dy2;
        double len1 = std::hypot(dx1, dy1);
        double len2 = std::hypot(dx2, dy2);
        double angleCos = dot / (len1 * len2);

        // Ожидаемый угол между сторонами в правильном восьмиугольнике: 135 градусов (-cos(135°) = -sqrt(2)/2)
        if (std::abs(angleCos + std::sqrt(2) / 2) > tolerance) {
            return false;
        }
    }

    return true;
}

template <Scalar T>
void Octagon<T>::SuggestCorrectPoints() const {
    auto center = GeometricCenter();
    double radius = std::hypot(static_cast<double>(points_[0]->x() - center.x()), static_cast<double>(points_[0]->y() - center.y()));
    const double angleStep = M_PI / 4;

    std::cout << "Suggested correct points for a regular octagon:\n";
    for (size_t i = 0; i < 8; ++i) {
        double angle = i * angleStep;
        T x = static_cast<T>(center.x() + radius * std::cos(angle));
        T y = static_cast<T>(center.y() + radius * std::sin(angle));
        std::cout << "(" << x << ", " << y << ")\n";
    }
}

template <Scalar T>
void Octagon<T>::UseSuggestedPoints() {
    auto center = GeometricCenter();
    double radius = std::hypot(static_cast<double>(points_[0]->x() - center.x()), static_cast<double>(points_[0]->y() - center.y()));
    const double angleStep = M_PI / 4;

    for (size_t i = 0; i < 8; ++i) {
        double angle = i * angleStep;
        T x = static_cast<T>(center.x() + radius * std::cos(angle));
        T y = static_cast<T>(center.y() + radius * std::sin(angle));
        points_[i]->x(x);
        points_[i]->y(y);
    }
}

template <Scalar T>
Octagon<T>::operator double() const {
    double area = 0;
    for (size_t i = 0; i < 8; ++i) {
        double x1 = static_cast<double>(points_[i]->x());
        double y1 = static_cast<double>(points_[i]->y());
        double x2 = static_cast<double>(points_[(i + 1) % 8]->x());
        double y2 = static_cast<double>(points_[(i + 1) % 8]->y());
        area += (x1 * y2 - x2 * y1);
    }
    return std::abs(area) / 2.0;
}

template <Scalar T>
Octagon<T>& Octagon<T>::operator=(const Octagon<T>& other) {
    if (this != &other) {
        for (size_t i = 0; i < 8; ++i) {
            points_[i] = std::make_unique<Point<T>>(*other.points_[i]);
        }
    }
    return *this;
}

template <Scalar T>
Octagon<T>& Octagon<T>::operator=(Octagon<T>&& other) noexcept {
    if (this != &other) {
        points_ = std::move(other.points_);
    }
    return *this;
}

template <Scalar T>
bool Octagon<T>::operator==(const Figure<T>& other) const {
    const Octagon<T>* otherOctagon = dynamic_cast<const Octagon<T>*>(&other);
    if (!otherOctagon) return false;
    for (size_t i = 0; i < 8; ++i) {
        if (!(*points_[i] == *otherOctagon->points_[i])) {
            return false;
        }
    }
    return true;
}

template <Scalar T>
void Octagon<T>::Draw(sf::RenderWindow& window) const {
    sf::ConvexShape octagonShape;
    octagonShape.setPointCount(8);
    for (size_t i = 0; i < 8; ++i) {
        octagonShape.setPoint(i, sf::Vector2f(static_cast<float>(points_[i]->x()), static_cast<float>(points_[i]->y())));
    }
    octagonShape.setFillColor(sf::Color::Red);
    window.draw(octagonShape);
}

template <Scalar T>
std::ostream& operator<<(std::ostream& os, const Octagon<T>& octagon) {
    octagon.Print(os);
    return os;
}

template <Scalar T>
std::istream& operator>>(std::istream& is, Octagon<T>& octagon) {
    octagon.Read(is);
    return is;
}

#endif
