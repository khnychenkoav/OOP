#ifndef MYVECTOR_HPP
#define MYVECTOR_HPP

#include <cstddef>
#include <stdexcept>

template<typename T>
class MyVector {
public:
    MyVector();
    MyVector(const MyVector& other);
    MyVector(MyVector&& other) noexcept;
    MyVector& operator=(const MyVector& other);
    MyVector& operator=(MyVector&& other) noexcept;
    ~MyVector();

    void push_back(const T& value);
    void erase(std::size_t index);
    T& operator[](std::size_t index);
    const T& operator[](std::size_t index) const;
    std::size_t size() const;

    // New: Iterator support
    T* begin();
    T* end();
    const T* begin() const;
    const T* end() const;

private:
    T* data_;
    std::size_t size_;
    std::size_t capacity_;

    void resize();
};

#include "MyVector.tpp"

#endif // MYVECTOR_HPP
