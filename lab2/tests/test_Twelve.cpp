#include <gtest/gtest.h>
#include "../src/Twelve.h"
#include "../src/TwelveExceptions.h"
#include <stdexcept>

// Тесты конструктора по умолчанию
TEST(TwelveTest, DefaultConstructor) {
    // Arrange & Act
    Twelve num;

    // Assert
    EXPECT_EQ(num, Twelve("0"));
}

// Тесты конструктора из строки
TEST(TwelveTest, StringConstructor_ValidInput) {
    // Arrange & Act
    Twelve num("A1");

    // Assert
    EXPECT_EQ(num.toString(), "A1");
}

TEST(TwelveTest, StringConstructor_InvalidInput) {
    // Arrange & Act & Assert
    EXPECT_THROW(Twelve("G3"), InvalidCharacterException);
}

// Тесты сложения
TEST(TwelveTest, Addition_WithoutCarry) {
    // Arrange
    Twelve num1("A1");
    Twelve num2("11");

    // Act
    Twelve result = num1 + num2;

    // Assert
    EXPECT_EQ(result, Twelve("B2"));
}

TEST(TwelveTest, Addition_WithCarry) {
    // Arrange
    Twelve num1("B9");
    Twelve num2("3");

    // Act
    Twelve result = num1 + num2;

    // Assert
    EXPECT_EQ(result, Twelve("100"));
}

// Тесты вычитания
TEST(TwelveTest, Subtraction_WithoutBorrow) {
    // Arrange
    Twelve num1("B2");
    Twelve num2("11");

    // Act
    Twelve result = num1 - num2;

    // Assert
    EXPECT_EQ(result, Twelve("A1"));
}

TEST(TwelveTest, Subtraction_NegativeResult) {
    // Arrange
    Twelve num1("11");
    Twelve num2("12");

    // Act & Assert
    EXPECT_THROW(num1 - num2, NegativeResultException);
}

// Тесты присваивания
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
    EXPECT_EQ(num1.toString(), "0");
}

// Тесты сравнения
TEST(TwelveTest, Comparison_Equal) {
    // Arrange
    Twelve num1("A1");
    Twelve num2("A1");

    // Act & Assert
    EXPECT_TRUE(num1 == num2);
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

TEST(TwelveTest, Comparison_NotEqual) {
    // Arrange
    Twelve num1("A1");
    Twelve num2("B1");

    // Act & Assert
    EXPECT_TRUE(num1 != num2);
}

// Тесты нормализации
TEST(TwelveTest, Normalize_WithLeadingZeros) {
    // Arrange
    Twelve num("000A1");

    // Act & Assert
    EXPECT_EQ(num.toString(), "A1");
}

// Тесты метода toString
TEST(TwelveTest, ToString) {
    // Arrange
    Twelve num("A1");

    // Act & Assert
    EXPECT_EQ(num.toString(), "A1");
}
