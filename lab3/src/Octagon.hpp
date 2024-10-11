#ifndef OCTAGON_HPP
#define OCTAGON_HPP

#include "Figure.hpp"
#include <array>

class Octagon : public Figure {
public:
    Octagon();
    Octagon(const std::array<std::pair<double, double>, 8>& points);
    Octagon(const Octagon& other);
    Octagon(Octagon&& other) noexcept;

    std::pair<double, double> GeometricCenter() const override;
    void Print(std::ostream& os) const override;
    void Read(std::istream& is) override;
    operator double() const override;

    Octagon& operator=(const Octagon& other);
    Octagon& operator=(Octagon&& other) noexcept;
    bool operator==(const Figure& other) const override;

    void Draw(sf::RenderWindow& window) const override;

    ~Octagon() override = default;

private:
    std::array<std::pair<double, double>, 8> points_;

    bool ValidateOctagon() const;

    void SuggestCorrectPoints() const;
    void UseSuggestedPoints();
};

std::ostream& operator<<(std::ostream& os, const Octagon& octagon);
std::istream& operator>>(std::istream& is, Octagon& octagon);

#endif
