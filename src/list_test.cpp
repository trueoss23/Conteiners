#include <gtest/gtest.h>
#include "s21_list.cpp"
#include <list>
// #include <tuple>

template <typename T>
void compare_lists(s21::list<T>* s21_list, std::list<T>* std_list) {
    ASSERT_EQ(s21_list->size(), std_list->size());
    ASSERT_EQ(s21_list->empty(), std_list->empty());
    typename s21::list<T>::iterator s21_it(s21_list->begin());
    typename std::list<T>::iterator std_it(std_list->begin());
    for (s21_it = s21_list->begin(); s21_it != s21_list->end();) {
        ASSERT_EQ(*s21_it, *std_it);
        ++s21_it;
        ++std_it;
    }
    ASSERT_EQ(s21_list->front(), std_list->front());
    ASSERT_EQ(s21_list->back(), std_list->back());
}

TEST(list_create_and_remove_suit, defolt_constructor) {
    s21::list<int> s21_list;
    std::list<int> std_list;
    compare_lists(&s21_list, &std_list);
}

TEST(list_create_and_remove_suit, parameterized_constructor) {
    int list_size = 15;
    s21::list<double> s21_list(list_size);
    std::list<double> std_list(list_size);
    compare_lists(&s21_list, &std_list);
}

TEST(list_create_and_remove_suit, initializer_list_constructor) {
    s21::list<int> s21_list{5, 2, 6, 3, 7};
    std::list<int> std_list{5, 2, 6, 3, 7};
    compare_lists(&s21_list, &std_list);
}

TEST(list_create_and_remove_suit, copy_constructor) {
    s21::list<char> s21_first{'a', 'b', 'c', 'd', 'e'};
    std::list<char> std_first{'a', 'b', 'c', 'd', 'e'};
    s21::list<char> s21_list(s21_first);
    std::list<char> std_list(std_first);
    compare_lists(&s21_first, &std_first);
    compare_lists(&s21_list, &std_list);
}

TEST(list_create_and_remove_suit, move_constructor) {
    s21::list<bool> s21_first{1, 0, 0, 1, 1};
    std::list<bool> std_first{1, 0, 0, 1, 1};
    s21::list<bool> s21_list((s21::list<bool>&&)s21_first);
    std::list<bool> std_list((std::list<bool>&&)std_first);
    compare_lists(&s21_first, &std_first);
    compare_lists(&s21_list, &std_list);
}

TEST(list_operator_overload_suit, assignment_operator) {
    // int list_size = 5;
    s21::list<bool> s21_first{1, 0, 0, 1, 1};
    std::list<bool> std_first{1, 0, 0, 1, 1};
    s21::list<bool> s21_list(7);
    s21_list = (s21::list<bool>&&)s21_first;
    std::list<bool> std_list(7);
    std_list = (std::list<bool>&&)std_first;
    compare_lists(&s21_first, &std_first);
    compare_lists(&s21_list, &std_list);
}

TEST(list_access_method_suit, access_front) {
    s21::list<double> s21_list{5.2, 6.3, 7.4, 8.5};
    std::list<double> std_list{5.2, 6.3, 7.4, 8.5};
    ASSERT_EQ(s21_list.front(), std_list.front());
}

TEST(list_access_method_suit, access_back) {
    s21::list<double> s21_list{5.2, 6.3, 7.4, 8.5};
    std::list<double> std_list{5.2, 6.3, 7.4, 8.5};
    ASSERT_EQ(s21_list.back(), std_list.back());
}

TEST(list_access_method_suit, iterators) {
    s21::list<char> s21_list{'a', 'b', 'c', 'd', 'e'};
    std::list<char> std_list{'a', 'b', 'c', 'd', 'e'};
    s21::list<char>::iterator s21_it(s21_list.begin());
    std::list<char>::iterator std_it(std_list.begin());
    while (s21_it != s21_list.end()) {
    ASSERT_EQ(*s21_it, *std_it);
    ++s21_it;
    ++std_it;
    }
    ASSERT_EQ(std_it == std_list.end(), 1);
}

