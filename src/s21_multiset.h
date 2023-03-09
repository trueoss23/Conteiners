#ifndef SRC_S21_MULTISET_H_
#define SRC_S21_MULTISET_H_

#include <vector>
#include "s21_set.cpp"

namespace s21 {
template <class T>
class Multiset : public Set<T>::Set {
    using value_type = T;
    using Key = T;
    using size_type = size_t;

 public:
    /* --БЛОК КОНСТРУКТОРОВ И ДЕСТРУКТОРОВ-- */
    Multiset():Set<T>::Set() {}
    explicit Multiset(value_type key):Set<T>::Set(key) {}
    Multiset(std::initializer_list<value_type> const &items);
    Multiset(const Multiset &ms);  //  COPY
    ~Multiset() {}
    Multiset<T>& operator=(Multiset &&ms);  //  MOVE
    Multiset<T>& operator=(const Multiset &ms);  //  COPY
    void copy_set_m(Multiset<T> * res, typename Set<T>::Tree_node * temp);
    /* ----------------------------------------------- */
    using iterator = typename Set<T>::SetIterator;
    /* ----------------------------------------------- */


    /* --БЛОК РАБОТЫ С МУЛЬТИМНОЖЕСТВОМ-- */
    void insert_(value_type value);
    iterator insert(const value_type& value);
    void merge(Multiset<T>& other);
    /* ----------------------------------------------- */

    /* --БЛОК ПРОСМОТРА МУЛЬТИМНОЖЕСТВА-- */
    size_type count(const Key& key);
    iterator find(const Key& key);
    std::pair<iterator, iterator> equal_range(const T& key);
    iterator lower_bound(const Key& key);
    iterator upper_bound(const Key& key);
    template<typename ...Args>
    std::vector<std::pair<iterator, bool>> emplace(Args&&... args);
    /* ----------------------------------------------- */
};
}  //  namespace s21
#endif  //  SRC_S21_MULTISET_H_
