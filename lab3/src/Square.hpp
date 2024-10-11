#ifndef SQUARE_HPP
#define SQUARE_HPP

#include "Figure.hpp"
#include <array>
#include <iostream>

class Square : public Figure {
public:
    Square();
    Square(const std::array<std::pair<double, double>, 4>& points);
    Square(const Square& other);
    Square(Square&& other) noexcept;

    std::pair<double, double> GeometricCenter() const override;
    void Print(std::ostream& os) const override;
    void Read(std::istream& is) override;
    operator double() const override;

    Square& operator=(const Square& other);
    Square& operator=(Square&& other) noexcept;
    bool operator==(const Figure& other) const override;

    void Draw(sf::RenderWindow& window) const override;

    ~Square() override = default;

private:
    std::array<std::pair<double, double>, 4> points_;

    bool ValidateSquare() const;

    void SuggestCorrectPoints() const;
};

std::ostream& operator<<(std::ostream& os, const Square& square);
std::istream& operator>>(std::istream& is, Square& square);

#endif
