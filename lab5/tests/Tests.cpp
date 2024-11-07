#include "MemoryResource.hpp"
#include "List.hpp"
#include "Struct.hpp"
#include <gtest/gtest.h>
#include <string>
#include <climits>

TEST(ListTest, PushBack_SingleElement) {
    // Arrange
    MemoryResource mem_resource;
    List<int> int_list{std::pmr::polymorphic_allocator<int>(&mem_resource)};

    // Act
    int_list.push_back(10);

    // Assert
    auto it = int_list.begin();
    EXPECT_EQ(*it, 10);
}

TEST(ListTest, PushBack_MultipleElements) {
    MemoryResource mem_resource;
    List<int> int_list{std::pmr::polymorphic_allocator<int>(&mem_resource)};
    int_list.push_back(1);
    int_list.push_back(2);
    int_list.push_back(3);
    auto it = int_list.begin();
    ++it;
    EXPECT_EQ(*it, 2);
}

TEST(ListTest, PushFront_SingleElement) {
    MemoryResource mem_resource;
    List<std::string> str_list{std::pmr::polymorphic_allocator<std::string>(&mem_resource)};
    str_list.push_front("Hello");
    auto it = str_list.begin();
    EXPECT_EQ(*it, "Hello");
}

TEST(ListTest, PushFront_MultipleElements) {
    MemoryResource mem_resource;
    List<char> char_list{std::pmr::polymorphic_allocator<char>(&mem_resource)};
    char_list.push_front('a');
    char_list.push_front('b');
    char_list.push_front('c');
    auto it = char_list.begin();
    EXPECT_EQ(*it, 'c');
}

TEST(ListTest, PopBack_FromSingleElementList) {
    MemoryResource mem_resource;
    List<int> int_list{std::pmr::polymorphic_allocator<int>(&mem_resource)};
    int_list.push_back(5);
    int_list.pop_back();
    EXPECT_TRUE(int_list.empty());
}

TEST(ListTest, PopBack_FromMultipleElementsList) {
    MemoryResource mem_resource;
    List<int> int_list{std::pmr::polymorphic_allocator<int>(&mem_resource)};
    int_list.push_back(1);
    int_list.push_back(2);
    int_list.pop_back();
    auto it = int_list.begin();
    EXPECT_EQ(*it, 1);
}

TEST(ListTest, PopFront_FromSingleElementList) {
    MemoryResource mem_resource;
    List<double> double_list{std::pmr::polymorphic_allocator<double>(&mem_resource)};
    double_list.push_front(3.14);
    double_list.pop_front();
    EXPECT_TRUE(double_list.empty());
}

TEST(ListTest, PopFront_FromMultipleElementsList) {
    MemoryResource mem_resource;
    List<std::string> str_list{std::pmr::polymorphic_allocator<std::string>(&mem_resource)};
    str_list.push_front("First");
    str_list.push_front("Second");
    str_list.pop_front();
    auto it = str_list.begin();
    EXPECT_EQ(*it, "First");
}

TEST(ListTest, Clear_NonEmptyList) {
    MemoryResource mem_resource;
    List<int> int_list{std::pmr::polymorphic_allocator<int>(&mem_resource)};
    int_list.push_back(1);
    int_list.clear();
    EXPECT_TRUE(int_list.empty());
}

TEST(ListTest, Clear_EmptyList) {
    MemoryResource mem_resource;
    List<int> int_list{std::pmr::polymorphic_allocator<int>(&mem_resource)};
    int_list.clear();
    EXPECT_TRUE(int_list.empty());
}

TEST(ListTest, EmptyList_CheckEmpty) {
    MemoryResource mem_resource;
    List<char> char_list{std::pmr::polymorphic_allocator<char>(&mem_resource)};
    EXPECT_TRUE(char_list.empty());
}

TEST(ListTest, NonEmptyList_CheckNotEmpty) {
    MemoryResource mem_resource;
    List<char> char_list{std::pmr::polymorphic_allocator<char>(&mem_resource)};
    char_list.push_back('x');
    EXPECT_FALSE(char_list.empty());
}

