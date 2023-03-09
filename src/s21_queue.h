#ifndef SRC_S21_QUEUE_H_
#define SRC_S21_QUEUE_H_
#include <iostream>

namespace s21 {
template <typename T>
class queue {
    using value_type = T;
    using reference = T &;
    using const_reference = const T &;
    using size_type = size_t;

 private:
    struct node {
        value_type data_;
        node* next_;
        node* prev_;
    };
    node *head_;
    node *tail_;

    void free_queue();

 public:
    queue();
    queue(std::initializer_list<value_type> const &items);
    queue(const queue &q);
    queue(queue &&q);
    queue operator=(queue &&q);
    ~queue();

    const_reference front();
    const_reference back();

    bool empty();
    size_type size();

    void push(const_reference value);
    void pop();
    void swap(queue& other);

    template <typename ...Args>
    void emplace_back(Args&&... args);
};
};  // namespace s21
#endif  // SRC_S21_QUEUE_H_
