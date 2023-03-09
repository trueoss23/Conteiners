#include <gtest/gtest.h>
#include "s21_multiset.cpp"

template <typename T>
void compare(typename s21::Multiset<T> s21_set_m, typename std::multiset<T> std_set_m) {
    ASSERT_EQ(s21_set_m.size(), std_set_m.size());
    ASSERT_EQ(s21_set_m.empty(), std_set_m.empty());
        typename s21::Multiset<T>::iterator it_21 = s21_set_m.begin();
        typename std::multiset<T>::iterator it_std = std_set_m.begin();
        while (it_21 != s21_set_m.end()) {
            ASSERT_EQ(*it_21, *it_std);
            ++it_21;
            ++it_std;
        }
}

TEST(multiset_create_and_remove_suit, defolt_constructor) {
    s21::Multiset<int> s21_set_m;
    std::multiset<int> std_set_m;
    compare(s21_set_m, std_set_m);

    s21::Multiset<std::string> s21_set_m1;
    std::multiset<std::string> std_set_m1;
    compare(s21_set_m1, std_set_m1);

    s21::Multiset<bool> s21_set_m2;
    std::multiset<bool> std_set_m2;
    compare(s21_set_m2, std_set_m2);
}

TEST(multiset_create_and_remove_suit, initialaizer_constructor) {
    s21::Multiset<int> s21_set{1, 2, 40, 500};
    std::multiset<int> std_set{1, 2, 40, 500};
    compare(s21_set, std_set);

    s21::Multiset<double> s21_set1{1.2, 2.0, 40.0, 500.7};
    std::multiset<double> std_set1{1.2, 2.0, 40.0, 500.7};
    compare(s21_set1, std_set1);

    s21::Multiset<bool> s21_set2{1, 0, 1, 0};
    std::multiset<bool> std_set2{1, 0, 1, 0};
    compare(s21_set2, std_set2);
}

TEST(multiset_create_and_remove_suit, copy_and_move_constructor) {
    s21::Multiset<int> s21_set_a{1, 2, 40, 500};
    s21::Multiset<int> s21_set_b(s21_set_a);
    std::multiset<int> std_set{1, 2, 40, 500};
    compare(s21_set_b, std_set);

    s21::Multiset<int> s21_set_a1{1, 2, 40, 500};
    s21::Multiset<int> s21_set_b1((s21::Multiset<int>&&)s21_set_a1);
    std::multiset<int> std_set1{1, 2, 40, 500};
    compare(s21_set_b1, std_set1);

    s21::Multiset<bool> s21_set_a2{1, 0, 0};
    std::multiset<bool> std_set2{1, 0, 0};
    s21::Multiset<bool> s21_set_b2;
    s21_set_b2 = (s21::Multiset<bool>&&)s21_set_a2;
    compare(s21_set_b2, std_set2);
}

TEST(multiset_create_and_remove_suit, equal) {
    s21::Multiset<double> s21_set_a{1., 2.5, 2.5, 2.5, 40., 500.};
    s21::Multiset<double> s21_set_b;
    s21_set_b = (s21::Multiset<double>&&)s21_set_a;
    std::multiset<double> std_set{1., 2.5, 2.5, 2.5, 40., 500.};
    compare(s21_set_b, std_set);
}

TEST(multiset_create_and_remove_suit, iterators) {
    s21::Multiset<int> s21_set1;
    s21::Multiset<int> s21_set2;
    std::multiset<int> std_set;
    for (int i  = 0; i < 1000; i++) {
        s21_set1.insert(i);
        s21_set2.insert(i);
        std_set.insert(i);
    }
    typename s21::Multiset<int>::iterator it1 = s21_set1.end();
    typename s21::Multiset<int>::iterator it2 = s21_set2.end();

    --it1;
    --it2;
    for (int i  = 0; i < 1000; i++) {
        ASSERT_TRUE(*it1 == *it2);
        --it1;
        --it2;
    }
}

