#ifndef SRC_S21_MAP_H_
#define SRC_S21_MAP_H_

#include "tree.h"

namespace s21 {
template <typename Key, typename T>
class map : protected Binary_tree<std::pair<Key, T> >::Binary_tree {
 public:
    using key_type = Key;
    using mapped_type = T;
    using value_type = std::pair<const key_type, mapped_type>;
    using reference = value_type &;
    using const_reference = const value_type &;
    using size_type = size_t;
    using bin_tree_node = typename Binary_tree<std::pair<Key, T> >::Binary_tree::Tree_node;

    class MapIterator;
    class MapConstIterator;

    using iterator = MapIterator;
    using const_iterator = MapConstIterator;

    map() {}
    map(std::initializer_list<value_type> const &items);
    map(const map &m) : Binary_tree<std::pair<Key, T> >::Binary_tree(m) {}
    map(map &&m) : Binary_tree<std::pair<Key, T> >::Binary_tree((map &&)m) {}
    ~map() {}
    map<Key, T> operator=(map &&m);

    mapped_type& at(const Key& key);
    mapped_type& operator[](const key_type& k);

    iterator begin();
    iterator end();

    bool empty() { return this->count_of_elem == 0 ? true : false; }
    size_type size() { return this->count_of_elem; }
    size_type max_size() { return std::allocator<bin_tree_node>().max_size(); }

    void clear();

    std::pair<iterator, bool> insert(const value_type& value);
    std::pair<iterator, bool> insert(const Key& key, const T& obj);
    std::pair<iterator, bool> insert_or_assign(const Key& key, const T& obj);

    void erase(iterator pos);
    void swap(map &other);
    void merge(map& other);

    bool contains(const Key& key);

    template<typename... Args>
    std::pair<iterator, bool> emplace(Args&&... args);

    class MapConstIterator;
    class MapIterator {
     friend void map<Key, T>::erase(iterator pos);
     private:
        bin_tree_node* _data;
        Binary_tree<std::pair<Key, T> >* _root;

        typename Binary_tree<std::pair<Key, T> >::Tree_node* find_most_left_elem();
        typename Binary_tree<std::pair<Key, T> >::Tree_node* find_most_right_elem();

     public:
        MapIterator() : _data(nullptr), _root(nullptr) {}
        MapIterator(bin_tree_node& node,
                    Binary_tree<std::pair<Key, T> >& root) : _data(&node), _root(&root) {}
        explicit MapIterator(map<Key, T> &m) : _data(m.root), _root(&m) {}
        ~MapIterator() { _data = nullptr; _root = nullptr; }
        operator MapConstIterator() { return MapConstIterator(_data); }

        value_type& operator*() { return (value_type&)(_data->data); }
        void operator++();
        void operator--();
        bool operator==(const MapIterator& other) { return this->_data == other._data ? 1 : 0; }
        bool operator!=(const MapIterator& other) { return this->_data != other._data ? 1 : 0; }
    };

    class MapConstIterator {
     friend void map<Key, T>::erase(iterator pos);
     private:
        bin_tree_node* _data;
        Binary_tree<std::pair<Key, T> >* _root;

        typename Binary_tree<std::pair<Key, T> >::Tree_node* find_most_left_elem();
        typename Binary_tree<std::pair<Key, T> >::Tree_node* find_most_right_elem();

     public:
        MapConstIterator() : _data(nullptr), _root(nullptr) {}
        MapConstIterator(bin_tree_node& node,
                    Binary_tree<std::pair<Key, T> >& root) : _data(&node), _root(&root) {}
        explicit MapConstIterator(map<Key, T> &m) : _data(m.root), _root(&m) {}
        ~MapConstIterator() { _data = nullptr; _root = nullptr; }
        operator MapIterator() { return MapIterator(_data); }

        const value_type& operator*() { return (value_type&)(_data->data); }
        void operator++();
        void operator--();
        bool operator==(const MapConstIterator& other) { return this->_data == other._data ? 1 : 0; }
        bool operator!=(const MapConstIterator& other) { return this->_data != other._data ? 1 : 0; }
    };

 private:
    bin_tree_node* find_elem(const key_type& k);
};
}  //  namespace s21

#endif  //  SRC_S21_MAP_H_
