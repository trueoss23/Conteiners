#include <gtest/gtest.h>
#include "s21_vector.cpp"

TEST(Member_functions_vector, member_functions) {
    s21::Vector<int> a;
    s21::Vector<int> b({1, 2, 3});
    s21::Vector<int> c(b);
    int k = 0;
    for (int i = 0; i < c.size(); i++) {
        if (c[i] == b[i]) {
            k++;
        }
    }
    ASSERT_TRUE(k == c.size());
    s21::Vector<int> d((s21::Vector<int>&&) b);
    k = 0;
    for (int i = 0; i < d.size(); i++) {
        if (d[i] == c[i]) {
            k++;
        }
    }
    ASSERT_TRUE(k == c.size() && b.empty());
    s21::Vector<int> e(3);
    ASSERT_EQ(e.size(), 3);
    ASSERT_ANY_THROW(s21::Vector<int> f(-1));
    s21::Vector<int> g;
    g = (s21::Vector<int>&&) c;
    k = 0;
    for (int i = 0; i < g.size(); i++) {
        if (g[i] == c[i]) {
            k++;
        }
    }
    ASSERT_TRUE(g.size() == k);
}

TEST(Element_access_vector, at) {
    s21::Vector<int> a({1, 2, 3});
    ASSERT_EQ(a.at(0), 1);
    ASSERT_ANY_THROW(a.at(-1));
    ASSERT_ANY_THROW(a.at(3));
    s21::Vector<int> b;
    ASSERT_ANY_THROW(b.at(0));
}

TEST(Element_access_vector, indx) {
    s21::Vector<int> a({1, 2, 3});
    ASSERT_EQ(a[0], 1);
}

TEST(Element_access_vector, front) {
    s21::Vector<int> a({1, 2, 3});
    ASSERT_EQ(a.front(), 1);
    s21::Vector<int> b;
    ASSERT_ANY_THROW(b.front());
}

TEST(Element_access_vector, back) {
    s21::Vector<int> a({1, 2, 3});
    ASSERT_EQ(a.back(), 3);
    s21::Vector<int> b;
    ASSERT_ANY_THROW(b.back());
}

TEST(Element_access_vector, data) {
    s21::Vector<int> a({1, 2, 3});
    s21::Vector<int>::iterator a_it;
    a_it = a.data();
    int k = 0;
    for (int i = 0; i < a.size(); i++, a_it++) {
        if (*a_it == a[i]) {
            k++;
        }
    }
    ASSERT_TRUE(k == a.size());
}

TEST(Iterators_vector, begin) {
    s21::Vector<int> a({1, 2, 3});
    s21::Vector<int>::iterator a_it = a.begin();
    ASSERT_TRUE(*a_it == a[0]);
}

TEST(Iterators_vector, end) {
    s21::Vector<int> a({1, 2, 3});
    s21::Vector<int>::iterator a_it = a.end() - 1;
    ASSERT_TRUE(*a_it == a[2]);
}

TEST(Capacity_vector, empty) {
    s21::Vector<int> a({1, 2, 3});
    s21::Vector<int> b;
    ASSERT_TRUE(b.empty());
    ASSERT_FALSE(a.empty());
}

TEST(Capacity_vector, size) {
    s21::Vector<int> a({1, 2, 3});
    s21::Vector<int> b;
    ASSERT_EQ(a.size(), 3);
    ASSERT_EQ(b.size(), 0);
}

TEST(Capacity_vector, max_size) {
    s21::Vector<int> a({1, 2, 3});
    s21::Vector<double> b;
    ASSERT_EQ(a.max_size(), 1073741823);
    ASSERT_EQ(b.max_size(), 536870911);
}

TEST(Capacity_vector, reserve) {
    s21::Vector<int> a({1, 2, 3});
    s21::Vector<int> b(a);
    a.reserve(4);
    int k = 0;
    for (int i = 0; i < a.size(); i++) {
        if (a[i] == b[i]) {
            k++;
        }
    }
    ASSERT_TRUE(k == a.size());
    ASSERT_ANY_THROW(a.reserve(-1));
    ASSERT_ANY_THROW(a.reserve(a.max_size() + 1));
}

TEST(Capacity_vector, capacity) {
    s21::Vector<int> a({1, 2, 3});
    s21::Vector<int> b;
    ASSERT_EQ(a.capacity(), 3);
    ASSERT_EQ(b.capacity(), 1);
    a.reserve(10);
    ASSERT_EQ(a.capacity(), 10);
}

TEST(Capacity_vector, shrink_to_fit) {
    s21::Vector<int> a({1, 2, 3});
    a.reserve(10);
    a.shrink_to_fit();
    ASSERT_EQ(a.capacity(), 3);
    s21::Vector<int> b;
    b.shrink_to_fit();
    ASSERT_EQ(b.capacity(), 0);
}

