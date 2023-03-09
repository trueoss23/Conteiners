#include <gtest/gtest.h>
#include "s21_stack.cpp"
#include <stack>

template <typename T>
void compare_stack(s21::Stack<T>& s21_stack, std::stack<T>& std_stack) {
    ASSERT_EQ(s21_stack.size(), std_stack.size());
    ASSERT_EQ(s21_stack.empty(), std_stack.empty());
    while (!(s21_stack.empty()) && !(std_stack.empty())) {
        ASSERT_EQ(s21_stack.top(), std_stack.top());
        s21_stack.pop();
        std_stack.pop();
    }
}

TEST(stack_create_and_remove_suit, initialazer_constructor_and_default) {
    s21::Stack<int> a({1, 2, 3, 4, -9 , 0});
    std::stack<int> b({1, 2, 3, 4, -9 , 0});
    compare_stack(a, b);


    s21::Stack<double> a1{1., 2., 3., 4., -9. , 0.};
    std::stack<double> b1;
    b1.push(1.); b1.push(2.); b1.push(3.); b1.push(4.); b1.push(-9.); b1.push(0.);
    compare_stack(a1, b1);

    s21::Stack<std::string> a2;
    std::stack<std::string> b2;
    a2.push("afag");
    b2.push("afag");
    compare_stack(a2, b2);

    a2.push("afag");
    b2.push("afag");
    a2.pop();
    b2.pop();
    compare_stack(a2, b2);
}

TEST(stack_create_and_remove_suit, copy_and_move_constructor) {
    s21::Stack<int> a{1, 2, 3, 4, -9 , 0};
    std::stack<int> b;
    b.push(1); b.push(2); b.push(3); b.push(4); b.push(-9); b.push(0);
    s21::Stack<int> c(a);
    compare_stack(c, b);

    s21::Stack<double> a1{1, 2, 3, 4, -9 , 0};
    std::stack<double> b1;
    b1.push(1); b1.push(2); b1.push(3); b1.push(4); b1.push(-9); b1.push(0);
    s21::Stack<double> c1;
    c1 = (s21::Stack<double>&&) a1;
    compare_stack(c1, b1);
}

TEST(stack_create_and_remove_suit, swap) {
    s21::Stack<int> a(1000);
    std::stack<int> b({0});
    s21::Stack<int> c(0);
    a.swap(c);
    compare_stack(a, b);

    s21::Stack<bool> a1(1);
    std::stack<bool> b1;
    b1.push(0);
    s21::Stack<bool> c1;
    c1.push(0);
    a1.swap(c1);
    compare_stack(a1, b1);
}

TEST(stack_create_and_remove_suit, equal) {
    s21::Stack<bool> a1{1};
    std::stack<bool> b1;
    b1.push(0);
    s21::Stack<bool> c1;
    c1.push(0);
    a1 = (s21::Stack<bool>&&)c1;
    compare_stack(a1, b1);
}