TEST(multiset_create_and_remove_suit, erase) {
    s21::Multiset<int> s21_set{-1, 2, 40, 500};
    std::multiset<int> std_set{2, 40, 500};
    typename s21::Multiset<int>::iterator it = s21_set.begin();
    s21_set.erase(it);
    compare(s21_set, std_set);

    s21::Multiset<int> s21_set1;
    std::multiset<int> std_set1;
    typename s21::Multiset<int>::iterator it1 = s21_set1.begin();
    s21_set1.erase(it1);
    compare(s21_set1, std_set1);

    s21::Multiset<int> s21_set2{-1, 2, 40, 500};
    std::multiset<int> std_set2{-1, 2, 40, 500};
    typename s21::Multiset<int>::iterator it2 = s21_set2.begin();
    typename std::set<int>::iterator it3 = std_set2.begin();
    ++it2;
    ++it2;
    ++it3;
    ++it3;
    s21_set2.erase(it2);
    std_set2.erase(it3);
    compare(s21_set2, std_set2);

    s21::Multiset<double> s21_set3;
    std::multiset<double> std_set3;
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

    s21::Multiset<std::string> s21_set4;
    std::multiset<std::string> std_set4;
    for (double k = 0.; k < 150.; k += 0.1) {
        s21_set4.insert("12");
        std_set4.insert("12");
    }
    for (double k = 150.; k > 80.; k -= 0.1) {
        auto i = s21_set4.end();
        auto j = std_set4.end();
        --i;
        --j;
        s21_set4.erase(i);
        std_set4.erase(j);
    }
    compare(s21_set4, std_set4);


    s21::Multiset<int> s21_set5{-1, -10, 2};
    std::multiset<int> std_set5;
    typename s21::Multiset<int>::iterator it5 = s21_set5.begin();
    ++it5;
    s21_set5.erase(it5);
    it5 = s21_set5.begin();
    s21_set5.erase(it5);
    it5 = s21_set5.begin();
    s21_set5.erase(it5);
    compare(s21_set5, std_set5);

    s21::Multiset<int> s21_set6{-1, -10, 10, 20};
    std::multiset<int> std_set6;
    typename s21::Multiset<int>::iterator it6 = s21_set6.begin();
    ++it6;
    s21_set6.erase(it6);
    it6 = s21_set6.begin();
    ++it6;
    s21_set6.erase(it6);
    it6 = s21_set6.begin();
    s21_set6.erase(it6);
    it6 = s21_set6.begin();
    s21_set6.erase(it6);
    compare(s21_set6, std_set6);
}

TEST(multiset_create_and_remove_suit, swap) {
    s21::Multiset<int> s21_set_a{1, 2, 40, 500};
    s21::Multiset<int> s21_set_b;
    s21_set_a.swap(s21_set_b);
    std::multiset<int> std_set{1, 2, 40, 500};
    compare(s21_set_b, std_set);

    s21::Multiset<bool> s21_set_a1{1, 0, 0, 0};
    s21::Multiset<bool> s21_set_b1(1);
    s21_set_b1.swap(s21_set_a1);
    std::multiset<bool> std_set1{1, 0, 0, 0};
    compare(s21_set_b1, std_set1);

    s21::Multiset<bool> s21_set_a2{1, 0, 0};
    std::multiset<bool> std_set2;
    s21::Multiset<bool> s21_set_b2;
    s21_set_a2 = (s21::Multiset<bool>&&)s21_set_b2;
    compare(s21_set_a2, std_set2);
}

TEST(multiset_create_and_remove_suit, merge) {
    s21::Multiset<int> s21_set_a{1, 3, 5, 7};
    s21::Multiset<int> s21_set_b{0, 2, 4, 6};

    s21_set_a.merge(s21_set_b);
    std::multiset<int> std_set{0, 1, 2, 3, 4, 5, 6, 7};
    compare(s21_set_a, std_set);

    s21::Multiset<bool> s21_set_a1{1};
    s21::Multiset<bool> s21_set_b1{0, 0, 0};
    s21_set_b1.merge(s21_set_a1);
    std::multiset<bool> std_set1{0, 0, 0, 1};
    compare(s21_set_b1, std_set1);

    s21::Multiset<std::string> s21_set_a2{"1", "0"};
    std::multiset<std::string> std_set2{"1", "0", "pwea"};
    s21::Multiset<std::string> s21_set_b2{"pwea"};
    s21_set_a2.merge(s21_set_b2);
    compare(s21_set_a2, std_set2);
}
