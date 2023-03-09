#include <gtest/gtest.h>
#include "s21_set.cpp"
#include <set>

template <typename T>
void compare(typename s21::Set<T> s21_set, typename std::set<T> std_set) {
    ASSERT_EQ(s21_set.size(), std_set.size());
    ASSERT_EQ(s21_set.empty(), std_set.empty());
        typename s21::Set<T>::iterator it_21 = s21_set.begin();
        typename std::set<T>::iterator it_std = std_set.begin();
        while (it_21 != s21_set.end()) {
            ASSERT_EQ(*it_21, *it_std);
            ++it_21;
            ++it_std;
        }
}

TEST(set_create_and_remove_suit, defolt_constructor) {
    s21::Set<int> s21_set;
    std::set<int> std_set;
    compare(s21_set, std_set);
}

TEST(set_create_and_remove_suit, initialaizer_constructor) {
    s21::Set<int> s21_set{1, 2, 40, 500};
    std::set<int> std_set{1, 2, 40, 500};
    compare(s21_set, std_set);

    s21::Set<double> s21_set1{1.2, 2.0, 40.0, 500.7};
    std::set<double> std_set1{1.2, 2.0, 40.0, 500.7};
    compare(s21_set1, std_set1);

    s21::Set<bool> s21_set2{1, 0, 0};
    std::set<bool> std_set2{1, 0, 1};
    compare(s21_set2, std_set2);
}

TEST(set_create_and_remove_suit, copy_and_move_constructor) {
    s21::Set<int> s21_set_a{1, 2, 40, 500};
    s21::Set<int> s21_set_b(s21_set_a);
    std::set<int> std_set{1, 2, 40, 500};
    compare(s21_set_b, std_set);

    s21::Set<int> s21_set_a1{1, 2, 40, 500};
    s21::Set<int> s21_set_b1((s21::Set<int>&&)s21_set_a1);
    std::set<int> std_set1{1, 2, 40, 500};
    compare(s21_set_b1, std_set1);

    s21::Set<bool> s21_set_a2{1, 0, 0};
    std::set<bool> std_set2;
    s21::Set<bool> s21_set_b2;
    s21_set_a2 = (s21::Set<bool>&&)s21_set_b2;
    compare(s21_set_a2, std_set2);
}

TEST(set_create_and_remove_suit, equal) {
    s21::Set<int> s21_set_a{500, 1, 2, 40, 500};
    s21::Set<int> s21_set_b;
    s21_set_b = (s21::Set<int>&&)s21_set_a;
    std::set<int> std_set{500, 1, 2, 40, 500};
    compare(s21_set_b, std_set);
}

TEST(set_create_and_remove_suit, iterators) {
    s21::Set<int> s21_set1{-1, 2, 40, 500};
    s21::Set<int> s21_set2{-1, 6, 44, 500};
    typename s21::Set<int>::iterator it1 = s21_set1.end();
    typename s21::Set<int>::iterator it2 = s21_set2.end();
    --it1;
    --it2;
    ASSERT_TRUE(*it1 == *it2);
    --it1;
    --it2;
    ASSERT_FALSE(*it1 == *it2);

    s21::Set<int> s21_set{-11, -2};
    std::set<int> std_set{-11, -2};
    for (int i= 0; i < 100; i++) {
        s21_set.insert(i);
        std_set.insert(i);
    }
    for (int i = 37; i < 1003; i += 4) {
        s21_set.insert(i);
        std_set.insert(i);
    }
    compare(s21_set, std_set);
        for (int i = 0; i < 50; i += 3) {
            auto it = s21_set.end();
            auto it1 = std_set.end();
            --it;
            --it1;
        s21_set.erase(it);
        std_set.erase(it1);
    }
    compare(s21_set, std_set);
}

TEST(set_create_and_remove_suit, erase) {
    s21::Set<int> s21_set{-1, 2, 40, 500};
    std::set<int> std_set{2, 40, 500};
    typename s21::Set<int>::iterator it = s21_set.begin();
    s21_set.erase(it);
    compare(s21_set, std_set);

    s21::Set<int> s21_set1;
    std::set<int> std_set1;
    typename s21::Set<int>::iterator it1 = s21_set1.begin();
    s21_set1.erase(it1);
    compare(s21_set1, std_set1);

    s21::Set<int> s21_set2{-1, 2, 40, 500};
    std::set<int> std_set2{-1, 2, 40, 500};
    typename s21::Set<int>::iterator it2 = s21_set2.begin();
    typename std::set<int>::iterator it3 = std_set2.begin();
    ++it2;
    ++it2;
    ++it3;
    ++it3;
    s21_set2.erase(it2);
    std_set2.erase(it3);
    compare(s21_set2, std_set2);

    s21::Set<double> s21_set3;
    std::set<double> std_set3;
    for (double k = 0.; k < 150.; k += 0.1) {
        s21_set3.insert(k);
        std_set3.insert(k);
    }
    for (double k = 0.; k < 150.; k += 0.6) {
        auto i = s21_set3.begin();
        auto j = std_set3.begin();
        s21_set3.erase(i);
        std_set3.erase(j);
    }
    for (double k = 150.; k > 80.; k -= 0.1) {
        auto i = s21_set3.end();
        auto j = std_set3.end();
        --i;
        --j;
        s21_set3.erase(i);
        std_set3.erase(j);
    }
    compare(s21_set3, std_set3);
}

TEST(set_create_and_remove_suit, swap) {
    s21::Set<int> s21_set_a{1, 2, 40, 500};
    s21::Set<int> s21_set_b;
    s21_set_a.swap(s21_set_b);
    std::set<int> std_set{1, 2, 40, 500};
    compare(s21_set_b, std_set);

    s21::Set<bool> s21_set_a1{1, 1, 0, 0};
    s21::Set<bool> s21_set_b1(1);
    s21_set_b1.swap(s21_set_a1);
    std::set<bool> std_set1{1, 0, 0, 0};
    compare(s21_set_b1, std_set1);

    s21::Set<bool> s21_set_a2{1, 0, 0};
    std::set<bool> std_set2;
    s21::Set<bool> s21_set_b2;
    s21_set_a2 = (s21::Set<bool>&&)s21_set_b2;
    compare(s21_set_a2, std_set2);
}

TEST(set_create_and_remove_suit, merge) {
    s21::Set<int> s21_set_a{1, 3, 5, 7};
    s21::Set<int> s21_set_b{0, 2, 4, 6};

    s21_set_a.merge(s21_set_b);
    std::set<int> std_set{0, 1, 2, 3, 4, 5, 6, 7};
    compare(s21_set_a, std_set);

    s21::Set<bool> s21_set_a1{1};
    s21::Set<bool> s21_set_b1;
    s21_set_b1.merge(s21_set_a1);
    std::set<bool> std_set1{1};
    compare(s21_set_b1, std_set1);

    s21::Set<bool> s21_set_a2{0, 0};
    std::set<bool> std_set2{0};
    s21::Set<bool> s21_set_b2;
    s21_set_a2.merge(s21_set_b2);
    compare(s21_set_a2, std_set2);
}
