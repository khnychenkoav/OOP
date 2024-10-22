#ifndef OCTAGON_HPP
#define OCTAGON_HPP

#include "Figure.hpp"
#include <array>
#include <memory>
#include "Point.hpp"
#include <SFML/Graphics.hpp>

template <Scalar T>
class Octagon : public Figure<T> {
public:
    Octagon();
    Octagon(const std::array<Point<T>, 8>& points);
    Octagon(const Octagon<T>& other);
    Octagon(Octagon<T>&& other) noexcept;

    Point<T> GeometricCenter() const override;
    void Print(std::ostream& os) const override;
    void Read(std::istream& is) override;
    operator double() const override;

    Octagon<T>& operator=(const Octagon<T>& other);
    Octagon<T>& operator=(Octagon<T>&& other) noexcept;
    bool operator==(const Figure<T>& other) const override;

    void Draw(sf::RenderWindow& window) const override;

    ~Octagon() override = default;

private:
    std::array<std::unique_ptr<Point<T>>, 8> points_;

    bool ValidateOctagon() const;

    void SuggestCorrectPoints() const;
    void UseSuggestedPoints();
};

template <Scalar T>
std::ostream& operator<<(std::ostream& os, const Octagon<T>& octagon);

template <Scalar T>
std::istream& operator>>(std::istream& is, Octagon<T>& octagon);

#include "Octagon.tpp"

#endif
