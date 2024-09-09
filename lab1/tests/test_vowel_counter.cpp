#include "../src/vowel_counter.h"
#include "gtest/gtest.h"

// Граничные случаи: одна гласная, одна согласная
TEST(VowelCounterTest, SingleVowel) {
    // Arrange
    std::string input = "a";

    // Act
    int result = countVowels(input);

    // Assert
    EXPECT_EQ(result, 1);
}

TEST(VowelCounterTest, SingleConsonant) {
    // Arrange
    std::string input = "b";

    // Act
    int result = countVowels(input);

    // Assert
    EXPECT_EQ(result, 0);
}

// Проверка строки с гласными
TEST(VowelCounterTest, CountSimpleString) {
    // Arrange
    std::string input = "hello";

    // Act
    int result = countVowels(input);

    // Assert
    EXPECT_EQ(result, 2);
}

// Пустая строка должна выбрасывать исключение
TEST(VowelCounterTest, EmptyStringThrows) {
    // Arrange
    std::string input = "";

    // Act & Assert
    EXPECT_THROW(countVowels(input), std::invalid_argument);
}

// Проверка на исключение при наличии заглавных букв
TEST(VowelCounterTest, UppercaseThrows) {
    // Arrange
    std::string input = "Hello";

    // Act & Assert
    EXPECT_THROW(countVowels(input), std::invalid_argument);
}

// Наличие не-латинских символов должно выбрасывать исключение
TEST(VowelCounterTest, NonLatinCharactersThrows) {
    // Arrange
    std::string input = "héllo";

    // Act & Assert
    EXPECT_THROW(countVowels(input), std::invalid_argument);
}

// Строка, состоящая только из гласных
TEST(VowelCounterTest, OnlyVowels) {
    // Arrange
    std::string input = "aeiou";

    // Act
    int result = countVowels(input);

    // Assert
    EXPECT_EQ(result, 5);
}

// Строка без гласных
TEST(VowelCounterTest, NoVowels) {
    // Arrange
    std::string input = "bcdfg";

    // Act
    int result = countVowels(input);

    // Assert
    EXPECT_EQ(result, 0);
}

// Проверка строки со смешанным регистром (должно выбрасывать исключение)
TEST(VowelCounterTest, MixedCaseStringThrows) {
    // Arrange
    std::string input = "ApPlE pIe";

    // Act & Assert
    EXPECT_THROW(countVowels(input), std::invalid_argument);
}

// Обработка пробелов: количество гласных должно быть верным
TEST(VowelCounterTest, SpaceHandling) {
    // Arrange
    std::string input = "a e i o u";

    // Act
    int result = countVowels(input);

    // Assert
    EXPECT_EQ(result, 5);
}

// Проверка на наличие чисел в строке (должно выбрасывать исключение)
TEST(VowelCounterTest, NumbersThrow) {
    // Arrange
    std::string input = "hello123";

    // Act & Assert
    EXPECT_THROW(countVowels(input), std::invalid_argument);
}

// Проверка на специальные символы (должно выбрасывать исключение)
TEST(VowelCounterTest, SpecialCharactersThrow) {
    // Arrange
    std::string input = "hello!";

    // Act & Assert
    EXPECT_THROW(countVowels(input), std::invalid_argument);
}

// Строка, содержащая только пробелы
TEST(VowelCounterTest, OnlySpaces) {
    // Arrange
    std::string input = "     ";

    // Act
    int result = countVowels(input);

    // Assert
    EXPECT_EQ(result, 0);
}

// Длинная строка
TEST(VowelCounterTest, LongString) {
    // Arrange
    std::string input = "the quick brown fox jumps over the lazy dog";

    // Act
    int result = countVowels(input);

    // Assert
    EXPECT_EQ(result, 11);
}

// Строка, содержащая повторяющиеся гласные
TEST(VowelCounterTest, RepeatedCharacters) {
    // Arrange
    std::string input = "aaaaaaaaaa";

    // Act
    int result = countVowels(input);

    // Assert
    EXPECT_EQ(result, 10);
}

// Проверка строк с табуляцией и пробелами
TEST(VowelCounterTest, StringWithTabsAndSpaces) {
    // Arrange
    std::string input = "a\te i o  u";

    // Act
    int result = countVowels(input);

    // Assert
    EXPECT_EQ(result, 5);
}

// Строка с не-алфавитными символами (должно выбрасывать исключение)
TEST(VowelCounterTest, NonAlphaCharactersThrow) {
    // Arrange
    std::string input = "hello@world";

    // Act & Assert
    EXPECT_THROW(countVowels(input), std::invalid_argument);
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