TEST(ListTest, Iterator_BeginEqualsEndOnEmptyList) {
    MemoryResource mem_resource;
    List<float> float_list{std::pmr::polymorphic_allocator<float>(&mem_resource)};
    EXPECT_TRUE(float_list.begin() == float_list.end());
}

TEST(ListTest, Iterator_BeginNotEqualsEndOnNonEmptyList) {
    MemoryResource mem_resource;
    List<float> float_list{std::pmr::polymorphic_allocator<float>(&mem_resource)};
    float_list.push_back(1.1f);
    EXPECT_TRUE(float_list.begin() != float_list.end());
}

TEST(ListTest, Iterator_Increment) {
    MemoryResource mem_resource;
    List<int> int_list{std::pmr::polymorphic_allocator<int>(&mem_resource)};
    int_list.push_back(100);
    int_list.push_back(200);
    auto it = int_list.begin();
    ++it;
    EXPECT_EQ(*it, 200);
}

TEST(ListTest, Iterator_Dereference) {
    MemoryResource mem_resource;
    List<std::string> str_list{std::pmr::polymorphic_allocator<std::string>(&mem_resource)};
    str_list.push_back("Data");
    auto it = str_list.begin();
    EXPECT_EQ(*it, "Data");
}

TEST(ListTest, Iterator_Equality) {
    MemoryResource mem_resource;
    List<int> int_list{std::pmr::polymorphic_allocator<int>(&mem_resource)};
    auto it1 = int_list.begin();
    auto it2 = int_list.begin();
    EXPECT_TRUE(it1 == it2);
}

TEST(ListTest, Iterator_Inequality) {
    MemoryResource mem_resource;
    List<int> int_list{std::pmr::polymorphic_allocator<int>(&mem_resource)};
    int_list.push_back(10);
    auto it1 = int_list.begin();
    auto it2 = int_list.end();
    EXPECT_TRUE(it1 != it2);
}

TEST(ListTest, UseWithCustomStruct_SingleElement) {
    MemoryResource mem_resource;
    List<Struct> struct_list{std::pmr::polymorphic_allocator<Struct>(&mem_resource)};
    Struct s(1, "Test", 3.14);
    struct_list.push_back(s);
    auto it = struct_list.begin();
    EXPECT_EQ(it->id, 1);
}

TEST(ListTest, UseWithCustomStruct_MultipleElements) {
    MemoryResource mem_resource;
    List<Struct> struct_list{std::pmr::polymorphic_allocator<Struct>(&mem_resource)};
    struct_list.push_back(Struct(1, "One", 1.1));
    struct_list.push_back(Struct(2, "Two", 2.2));
    auto it = struct_list.begin();
    ++it;
    EXPECT_EQ(it->name, "Two");
}

TEST(ListTest, PushBack_MaxInteger) {
    MemoryResource mem_resource;
    List<int> int_list{std::pmr::polymorphic_allocator<int>(&mem_resource)};
    int_list.push_back(INT_MAX);
    auto it = int_list.begin();
    EXPECT_EQ(*it, INT_MAX);
}

TEST(ListTest, PushBack_MinInteger) {
    MemoryResource mem_resource;
    List<int> int_list{std::pmr::polymorphic_allocator<int>(&mem_resource)};
    int_list.push_back(INT_MIN);
    auto it = int_list.begin();
    EXPECT_EQ(*it, INT_MIN);
}

TEST(ListTest, PushBack_Zero) {
    MemoryResource mem_resource;
    List<int> int_list{std::pmr::polymorphic_allocator<int>(&mem_resource)};
    int_list.push_back(0);
    auto it = int_list.begin();
    EXPECT_EQ(*it, 0);
}

