#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <memory>
#include <stdexcept>

template <class T>
class Array {
public:
    Array();
    Array(const Array<T>& other);
    Array(Array<T>&& other) noexcept;
    Array<T>& operator=(const Array<T>& other);
    Array<T>& operator=(Array<T>&& other) noexcept;
    ~Array();

    void push_back(const T& value);
    void erase(std::size_t index);
    T& operator[](std::size_t index);
    const T& operator[](std::size_t index) const;
    std::size_t size() const;

    T* begin();
    T* end();
    const T* begin() const;
    const T* end() const;

private:
    std::unique_ptr<T[]> data_;
    std::size_t size_;
    std::size_t capacity_;

    void resize();
};

#include "Array.tpp"

#endif
