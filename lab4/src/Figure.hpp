#ifndef FIGURE_HPP
#define FIGURE_HPP

#include <iostream>
#include <memory>
#include "Point.hpp"
#include <SFML/Graphics.hpp>

template <Scalar T>
class Figure {
public:
    virtual Point<T> GeometricCenter() const = 0;
    virtual void Print(std::ostream& os) const = 0;
    virtual void Read(std::istream& is) = 0;
    virtual operator double() const = 0;

    virtual bool operator==(const Figure<T>& other) const = 0;
    virtual void Draw(sf::RenderWindow& window) const = 0;

    virtual ~Figure() = default;
};

#endif