TEST(list_capacity_suit, empty_and_size_test) {
    s21::list<int> s21_list1;
    std::list<int> std_list1;
    ASSERT_EQ(s21_list1.size(), std_list1.size());
    ASSERT_EQ(s21_list1.empty(), std_list1.empty());

    s21::list<int> s21_list2(5);
    std::list<int> std_list2(5);
    ASSERT_EQ(s21_list2.size(), std_list2.size());
    ASSERT_EQ(s21_list2.empty(), std_list2.empty());

    s21::list<double> s21_list3{5.2, 6.3, 7.4, 8.5};
    std::list<double> std_list3{5.2, 6.3, 7.4, 8.5};
    ASSERT_EQ(s21_list3.size(), std_list3.size());
    ASSERT_EQ(s21_list3.empty(), std_list3.empty());
}

TEST(list_capacity_suit, max_size_test) {
    s21::list<int> s21_list{5, 2, 6, 3, 7};
    std::list<int> std_list{5, 2, 6, 3, 7};
    ASSERT_EQ(s21_list.max_size(), std_list.max_size());
}

TEST(list_modifers_suit, clear_test) {
    s21::list<int> s21_list1;
    std::list<int> std_list1;
    s21_list1.clear();
    std_list1.clear();
    compare_lists(&s21_list1, &std_list1);

    s21::list<int> s21_list2(5);
    std::list<int> std_list2(5);
    s21_list2.clear();
    std_list2.clear();
    compare_lists(&s21_list2, &std_list2);

    s21::list<double> s21_list3{5.2, 6.3, 7.4, 8.5};
    std::list<double> std_list3{5.2, 6.3, 7.4, 8.5};
    s21_list3.clear();
    std_list3.clear();
    compare_lists(&s21_list3, &std_list3);
}

TEST(list_modifers_suit, insert_test) {
    s21::list<int> s21_list1(1);
    std::list<int> std_list1(1);
    s21::list<int>::iterator s21_it(s21_list1.end());
    std::list<int>::iterator std_it(std_list1.end());
    s21_it = s21_list1.insert(s21_it, 12);
    std_it = std_list1.insert(std_it, 12);
    ASSERT_EQ(*s21_it, *std_it);
    compare_lists(&s21_list1, &std_list1);

    s21::list<int> s21_list2(1);
    std::list<int> std_list2(1);
    s21_it = s21_list2.insert(s21_list2.begin(), 12);
    std_it = std_list2.insert(std_list2.begin(), 12);
    ASSERT_EQ(*s21_it, *std_it);
    compare_lists(&s21_list2, &std_list2);

    s21::list<int> s21_list3;
    std::list<int> std_list3;
    s21_it = s21_list3.insert(s21_list3.begin(), 12);
    std_it = std_list3.insert(std_list3.begin(), 12);
    ASSERT_EQ(*s21_it, *std_it);
    compare_lists(&s21_list3, &std_list3);

    s21::list<int> s21_list4{12, 23, 34, 45, 56, 67, 78, 89, 90};
    std::list<int> std_list4{12, 23, 34, 45, 56, 67, 78, 89, 90};
    s21_it = s21_list4.begin();
    std_it = std_list4.begin();
    for (int i = 0; i < 5; i++) {
        ++s21_it;
        ++std_it;
    }
    s21_it = s21_list4.insert(s21_list4.begin(), 12);
    std_it = std_list4.insert(std_list4.begin(), 12);
    ASSERT_EQ(*s21_it, *std_it);
    compare_lists(&s21_list4, &std_list4);
}

TEST(list_modifers_suit, erase_test) {
    s21::list<int> s21_list1(1);
    std::list<int> std_list1(1);
    s21::list<int>::iterator s21_it(s21_list1.begin());
    std::list<int>::iterator std_it(std_list1.begin());
    s21_list1.erase(s21_it);
    std_list1.erase(std_it);
    compare_lists(&s21_list1, &std_list1);

    s21::list<int> s21_list2(2);
    std::list<int> std_list2(2);
    s21_it = s21_list2.end();
    std_it = std_list2.end();
    --s21_it;
    --std_it;
    s21_list2.erase(s21_it);
    std_list2.erase(std_it);
    compare_lists(&s21_list2, &std_list2);
}

