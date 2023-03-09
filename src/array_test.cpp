#include <gtest/gtest.h>
#include "s21_array.cpp"

TEST(Member_functions_array, member_functions) {
    s21::array<int, 1> a;
    s21::array<int, 3> b({1, 2, 3});
    s21::array<int, 3> c(b);
    int k = 0;
    for (int i = 0; i < c.size(); i++) {
        if (c[i] == b[i]) {
            k++;
        }
    }
    ASSERT_TRUE(k == c.size());
    s21::array<int, 3> d((s21::array<int, 3>&&) b);
    k = 0;
    for (int i = 0; i < d.size(); i++) {
        if (d[i] == c[i]) {
            k++;
        }
    }
    ASSERT_TRUE(k == c.size()&& b.data() == nullptr);
    s21::array<int, 3> e;
    ASSERT_EQ(e.size(), 3);
    s21::array<int, 1> g;
    g = (s21::array<int, 1>&&) c;
    k = 0;
    for (int i = 0; i < g.size(); i++) {
        if (g[i] == c[i]) {
            k++;
        }
    }
    ASSERT_TRUE(g.size() == k);
}

TEST(Element_access_array, at) {
    s21::array<int, 3> a({1, 2, 3});
    ASSERT_EQ(a.at(0), 1);
    ASSERT_ANY_THROW(a.at(-1));
    ASSERT_ANY_THROW(a.at(3));
}

TEST(Element_access_array, indx) {
    s21::array<int, 3> a({1, 2, 3});
    ASSERT_EQ(a[0], 1);
}

TEST(Element_access_array, front) {
    s21::array<int, 3> a({1, 2, 3});
    ASSERT_EQ(a.front(), 1);
}

TEST(Element_access_array, back) {
    s21::array<int, 3> a({1, 2, 3});
    ASSERT_EQ(a.back(), 3);
}

TEST(Element_access_array, data) {
    s21::array<int, 3> a({1, 2, 3});
    s21::array<int, 3>::iterator a_it;
    a_it = a.data();
    int k = 0;
    for (int i = 0; i < a.size(); i++, a_it++) {
        if (*a_it == a[i]) {
            k++;
        }
    }
    ASSERT_TRUE(k == a.size());
}

TEST(Iterators_array, begin) {
    s21::array<int, 3> a({1, 2, 3});
    s21::array<int, 3>::iterator a_it = a.begin();
    ASSERT_TRUE(*a_it == a[0]);
}

TEST(Iterators_array, end) {
    s21::array<int, 3> a({1, 2, 3});
    s21::array<int, 3>::iterator a_it = a.end() - 1;
    ASSERT_TRUE(*a_it == a[2]);
}

TEST(Capacity_array, empty) {
    s21::array<int, 3> a({1, 2, 3});
    s21::array<int, 0> b;
    ASSERT_TRUE(b.empty());
    ASSERT_FALSE(a.empty());
}

TEST(Capacity_array, size) {
    s21::array<int, 3> a({1, 2, 3});
    s21::array<int, 0> b;
    ASSERT_EQ(a.size(), 3);
    ASSERT_EQ(b.size(), 0);
}

TEST(Capacity_array, max_size) {
    s21::array<int, 3> a({1, 2, 3});
    s21::array<int, 0> b;
    ASSERT_EQ(a.max_size(), 3);
    ASSERT_EQ(b.max_size(), 0);
}

TEST(Modifiers_array, swap) {
    s21::array<int, 3> a({1, 2, 3});
    s21::array<int, 3> b({3, 2, 1});
    a.swap(b);
    int k = 0;
    for (int i = 0; i < a.size(); i++) {
        if (i + 1 == b[i] && a.size() - i == a[i]) {
            k++;
        }
    }
    ASSERT_TRUE(k == a.size());
}

TEST(Modifiers_array, fill) {
    s21::array<int, 3> a({1, 2, 3});
    a.fill(4);
    int k = 0;
    for (int i = 0; i < a.size(); i++) {
        if (a[i] == 4) {
            k++;
        }
    }
    ASSERT_TRUE(k == a.size());
}
