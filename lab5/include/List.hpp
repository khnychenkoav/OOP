#ifndef LIST_HPP
#define LIST_HPP

#include <memory_resource>
#include <memory>
#include <iterator>
#include <vector>

template <typename T>
class List {
public:
    using allocator_type = std::pmr::polymorphic_allocator<T>;
    class Iterator;

    explicit List(const allocator_type& alloc = allocator_type{})
        : alloc_(alloc.resource()), head_(nullptr), tail_(nullptr) {}
    ~List();

    void push_back(const T& value);
    void push_front(const T& value);
    void pop_back();
    void pop_front();
    bool empty() const { return head_ == nullptr; }
    void clear();

    Iterator begin() { return Iterator(head_); }
    Iterator end() { return Iterator(nullptr); }
    void sort();

private:
    struct Node {
        T data;
        Node* prev;
        Node* next;
        Node(const T& value, Node* p, Node* n) : data(value), prev(p), next(n) {}
    };

    std::pmr::memory_resource* alloc_;
    Node* head_;
    Node* tail_;
    using NodeAllocator = std::pmr::polymorphic_allocator<Node>;

    Node* create_node(const T& value, Node* prev, Node* next);
    void delete_node(Node* node);

public:
    class Iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using reference = T&;
        using pointer = T*;

        Iterator(Node* node) : node_(node) {}
        reference operator*() const { return node_->data; }
        pointer operator->() const { return &node_->data; }

        Iterator& operator++() {
            node_ = node_->next;
            return *this;
        }

        Iterator operator++(int) {
            Iterator tmp = *this;
            node_ = node_->next;
            return tmp;
        }

        friend bool operator==(const Iterator& a, const Iterator& b) {
            return a.node_ == b.node_;
        }

        friend bool operator!=(const Iterator& a, const Iterator& b) {
            return a.node_ != b.node_;
        }

    private:
        Node* node_;
    };
};

#include "List.tpp"

#endif
