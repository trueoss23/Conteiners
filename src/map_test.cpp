#include <gtest/gtest.h>
#include "s21_map.cpp"
#include <map>

template <typename Key, typename T>
void compare_maps(s21::map<Key, T>* s21_map, std::map<Key, T>* std_map) {
    ASSERT_EQ(s21_map->size(), std_map->size());
    ASSERT_EQ(s21_map->empty(), std_map->empty());
    typename s21::map<Key, T>::iterator s21_it = s21_map->begin();
    typename std::map<Key, T>::iterator std_it = std_map->begin();
    while (s21_it != s21_map->end()) {
        ASSERT_EQ((*s21_it).first, (*std_it).first);
        ASSERT_EQ((*s21_it).second, (*std_it).second);
        ++s21_it;
        ++std_it;
    }
}

TEST(map_create_and_remove_suit, defolt_constructor) {
    s21::map<int, int> s21_map;
    std::map<int, int> std_map;
    compare_maps(&s21_map, &std_map);
}

TEST(map_create_and_remove_suit, initializer_list_constructor) {
    s21::map<double, bool> s21_map{std::pair<double, bool> (12., true),
                                    std::pair<double, bool> (13., true),
                                    std::pair<double, bool> (14., true),
                                    std::pair<double, bool> (15., true),
                                    std::pair<double, bool> (16., false),
                                    std::pair<double, bool> (16., false),
                                    std::pair<double, bool> (17., false)};

    std::map<double, bool> std_map{std::pair<double, bool> (12., true),
                                    std::pair<double, bool> (13., true),
                                    std::pair<double, bool> (14., true),
                                    std::pair<double, bool> (15., true),
                                    std::pair<double, bool> (16., false),
                                    std::pair<double, bool> (16., false),
                                    std::pair<double, bool> (17., false)};
    compare_maps(&s21_map, &std_map);
}

TEST(map_create_and_remove_suit, copy_constructor) {
    s21::map<double, char> s21_map;
    std::map<double, char> std_map;

    s21::map<double, char> s21_map_copy(s21_map);
    std::map<double, char> std_map_copy(std_map);
    compare_maps(&s21_map, &std_map);
    compare_maps(&s21_map_copy, &std_map_copy);

    for (double i = 0; i < 10; i += 1.) {
        std::pair< int, char> k(i + 10, (int)i + 'a');
        s21_map.insert(k);
        std_map.insert(k);
    }
    s21::map<double, char> s21_map_copy1(s21_map);
    std::map<double, char> std_map_copy1(std_map);
    compare_maps(&s21_map, &std_map);
    compare_maps(&s21_map_copy1, &std_map_copy1);
}

TEST(map_create_and_remove_suit, move_constructor) {
    s21::map<double, char> s21_map;
    std::map<double, char> std_map;

    s21::map<double, char> s21_map_move((s21::map<double, char> &&)s21_map);
    std::map<double, char> std_map_move((std::map<double, char> &&)std_map);
    compare_maps(&s21_map, &std_map);
    compare_maps(&s21_map_move, &std_map_move);

    for (double i = 0; i < 10; i += 1.) {
        std::pair< int, char> k(i + 10, (int)i + 'a');
        s21_map.insert(k);
        std_map.insert(k);
    }
    s21::map<double, char> s21_map_move1((s21::map<double, char> &&)s21_map);
    std::map<double, char> std_map_move1((std::map<double, char> &&)std_map);
    compare_maps(&s21_map, &std_map);
    compare_maps(&s21_map_move1, &std_map_move1);
}

