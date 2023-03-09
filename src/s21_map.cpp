#include "s21_map.h"

namespace s21 {
    template <typename Key, typename T>
    map<Key, T>::map(std::initializer_list<value_type> const &items) {
        int count_elem = items.size();
        if (items.size()) {
            for (int i = 0; i < count_elem; i++) {
                this->insert((value_type)items.begin()[i]);
            }
        }
    }

    template <typename Key, typename T>
    map<Key, T> map<Key, T>::operator=(map &&m) {
        this->swap(m);
        return *this;
    }

    template <typename Key, typename T>
    void map<Key, T>::MapIterator::operator++() {
        if (this->_data->right != nullptr) {
            this->_data = this->_data->right;
            while (this->_data->left != nullptr) {
                this->_data = this->_data->left;
            }
        } else if (this->_data->parent != nullptr && this->_data != this->find_most_right_elem()) {
            MapIterator old_node(*(this->_data), *(this->_root));
            this->_data = this->_data->parent;
            while (this->_data->parent != nullptr && this->_data->right == old_node._data) {
                old_node._data = this->_data;
                this->_data = this->_data->parent;
            }
        } else if (this->_data == this->find_most_right_elem()) {
            this->_data = this->_root->hide_node;
        } else if (this->_data == this->_root->hide_node) {
            this->_data = this->find_most_right_elem();
        }
    }

    template <typename Key, typename T>
    void map<Key, T>::MapIterator::operator--() {
        if (this->_data->left != nullptr) {
            this->_data = this->_data->left;
            while (this->_data->right != nullptr) {
                this->_data = this->_data->right;
            }
        } else if (this->_data->parent != nullptr && this->_data != this->find_most_left_elem()) {
            MapIterator old_node(*(this->_data), *(this->_root));
            this->_data = this->_data->parent;
            while (this->_data->parent != nullptr && this->_data->left == old_node._data) {
                old_node._data = this->_data;
                this->_data = this->_data->parent;
            }
        } else if (this->_data == this->find_most_left_elem()) {
            this->_data = this->_root->hide_node;
        } else if (this->_data == this->_root->hide_node) {
            this->_data = this->find_most_right_elem();
        }
    }

    template <typename Key, typename T>
    typename Binary_tree<std::pair<Key, T> >::Tree_node* map<Key, T>::MapIterator::find_most_left_elem() {
        MapIterator left_elem(*(this->_root->root), *(this->_root));
        while (left_elem._data->parent != nullptr) {
            left_elem._data = left_elem._data->parent;
        }
        while (left_elem._data->left != nullptr) {
            left_elem._data = left_elem._data->left;
        }
        return left_elem._data;
    }

    template <typename Key, typename T>
    typename Binary_tree<std::pair<Key, T> >::Tree_node* map<Key, T>::MapIterator::find_most_right_elem() {
        MapIterator right_elem(*(this->_root->root), *(this->_root));
        while (right_elem._data->parent != nullptr) {
            right_elem._data = right_elem._data->parent;
        }
        while (right_elem._data->right != nullptr) {
            right_elem._data = right_elem._data->right;
        }
        return right_elem._data;
    }

    template <typename Key, typename T>
    typename map<Key, T>::mapped_type& map<Key, T>::at(const Key& key) {
        if (this->root == nullptr) {
            throw std::out_of_range("Incorrect input, map is empty");
        }
        bin_tree_node* finded_node = this->find_elem(key);
        if (finded_node == nullptr) {
            throw std::out_of_range("Incorrect input, key is not exist");
        }
        map<Key, T>::iterator it(*finded_node, *this);
        return (*it).second;
    }

    template <typename Key, typename T>
    typename map<Key, T>::mapped_type& map<Key, T>::operator[](const key_type& k) {
        map<Key, T>::iterator it;
        mapped_type a;
        std::pair<s21::map<Key, T>::iterator, bool> pair = this->insert(k, a);
        it = pair.first;
        return (*it).second;
    }

    template <typename Key, typename T>
    typename map<Key, T>::iterator map<Key, T>::begin() {
        typename Binary_tree<std::pair<Key, T> >::Tree_node* left_elem = nullptr;
        if (this->root != nullptr) {
            left_elem = this->root;
            while (left_elem->left != nullptr) {
                left_elem = left_elem->left;
            }
        } else {
            left_elem = this->hide_node;
        }
        iterator it(*left_elem, *(this));
        return it;
    }

    template <typename Key, typename T>
    typename map<Key, T>::iterator map<Key, T>::end() {
        iterator it(*this->hide_node, *(this));
        return it;
    }

