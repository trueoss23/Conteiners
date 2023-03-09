#include "s21_list.h"
#include <iostream>
// #include <initializer_list>
#include <list>
// #include <limits>
// #include <cstdarg>


namespace s21 {
    template <typename T>
    list<T>::list() {
        this->count_added_elem = 0;
        this->head = nullptr;
        this->tail = nullptr;
        this->create_count_node();
    }

    template <typename T>
    list<T>::list(size_t n) {
        count_added_elem = 0;
        this->head = nullptr;
        this->tail = nullptr;
        this->create_count_node();
        for (int i = 0; i < n; i++) {
            this->push_front(0);
        }
    }

    template <typename T>
    list<T>::list(const list &l) {
        s21::list<T>::iterator start(l.head);
        s21::list<T>::iterator stop(l.tail->next);
        this->count_added_elem = 0;
        this->head = nullptr;
        this->tail = nullptr;
        this->create_count_node();
        while (start != stop) {
            this->push_back(*start);
            ++start;
        }
    }

    template <typename T>
    list<T>::list(std::initializer_list<value_type> const &items) {
        int count_elem = items.size();
        this->count_added_elem = 0;
        this->head = nullptr;
        this->tail = nullptr;
        this->create_count_node();
        if (items.size()) {
            for (int i = 0; i < count_elem; i++) {
                this->push_back((value_type)items.begin()[i]);
            }
        }
    }

    template <typename T>
    list<T>::list(list &&l) {
        this->count_added_elem = l.count_added_elem;
        this->head = l.head;
        this->tail = l.tail;
        l.count_added_elem = 0;
        l.head = nullptr;
        l.tail = nullptr;
        l.create_count_node();
    }

    template <typename T>
    list<T>::~list() {
        this->free_list();
    }

    template <typename T>
    typename list<T>::list list<T>::operator=(list &&l) {
        this->free_list();
        this->count_added_elem = l.count_added_elem;
        this->head = l.head;
        this->tail = l.tail;
        l.count_added_elem = 0;
        l.head = nullptr;
        l.tail = nullptr;
        l.create_count_node();
        return *this;
    }

    template <typename T>
    bool list<T>::empty() {
        return this->count_added_elem == 0 ? 1 : 0;
    }

    template <typename T>
    size_type list<T>::size() {
        return this->count_added_elem;
    }

    template <typename T>
    void list<T>::push_front(T value) {
        list_node *tmp = new list_node;
        list_node *count_node = this->head->prev;
        count_node->next = tmp;
        tmp->_value = value;
        if (count_added_elem > 0) {
            tmp->prev = this->head->prev;
            tmp->next = this->head;
            this->head->prev = tmp;

        } else {
            this->head->prev = tmp;
            this->head->next = tmp;
            tmp->next = this->head;
            tmp->prev = this->head;
            this->tail = tmp;
        }
        this->head = tmp;
        count_added_elem++;
    }

    template <typename T>
    void list<T>::pop_front() {
        list<T>::iterator f(this->begin());
        this->erase(f);
    }

    template <typename T>
    void list<T>::push_back(T value) {
        list_node *tmp = new list_node;
        list_node *count_node = this->head->prev;
        count_node->prev = tmp;
        tmp->_value = value;
        if (count_added_elem == 0) {
            tmp->next = this->tail;
            tmp->prev = this->tail;
            this->head->prev = tmp;
            this->tail->next = tmp;
            this->head = tmp;
        } else {
            this->tail->next = tmp;
        }
        tmp->prev = this->tail;
        tmp->next = this->head->prev;
        this->tail = tmp;
        count_added_elem++;
    }

    template <typename T>
    void list<T>::pop_back() {
        list<T>::iterator b(this->tail);
        this->erase(b);
    }

    template <typename T>
    void list<T>::swap(list& other) {
        list intermediate;
        intermediate.free_list();
        intermediate.head = this->head;
        intermediate.tail = this->tail;
        intermediate.count_added_elem = this->count_added_elem;
        this->head = other.head;
        this->tail = other.tail;
        this->count_added_elem = other.count_added_elem;
        other.head = intermediate.head;
        other.tail = intermediate.tail;
        other.count_added_elem = intermediate.count_added_elem;
        intermediate.head = nullptr;
        intermediate.tail = nullptr;
        intermediate.count_added_elem = 0;
    }

    template <typename T>
    void list<T>::merge(list& other) {
        list res((list &&)*this);
        list_node *prev;
        list<T>::iterator it_res = res.begin();
        list<T>::iterator it_other = other.begin();
        while (it_res != res.end() && it_other != other.end()) {
            if (*it_res < *it_other) {
                this->push_back(*it_res);
                ++it_res;
            } else {
                this->push_back(*it_other);
                ++it_other;
            }
        }
        while (it_res != res.end()) {
            this->push_back(*it_res);
            ++it_res;
        }
        while (it_other != other.end()) {
            this->push_back(*it_other);
            ++it_other;
        }
        other.free_list();
        other.create_count_node();
        res.free_list();
    }

    template <typename T>
    void list<T>::splice(const_iterator pos, list& other) {
        if (this->count_added_elem == 0) {
            this->swap(other);
        } else {
            if (pos == this->begin()) this->head = other.head;
            if (pos == this->end()) this->tail = other.tail;
            other.delete_count_node();
            this->count_added_elem += other.count_added_elem;
            list_node *curent = pos.get_data();
            list_node *old_prev = curent->prev;
            curent->prev = other.tail;
            old_prev->next = other.head;
            other.head->prev = old_prev;
            other.tail->next = curent;
            other.head = nullptr;
            other.tail = nullptr;
            other.count_added_elem = 0;
            other.create_count_node();
        }
    }

