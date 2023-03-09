#include <iostream>
#include "s21_set.h"

namespace s21 {
    /* --ИТЕРАТОР-- */
    template <class T>
    typename Set<T>::iterator Set<T>::begin() {
        typename Set<T>::iterator temp(this->hide_node, this);
        if (this->root != nullptr) {
            temp = typename Set<T>::iterator(this->find_most_left_elem(), this);
        }
        return temp;
    }
    template <class T>
    typename Set<T>::iterator Set<T>::end() {
        typename Set<T>::iterator temp(this->hide_node, this);
        return temp;
    }
        template<class T>
    typename Set<T>::iterator Set<T>::iterator::operator++() {
        if (this->_root->size_of_tree() > 0) {
            if (this->node == this->_root->find_most_right_elem()) {
                _root->hide_node->data = _root->size_of_tree();
                this->node = this->_root->hide_node;
            } else if (this->node == this->_root->hide_node) {
                this->node = this->_root->find_most_right_elem();
            } else {
                if (this->node->right != nullptr) {  //  если у узла есть правый элемент
                //  то след за ним будет минимальным элементом в этом поддереве
                    this->node = this->node->right->minimum();
                } else {  //  Идем вверх пока не встретим узел который является
                          //  левым дочерним узлом своего родителя
                    iterator y(this->node->parent, this->_root);
                    while (y.node != nullptr && this->node == y.node->right) {
                        this->node = y.node;
                        y.node = y.node->parent;
                    }
                    this->node = y.node;
                }
            }
        }
        return *this;
    }

    template <class T>
    typename Set<T>::iterator Set<T>::iterator::operator--() {
        if (this->_root->size_of_tree() > 0) {
            if (this->node == this->_root->find_most_left_elem()) {
                _root->hide_node->data = _root->size_of_tree();
                this->node = this->_root->hide_node;
            } else if (this->node == this->_root->hide_node) {
                this->node = this->_root->find_most_right_elem();
            } else {
                if (this->node->left != nullptr) {
                    this->node = this->node->left->maximum();
                } else {
                    iterator y(this->node->parent, this->_root);
                    while (y.node != nullptr && this->node == y.node->left) {
                        this->node = y.node;
                        y.node = y.node->parent;
                    }
                    this->node = y.node;
                }
            }
        }
        return *this;
    }
    /* ----------------------------------------------- */

    /* --ПРОЧИЕ ФУНКЦИИ-- */
    template<class T>
    Set<T> Set<T>::operator=(const Set<T> &s) {
        this->delete_tree(this->root);
        this->root = nullptr;
        copy_set(this, s.root);
        return *this;
    }

    template<class T>
    Set<T> Set<T>::operator=(Set<T> &&s) {
        this->delete_tree(this->root);
        this->root = s.root;
        this->count_of_elem = s.count_of_elem;
        s.root = nullptr;
        s.count_of_elem = 0;
        return *this;
    }

    template<class T>
    void Set<T>::copy_set(Set<T> * res, typename Set<T>::Tree_node * temp) {
        if (temp) {
            res->delete_tree(res->root);
            res->insert_in_tree(temp->data);
            this->count_of_elem++;
            copy_set(res, temp->left);
            copy_set(res, temp->right);
        }
    }
    /* ----------------------------------------------- */

    /* --БЛОК ПРОВЕРКИ НАПОЛНЕНИЯ-- */
    template <class T>
    bool Set<T>::empty() {
        return this->root == nullptr;
    }

    template <class T>
    size_type Set<T>::size() {
        return this->size_of_tree();
    }

    template <class T>
    size_type Set<T>::max_size() {
        return std::allocator<typename Binary_tree<T>::Tree_node>().max_size();
    }

    /* ----------------------------------------------- */

    /* --БЛОК РАБОТЫ С ДЕРЕВОМ-- */
    template <class T>
    void Set<T>::erase(iterator pos) {
        if (pos != end()) {
            this->delete_without_find(pos.get_node());
        }
    }

    template <class T>
    void Set<T>::clear() {
        this->delete_tree(this->root);
        if (this->hide_node) {
            delete this->hide_node;
            this->hide_node = nullptr;
            this->count_of_elem++= 0;
            this->root = nullptr;
        }
        this->count_of_elem++= 0;
        this->root = nullptr;
    }

    template <class T>
    void Set<T>::swap(Set<T>& other) {
        int temp_count_of_elem = other.count_of_elem;
        typename Set<T>::Tree_node * temp = other.root;
        other.root = this->root;
        this->root = temp;
        other.count_of_elem = this->count_of_elem;
        this->count_of_elem = temp_count_of_elem;
    }

    template <class T>
    std::pair<typename Set<T>::iterator, bool> Set<T>::insert(const value_type& value) {
        std::pair<typename Set<T>::iterator, bool> res;
        bool temp = this-> insert_in_tree(value);
        res.first = this->find(value);
        if (temp) {
            res.second = temp;
        } else {
            res.second = false;
        }
        return res;
    }

    template <class T>
    typename Set<T>::iterator Set<T>::find(const T& key) {
        typename Set<T>::iterator it(this->find_in_tree(key), this);
        return it;
    }

    template <class T>
    bool Set<T>::contains(const T& key) {
        return this->find_in_tree(key);
    }

    template <class T>
    void Set<T>::merge(Set<T>& other) {
        auto i = other.begin();
        while (i != other.end()) {
            this->insert_in_tree(*i);
            ++i;
        }
    }
    template <class T>
    template<typename ...Args>
    std::vector<std::pair<typename Set<T>::iterator, bool>> Set<T>::emplace(Args&&... args) {
        std::vector<std::pair<typename Set<T>::iterator, bool>> res;
        std::pair<typename Set<T>::iterator, bool> p;
        Set<T> temp_set {args...};
        temp_set.print();
        auto it = temp_set.begin();
        while (it != temp_set.end()) {
            if (this->contains(*it)) {
                p.second = 0;
                p.first = this->find(*it);
            } else {
                p.second = 1;
                std::pair<typename Set<T>::iterator, bool> temp_p = this->insert((const T&)(*it));
                p.first = temp_p.first;
            }
            ++it;
            res.push_back(p);
        }
        return res;
    }
    /* ----------------------------------------------- */
}  //  namespace s21
