#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "Figure.hpp"
#include <array>
#include <memory>
#include "Point.hpp"
#include <SFML/Graphics.hpp>

template <Scalar T>
class Triangle : public Figure<T> {
public:
    Triangle();
    Triangle(const std::array<Point<T>, 3>& points);
    Triangle(const Triangle<T>& other);
    Triangle(Triangle<T>&& other) noexcept;

    Point<T> GeometricCenter() const override;
    void Print(std::ostream& os) const override;
    void Read(std::istream& is) override;
    operator double() const override;
    void Draw(sf::RenderWindow& window) const override;

    Triangle<T>& operator=(const Triangle<T>& other);
    Triangle<T>& operator=(Triangle<T>&& other) noexcept;
    bool operator==(const Figure<T>& other) const override;

    ~Triangle() override = default;

private:
    std::array<std::unique_ptr<Point<T>>, 3> points_;

    bool ValidateTriangle() const;

    void SuggestCorrectPoints() const;
    void UseSuggestedPoints();
};

template <Scalar T>
std::ostream& operator<<(std::ostream& os, const Triangle<T>& triangle);

template <Scalar T>
std::istream& operator>>(std::istream& is, Triangle<T>& triangle);

#include "Triangle.tpp"

#endif