TEST(ListTest, PushFront_MaxInteger) {
    MemoryResource mem_resource;
    List<int> int_list{std::pmr::polymorphic_allocator<int>(&mem_resource)};
    int_list.push_front(INT_MAX);
    auto it = int_list.begin();
    EXPECT_EQ(*it, INT_MAX);
}

TEST(ListTest, PushFront_MinInteger) {
    MemoryResource mem_resource;
    List<int> int_list{std::pmr::polymorphic_allocator<int>(&mem_resource)};
    int_list.push_front(INT_MIN);
    auto it = int_list.begin();
    EXPECT_EQ(*it, INT_MIN);
}

TEST(ListTest, PushFront_Zero) {
    MemoryResource mem_resource;
    List<int> int_list{std::pmr::polymorphic_allocator<int>(&mem_resource)};
    int_list.push_front(0);
    auto it = int_list.begin();
    EXPECT_EQ(*it, 0);
}

TEST(ListTest, MultiplePushPop_Back) {
    MemoryResource mem_resource;
    List<int> int_list{std::pmr::polymorphic_allocator<int>(&mem_resource)};
    int_list.push_back(1);
    int_list.push_back(2);
    int_list.pop_back();
    auto it = int_list.begin();
    EXPECT_EQ(*it, 1);
}

TEST(ListTest, MultiplePushPop_Front) {
    MemoryResource mem_resource;
    List<int> int_list{std::pmr::polymorphic_allocator<int>(&mem_resource)};
    int_list.push_front(1);
    int_list.push_front(2);
    int_list.pop_front();
    auto it = int_list.begin();
    EXPECT_EQ(*it, 1);
}

TEST(ListTest, EmptyAfterPushPop) {
    MemoryResource mem_resource;
    List<int> int_list{std::pmr::polymorphic_allocator<int>(&mem_resource)};
    int_list.push_back(5);
    int_list.pop_back();
    EXPECT_TRUE(int_list.empty());
}

TEST(ListTest, IteratorPostIncrement) {
    MemoryResource mem_resource;
    List<char> char_list{std::pmr::polymorphic_allocator<char>(&mem_resource)};
    char_list.push_back('a');
    char_list.push_back('b');
    auto it = char_list.begin();
    auto current = *it++;
    EXPECT_EQ(current, 'a');
}

TEST(ListTest, IteratorPreIncrement) {
    MemoryResource mem_resource;
    List<char> char_list{std::pmr::polymorphic_allocator<char>(&mem_resource)};
    char_list.push_back('a');
    char_list.push_back('b');
    auto it = char_list.begin();
    ++it;
    EXPECT_EQ(*it, 'b');
}

TEST(ListTest, IteratorComparisonAfterIncrement) {
    MemoryResource mem_resource;
    List<double> double_list{std::pmr::polymorphic_allocator<double>(&mem_resource)};
    double_list.push_back(1.1);
    double_list.push_back(2.2);
    auto it = double_list.begin();
    ++it;
    EXPECT_TRUE(it != double_list.end());
}

TEST(ListTest, IteratorAtEndAfterIncrement) {
    MemoryResource mem_resource;
    List<int> int_list{std::pmr::polymorphic_allocator<int>(&mem_resource)};
    int_list.push_back(10);
    auto it = int_list.begin();
    ++it;
    EXPECT_TRUE(it == int_list.end());
}

TEST(ListTest, BeginPointsToFirstElement) {
    MemoryResource mem_resource;
    List<std::string> str_list{std::pmr::polymorphic_allocator<std::string>(&mem_resource)};
    str_list.push_back("First");
    str_list.push_back("Second");
    auto it = str_list.begin();
    EXPECT_EQ(*it, "First");
}

TEST(ListTest, EndPointsBeyondLastElement) {
    MemoryResource mem_resource;
    List<float> float_list{std::pmr::polymorphic_allocator<float>(&mem_resource)};
    auto it = float_list.end();
    EXPECT_TRUE(it == float_list.end());
}

