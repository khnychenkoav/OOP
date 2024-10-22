#include <gtest/gtest.h>
#include "../src/Triangle.hpp"
#include "../src/Square.hpp"
#include "../src/Octagon.hpp"
#include "../src/Array.hpp"
#include <cmath>

TEST(TriangleTest, DefaultConstructor) {
    Triangle<double> t;
    Point<double> center = t.GeometricCenter();
    EXPECT_DOUBLE_EQ(center.x(), 0.0);
    EXPECT_DOUBLE_EQ(center.y(), 0.0);
}

TEST(TriangleTest, ConstructorWithPoints) {
    std::array<Point<double>, 3> points = {Point<double>(0, 0), Point<double>(1, 0), Point<double>(0.5, std::sqrt(0.75))};
    Triangle<double> t(points);
    Point<double> center = t.GeometricCenter();
    EXPECT_NEAR(center.x(), 0.5, 1e-6);
    EXPECT_NEAR(center.y(), std::sqrt(0.75) / 3.0, 1e-6);
}

TEST(TriangleTest, AreaCalculation) {
    std::array<Point<double>, 3> points = {Point<double>(0, 0), Point<double>(1, 0), Point<double>(0.5, std::sqrt(0.75))};
    Triangle<double> t(points);
    double area = static_cast<double>(t);
    EXPECT_NEAR(area, 0.5 * 1.0 * std::sqrt(0.75), 1e-6);
}

TEST(TriangleTest, CopyConstructor) {
    std::array<Point<double>, 3> points = {Point<double>(0, 0), Point<double>(1, 0), Point<double>(0.5, std::sqrt(0.75))};
    Triangle<double> t(points);
    Triangle<double> t_copy(t);
    EXPECT_EQ(t.GeometricCenter(), t_copy.GeometricCenter());
}

TEST(TriangleTest, MoveConstructor) {
    std::array<Point<double>, 3> points = {Point<double>(0, 0), Point<double>(1, 0), Point<double>(0.5, std::sqrt(0.75))};
    Triangle<double> t(points);
    Triangle<double> t_move(std::move(t));
    Point<double> center = t_move.GeometricCenter();
    EXPECT_NEAR(center.x(), 0.5, 1e-6);
}

TEST(TriangleTest, EqualityOperator) {
    std::array<Point<double>, 3> points1 = {Point<double>(0, 0), Point<double>(1, 0), Point<double>(0.5, std::sqrt(0.75))};
    std::array<Point<double>, 3> points2 = points1;
    Triangle<double> t1(points1);
    Triangle<double> t2(points2);
    EXPECT_TRUE(t1 == t2);
}

TEST(SquareTest, DefaultConstructor) {
    Square<double> s;
    Point<double> center = s.GeometricCenter();
    EXPECT_DOUBLE_EQ(center.x(), 0.0);
    EXPECT_DOUBLE_EQ(center.y(), 0.0);
}

TEST(SquareTest, ConstructorWithPoints) {
    std::array<Point<double>, 4> points = {Point<double>(0, 0), Point<double>(1, 0), Point<double>(1, 1), Point<double>(0, 1)};
    Square<double> s(points);
    Point<double> center = s.GeometricCenter();
    EXPECT_NEAR(center.x(), 0.5, 1e-6);
    EXPECT_NEAR(center.y(), 0.5, 1e-6);
}

TEST(SquareTest, AreaCalculation) {
    std::array<Point<double>, 4> points = {Point<double>(0, 0), Point<double>(1, 0), Point<double>(1, 1), Point<double>(0, 1)};
    Square<double> s(points);
    double area = static_cast<double>(s);
    EXPECT_NEAR(area, 1.0, 1e-6);
}

TEST(SquareTest, CopyConstructor) {
    std::array<Point<double>, 4> points = {Point<double>(0, 0), Point<double>(1, 0), Point<double>(1, 1), Point<double>(0, 1)};
    Square<double> s(points);
    Square<double> s_copy(s);
    EXPECT_EQ(s.GeometricCenter(), s_copy.GeometricCenter());
}

TEST(OctagonTest, DefaultConstructor) {
    Octagon<double> o;
    Point<double> center = o.GeometricCenter();
    EXPECT_DOUBLE_EQ(center.x(), 0.0);
    EXPECT_DOUBLE_EQ(center.y(), 0.0);
}

TEST(OctagonTest, ConstructorWithPoints) {
    std::array<Point<double>, 8> points = {
        Point<double>(0, 0), Point<double>(1, 0), Point<double>(2, 1), Point<double>(2, 2),
        Point<double>(1, 3), Point<double>(0, 3), Point<double>(-1, 2), Point<double>(-1, 1)
    };
    Octagon<double> o(points);
    Point<double> center = o.GeometricCenter();
    EXPECT_NEAR(center.x(), 0.5, 1e-6);
    EXPECT_NEAR(center.y(), 1.5, 1e-6);
}

TEST(OctagonTest, AreaCalculation) {
    std::array<Point<double>, 8> points = {
        Point<double>(0, 0), Point<double>(1, 0), Point<double>(2, 1), Point<double>(2, 2),
        Point<double>(1, 3), Point<double>(0, 3), Point<double>(-1, 2), Point<double>(-1, 1)
    };
    Octagon<double> o(points);
    double area = static_cast<double>(o);
    EXPECT_NEAR(area, 7.5, 1e-0);
}

TEST(OctagonTest, CopyConstructor) {
    std::array<Point<double>, 8> points = {
        Point<double>(0, 0), Point<double>(1, 0), Point<double>(2, 1), Point<double>(2, 2),
        Point<double>(1, 3), Point<double>(0, 3), Point<double>(-1, 2), Point<double>(-1, 1)
    };
    Octagon<double> o(points);
    Octagon<double> o_copy(o);
    EXPECT_EQ(o.GeometricCenter(), o_copy.GeometricCenter());
}

TEST(ArrayTest, PushBackAndErase) {
    Array<Triangle<double>> triangleArray;
    std::array<Point<double>, 3> points = {Point<double>(0, 0), Point<double>(1, 0), Point<double>(0.5, 1)};
    Triangle<double> t(points);
    triangleArray.push_back(t);
    EXPECT_EQ(triangleArray.size(), 1);
    triangleArray.erase(0);
    EXPECT_EQ(triangleArray.size(), 0);
}

TEST(ArrayTest, CopyAndMove) {
    Array<Square<double>> squareArray;
    std::array<Point<double>, 4> points = {Point<double>(0, 0), Point<double>(1, 0), Point<double>(1, 1), Point<double>(0, 1)};
    Square<double> s(points);
    squareArray.push_back(s);

    Array<Square<double>> squareArrayCopy(squareArray);
    EXPECT_EQ(squareArrayCopy.size(), 1);

    Array<Square<double>> squareArrayMove(std::move(squareArray));
    EXPECT_EQ(squareArrayMove.size(), 1);
    EXPECT_EQ(squareArray.size(), 0);
}