TEST(map_create_and_remove_suit, operator) {
    s21::map<double, char> s21_map;
    std::map<double, char> std_map;

    s21::map<double, char> s21_map_move{{12., 'a'}, {15., 'w'}, {4., 't'}, {-4., 'p'}, {111., 'q'}};
    std::map<double, char> std_map_move{{12., 'a'}, {15., 'w'}, {4., 't'}, {-4., 'p'}, {111., 'q'}};
    s21_map_move = ((s21::map<double, char>&&)s21_map);
    s21_map_move = ((s21::map<double, char>&&)s21_map);
    compare_maps(&s21_map, &std_map);
    compare_maps(&s21_map_move, &std_map_move);

    for (double i = 0; i < 10; i += 1.) {
        std::pair< int, char> k(i + 10, (int)i + 'a');
        s21_map.insert(k);
        std_map.insert(k);
    }
    s21::map<double, char> s21_map_move1((s21::map<double, char> &&)s21_map);
    std::map<double, char> std_map_move1((std::map<double, char> &&)std_map);
    compare_maps(&s21_map, &std_map);
    compare_maps(&s21_map_move1, &std_map_move1);
}

TEST(map_element_access_suit, at) {
    s21::map<int, bool> s21_map {{1, true}, {5, false}, {7, true}, {16, false, }, {6, false}};
    std::map<int, bool> std_map {{1, true}, {5, false}, {7, true}, {16, false, }, {6, false}};

    s21_map.at(7) = false;
    std_map.at(7) = false;

    compare_maps(&s21_map, &std_map);
}

TEST(map_element_access_suit, operator) {
    s21::map<int, bool> s21_map {{1, true}, {5, false}, {7, true}, {16, false, }, {6, false}};
    std::map<int, bool> std_map {{1, true}, {5, false}, {7, true}, {16, false, }, {6, false}};

    s21_map[7] = false;
    std_map[7] = false;

    compare_maps(&s21_map, &std_map);

    s21_map[2] = false;
    std_map[2] = false;

    compare_maps(&s21_map, &std_map);
}

TEST(map_capacity_suit, max_size) {
    s21::map<double, char> s21_map;
    std::map<double, char> std_map;

    ASSERT_EQ(s21_map.max_size(), std_map.max_size());

    s21::map<std::string, bool> s21_map1;
    std::map<std::string, bool> std_map1;

    ASSERT_EQ(s21_map1.max_size(), std_map1.max_size());
}

TEST(map_modifiers_suit, clear) {
    s21::map<std::string, std::string> s21_map({{"15", "123"}, {"16", "321"}, {"17", "17"},
                                                {"18", "qwe"}, {"19", "ewq"}});
    std::map<std::string, std::string> std_map({{"15", "123"}, {"16", "321"}, {"17", "17"},
                                                {"18", "qwe"}, {"19", "ewq"}});

    s21_map.clear();
    std_map.clear();

    compare_maps(&s21_map, &std_map);

    s21_map.clear();
    std_map.clear();

    compare_maps(&s21_map, &std_map);
}

TEST(map_modifiers_suit, insert_const_value_type) {
    s21::map<int, int> s21_map;
    std::map<int, int> std_map;
    s21::map<int, int>::iterator it_s21_map;
    std::map<int, int>::iterator it_std_map;
    std::pair<s21::map<int, int>::iterator, bool> s21k = s21_map.insert(std::pair<int, int> (1, 2));
    std::pair<std::map<int, int>::iterator, bool> stdk = std_map.insert(std::pair<int, int> (1, 2));
    it_s21_map = s21k.first;
    it_std_map = stdk.first;
    ASSERT_EQ((*it_s21_map).first, (*it_std_map).first);
    ASSERT_EQ((*it_s21_map).second, (*it_std_map).second);
    ASSERT_EQ(s21k.second, stdk.second);

    s21k = s21_map.insert(std::pair<int, int> (1, 1));
    it_s21_map = s21k.first;
    stdk = std_map.insert(std::pair<int, int> (1, 1));
    it_std_map = stdk.first;

    ASSERT_EQ((*it_s21_map).first, (*it_std_map).first);
    ASSERT_EQ((*it_s21_map).second, (*it_std_map).second);
    ASSERT_EQ(s21k.second, stdk.second);

    s21k = s21_map.insert(std::pair<int, int> (2, 1));
    it_s21_map = s21k.first;
    stdk = std_map.insert(std::pair<int, int> (2, 1));
    it_std_map = stdk.first;

    ASSERT_EQ((*it_s21_map).first, (*it_std_map).first);
    ASSERT_EQ((*it_s21_map).second, (*it_std_map).second);
    ASSERT_EQ(s21k.second, stdk.second);

    compare_maps(&s21_map, &std_map);
}

