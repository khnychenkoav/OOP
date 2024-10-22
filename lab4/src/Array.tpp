#ifndef ARRAY_TPP
#define ARRAY_TPP

#include "Array.hpp"

template <class T>
Array<T>::Array() : data_(nullptr), size_(0), capacity_(0) {}

template <class T>
Array<T>::Array(const Array<T>& other) : data_(nullptr), size_(other.size_), capacity_(other.capacity_) {
    if (capacity_ > 0) {
        data_ = std::make_unique<T[]>(capacity_);
        for (std::size_t i = 0; i < size_; ++i) {
            data_[i] = other.data_[i];
        }
    }
}

template <class T>
Array<T>::Array(Array<T>&& other) noexcept : data_(std::move(other.data_)), size_(other.size_), capacity_(other.capacity_) {
    other.size_ = 0;
    other.capacity_ = 0;
}

template <class T>
Array<T>& Array<T>::operator=(const Array<T>& other) {
    if (this != &other) {
        data_.reset();
        size_ = other.size_;
        capacity_ = other.capacity_;
        if (capacity_ > 0) {
            data_ = std::make_unique<T[]>(capacity_);
            for (std::size_t i = 0; i < size_; ++i) {
                data_[i] = other.data_[i];
            }
        }
    }
    return *this;
}

template <class T>
Array<T>& Array<T>::operator=(Array<T>&& other) noexcept {
    if (this != &other) {
        data_ = std::move(other.data_);
        size_ = other.size_;
        capacity_ = other.capacity_;
        other.size_ = 0;
        other.capacity_ = 0;
    }
    return *this;
}

template <class T>
Array<T>::~Array() {
    data_.reset();
}

template <class T>
void Array<T>::push_back(const T& value) {
    if (size_ == capacity_) {
        resize();
    }
    data_[size_++] = value;
}

template <class T>
void Array<T>::erase(std::size_t index) {
    if (index >= size_) {
        throw std::out_of_range("Index out of range");
    }
    for (std::size_t i = index; i < size_ - 1; ++i) {
        data_[i] = std::move(data_[i + 1]);
    }
    --size_;
}

template <class T>
T& Array<T>::operator[](std::size_t index) {
    if (index >= size_) {
        throw std::out_of_range("Index out of range");
    }
    return data_[index];
}

template <class T>
const T& Array<T>::operator[](std::size_t index) const {
    if (index >= size_) {
        throw std::out_of_range("Index out of range");
    }
    return data_[index];
}

template <class T>
std::size_t Array<T>::size() const {
    return size_;
}

template <class T>
void Array<T>::resize() {
    std::size_t new_capacity = capacity_ == 0 ? 1 : capacity_ * 2;
    std::unique_ptr<T[]> new_data = std::make_unique<T[]>(new_capacity);

    for (std::size_t i = 0; i < size_; ++i) {
        new_data[i] = std::move(data_[i]);
    }
    capacity_ = new_capacity;
    data_ = std::move(new_data);
}

template <class T>
T* Array<T>::begin() {
    return data_.get();
}

template <class T>
T* Array<T>::end() {
    return data_.get() + size_;
}

template <class T>
const T* Array<T>::begin() const {
    return data_.get();
}

template <class T>
const T* Array<T>::end() const {
    return data_.get() + size_;
}

#endif