TEST(list_modifers_suit, push_and_pop_back_test) {
    s21::list<int> s21_list1;
    std::list<int> std_list1;
    s21_list1.push_back(15);
    std_list1.push_back(15);
    compare_lists(&s21_list1, &std_list1);
    s21_list1.pop_back();
    std_list1.pop_back();
    compare_lists(&s21_list1, &std_list1);

    s21::list<double> s21_list2(10);
    std::list<double> std_list2(10);
    s21_list2.push_back(15.7);
    std_list2.push_back(15.7);
    compare_lists(&s21_list1, &std_list1);
    s21_list2.pop_back();
    std_list2.pop_back();
    compare_lists(&s21_list2, &std_list2);

    s21::list<char> s21_list3{'a', 'b', 'c', 'd', 'e'};
    std::list<char> std_list3{'a', 'b', 'c', 'd', 'e'};
    s21_list3.push_back('N');
    std_list3.push_back('N');
    compare_lists(&s21_list3, &std_list3);
    s21_list3.pop_back();
    std_list3.pop_back();
    compare_lists(&s21_list3, &std_list3);
}

TEST(list_modifers_suit, push_and_pop_from_test) {
    s21::list<int> s21_list1;
    std::list<int> std_list1;
    s21_list1.push_front(15);
    std_list1.push_front(15);
    compare_lists(&s21_list1, &std_list1);
    s21_list1.pop_front();
    std_list1.pop_front();
    compare_lists(&s21_list1, &std_list1);

    s21::list<double> s21_list2(10);
    std::list<double> std_list2(10);
    s21_list2.push_front(15.7);
    std_list2.push_front(15.7);
    compare_lists(&s21_list1, &std_list1);
    s21_list2.pop_front();
    std_list2.pop_front();
    compare_lists(&s21_list2, &std_list2);

    s21::list<char> s21_list3{'a', 'b', 'c', 'd', 'e'};
    std::list<char> std_list3{'a', 'b', 'c', 'd', 'e'};
    s21_list3.push_front('N');
    std_list3.push_front('N');
    compare_lists(&s21_list3, &std_list3);
    s21_list3.pop_front();
    std_list3.pop_front();
    compare_lists(&s21_list3, &std_list3);
}

TEST(list_modifers_suit, swap_test) {
    s21::list<int> s21_list1;
    std::list<int> std_list1;
    s21::list<int> s21_list2(10);
    std::list<int> std_list2(10);
    s21_list1.swap(s21_list2);
    std_list1.swap(std_list2);
    compare_lists(&s21_list1, &std_list1);
    compare_lists(&s21_list2, &std_list2);

    s21::list<char> s21_list3(10);
    std::list<char> std_list3(10);
    s21::list<char> s21_list4{'a', 'b', 'c', 'd', 'e'};
    std::list<char> std_list4{'a', 'b', 'c', 'd', 'e'};
    s21_list3.swap(s21_list4);
    std_list3.swap(std_list4);
    compare_lists(&s21_list3, &std_list3);
    compare_lists(&s21_list4, &std_list4);
}

TEST(list_modifers_suit, splice_test) {
    s21::list<int> s21_list1(1);
    std::list<int> std_list1(1);
    s21::list<int> s21_list2(10);
    std::list<int> std_list2(10);
    s21_list1.splice(s21_list1.begin(), s21_list2);
    std_list1.splice(std_list1.begin(), std_list2);
    compare_lists(&s21_list1, &std_list1);
    compare_lists(&s21_list2, &std_list2);

    s21::list<char> s21_list3(10);
    std::list<char> std_list3(10);
    s21::list<char> s21_list4{'a', 'b', 'c', 'd', 'e'};
    std::list<char> std_list4{'a', 'b', 'c', 'd', 'e'};
    s21::list<char>::const_iterator s21_it(s21_list3.begin());
    std::list<char>::const_iterator std_it(std_list3.begin());
    ++s21_it;
    ++std_it;
    s21_list3.splice(s21_it, s21_list4);
    std_list3.splice(std_it, std_list4);
    compare_lists(&s21_list3, &std_list3);
    compare_lists(&s21_list4, &std_list4);

    s21::list<int> s21_list5(1);
    std::list<int> std_list5(1);
    s21::list<int> s21_list6(10);
    std::list<int> std_list6(10);
    s21_list6.splice(s21_list6.begin(), s21_list5);
    std_list6.splice(std_list6.begin(), std_list5);
    compare_lists(&s21_list5, &std_list5);
    compare_lists(&s21_list6, &std_list6);
}

