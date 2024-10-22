#ifndef SQUARE_HPP
#define SQUARE_HPP

#include "Figure.hpp"
#include <array>
#include <memory>
#include "Point.hpp"
#include <SFML/Graphics.hpp>

template <Scalar T>
class Square : public Figure<T> {
public:
    Square();
    Square(const std::array<Point<T>, 4>& points);
    Square(const Square<T>& other);
    Square(Square<T>&& other) noexcept;

    Point<T> GeometricCenter() const override;
    void Print(std::ostream& os) const override;
    void Read(std::istream& is) override;
    operator double() const override;

    Square<T>& operator=(const Square<T>& other);
    Square<T>& operator=(Square<T>&& other) noexcept;
    bool operator==(const Figure<T>& other) const override;

    void Draw(sf::RenderWindow& window) const override;

    ~Square() override = default;

private:
    std::array<std::unique_ptr<Point<T>>, 4> points_;

    bool ValidateSquare() const;

    void SuggestCorrectPoints() const;
    void UseSuggestedPoints();
};

template <Scalar T>
std::ostream& operator<<(std::ostream& os, const Square<T>& square);

template <Scalar T>
std::istream& operator>>(std::istream& is, Square<T>& square);

#include "Square.tpp"

#endif
