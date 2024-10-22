#ifndef POINT_TPP
#define POINT_TPP

#include "Point.hpp"

template <Scalar T>
Point<T>::Point() : x_(T()), y_(T()) {}

template <Scalar T>
Point<T>::Point(T x, T y) : x_(x), y_(y) {}

template <Scalar T>
T Point<T>::x() const { return x_; }

template <Scalar T>
T Point<T>::y() const { return y_; }

template <Scalar T>
void Point<T>::x(T x) { x_ = x; }

template <Scalar T>
void Point<T>::y(T y) { y_ = y; }

template <Scalar T>
bool Point<T>::operator==(const Point<T>& other) const {
    return x_ == other.x_ && y_ == other.y_;
}

template <Scalar T>
std::istream& operator>>(std::istream& is, Point<T>& point) {
    T x, y;
    is >> x >> y;
    point.x(x);
    point.y(y);
    return is;
}

template <Scalar T>
std::ostream& operator<<(std::ostream& os, const Point<T>& point) {
    os << "(" << point.x() << ", " << point.y() << ")";
    return os;
}

#endif