    template <typename T>
    void list<T>::reverse() {
        list<T>::iterator it(this->head);
        do {
            list_node *curent = it.get_data();
            list_node *next = curent->next;
            curent->next = curent->prev;
            curent->prev = next;
            it =  s21::list<T>::iterator(next);
        } while (it.get_data() != this->head);
        list_node *tail_of_this = this->tail;
        this->tail = this->head;
        this->head = tail_of_this;
    }

    template <typename T>
    void list<T>::unique() {
            list_node *curent = this->head;
            list<T>::iterator iter(this->begin());
            while (iter != this->end() && iter.get_data() != this->tail) {
                list_node *after_curent = curent->next;
                if (curent->_value == after_curent->_value) {
                    list<T>::iterator iter_for_delete(iter.get_data());
                    ++iter_for_delete;
                    this->erase(iter_for_delete);
                } else {
                    ++iter;
                    curent = curent->next;
                }
            }
    }

    template <typename T>
    void list<T>::sort() {
        if (this->count_added_elem > 1) {
            this->delete_count_node();
            if (this->head != nullptr && this->head->next != nullptr) {
                list *c = this->divide_list();
                if (this->head->next != nullptr) this->sort();
                if (c->head != nullptr && c->head->next != nullptr) c->sort();
                this->merge(*c);
                delete c;
            }
        }
    }

    template <typename T>
    list<T>* s21::list<T>::divide_list() {
        list_node *a = this->head;
        list_node *b = this->head->next;
        list *c = new list();
        c->free_list();
        if (this->tail != nullptr) {
            c->tail = this->tail;
            this->tail->next = nullptr;
        }
        while (b != nullptr && b->next != nullptr) {
            a = a->next;
            b = b->next;
            b = b->next;
        }
        c->head = a->next;
        c->tail->next = nullptr;
        c->count_added_elem = this->count_added_elem / 2;
        a->next = nullptr;
        this->tail = a;
        return c;
    }

    template <typename T>
    void list<T>::clear() {
        this->free_list();
        this->create_count_node();
    }

    template <typename T>
    typename list<T>::iterator list<T>::insert(iterator pos, T value) {
        if (this->head == this->head->prev || pos.get_data() == this->tail->next) {
            this->push_back(value);
            pos =  s21::list<T>::iterator(this->tail);
        } else if (pos.get_data() == this->head) {
            this->push_front(value);
            pos =  s21::list<T>::iterator(this->head);
        } else {
            list_node *tmp = new list_node;
            list_node *curent = pos.get_data();
            list_node *before_curent = curent->prev;
            tmp->_value = value;
            tmp->next = curent;
            tmp->prev = curent->prev;
            curent->prev = tmp;
            before_curent->next = tmp;
            count_added_elem++;
            pos =  s21::list<T>::iterator(tmp);
        }
        return pos;
    }

    template <typename T>
    void list<T>::erase(iterator pos) {
        list_node *p = pos.get_data();
        list_node *before_p = p->prev;
        list_node *after_p = p->next;
        if (p == this->head) {
            this->head = after_p;
        }
        if (p == this->tail) {
            this->tail = before_p;
        }
        before_p->next = after_p;
        after_p->prev = before_p;
        delete p;
        count_added_elem--;
        if (this->count_added_elem < 0) {
            this->create_count_node();
            count_added_elem = 0;
        }
    }

    template <typename T>
    void list<T>::free_list() {
        this->delete_count_node();
        list_node *pnt;
        while (this->head != nullptr) {
            pnt = this->head;
            this->head = this->head->next;
            delete pnt;
        }
        this->head = nullptr;
        this->tail = nullptr;
        this->count_added_elem = 0;
    }

    template <typename T>
    void list<T>::create_count_node() {
        list_node *count = new list_node();
        count->_value = 0;
        if (this->head == nullptr) {
            head = count;
            tail = count;
            this->head->next = this->tail;
            this->tail->prev = this->head;
        }
        this->head->prev = this->tail;
        this->tail->next = this->head;
    }

    template <typename T>
    void list<T>::delete_count_node() {
        if (this->tail != nullptr)  {
            if (this->tail->next != this->head && this->tail->next != nullptr) {
            list_node *count = this->tail->next;
            this->tail->next = nullptr;
            this->head->prev = nullptr;
            delete count;
            } else {
                this->tail->next = nullptr;
            }
        }
    }
    template <typename T>
    template <typename... Args>
    typename list<T>::iterator list<T>::emplace(const_iterator pos, Args&&... args) {
        list<T> temp_args_list{args...};
        this->splice(pos, temp_args_list);
        pos = temp_args_list.begin();
        return pos;
    }

    template <typename T>
    template <typename... Args>
    void list<T>::emplace_back(Args&&... args) {
        list<T> temp_args_list{args...};
        this->splice(this->end(), temp_args_list);
    }

    template <typename T>
    template <typename... Args>
    void list<T>::emplace_front(Args&&... args) {
        list<T> temp_args_list{args...};
        this->splice(this->begin(), temp_args_list);
    }
}  //  namespace s21