    template <typename Key, typename T>
    std::pair<typename map<Key, T>::iterator, bool> map<Key, T>::insert(const value_type& value) {
        map<Key, T>::iterator it;
        bool value_exist = false;
        if (this->root == nullptr) {
            bin_tree_node* temp = new bin_tree_node();
            temp->Tree(value, 0, nullptr, nullptr);
            this->root = temp;
            temp->set_color(1);
            temp->parent = nullptr;
            this->count_of_elem++;
            it = map<Key, T>::iterator(*temp, *this);
        } else {
            bin_tree_node* checking_node = this->root;
            bin_tree_node* possible_parent = nullptr;
            while (checking_node != nullptr && !value_exist) {
                possible_parent = checking_node;
                if (checking_node->data.first < value.first) {
                    checking_node = checking_node->right;
                } else if (checking_node->data.first > value.first) {
                    checking_node = checking_node->left;
                } else {
                    value_exist = true;
                    it = map<Key, T>::iterator(*checking_node, *this);
                }
            }
            if (!value_exist) {
                bin_tree_node* temp = new bin_tree_node();
                temp->Tree(value, 0, nullptr, nullptr);
                temp->parent = possible_parent;
                if (possible_parent->data.first < temp->data.first) {
                    possible_parent->right = temp;
                } else {
                    possible_parent->left = temp;
                }
                this->fix_after_insert(temp);
                this->count_of_elem++;
                it = map<Key, T>::iterator(*temp, *this);
            }
        }
        return std::pair<map<Key, T>::iterator, bool> (it, !value_exist);
    }

    template <typename Key, typename T>
    std::pair<typename map<Key, T>::iterator, bool> map<Key, T>::insert(const Key& key, const T& obj) {
        return this->insert(std::pair<const key_type, mapped_type> (key, obj));
    }

    template <typename Key, typename T>
    std::pair<typename map<Key, T>::iterator, bool> map<Key, T>::insert_or_assign(const Key& key,
                                                                                  const T& obj) {
        std::pair<s21::map<int, int>::iterator, bool> k = this->insert(key, obj);
        if (k.second == false) {
            (*k.first).second = obj;
        }
        return k;
    }

    template <typename Key, typename T>
    void map<Key, T>::erase(iterator pos) {
        if (pos != this->end()) {
            this->delete_without_find(pos._data);
        }
    }

    template <typename Key, typename T>
    void map<Key, T>::swap(map& other) {
        map<Key, T> intermediate;
        intermediate.root = this->root;
        intermediate.count_of_elem = this->count_of_elem;
        this->root = other.root;
        this->count_of_elem = other.count_of_elem;
        other.root = intermediate.root;
        other.count_of_elem = intermediate.count_of_elem;
        intermediate.root = nullptr;
        intermediate.count_of_elem = 0;
    }

    template <typename Key, typename T>
    void map<Key, T>::merge(map &other) {
        for (map<Key, T>::iterator it_other = other.begin(); it_other != other.end(); ) {
            if ((this->insert(*it_other)).second) {
                map<Key, T>::iterator it_for_delete = it_other;
                ++it_other;
                other.erase(it_for_delete);
            } else {
                ++it_other;
            }
        }
    }

    template <typename Key, typename T>
    void map<Key, T>::clear() {
        this->delete_tree(this->root);
        this->root = nullptr;
        this->count_of_elem = 0;
    }

    template <typename Key, typename T>
    bool map<Key, T>::contains(const Key& key) {
        bool res = true;
        if (this->find_elem(key) == nullptr) {
            res = false;
        }
        return res;
    }

    template <typename Key, typename T>
    template <typename... Args>
    std::pair<typename map<Key, T>::iterator, bool> map<Key, T>::emplace(Args&&... args) {
        map<Key, T> temp_args_map{args...};
        map<Key, T>::iterator it = temp_args_map.begin();
        std::pair<typename map<Key, T>::iterator, bool> res;
        res.second = false;
        while (it != temp_args_map.end()) {
            res = (this->insert(*it));
            ++it;
        }
        temp_args_map.clear();
        return res;
    }

    template <typename Key, typename T>
    typename map<Key, T>::bin_tree_node* map<Key, T>::find_elem(const key_type& k) {
        bin_tree_node* elem = nullptr;
        bin_tree_node* checking_node = this->root;
        while (checking_node != nullptr && elem == nullptr) {
            if (checking_node->data.first < k) {
                checking_node = checking_node->right;
            } else if (checking_node->data.first > k) {
                checking_node = checking_node->left;
            } else {
                elem = checking_node;
            }
        }
        return elem;
    }
}  //  namespace s21
