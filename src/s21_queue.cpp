#include "s21_queue.h"
namespace s21 {
    template <typename T>
    queue<T>::queue() {
        head_ = nullptr;
        tail_ = nullptr;
    }

    template <typename T>
    queue<T>::queue(std::initializer_list<value_type> const &items) {
        head_ = nullptr;
        tail_ = nullptr;
        if (items.size()) {
            for (int i = 0; i < items.size(); i++) {
                push(items.begin()[i]);
            }
        }
    }

    template <typename T>
    queue<T>::queue(const queue &q) {
        node *tmp = q.head_;
        head_ = nullptr;
        tail_ = nullptr;

        while (tmp != nullptr) {
            push(tmp->data_);
            tmp = tmp->next_;
        }
    }

    template <typename T>
    queue<T>::queue(queue &&q) {
        head_ = q.head_;
        tail_ = q.tail_;
        q.head_ = nullptr;
        q.tail_ = nullptr;
    }

    template <typename T>
    typename queue<T>::queue queue<T>::operator=(queue &&q) {
        if (this->size() > 0) {
            free_queue();
        }
        node *tmp = q.head_;
        while (tmp != nullptr) {
            push(tmp->data_);
            tmp = tmp->next_;
        }
        return *this;
    }

    template <typename T>
    void queue<T>::free_queue() {
        if (head_ != nullptr) {
            node *tmp;
            while (head_ != nullptr) {
                tmp = head_;
                head_ = head_->next_;
                delete tmp;
            }
        }
        head_ = nullptr;
        tail_ = nullptr;
    }

    template <typename T>
    queue<T>::~queue() {
        free_queue();
    }

    template <typename T>
    typename queue<T>::const_reference queue<T>::front() {
        return (size() > 0) ? head_->data_ : (const_reference) 0;
    }

    template <typename T>
    typename queue<T>::const_reference queue<T>::back() {
        return tail_->data_;
    }

    template <typename T>
    bool queue<T>::empty() {
        return (tail_ == nullptr) ? true : false;
    }

    template <typename T>
    typename queue<T>::size_type queue<T>::size() {
        size_type result = 0;
        node *tmp = head_;
        while (tmp != nullptr) {
            result++;
            tmp = tmp->next_;
        }
        return result;
    }

    template <typename T>
    void queue<T>::push(const_reference value) {
        node *tmp = new node;
        tmp->data_ = value;
        tmp->next_ = nullptr;
        tmp->prev_ = nullptr;
        if (tail_ == nullptr) {
            head_ = tmp;
            tail_ = tmp;
        } else {
            tmp->prev_ = tail_;
            tail_->next_ = tmp;
            tail_ = tail_->next_;
        }
    }

    template <typename T>
    void queue<T>::pop() {
        if (head_ != nullptr) {
            node *tmp = head_;
            head_ = head_->next_;
            delete tmp;
        }
    }

    template <typename T>
    void queue<T>::swap(queue& other) {
        queue<T> tmp(other);
        other.free_queue();
        node *tmp_node = head_;
        while (tmp_node != nullptr) {
            other.push(tmp_node->data_);
            tmp_node = tmp_node->next_;
        }
        free_queue();
        tmp_node = tmp.head_;
        while (tmp_node != nullptr) {
            push(tmp_node->data_);
            tmp_node = tmp_node->next_;
        }
    }

    template <typename T>
    template <typename ... Args>
    void queue<T>::emplace_back(Args&&... args) {
        queue<T> tmp_queue({args...});
        while (tmp_queue.size() > 0) {
            push(tmp_queue.front());
            tmp_queue.pop();
        }
    }
}  // namespace s21
