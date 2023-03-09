#ifndef SRC_S21_VECTOR_H_
#define SRC_S21_VECTOR_H_
#include <iostream>

namespace s21 {
template <typename T>
class Vector {
 public:
    using value_type = T;
    using reference = T &;
    using const_reference = const T &;
    using iterator = T *;
    using const_iterator = const T *;
    using size_type = size_t;

    Vector();
    explicit Vector(size_type n);
    Vector(std::initializer_list<value_type> const &items);
    Vector(const Vector &v);
    Vector(Vector &&v);
    Vector operator=(Vector &&v);
    ~Vector();

    reference at(size_type pos);
    reference operator[](size_type pos);
    const_reference front();
    const_reference back();
    iterator data();

    iterator begin();
    iterator end();

    bool empty();
    size_type size();
    size_type max_size();
    void reserve(size_type size);
    size_type capacity();
    void shrink_to_fit();

    void clear();
    iterator insert(iterator pos, const_reference value);
    void erase(iterator pos);
    void push_back(const_reference value);
    void pop_back();
    void swap(Vector& other);

    template <typename ...Args>
    iterator emplace(const_iterator pos, Args&&... args);
    template <typename ...Args>
    void emplace_back(Args&&... args);

 private:
    value_type *current_value;
    long long int current_size;
    long long int current_capacity;
};

};  // namespace s21
#endif  // SRC_S21_VECTOR_H_
