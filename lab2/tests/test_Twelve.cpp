#include <gtest/gtest.h>
#include "../src/Twelve.h"
#include "../src/TwelveExceptions.h"
#include <stdexcept>

TEST(TwelveTest, DefaultConstructor) {
    // Arrange & Act
    Twelve num;

    // Assert
    EXPECT_EQ(num, Twelve("0"));
}

TEST(TwelveTest, StringConstructor_ValidInput) {
    Twelve num("A1");
    EXPECT_EQ(num.toString(), "A1");
}

TEST(TwelveTest, StringConstructor_InvalidInput) {
    EXPECT_THROW(Twelve("G3"), InvalidCharacterException);
}

TEST(TwelveTest, Addition_WithoutCarry) {
    Twelve num1("A1");
    Twelve num2("11");
    Twelve result = num1 + num2;
    EXPECT_EQ(result, Twelve("B2"));
}

TEST(TwelveTest, Addition_WithCarry) {
    Twelve num1("B9");
    Twelve num2("3");
    Twelve result = num1 + num2;
    EXPECT_EQ(result, Twelve("100"));
}

TEST(TwelveTest, Addition_WithOverflow) {
    Twelve num1("BBBBBBBBBB");
    Twelve num2("1");
    EXPECT_THROW(num1 + num2, OverflowException);
}

TEST(TwelveTest, Subtraction_WithoutBorrow) {
    Twelve num1("B2");
    Twelve num2("11");
    Twelve result = num1 - num2;
    EXPECT_EQ(result, Twelve("A1"));
}

TEST(TwelveTest, Subtraction_WithBorrow) {
    Twelve num1("A1");
    Twelve num2("2");
    Twelve result = num1 - num2;
    EXPECT_EQ(result, Twelve("9B"));
}

TEST(TwelveTest, Subtraction_NegativeResult) {
    Twelve num1("11");
    Twelve num2("12");
    EXPECT_THROW(num1 - num2, NegativeResultException);
}

TEST(TwelveTest, CopyAssignment) {
    Twelve num1("A1");
    Twelve num2;
    num2 = num1;
    EXPECT_EQ(num2, num1);
}

TEST(TwelveTest, MoveAssignment) {
    Twelve num1("A1");
    Twelve num2;
    num2 = std::move(num1);
    EXPECT_EQ(num2.toString(), "A1");
    EXPECT_EQ(num1.toString(), "0");
}

TEST(TwelveTest, AdditionAssignment) {
    Twelve num1("A1");
    Twelve num2("11");
    num1 += num2;
    EXPECT_EQ(num1, Twelve("B2"));
}

TEST(TwelveTest, SubtractionAssignment) {
    Twelve num1("A1");
    Twelve num2("11");
    num1 -= num2;
    EXPECT_EQ(num1, Twelve("90"));
}

TEST(TwelveTest, Comparison_Equal) {
    Twelve num1("A1");
    Twelve num2("A1");
    EXPECT_TRUE(num1 == num2);
}

TEST(TwelveTest, Comparison_NotEqual) {
    Twelve num1("A1");
    Twelve num2("B1");
    EXPECT_TRUE(num1 != num2);
}

TEST(TwelveTest, Comparison_LessThan) {
    Twelve num1("A1");
    Twelve num2("B1");
    EXPECT_TRUE(num1 < num2);
}

TEST(TwelveTest, Comparison_GreaterThan) {
    Twelve num1("B1");
    Twelve num2("A1");
    EXPECT_TRUE(num1 > num2);
}

TEST(TwelveTest, Normalize_WithLeadingZeros) {
    Twelve num("000A1");
    EXPECT_EQ(num.toString(), "A1");
}

TEST(TwelveTest, ToString) {
    Twelve num("A1");
    EXPECT_EQ(num.toString(), "A1");
}

TEST(TwelveTest, ToString_WithLeadingZeros) {
    Twelve num("000B1");
    EXPECT_EQ(num.toString(), "B1");
}

TEST(TwelveTest, InvalidCharacterExceptionTest) {
    EXPECT_THROW({
        Twelve num("Z3");
    }, InvalidCharacterException);
}

TEST(TwelveTest, FromDecimal) {
    unsigned long long decimal = 144;
    Twelve t = Twelve::fromDecimal(decimal);
    EXPECT_EQ(t.toString(), "100");
}

TEST(TwelveTest, ToDecimal) {
    Twelve t("100");
    unsigned long long decimal = t.toDecimal();
    EXPECT_EQ(decimal, 144);
}

TEST(TwelveTest, Multiplication) {
    Twelve t1("10");
    Twelve t2("2");
    Twelve result = t1 * t2;
    EXPECT_EQ(result.toString(), "20");
}

TEST(TwelveTest, MultiplicationAssignment) {
    Twelve t1("10");
    Twelve t2("2");
    t1 *= t2;
    EXPECT_EQ(t1.toString(), "20");
}

TEST(TwelveTest, Division) {
    Twelve t1("20");
    Twelve t2("2");
    Twelve result = t1 / t2;
    EXPECT_EQ(result.toString(), "10");
}

TEST(TwelveTest, DivisionAssignment) {
    Twelve t1("20");
    Twelve t2("2");
    t1 /= t2;
    EXPECT_EQ(t1.toString(), "10");
}

TEST(TwelveTest, DivisionByZero) {
    Twelve t1("20");
    Twelve t2("0");
    EXPECT_THROW(t1 / t2, DivisionByZeroException);
}

TEST(TwelveTest, OverflowAddition) {
    Twelve t1("BBBBBBBBBB");
    Twelve t2("1");
    EXPECT_THROW(t1 + t2, OverflowException);
}

TEST(TwelveTest, OverflowMultiplication) {
    Twelve t1("BBBBBBBBBB");
    Twelve t2("2");
    EXPECT_THROW(t1 * t2, OverflowException);
}

TEST(TwelveTest, NegativeResultSubtraction) {
    Twelve t1("1");
    Twelve t2("2");
    EXPECT_THROW(t1 - t2, NegativeResultException);
}
