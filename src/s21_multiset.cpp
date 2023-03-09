
#include "s21_multiset.h"
namespace s21 {
/* --БЛОК КОНСТРУКТОРОВ И ДЕСТРУКТОРОВ-- */
template <class T>
Multiset<T>::Multiset(const Multiset &ms) {  //  COPY
    this->root = nullptr;
    this->hide_node->parent = nullptr;
    this->hide_node->left = nullptr;
    this->hide_node->right = nullptr;
    this->count_of_elem = 0;
    copy_set_m(this, ms.root);
}

template <class T>
Multiset<T>::Multiset(std::initializer_list<T> const &items) {
    this->root = nullptr;
    this->hide_node->parent = nullptr;
    this->hide_node->left = nullptr;
    this->hide_node->right = nullptr;
    this->count_of_elem = 0;
    if (items.size()) {
        for (int i = 0; i < items.size(); i++) {
            insert(items.begin()[i]);
        }
    }
}

template <class T>
Multiset<T>& Multiset<T>::operator=(const Multiset &ms) {  // COPY
        this->delete_tree(this->root);
        this->root = nullptr;
        copy_set_m(this, ms.root);
        return *this;
}

template <class T>
Multiset<T>& Multiset<T>::operator=(Multiset<T> &&ms) {  // MOVE
    this->delete_tree(this->root);
    this->root = ms.root;
    this->count_of_elem = ms.count_of_elem;
    ms.root = nullptr;
    ms.count_of_elem = 0;
    return *this;
}
/* ----------------------------------------------- */

/* --БЛОК РАБОТЫ С МУЛЬТИМНОЖЕСТВОМ-- */

template <class T>
void Multiset<T>::insert_(T value) {
    typename Binary_tree<T>::Tree_node * temp = new typename Binary_tree<T>::Tree_node();
    temp->Tree(value, 0, nullptr, nullptr);
    if (this->root == nullptr) {
        this->root = temp;
        temp->set_color(1);
        temp->parent = nullptr;
        this->count_of_elem++;
    } else {
        typename Binary_tree<T>::Tree_node * p = this->root;
        typename Binary_tree<T>::Tree_node * q = nullptr;
        while (p != nullptr) {
            q = p;
            if (p->data <= temp->data) {
                p = p->right;
            } else if (p->data > temp->data) {
                p = p->left;
            }
        }
            temp->parent = q;
            if (q->data <= temp->data) {
                q->right = temp;
            } else {
                q->left = temp;
            }
            this->fix_after_insert(temp);
            this->count_of_elem++;
    }
}

template <class T>
typename Multiset<T>::iterator Multiset<T>::insert(const T& value) {
    typename Binary_tree<T>::Tree_node * temp = new typename Binary_tree<T>::Tree_node();
    temp->Tree(value, 0, nullptr, nullptr);
    if (this->root == nullptr) {
        this->root = temp;
        temp->set_color(1);
        temp->parent = nullptr;
        this->count_of_elem++;
    } else {
        typename Binary_tree<T>::Tree_node * p = this->root;
        typename Binary_tree<T>::Tree_node * q = nullptr;
        while (p != nullptr) {
            q = p;
            if (p->data <= temp->data) {
                p = p->right;
            } else if (p->data > temp->data) {
                p = p->left;
            }
        }
            temp->parent = q;
            if (q->data <= temp->data) {
                q->right = temp;
            } else {
                q->left = temp;
            }
            this->fix_after_insert(temp);
            this->count_of_elem++;
    }
    typename Set<T>::iterator it(temp, this);
    return it;
}

template<class T>
void Multiset<T>::copy_set_m(Multiset<T> * res, typename Set<T>::Tree_node * temp) {
    if (temp) {
        res->insert(temp->data);
        copy_set_m(res, temp->left);
        copy_set_m(res, temp->right);
    }
}

template<class T>
void Multiset<T>::merge(Multiset<T>& other) {
    auto i = other.begin();
    while (i != other.end()) {
        this->insert(*i);
        ++i;
    }
}
/* ----------------------------------------------- */

/* --БЛОК ПРОСМОТРА МУЛЬТИМНОЖЕСТВА-- */
template <class T>
size_type Multiset<T>::count(const T& key) {
    int res = 0;
    auto i = this->begin();
    while (i != this->end()) {
        if (*i == key)
            res++;
        ++i;
    }
    return res;
}

template <class T>
typename Multiset<T>::iterator Multiset<T>::find(const T& key) {
    auto it = this->begin();
    bool flag_find = false;
    for (; it != this->end(); ++it) {
        if (*it == key) {
            flag_find = true;
            break;
        }
    }
    typename Set<T>::iterator res(it);
    return res;
}

template<class T>
std::pair<typename Multiset<T>::iterator, typename Multiset<T>::iterator>
Multiset<T>::equal_range(const T& key) {
    std::pair<typename Multiset<T>::iterator, typename Multiset<T>::iterator> res;
    typename Multiset<T>::iterator it = find(key);
    res.first = it;
    while (*it == key && it != this->end()) {
        ++it;
    }
    res.second = it;
    return res;
}

template<class T>
typename Multiset<T>::iterator  Multiset<T>::lower_bound(const T& key) {
    typename Set<T>::iterator res = this->begin();
    while (res.get_node()->data < key && res.get_node() != this->hide_node) {
        ++res;
    }
    return res;
}

template<class T>
typename Multiset<T>::iterator  Multiset<T>::upper_bound(const T& key) {
    typename Set<T>::iterator res = this->begin();
    while (res.get_node()->data <= key && res.get_node() != this->hide_node) {
        ++res;
    }
    return res;
}

template<class T>
template<typename ...Args>
std::vector<std::pair<typename Multiset<T>::iterator , bool>> Multiset<T>::emplace(Args&&... args) {
    std::vector<std::pair<typename Set<T>::iterator, bool>> res;
    std::pair<typename Set<T>::iterator, bool> p;
    Multiset<T> temp_set {args...};
    temp_set.print();
    auto it = temp_set.begin();
    while (it != temp_set.end()) {
        p.first = this->insert(*it);
        p.second = 1;
        ++it;
        res.push_back(p);
    }
    return res;
}
/* ----------------------------------------------- */
}  //  namespace s21
