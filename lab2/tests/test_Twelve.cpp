#include <gtest/gtest.h>
#include "../src/Twelve.h"
#include "../src/TwelveExceptions.h"
#include <stdexcept>

TEST(TwelveTest, DefaultConstructor) {
    // Arrange & Act
    Twelve num;

    // Assert
    EXPECT_EQ(num.toString(), "");
}

TEST(TwelveTest, StringConstructor_ValidInput) {
    // Arrange
    Twelve num("A1");

    // Act & Assert
    EXPECT_EQ(num.toString(), "A1");
}

TEST(TwelveTest, StringConstructor_InvalidInput) {
    // Arrange & Act & Assert
    EXPECT_THROW(Twelve("G3"), std::invalid_argument);
}

TEST(TwelveTest, Addition_WithoutCarry) {
    // Arrange
    Twelve num1("A1");
    Twelve num2("11");

    // Act
    Twelve result = num1 + num2;

    // Assert
    EXPECT_EQ(result.toString(), "B2");
}

TEST(TwelveTest, Addition_WithCarry) {
    // Arrange
    Twelve num1("B9");
    Twelve num2("3");

    // Act
    Twelve result = num1 + num2;

    // Assert
    EXPECT_EQ(result.toString(), "100");
}

TEST(TwelveTest, Subtraction_WithoutBorrow) {
    // Arrange
    Twelve num1("B2");
    Twelve num2("11");

    // Act
    Twelve result = num1 - num2;

    // Assert
    EXPECT_EQ(result.toString(), "A1");
}

TEST(TwelveTest, Subtraction_WithBorrow) {
    // Arrange
    Twelve num1("A1");
    Twelve num2("2");

    // Act
    Twelve result = num1 - num2;

    // Assert
    EXPECT_EQ(result.toString(), "9B");
}

TEST(TwelveTest, Subtraction_NegativeResult) {
    // Arrange
    Twelve num1("11");
    Twelve num2("12");

    // Act & Assert
    EXPECT_THROW(num1 - num2, NegativeResultException);
}

TEST(TwelveTest, CopyAssignment) {
    // Arrange
    Twelve num1("A1");
    Twelve num2;

    // Act
    num2 = num1;

    // Assert
    EXPECT_EQ(num2, num1);
}

TEST(TwelveTest, MoveAssignment) {
    // Arrange
    Twelve num1("A1");
    Twelve num2;

    // Act
    num2 = std::move(num1);

    // Assert
    EXPECT_EQ(num2.toString(), "A1");
    EXPECT_EQ(num1.toString(), "");
}

TEST(TwelveTest, AdditionAssignment) {
    // Arrange
    Twelve num1("A1");
    Twelve num2("11");

    // Act
    num1 += num2;

    // Assert
    EXPECT_EQ(num1.toString(), "B2");
}

TEST(TwelveTest, SubtractionAssignment) {
    // Arrange
    Twelve num1("A1");
    Twelve num2("11");

    // Act
    num1 -= num2;

    // Assert
    EXPECT_EQ(num1.toString(), "90");
}

TEST(TwelveTest, Comparison_Equal) {
    // Arrange
    Twelve num1("A1");
    Twelve num2("A1");

    // Act & Assert
    EXPECT_TRUE(num1 == num2);
}

TEST(TwelveTest, Comparison_NotEqual) {
    // Arrange
    Twelve num1("A1");
    Twelve num2("B1");

    // Act & Assert
    EXPECT_TRUE(num1 != num2);
}

TEST(TwelveTest, Comparison_LessThan) {
    // Arrange
    Twelve num1("A1");
    Twelve num2("B1");

    // Act & Assert
    EXPECT_TRUE(num1 < num2);
}

TEST(TwelveTest, Comparison_GreaterThan) {
    // Arrange
    Twelve num1("B1");
    Twelve num2("A1");

    // Act & Assert
    EXPECT_TRUE(num1 > num2);
}

TEST(TwelveTest, Normalize_WithLeadingZeros) {
    // Arrange
    Twelve num("000A1");

    // Act & Assert
    EXPECT_EQ(num.toString(), "A1");
}

TEST(TwelveTest, ToString) {
    // Arrange
    Twelve num("A1");

    // Act & Assert
    EXPECT_EQ(num.toString(), "A1");
}

TEST(TwelveTest, ToString_WithLeadingZeros) {
    // Arrange
    Twelve num("000B1");

    // Act & Assert
    EXPECT_EQ(num.toString(), "B1");
}

TEST(TwelveTest, FromDecimal) {
    // Arrange
    unsigned long long decimal = 144;

    // Act
    Twelve t = Twelve::fromDecimal(decimal);

    // Assert
    EXPECT_EQ(t.toString(), "100");
}

TEST(TwelveTest, ToDecimal) {
    // Arrange
    Twelve t("100");

    // Act
    unsigned long long decimal = t.toDecimal();

    // Assert
    EXPECT_EQ(decimal, 144);
}

TEST(TwelveTest, Multiplication) {
    // Arrange
    Twelve t1("10");
    Twelve t2("2");

    // Act
    Twelve result = t1 * t2;

    // Assert
    EXPECT_EQ(result.toString(), "20");
}

TEST(TwelveTest, MultiplicationAssignment) {
    // Arrange
    Twelve t1("10");
    Twelve t2("2");

    // Act
    t1 *= t2;

    // Assert
    EXPECT_EQ(t1.toString(), "20");
}
