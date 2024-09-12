#include "../src/vowel_counter.h"
#include "gtest/gtest.h"

TEST(VowelCounterTest, SingleVowel) {
    //Arrange
    std::string input = "a";
    //Act
    int result = countVowels(input);
    //Assert
    EXPECT_EQ(result, 1);
}

TEST(VowelCounterTest, SingleConsonant) {
    std::string input = "b";
    int result = countVowels(input);
    EXPECT_EQ(result, 0);
}

TEST(VowelCounterTest, CountSimpleString) {
    std::string input = "hello";
    int result = countVowels(input);
    EXPECT_EQ(result, 2);
}

TEST(VowelCounterTest, EmptyStringThrows) {
    //Arrange
    std::string input = "";
    //Act&Assert
    EXPECT_THROW(countVowels(input), std::invalid_argument);
}

TEST(VowelCounterTest, UppercaseThrows) {
    std::string input = "Hello";
    EXPECT_THROW(countVowels(input), std::invalid_argument);
}

TEST(VowelCounterTest, NonLatinCharactersThrows) {
    std::string input = "héllo";
    EXPECT_THROW(countVowels(input), std::invalid_argument);
}

TEST(VowelCounterTest, OnlyVowels) {
    std::string input = "aeiou";
    int result = countVowels(input);
    EXPECT_EQ(result, 5);
}

TEST(VowelCounterTest, NoVowels) {
    std::string input = "bcdfg";
    int result = countVowels(input);
    EXPECT_EQ(result, 0);
}

TEST(VowelCounterTest, MixedCaseStringThrows) {
    std::string input = "ApPlE pIe";
    EXPECT_THROW(countVowels(input), std::invalid_argument);
}

TEST(VowelCounterTest, SpaceHandling) {
    std::string input = "a e i o u";
    int result = countVowels(input);
    EXPECT_EQ(result, 5);
}

TEST(VowelCounterTest, NumbersThrow) {
    std::string input = "hello123";
    EXPECT_THROW(countVowels(input), std::invalid_argument);
}

TEST(VowelCounterTest, SpecialCharactersThrow) {
    std::string input = "hello!";
    EXPECT_THROW(countVowels(input), std::invalid_argument);
}

TEST(VowelCounterTest, OnlySpaces) {
    std::string input = "     ";
    int result = countVowels(input);
    EXPECT_EQ(result, 0);
}

TEST(VowelCounterTest, LongString) {
    std::string input = "the quick brown fox jumps over the lazy dog";
    int result = countVowels(input);
    EXPECT_EQ(result, 12);
}

TEST(VowelCounterTest, RepeatedCharacters) {
    std::string input = "aaaaaaaaaa";
    int result = countVowels(input);
    EXPECT_EQ(result, 10);
}

TEST(VowelCounterTest, StringWithTabsAndSpaces) {
    std::string input = "a\te i o  u";
    int result = countVowels(input);
    EXPECT_EQ(result, 5);
}

TEST(VowelCounterTest, NonAlphaCharactersThrow) {
    std::string input = "hello@world";
    EXPECT_THROW(countVowels(input), std::invalid_argument);
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
