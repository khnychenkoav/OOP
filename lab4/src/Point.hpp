#ifndef POINT_HPP
#define POINT_HPP

#include <concepts>
#include <type_traits>
#include <iostream>

template <typename T>
concept Scalar = std::is_scalar_v<T>;

template <Scalar T>
class Point {
public:
    Point();
    Point(T x, T y);

    T x() const;
    T y() const;

    void x(T x);
    void y(T y);

    bool operator==(const Point<T>& other) const;

private:
    T x_;
    T y_;
};

#include "Point.tpp"

#endif
