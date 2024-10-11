#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "Figure.hpp"
#include <array>
#include <iostream>

class Triangle : public Figure {
public:
    Triangle();
    Triangle(const std::array<std::pair<double, double>, 3>& points);
    Triangle(const Triangle& other);
    Triangle(Triangle&& other) noexcept;

    std::pair<double, double> GeometricCenter() const override;
    void Print(std::ostream& os) const override;
    void Read(std::istream& is) override;
    operator double() const override;

    Triangle& operator=(const Triangle& other);
    Triangle& operator=(Triangle&& other) noexcept;
    bool operator==(const Figure& other) const override;

    void Draw(sf::RenderWindow& window) const override;

    ~Triangle() override = default;

private:
    std::array<std::pair<double, double>, 3> points_;

    bool ValidateTriangle() const;

    void SuggestCorrectPoints() const;
};

std::ostream& operator<<(std::ostream& os, const Triangle& triangle);
std::istream& operator>>(std::istream& is, Triangle& triangle);

#endif
