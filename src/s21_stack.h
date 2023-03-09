#ifndef SRC_S21_STACK_H_
#define SRC_S21_STACK_H_

namespace s21{
template <class T>
class Stack {
    using value_type = T;
    using const_reference = const T&;
    using size_type = size_t;

 private:
    struct node {
        T data;
        node * prev;
    };

    size_type count_of_elements;
    node * head;

 public:
    Stack();
    explicit Stack(T _data);
    Stack(std::initializer_list<value_type> const &items);
    Stack(const Stack<T> &s);
    Stack(Stack<T> &&s);
    ~Stack();

    Stack operator=(Stack<T> &&s);
    const_reference top();
    bool empty();
    size_type size();
    void swap(Stack& other);
    void vision_stack();
    void push(const_reference value);
    void pop();
    template<typename ...Args>
    void emplace_front(Args&&... args);
};
};  // namespace s21
#endif  //  SRC_S21_STACK_H_
