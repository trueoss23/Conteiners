#ifndef SRC_TREE_H_
#define SRC_TREE_H_
using size_type = size_t;

namespace s21 {
template <class T>
class Binary_tree {
using value_type = T;

 protected:
    struct Tree_node {
        bool color;
        T data;
        Tree_node * parent;
        Tree_node * left;
        Tree_node * right;
        T get_data();
        bool get_color();
        void set_color(bool curr_color);
        void set_data(T key);
        void Tree(T _data, bool _color, Tree_node * _left, Tree_node * _right);
        void free();
        Tree_node * minimum();
        Tree_node * maximum();
        Tree_node * operator=(Tree_node * b);
        bool operator==(Tree_node * b);
    };
    explicit Binary_tree(T key);
    Binary_tree();
    Binary_tree(std::initializer_list<value_type> const &items);
    Binary_tree(const Binary_tree<T>& other);
    Binary_tree(Binary_tree<T> && other);
    ~Binary_tree();

    void copy(Binary_tree<T> * res, Tree_node * temp);
    Tree_node * find_hide_node();
    void delete_hide_node();
    void add_hide_node();
    void swap_nodes(Tree_node * a, Tree_node * b);
    void swap_color(Tree_node * a, Tree_node * b);
    void delete_without_find(Tree_node * temp);
    void delete_black_node_with_one_chield(Tree_node * temp, Tree_node * chield, bool* flag_delete);
    void delete_black_node_with_no_cheild(Tree_node * temp);
    void rebalance_after_hard_delete(Tree_node * temp);
    void righ_children_brothers_is_red(Tree_node * temp, Tree_node * bro);
    void fix_after_insert(Tree_node * temp);
    void left_rotate(Tree_node * x);
    void right_rotate(Tree_node * x);
    void delete_tree(Tree_node * curr);
    Tree_node * find_in_tree(T);
    bool insert_in_tree(T);

 public:
    Tree_node * root;
    Tree_node * hide_node;
    size_type count_of_elem;
    size_type size_of_tree();
    Tree_node * find_most_left_elem();
    Tree_node * find_most_right_elem();
};
}  //  namespace s21

#include "tree.cpp"

#endif  //  SRC_TREE_H_