TEST(Modifiers_vector, clear) {
    s21::Vector<int> a({1, 2, 3});
    a.clear();
    ASSERT_EQ(a.size(), 0);
    s21::Vector<int> b;
    b.clear();
    ASSERT_EQ(b.size(), 0);
}

TEST(Modifiers_vector, insert) {
    s21::Vector<int> a({1, 2, 3});
    s21::Vector<int>::iterator a_it;
    a.insert(a.end(), 4);
    int k = 0;
    for (int i = 0; i < a.size(); i++) {
        if (i + 1 == a[i]) {
            k++;
        }
    }
    ASSERT_TRUE(k == a.size());

    s21::Vector<int> b({1, 8, 2, 3, 4});
    a.insert(a.begin() + 1, 8);
    k = 0;
    for (int i = 0; i < a.size(); i++) {
        if (b[i] == a[i]) {
            k++;
        }
    }
    ASSERT_TRUE(k == a.size());

    s21::Vector<int> c({1});
    c.insert(c.end(), 2);
    k = 0;
    for (int i = 0; i < c.size(); i++) {
        if (i + 1 == c[i]) {
            k++;
        }
    }
    ASSERT_TRUE(k == c.size());

    s21::Vector<int> d;
    d.insert(d.begin(), 1);
    k = 0;
    for (int i = 0; i < d.size(); i++) {
        if (i + 1 == d[i]) {
            k++;
        }
    }
    ASSERT_TRUE(k == d.size());
}

TEST(Modifiers_vector, erase) {
    s21::Vector<int> a({1, 2, 3});
    a.erase(a.end() - 1);
    int k = 0;
    for (int i = 0; i < a.size(); i++) {
        if (i + 1 == a[i]) {
            k++;
        }
    }
    ASSERT_TRUE(k == a.size());

    a.erase(a.begin());
    ASSERT_EQ(a[0], 2);
}

TEST(Modifiers_vector, push_back) {
    s21::Vector<int> a({1, 2, 3});
    a.push_back(4);
    ASSERT_EQ(a[3], 4);

    s21::Vector<int> b;
    b.push_back(17);
    ASSERT_EQ(b[0], 17);
}

TEST(Modifiers_vector, pop_back) {
    s21::Vector<int> a({1, 2, 3});
    a.pop_back();
    ASSERT_EQ(*(a.end() - 1), 2);

    s21::Vector<int> b;
    b.pop_back();
}

TEST(Modifiers_vector, swap) {
    s21::Vector<int> a({1, 2, 3});
    s21::Vector<int> b({3, 2, 1});
    a.swap(b);
    int k = 0;
    for (int i = 0; i < a.size(); i++) {
        if (i + 1 == b[i] && a.size() - i == a[i]) {
            k++;
        }
    }
    ASSERT_TRUE(k == a.size());

    s21::Vector<int> c({1});
    s21::Vector<int> d({1, 2, 3});
    c.swap(d);
    k = 0;
    for (int i = 0; i < c.size(); i++) {
        if (c[i] == b[i]) {
            k++;
        }
    }
    ASSERT_TRUE(k == c.size() && d.size() == 1 && d[0] == 1);

    s21::Vector<int> e;
    s21::Vector<int> f({1, 2, 3});
    e.swap(f);
    ASSERT_TRUE(f.size() == 0 && e.size() == 3);
}

TEST(Emplaces_vector, emplace) {
    s21::Vector<int> a({1, 2, 3});
    s21::Vector<int> b({5, 6, 1, 2, 3});
    s21::Vector<int>::iterator iter = a.emplace(a.begin(), 5, 6);
    int k = 0;
    for (int i = 0; i < a.size(); i++) {
        if (a[i] == b[i]) {
            k++;
        }
    }
    ASSERT_TRUE(k == a.size() && (*iter) == 5);

    s21::Vector<int> c({5, 6, 1, 2, 3, 4});
    iter = a.emplace(a.end(), 4);
    k = 0;
    for (int i = 0; i < a.size(); i++) {
        if (a[i] == c[i]) {
            k++;
        }
    }
    ASSERT_TRUE(k == a.size() && (*iter) == 4);

    s21::Vector<int> d({5, 6, 1, 7, 8, 9, 2, 3, 4});
    iter = a.emplace(a.begin() + 3, 7, 8, 9);
    k = 0;
    for (int i = 0; i < a.size(); i++) {
        if (a[i] == d[i]) {
            k++;
        }
    }
    ASSERT_TRUE(k == a.size() && (*iter) == 7);
}

TEST(Emplaces_vector, emplace_back) {
    s21::Vector<int> a({1, 2, 3});
    s21::Vector<int> b({1, 2, 3, 4, 5});
    int k = 0;
    for (int i = 0; i < a.size(); i++) {
        if (a[i] == b[i]) {
            k++;
        }
    }
    ASSERT_TRUE(k == a.size());
}

