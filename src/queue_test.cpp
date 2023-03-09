#include <gtest/gtest.h>
#include "s21_queue.cpp"

TEST(Member_functions_queue, member_functions) {
    s21::queue<int> a;
    ASSERT_EQ(a.size(), 0);

    s21::queue<int> b({1, 2});
    ASSERT_TRUE(b.front() == 1 && b.back() == 2);

    s21::queue<int> c(b);
    ASSERT_TRUE(b.front() == c.front() && b.back() == c.back());

    s21::queue<int> d((s21::queue<int>&&)c);
    ASSERT_TRUE(c.size() == 0 && d.front() == b.front() && d.back() == b.back());

    s21::queue<int> f;
    f = (s21::queue<int>&&)d;
    ASSERT_TRUE(d.front() == f.front() && d.back() == f.back());
}

TEST(Element_access_queue, front) {
    s21::queue<int> a({1, 2, 3});
    ASSERT_EQ(a.front(), 1);
}

TEST(Element_access_queue, back) {
    s21::queue<int> a({1, 2, 3});
    ASSERT_EQ(a.back(), 3);
}

TEST(Capacity_queue, empty) {
    s21::queue<int> a({1, 2, 3});
    ASSERT_FALSE(a.empty());

    s21::queue<int> b;
    ASSERT_TRUE(b.empty());
}

TEST(Capacity_queue, size) {
    s21::queue<int> a({1, 2, 3});
    ASSERT_EQ(a.size(), 3);

    s21::queue<int> b;
    ASSERT_EQ(b.size(), 0);
}

TEST(Modifiers_queue, push) {
    s21::queue<int> a({1, 2, 3});
    a.push(4);
    ASSERT_EQ(a.back(), 4);

    s21::queue<int> b;
    b.push(0);
    ASSERT_EQ(b.back(), 0);
}

TEST(Modifiers_queue, pop) {
    s21::queue<int> a({1, 2, 3});
    a.pop();
    ASSERT_EQ(a.front(), 2);
}

TEST(Modifiers_queue, swap) {
    s21::queue<int> a({1, 2});
    s21::queue<int> b({3, 4});
    a.swap(b);
    ASSERT_TRUE(a.front() == 3 && a.back() == 4 && b.front() == 1 && b.back() == 2);

    s21::queue<int> c;
    c.swap(b);
    ASSERT_TRUE(b.size() == 0 && c.front() == 1 && c.back() == 2);
}

TEST(Emplace_queue, emplace_back) {
    s21::queue<int> a({1, 2});
    a.emplace_back(3);
    ASSERT_EQ(a.back(), 3);

    s21::queue<int> b;
    b.emplace_back(1);
    ASSERT_EQ(b.back(), 1);
}