TEST(map_modifiers_suit, insert_key_and_obj) {
    s21::map<int, int> s21_map;
    std::map<int, int> std_map{{1, 2}, {2, 1}};
    std::pair<s21::map<int, int>::iterator, bool> k = s21_map.insert(1, 2);
    s21::map<int, int>::iterator it_s21_map;
    it_s21_map = k.first;
    ASSERT_EQ((*it_s21_map).first, 1);
    ASSERT_EQ((*it_s21_map).second, 2);
    ASSERT_EQ(k.second, 1);

    k = s21_map.insert(1, 1);
    it_s21_map = k.first;
    ASSERT_EQ((*it_s21_map).first, 1);
    ASSERT_EQ((*it_s21_map).second, 2);
    ASSERT_EQ(k.second, 0);

    k = s21_map.insert(2, 1);
    it_s21_map = k.first;
    ASSERT_EQ((*it_s21_map).first, 2);
    ASSERT_EQ((*it_s21_map).second, 1);
    ASSERT_EQ(k.second, 1);

    compare_maps(&s21_map, &std_map);
}

TEST(map_modifiers_suit, insert_or_assign) {
    s21::map<int, int> s21_map;
    std::map<int, int> std_map;
    s21::map<int, int>::iterator it_s21_map;
    std::map<int, int>::iterator it_std_map;
    std::pair<s21::map<int, int>::iterator, bool> s21k = s21_map.insert_or_assign(1, 2);
    std::pair<std::map<int, int>::iterator, bool> stdk = std_map.insert_or_assign(1, 2);
    it_s21_map = s21k.first;
    it_std_map = stdk.first;
    ASSERT_EQ((*it_s21_map).first, (*it_std_map).first);
    ASSERT_EQ((*it_s21_map).second, (*it_std_map).second);
    ASSERT_EQ(s21k.second, stdk.second);

    s21k = s21_map.insert_or_assign(1, 1);
    it_s21_map = s21k.first;
    stdk = std_map.insert_or_assign(1, 1);
    it_std_map = stdk.first;

    ASSERT_EQ((*it_s21_map).first, (*it_std_map).first);
    ASSERT_EQ((*it_s21_map).second, (*it_std_map).second);
    ASSERT_EQ(s21k.second, stdk.second);

    s21k = s21_map.insert_or_assign(2, 1);
    it_s21_map = s21k.first;
    stdk = std_map.insert_or_assign(2, 1);
    it_std_map = stdk.first;

    ASSERT_EQ((*it_s21_map).first, (*it_std_map).first);
    ASSERT_EQ((*it_s21_map).second, (*it_std_map).second);
    ASSERT_EQ(s21k.second, stdk.second);

    compare_maps(&s21_map, &std_map);
}

TEST(map_modifiers_suit, erase) {
    s21::map<int, std::string> s21_map({{15, "123"}});
    std::map<int, std::string> std_map({{15, "123"}});
    s21::map<int, std::string>::iterator it_s21_map = s21_map.begin();
    std::map<int, std::string>::iterator it_std_map = std_map.begin();
    s21_map.erase(it_s21_map);
    std_map.erase(it_std_map);
    compare_maps(&s21_map, &std_map);

    s21::map<int, std::string> s21_map2({{16, "123"}, {17, "123"}, {18, "123"}});
    std::map<int, std::string> std_map2({{16, "123"}, {17, "123"}, {18, "123"}});
    it_s21_map = s21_map2.begin();
    it_std_map = std_map2.begin();
    s21_map2.erase(it_s21_map);
    std_map2.erase(it_std_map);
    compare_maps(&s21_map2, &std_map2);

    s21::map<int, std::string> s21_map3({{15, "123"}, {16, "321"}, {17, "17"}, {18, "qwe"}, {19, "ewq"}});
    s21_map3.insert({12, "A"});
    s21_map3.insert({10, "A"});
    s21_map3.insert({13, "A"});
    std::map<int, std::string> std_map3({{15, "123"}, {16, "321"}, {17, "17"}, {18, "qwe"}, {19, "ewq"}});
    std_map3.insert({12, "A"});
    std_map3.insert({10, "A"});
    std_map3.insert({13, "A"});
    it_s21_map = s21_map3.begin();
    it_std_map = std_map3.begin();
    s21_map3.erase(it_s21_map);
    std_map3.erase(it_std_map);
    compare_maps(&s21_map3, &std_map3);
    // s21_map.print();
}

