#include <iostream>
#include "s21_stack.h"

namespace s21 {
    template <class T>
    using value_type = T;
    template <class T>
    using const_reference = const T&;
    using size_type = size_t;
    /* --БЛОК КОНСТРУКТОРОВ И ДЕСТРУКТОРОВ-- */
    template <class T>
    Stack<T>::Stack() {  //  DEFAULT
        count_of_elements = 0;
        head = nullptr;
    }
    template <class T>
    Stack<T>::Stack(T _data) {  //  PARAMETR
        head = nullptr;
        count_of_elements = 0;
        push(_data);
    }

    template <class T>
    Stack<T>::Stack(const Stack<T> &s) {  //  COPY
        Stack<T> temp_stack;
        int count = s.count_of_elements;
        head = nullptr;
        node * temp1 = s.head;
        while (count > 0) {
            temp_stack.push(temp1->data);
            temp1 = temp1->prev;
            count--;
        }
        count = temp_stack.count_of_elements;
        count_of_elements = 0;
        node * temp2 = temp_stack.head;
        while (count > 0) {
            push(temp2->data);
            temp2 = temp2->prev;
            count--;
        }
    }

    template <class T>
    Stack<T>::Stack(Stack<T> &&s) {  //  MOVE
        head = s.head;
        s.head = nullptr;
        count_of_elements = s.count_of_elements;
        s.count_of_elements = 0;
    }
    template <class T>
    Stack<T>::Stack(std::initializer_list<value_type> const &items) {  //  INITIALAIZER LIST
        head = nullptr;
        count_of_elements = 0;
        if (items.size()) {
            for (int i = 0; i < items.size(); i++) {
                push((value_type)items.begin()[i]);
            }
        }
    }

    template <class T>
    Stack<T>::~Stack() {  //  DESTRUCTOR
        while (count_of_elements > 0) {
            pop();
        }
        head = nullptr;
    }
    /* ----------------------------------------------- */

    /* --БЛОК ПРОВЕРКИ НАПОЛНЕНИЯ-- */
    template <class T>
    bool Stack<T>::empty() {
        return head == nullptr;
    }
    template <class T>
    typename Stack<T>::const_reference Stack<T>::top() {
        return head->data;
    }
    template <class T>
    size_type Stack<T>::size() {
        return count_of_elements;
    }
    /* ----------------------------------------------- */

    /* --ПРОЧИЕ ФУНКЦИИ-- */
    template <class T>
    void Stack<T>::push(const_reference value) {
        count_of_elements++;
        node * res = new node();
        res->data = value;
        res->prev = head;
        head = res;
    }

    template <class T>
    void Stack<T>::pop() {
        if (head != nullptr) {
            count_of_elements--;
            node * temp = head;
            head = head->prev;
            delete temp;
        }
    }

    template <class T>
    Stack<T> Stack<T>::operator=(Stack<T> &&s) {
        while (count_of_elements > 0) {
            pop();
        }
        head = nullptr;
        Stack<T> temp_stack;

        int count = s.count_of_elements;

        head = nullptr;
        node * temp1 = s.head;
        while (count > 0) {
            temp_stack.push(temp1->data);
            temp1 = temp1->prev;
            count--;
        }
        count = temp_stack.count_of_elements;
        count_of_elements = 0;
        node * temp2 = temp_stack.head;
        while (count > 0) {
            push(temp2->data);
            temp2 = temp2->prev;
            count--;
        }
        return *this;
    }

    template <class T>
    void Stack<T>::swap(Stack& other) {
        node * temp_node = other.head;
        int temp_count = other.count_of_elements;
        other.count_of_elements = count_of_elements;
        other.head = head;
        head = temp_node;
        count_of_elements = temp_count;
    }

    template <class T>
    template<typename ...Args>
    void Stack<T>::emplace_front(Args&&... args) {
        Stack<T> temp_stack{args...};
        Stack<T> res;
        while ((temp_stack.count_of_elements > 0)) {
            res.push(temp_stack.top());
            temp_stack.pop();
        }
        while ((res.count_of_elements > 0)) {
            this->push(res.top());
            res.pop();
        }
    }
    template <class T>
    void Stack<T>::vision_stack() {
        node * temp = head;
        int i = 0;
        while (i < size()) {
            i++;
            std::cout << temp->data << std::endl;
            temp = temp->prev;
        }
    }
    /* ----------------------------------------------- */
}  //  namespace s21