TEST(list_modifers_suit, reverse_test) {
    s21::list<char> s21_list1{'a', 'b', 'c', 'd', 'e'};
    std::list<char> std_list1{'a', 'b', 'c', 'd', 'e'};
    s21_list1.reverse();
    std_list1.reverse();
    compare_lists(&s21_list1, &std_list1);

    s21::list<int> s21_list2{2, 5, 3, 6, 4, 7, 58, 69};
    std::list<int> std_list2{2, 5, 3, 6, 4, 7, 58, 69};
    s21_list2.reverse();
    std_list2.reverse();
    compare_lists(&s21_list2, &std_list2);

    s21::list<double> s21_list3;
    std::list<double> std_list3;
    s21_list3.reverse();
    std_list3.reverse();
    compare_lists(&s21_list3, &std_list3);
}

TEST(list_modifers_suit, unique_test) {
    s21::list<char> s21_list1{'a', 'b', 'b', 'b', 'a', 'c', 'd', 'e'};
    std::list<char> std_list1{'a', 'b', 'b', 'b', 'a', 'c', 'd', 'e'};
    s21_list1.unique();
    std_list1.unique();
    compare_lists(&s21_list1, &std_list1);

    s21::list<int> s21_list2{2, 5, 3, 6, 4, 7, 58, 69, 58, 58, 58};
    std::list<int> std_list2{2, 5, 3, 6, 4, 7, 58, 69, 58, 58, 58};
    s21_list2.unique();
    std_list2.unique();
    compare_lists(&s21_list2, &std_list2);

    s21::list<double> s21_list3;
    std::list<double> std_list3;
    s21_list3.unique();
    std_list3.unique();
    compare_lists(&s21_list3, &std_list3);

    s21::list<double> s21_list4(10);
    std::list<double> std_list4(10);
    s21_list4.unique();
    std_list4.unique();
    compare_lists(&s21_list4, &std_list4);
}

TEST(list_modifers_suit, merge_test) {
    s21::list<int> s21_list1{1, 3, 5, 7};
    std::list<int> std_list1{1, 3, 5, 7};
    s21::list<int> s21_list2{2, 4, 6, 8};
    std::list<int> std_list2{2, 4, 6, 8};
    s21_list1.merge(s21_list2);
    std_list1.merge(std_list2);
    compare_lists(&s21_list1, &std_list1);
    compare_lists(&s21_list2, &std_list2);

    s21::list<char> s21_list3(2);
    std::list<char> std_list3(2);
    s21::list<char> s21_list4{'a', 'b', 'c'};
    std::list<char> std_list4{'a', 'b', 'c'};
    s21_list3.merge(s21_list4);
    std_list3.merge(std_list4);
    compare_lists(&s21_list3, &std_list3);
    compare_lists(&s21_list4, &std_list4);

    s21::list<int> s21_list5(1);
    std::list<int> std_list5(1);
    s21::list<int> s21_list6(10);
    std::list<int> std_list6(10);
    s21_list6.merge(s21_list5);
    std_list6.merge(std_list5);
    compare_lists(&s21_list5, &std_list5);
    compare_lists(&s21_list6, &std_list6);
}

TEST(list_modifers_suit, sort_test) {
    s21::list<char> s21_list1{'a', 'q', '.', 'b', 'b', 'b', 'a', 'c', '1', 'd', 'e'};
    std::list<char> std_list1{'a', 'q', '.', 'b', 'b', 'b', 'a', 'c', '1', 'd', 'e'};
    s21_list1.sort();
    std_list1.sort();
    compare_lists(&s21_list1, &std_list1);

    s21::list<int> s21_list2{20, 5, 3, -10, 6, 4, 7, 58, 69, 58, 58, 58};
    std::list<int> std_list2{20, 5, 3, -10, 6, 4, 7, 58, 69, 58, 58, 58};
    s21_list2.sort();
    std_list2.sort();
    compare_lists(&s21_list2, &std_list2);

    s21::list<double> s21_list3;
    std::list<double> std_list3;
    s21_list3.sort();
    std_list3.sort();
    compare_lists(&s21_list3, &std_list3);

    s21::list<double> s21_list4(4);
    std::list<double> std_list4(4);
    s21_list4.sort();
    std_list4.sort();
    compare_lists(&s21_list4, &std_list4);

    s21::list<double> s21_list5(12345);
    std::list<double> std_list5(12345);
    s21_list5.sort();
    std_list5.sort();
    compare_lists(&s21_list5, &std_list5);
}