TEST(map_modifiers_suit, swap) {
    s21::map<int, std::string> s21_map({{15, "123"}, {16, "321"}, {17, "17"}, {18, "qwe"}, {19, "ewq"}});
    std::map<int, std::string> std_map({{15, "123"}, {16, "321"}, {17, "17"}, {18, "qwe"}, {19, "ewq"}});

    s21::map<int, std::string> s21_map_for_swap({{5, "5"}, {4, "4"}, {3, "3"}, {2, "2"}, {1, "1"}});
    std::map<int, std::string> std_map_for_swap({{5, "5"}, {4, "4"}, {3, "3"}, {2, "2"}, {1, "1"}});

    s21_map.swap(s21_map_for_swap);
    std_map.swap(std_map_for_swap);

    compare_maps(&s21_map, &std_map);
    compare_maps(&s21_map_for_swap, &std_map_for_swap);
}

TEST(map_modifiers_suit, merge) {
    s21::map<int, std::string> s21_map({{15, "123"}, {16, "321"}, {17, "17"}, {18, "qwe"}, {19, "ewq"}});
    std::map<int, std::string> std_map({{15, "123"}, {16, "321"}, {17, "17"}, {18, "qwe"}, {19, "ewq"}});

    s21::map<int, std::string> s21_map_for_merge({{15, "5"}, {4, "4"}, {3, "3"}, {2, "2"}, {1, "1"}});
    std::map<int, std::string> std_map_for_merge({{15, "5"}, {4, "4"}, {3, "3"}, {2, "2"}, {1, "1"}});

    s21_map.merge(s21_map_for_merge);
    std_map.merge(std_map_for_merge);

    compare_maps(&s21_map, &std_map);
    compare_maps(&s21_map_for_merge, &std_map_for_merge);
}

TEST(map_lookup_suit, contains) {
    s21::map<int, bool> s21_map {{1, true}, {5, false}, {7, true}, {16, false, }, {6, false}};

    ASSERT_TRUE(s21_map.contains(5));
    ASSERT_FALSE(s21_map.contains(55));

    s21::map<int, bool> s21_map1;

    ASSERT_FALSE(s21_map.contains(0));
}

TEST(map_bonus_part_suit, emplace) {
    s21::map<int, double> s21_map;
    std::map<int, double> std_map;
    s21_map.emplace(std::pair<int, double> (1, 1.),
                    std::pair<int, double> (7, 7.),
                    std::pair<int, double> (-5, 15.),
                    std::pair<int, double> (99, 0.));
    std_map.insert({1, 1.});
    std_map.insert({7, 7.});
    std_map.insert({-5, 15.});
    std_map.insert({99, 0.});

    compare_maps(&s21_map, &std_map);

    s21_map.emplace(std::pair<int, double> (1, 1.),
                    std::pair<int, double> (17, 7.),
                    std::pair<int, double> (-15, 15.),
                    std::pair<int, double> (99, 0.));
    std_map.insert({1, 1.});
    std_map.insert({17, 7.});
    std_map.insert({-15, 15.});
    std_map.insert({99, 0.});

    compare_maps(&s21_map, &std_map);

    s21_map.emplace();

    compare_maps(&s21_map, &std_map);
}
