#include <gtest/gtest.h>
#include "../src/Triangle.hpp"
#include "../src/Square.hpp"
#include "../src/Octagon.hpp"
#include "../src/MyVector.hpp"
#include <cmath>

TEST(TriangleTest, DefaultConstructor) {
    Triangle t;
    auto [x, y] = t.GeometricCenter();
    EXPECT_DOUBLE_EQ(x, 0.0);
    EXPECT_DOUBLE_EQ(y, 0.0);
}

TEST(TriangleTest, ConstructorWithPoints) {
    std::array<std::pair<double, double>, 3> points = {{{0, 0}, {1, 0}, {0.5, std::sqrt(0.75)}}};
    Triangle t(points);
    auto [x, y] = t.GeometricCenter();
    EXPECT_NEAR(x, 0.5, 1e-6);
    EXPECT_NEAR(y, std::sqrt(0.75) / 3.0, 1e-6);
}

TEST(TriangleTest, AreaCalculation) {
    std::array<std::pair<double, double>, 3> points = {{{0, 0}, {1, 0}, {0.5, std::sqrt(0.75)}}};
    Triangle t(points);
    double area = t;
    EXPECT_NEAR(area, 0.5 * 1.0 * std::sqrt(0.75), 1e-6);
}

TEST(TriangleTest, CopyConstructor) {
    std::array<std::pair<double, double>, 3> points = {{{0, 0}, {1, 0}, {0.5, std::sqrt(0.75)}}};
    Triangle t(points);
    Triangle t_copy(t);
    EXPECT_EQ(t.GeometricCenter(), t_copy.GeometricCenter());
}

TEST(TriangleTest, MoveConstructor) {
    std::array<std::pair<double, double>, 3> points = {{{0, 0}, {1, 0}, {0.5, std::sqrt(0.75)}}};
    Triangle t(points);
    Triangle t_move(std::move(t));
    auto [x, y] = t_move.GeometricCenter();
    EXPECT_NEAR(x, 0.5, 1e-6);
}


TEST(TriangleTest, EqualityOperator) {
    std::array<std::pair<double, double>, 3> points1 = {{{0, 0}, {1, 0}, {0.5, std::sqrt(0.75)}}};
    std::array<std::pair<double, double>, 3> points2 = points1;
    Triangle t1(points1);
    Triangle t2(points2);
    EXPECT_TRUE(t1 == t2);
}

TEST(SquareTest, DefaultConstructor) {
    Square s;
    auto [x, y] = s.GeometricCenter();
    EXPECT_DOUBLE_EQ(x, 0.0);
    EXPECT_DOUBLE_EQ(y, 0.0);
}

TEST(SquareTest, ConstructorWithPoints) {
    std::array<std::pair<double, double>, 4> points = {{{0, 0}, {1, 0}, {1, 1}, {0, 1}}};
    Square s(points);
    auto [x, y] = s.GeometricCenter();
    EXPECT_NEAR(x, 0.5, 1e-6);
    EXPECT_NEAR(y, 0.5, 1e-6);
}

TEST(SquareTest, AreaCalculation) {
    std::array<std::pair<double, double>, 4> points = {{{0, 0}, {1, 0}, {1, 1}, {0, 1}}};
    Square s(points);
    double area = s;
    EXPECT_NEAR(area, 1.0, 1e-6);
}

TEST(SquareTest, CopyConstructor) {
    std::array<std::pair<double, double>, 4> points = {{{0, 0}, {1, 0}, {1, 1}, {0, 1}}};
    Square s(points);
    Square s_copy(s);
    EXPECT_EQ(s.GeometricCenter(), s_copy.GeometricCenter());
}

TEST(OctagonTest, DefaultConstructor) {
    Octagon o;
    auto [x, y] = o.GeometricCenter();
    EXPECT_DOUBLE_EQ(x, 0.0);
    EXPECT_DOUBLE_EQ(y, 0.0);
}

TEST(OctagonTest, ConstructorWithPoints) {
    std::array<std::pair<double, double>, 8> points = {
        {{0, 0}, {1, 0}, {2, 1}, {2, 2}, {1, 3}, {0, 3}, {-1, 2}, {-1, 1}}};
    Octagon o(points);
    auto [x, y] = o.GeometricCenter();
    EXPECT_NEAR(x, 0.5, 1e-6);
    EXPECT_NEAR(y, 1.5, 1e-6);
}

TEST(OctagonTest, AreaCalculation) {
    std::array<std::pair<double, double>, 8> points = {
        {{0, 0}, {1, 0}, {2, 1}, {2, 2}, {1, 3}, {0, 3}, {-1, 2}, {-1, 1}}};
    Octagon o(points);
    double area = o;
    EXPECT_NEAR(area, 7.5, 1);
}

TEST(OctagonTest, CopyConstructor) {
    std::array<std::pair<double, double>, 8> points = {
        {{0, 0}, {1, 0}, {2, 1}, {2, 2}, {1, 3}, {0, 3}, {-1, 2}, {-1, 1}}};
    Octagon o(points);
    Octagon o_copy(o);
    EXPECT_EQ(o.GeometricCenter(), o_copy.GeometricCenter());
}