TEST(ListTest, MultiplePushBack_CheckOrder) {
    MemoryResource mem_resource;
    List<int> int_list{std::pmr::polymorphic_allocator<int>(&mem_resource)};
    int_list.push_back(1);
    int_list.push_back(2);
    int_list.push_back(3);
    auto it = int_list.begin();
    EXPECT_EQ(*it, 1);
}

TEST(ListTest, MultiplePushFront_CheckOrder) {
    MemoryResource mem_resource;
    List<int> int_list{std::pmr::polymorphic_allocator<int>(&mem_resource)};
    int_list.push_front(1);
    int_list.push_front(2);
    int_list.push_front(3);
    auto it = int_list.begin();
    EXPECT_EQ(*it, 3);
}

TEST(ListTest, CopyConstructor_SingleElement) {
    MemoryResource mem_resource;
    List<int> original{std::pmr::polymorphic_allocator<int>(&mem_resource)};
    original.push_back(42);
    List<int> copy = original;
    auto it = copy.begin();
    EXPECT_EQ(*it, 42);
}

TEST(ListTest, CopyConstructor_EmptyList) {
    MemoryResource mem_resource;
    List<int> original{std::pmr::polymorphic_allocator<int>(&mem_resource)};
    List<int> copy = original;
    EXPECT_TRUE(copy.empty());
}

TEST(ListTest, AssignmentOperator_SingleElement) {
    MemoryResource mem_resource;
    List<int> list1{std::pmr::polymorphic_allocator<int>(&mem_resource)};
    List<int> list2{std::pmr::polymorphic_allocator<int>(&mem_resource)};
    list1.push_back(99);
    list2 = list1;
    auto it = list2.begin();
    EXPECT_EQ(*it, 99);
}

TEST(ListTest, AssignmentOperator_EmptyList) {
    MemoryResource mem_resource;
    List<int> list1{std::pmr::polymorphic_allocator<int>(&mem_resource)};
    List<int> list2{std::pmr::polymorphic_allocator<int>(&mem_resource)};
    list2 = list1;
    EXPECT_TRUE(list2.empty());
}

TEST(ListTest, SelfAssignment_CheckIntegrity) {
    MemoryResource mem_resource;
    List<int> int_list{std::pmr::polymorphic_allocator<int>(&mem_resource)};
    int_list.push_back(10);
    int_list = int_list;
    auto it = int_list.begin();
    EXPECT_EQ(*it, 10);
}

TEST(ListTest, MoveConstructor) {
    MemoryResource mem_resource;
    List<int> original{std::pmr::polymorphic_allocator<int>(&mem_resource)};
    original.push_back(5);
    List<int> moved = std::move(original);
    auto it = moved.begin();
    EXPECT_EQ(*it, 5);
}

TEST(ListTest, MoveAssignmentOperator) {
    MemoryResource mem_resource;
    List<int> list1{std::pmr::polymorphic_allocator<int>(&mem_resource)};
    List<int> list2{std::pmr::polymorphic_allocator<int>(&mem_resource)};
    list1.push_back(15);
    list2 = std::move(list1);
    auto it = list2.begin();
    EXPECT_EQ(*it, 15);
}

TEST(ListTest, PopBackOnEmptyList) {
    MemoryResource mem_resource;
    List<int> int_list{std::pmr::polymorphic_allocator<int>(&mem_resource)};
    EXPECT_NO_THROW(int_list.pop_back());
}

TEST(ListTest, PopFrontOnEmptyList) {
    MemoryResource mem_resource;
    List<int> int_list{std::pmr::polymorphic_allocator<int>(&mem_resource)};
    EXPECT_NO_THROW(int_list.pop_front());
}

TEST(ListTest, PushBackNullptrForPointerType) {
    MemoryResource mem_resource;
    List<int*> ptr_list{std::pmr::polymorphic_allocator<int*>(&mem_resource)};
    ptr_list.push_back(nullptr);
    auto it = ptr_list.begin();
    EXPECT_EQ(*it, nullptr);
}
