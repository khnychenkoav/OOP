#ifndef LIST_TPP
#define LIST_TPP

#include "List.hpp"
#include <cassert>
#include <algorithm>

template <typename T>
List<T>::~List() {
    clear();
}

template <typename T>
void List<T>::push_back(const T& value) {
    Node* new_node = create_node(value, tail_, nullptr);
    if (tail_) {
        tail_->next = new_node;
    } else {
        head_ = new_node;
    }
    tail_ = new_node;
}

template <typename T>
void List<T>::push_front(const T& value) {
    Node* new_node = create_node(value, nullptr, head_);
    if (head_) {
        head_->prev = new_node;
    } else {
        tail_ = new_node;
    }
    head_ = new_node;
}

template <typename T>
void List<T>::pop_back() {
    if (!tail_) return;
    Node* node_to_delete = tail_;
    tail_ = tail_->prev;
    if (tail_) {
        tail_->next = nullptr;
    } else {
        head_ = nullptr;
    }
    delete_node(node_to_delete);
}

template <typename T>
void List<T>::pop_front() {
    if (!head_) return;
    Node* node_to_delete = head_;
    head_ = head_->next;
    if (head_) {
        head_->prev = nullptr;
    } else {
        tail_ = nullptr;
    }
    delete_node(node_to_delete);
}

template <typename T>
void List<T>::clear() {
    Node* current = head_;
    while (current) {
        Node* next = current->next;
        delete_node(current);
        current = next;
    }
    head_ = nullptr;
    tail_ = nullptr;
}

template <typename T>
typename List<T>::Node* List<T>::create_node(const T& value, Node* prev, Node* next) {
    NodeAllocator node_alloc(alloc_);
    Node* new_node = node_alloc.allocate(1);
    std::allocator_traits<NodeAllocator>::construct(node_alloc, new_node, value, prev, next);
    return new_node;
}

template <typename T>
void List<T>::delete_node(Node* node) {
    NodeAllocator node_alloc(alloc_);
    std::allocator_traits<NodeAllocator>::destroy(node_alloc, node);
    node_alloc.deallocate(node, 1);
}

template <typename T>
void List<T>::sort() {
    std::vector<T> elements;
    for (Node* current = head_; current != nullptr; current = current->next) {
        elements.push_back(current->data);
    }
    std::sort(elements.begin(), elements.end());
    Node* current = head_;
    for (const auto& val : elements) {
        current->data = val;
        current = current->next;
    }
}

#endif
