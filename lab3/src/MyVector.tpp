#ifndef MYVECTOR_TPP
#define MYVECTOR_TPP

#include "MyVector.hpp"

template<typename T>
MyVector<T>::MyVector() : data_(nullptr), size_(0), capacity_(0) {}

template<typename T>
MyVector<T>::MyVector(const MyVector& other) : data_(nullptr), size_(other.size_), capacity_(other.capacity_) {
    if (capacity_ > 0) {
        data_ = new T[capacity_];
        for (std::size_t i = 0; i < size_; ++i) {
            data_[i] = other.data_[i];
        }
    }
}

template<typename T>
MyVector<T>::MyVector(MyVector&& other) noexcept : data_(other.data_), size_(other.size_), capacity_(other.capacity_) {
    other.data_ = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;
}

template<typename T>
MyVector<T>& MyVector<T>::operator=(const MyVector& other) {
    if (this != &other) {
        delete[] data_;
        size_ = other.size_;
        capacity_ = other.capacity_;
        data_ = new T[capacity_];
        for (std::size_t i = 0; i < size_; ++i) {
            data_[i] = other.data_[i];
        }
    }
    return *this;
}

template<typename T>
MyVector<T>& MyVector<T>::operator=(MyVector&& other) noexcept {
    if (this != &other) {
        delete[] data_;
        data_ = other.data_;
        size_ = other.size_;
        capacity_ = other.capacity_;

        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    }
    return *this;
}

template<typename T>
MyVector<T>::~MyVector() {
    delete[] data_;
}

template<typename T>
void MyVector<T>::push_back(const T& value) {
    if (size_ == capacity_) {
        resize();
    }
    data_[size_++] = value;
}

template<typename T>
void MyVector<T>::erase(std::size_t index) {
    if (index >= size_) {
        throw std::out_of_range("Index out of range");
    }
    for (std::size_t i = index; i < size_ - 1; ++i) {
        data_[i] = std::move(data_[i + 1]);
    }
    --size_;
}

template<typename T>
T& MyVector<T>::operator[](std::size_t index) {
    if (index >= size_) {
        throw std::out_of_range("Index out of range");
    }
    return data_[index];
}

template<typename T>
const T& MyVector<T>::operator[](std::size_t index) const {
    if (index >= size_) {
        throw std::out_of_range("Index out of range");
    }
    return data_[index];
}

template<typename T>
std::size_t MyVector<T>::size() const {
    return size_;
}

template<typename T>
void MyVector<T>::resize() {
    capacity_ = capacity_ == 0 ? 1 : capacity_ * 2;
    T* newData = new T[capacity_];
    for (std::size_t i = 0; i < size_; ++i) {
        newData[i] = std::move(data_[i]);
    }
    delete[] data_;
    data_ = newData;
}

template<typename T>
T* MyVector<T>::begin() {
    return data_;
}

template<typename T>
T* MyVector<T>::end() {
    return data_ + size_;
}

template<typename T>
const T* MyVector<T>::begin() const {
    return data_;
}

template<typename T>
const T* MyVector<T>::end() const {
    return data_ + size_;
}

#endif // MYVECTOR_TPP