TEST(list_bonus_part_suit, emplace_test) {
    s21::list<int> s21_list;
    std::list<int> std_list;
    s21::list<int>::iterator s21_it(s21_list.begin());
    std::list<int>::iterator std_it(std_list.begin());
    s21_list.emplace(s21_it, 3, 5, 7, 9, 1, 3, 5);
    std_list.emplace(std_it, 3);
    std_list.emplace(std_it, 5);
    std_list.emplace(std_it, 7);
    std_list.emplace(std_it, 9);
    std_list.emplace(std_it, 1);
    std_list.emplace(std_it, 3);
    std_list.emplace(std_it, 5);

    compare_lists(&s21_list, &std_list);

    s21_it = s21_list.begin();
    std_it = std_list.begin();
    ++s21_it;
    ++std_it;
    s21_list.emplace(s21_it, 8, 6, 4);
    std_list.emplace(std_it, 8);
    std_list.emplace(std_it, 6);
    std_list.emplace(std_it, 4);
    compare_lists(&s21_list, &std_list);

    s21_it = s21_list.end();
    std_it = std_list.end();
    s21_list.emplace(s21_it, 11, 22, 33);
    std_list.emplace(std_it, 11);
    std_list.emplace(std_it, 22);
    std_list.emplace(std_it, 33);
    compare_lists(&s21_list, &std_list);
}

TEST(list_bonus_part_suit, emplace_back_test) {
    s21::list<int> s21_list;
    std::list<int> std_list;
    std::list<int>::iterator std_it(std_list.end());
    s21_list.emplace_back(3, 5, 7, 9, 1, 3, 5);
    std_list.emplace(std_it, 3);
    std_list.emplace(std_it, 5);
    std_list.emplace(std_it, 7);
    std_list.emplace(std_it, 9);
    std_list.emplace(std_it, 1);
    std_list.emplace(std_it, 3);
    std_list.emplace(std_it, 5);

    compare_lists(&s21_list, &std_list);

    std_it = std_list.end();
    s21_list.emplace_back(8, 6, 4);
    std_list.emplace(std_it, 8);
    std_list.emplace(std_it, 6);
    std_list.emplace(std_it, 4);
    compare_lists(&s21_list, &std_list);

    std_it = std_list.end();
    s21_list.emplace_back(11, 22, 33);
    std_list.emplace(std_it, 11);
    std_list.emplace(std_it, 22);
    std_list.emplace(std_it, 33);
    compare_lists(&s21_list, &std_list);
}

TEST(list_bonus_part_suit, emplace_front_test) {
    s21::list<int> s21_list;
    std::list<int> std_list;
    std::list<int>::iterator std_it(std_list.begin());
    s21_list.emplace_front(3, 5, 7, 9, 1, 3, 5);
    std_list.emplace(std_it, 3);
    std_list.emplace(std_it, 5);
    std_list.emplace(std_it, 7);
    std_list.emplace(std_it, 9);
    std_list.emplace(std_it, 1);
    std_list.emplace(std_it, 3);
    std_list.emplace(std_it, 5);

    compare_lists(&s21_list, &std_list);

    std_it = std_list.begin();
    s21_list.emplace_front(8, 6, 4);
    std_list.emplace(std_it, 8);
    std_list.emplace(std_it, 6);
    std_list.emplace(std_it, 4);
    compare_lists(&s21_list, &std_list);

    std_it = std_list.begin();
    s21_list.emplace_front(11, 22, 33);
    std_list.emplace(std_it, 11);
    std_list.emplace(std_it, 22);
    std_list.emplace(std_it, 33);
    compare_lists(&s21_list, &std_list);
}
