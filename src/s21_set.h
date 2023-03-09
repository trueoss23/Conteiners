#ifndef SRC_S21_SET_H_
#define SRC_S21_SET_H_

#include "tree.h"
#include <vector>

namespace s21 {
template <class T>
class Set : protected Binary_tree<T>::Binary_tree {
 public:
    using value_type = T;
    using Key = T;
    using size_type = size_t;
    class SetIterator;
    using iterator = SetIterator;
    /* --БЛОК КОНСТРУКТОРОВ И ДЕСТРУКТОРОВ-- */
    Set():Binary_tree<T>::Binary_tree() {}
    explicit Set(T key):Binary_tree<T>::Binary_tree(key) {}
    Set(std::initializer_list<value_type> const &items):Binary_tree<T>::Binary_tree(items) {}
    Set(const Set &s):Binary_tree<T>::Binary_tree(s) {}  //  COPY constr
    Set(Set &&s):Binary_tree<T>::Binary_tree(s) {}  //  MOVE constr
    ~Set() {}
    /* ----------------------------------------------- */
    Set<T> operator=(const Set<T> &s);
    Set<T> operator=(Set<T> &&s);
    void copy_set(Set<T> * res, typename Set<T>::Tree_node * temp);

    /* --ИТЕРАТОР-- */

    class SetIterator {
     private:
        typename Binary_tree<T>::Tree_node * node;
        Binary_tree<T> *_root;

     public:
        SetIterator() : node(nullptr), _root(nullptr) {}
        SetIterator(typename Binary_tree<T>::Tree_node * _node, Binary_tree<T> * __root) {
            node = _node;
            _root = __root;
        }
        ~SetIterator() { node = nullptr; _root = nullptr; }

        SetIterator operator++();
        SetIterator operator--();
        T& operator*() {
            if ((_root->root == nullptr) || this->node == nullptr)
                throw std::out_of_range("index is out of range\n");
            return this->node->data;
        }

        bool operator!=(SetIterator b) { return !(&(node->data) == &(b.node->data)); }
        bool operator==(SetIterator b) { return node == b.node; }
        SetIterator operator=(SetIterator  b) {
            this->_root = b._root;
            this->node = b.node;
            return *this;
        }

        typename Binary_tree<T>::Tree_node * get_node() { return node; }
    };

    iterator begin();
    iterator end();
    /* ----------------------------------------------- */

    /* --БЛОК ПРОВЕРКИ НАПОЛНЕНИЯ-- */
    bool empty();
    size_type size();
    size_type max_size();
    /* ----------------------------------------------- */

    /* --БЛОК РАБОТЫ С МНОЖЕСТВОМ-- */
    void clear();
    std::pair<iterator, bool> insert(const value_type& value);
    void erase(iterator pos);
    void swap(Set<T>& other);
    void merge(Set<T>& other);

    iterator find(const Key& key);
    bool contains(const Key& key);
    template<typename ...Args>
    std::vector<std::pair<iterator, bool>> emplace(Args&&... args);
    /* ----------------------------------------------- */
};
}  //  namespace s21
#endif  //  SRC_S21_SET_H_
