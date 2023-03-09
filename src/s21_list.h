#ifndef SRC_S21_LIST_H_
#define SRC_S21_LIST_H_

namespace s21 {
using size_type = size_t;
template <typename T>
class list {
    using value_type = T;
    using reference = T &;
    using const_reference = const T &;

 private:
        struct list_node {
            value_type _value;
            list_node *next;
            list_node *prev;
        };
        list_node *head;
        list_node *tail;
        size_type count_added_elem;

        void create_count_node();
        void delete_count_node();
        void free_list();
        list<value_type>* divide_list();

 public:
    class ListConstIterator;
    class ListIterator {
     private:
        list_node *data;

     public:
        ListIterator() : data(NULL) {}
        explicit ListIterator(list_node *node) : data(node) {}
        explicit ListIterator(list& node) : data(node.head) {}
        ListIterator(const ListIterator& other) : data(other.data) {}
        value_type& operator*() { return data->_value; }
        void operator++() { data = data->next; }
        void operator--() { data = data->prev; }
        bool operator==(const ListIterator& other) { return this->data == other.data ? 1 : 0; }
        bool operator!=(const ListIterator& other) { return this->data != other.data ? 1 : 0; }
        operator ListConstIterator() const { return ListConstIterator(data); }
        list_node* get_data() { return data; }
    };
    class ListConstIterator {
     private:
        list_node *data;

     public:
        ListConstIterator() : data(NULL) {}
        explicit ListConstIterator(list_node *node) : data(node) {}
        explicit ListConstIterator(list& node) : data(node.head) {}
        ListConstIterator(const ListConstIterator& other) : data(other.data) {}
        const value_type& operator*() { return data->_value; }
        void operator++() { data = data->next; }
        void operator--() { data = data->prev; }
        bool operator==(const ListConstIterator& other) { return this->data == other.data ? 1 : 0; }
        bool operator!=(const ListConstIterator& other) { return this->data != other.data ? 1 : 0; }
        operator ListIterator() const { return ListIterator(data); }
        list_node* get_data() { return data; }
    };

    using iterator = ListIterator;
    using const_iterator = ListConstIterator;
    list();
    explicit list(size_type n);
    list(std::initializer_list<value_type> const &items);
    list(const list &l);
    list(list &&l);
    ~list();
    list operator=(list &&l);

    const_reference front() { return this->head->_value; }
    const_reference back() { return this->tail->_value; }

    iterator begin() { return  s21::list<T>::iterator(this->head); }
    iterator end() { return  s21::list<T>::iterator(this->tail->next); }

    bool empty();
    size_type size();
    size_type max_size() { return std::allocator<s21::list<value_type>::list_node>().max_size(); }

    void clear();
    iterator insert(iterator pos, value_type value);
    void erase(iterator pos);
    void push_back(value_type value);
    void pop_back();
    void push_front(value_type value);
    void pop_front();
    void swap(list& other);
    void merge(list& other);
    void splice(const_iterator pos, list& other);
    void reverse();
    void unique();
    void sort();

    template<typename... Args>
    iterator emplace(const_iterator pos, Args&&... args);
    template<typename... Args>
    void emplace_back(Args&&... args);
    template<typename... Args>
    void emplace_front(Args&&... args);
};
};  //  namespace s21

#endif  //  SRC_S21_LIST_H_
