#include <iostream>
#include "tree.h"

namespace s21 {
template <class T>
Binary_tree<T>::Binary_tree() {
    this->root = nullptr;
    this->hide_node = new Tree_node;
    this->hide_node->parent = nullptr;
    this->hide_node->left = nullptr;
    this->hide_node->right = nullptr;
    this->count_of_elem = 0;
}

template <class T>
Binary_tree<T>::Binary_tree(T key) {
    this->root = new Tree_node;
    this->root->Tree(key, 1, nullptr, nullptr);
    this->hide_node = new Tree_node;
    this->count_of_elem = 1;
}

template <class T>
Binary_tree<T>::Binary_tree(std::initializer_list<value_type> const &items) {
    this->root = nullptr;
    this->hide_node = new Tree_node;
    this->hide_node->parent = nullptr;
    this->hide_node->left = nullptr;
    this->hide_node->right = nullptr;
    this->count_of_elem = 0;
    if (items.size()) {
        for (int i = 0; i < items.size(); i++) {
            insert_in_tree(items.begin()[i]);
        }
    }
}

template <class T>
Binary_tree<T>::Binary_tree(const Binary_tree & other) {  // COPY constructor
    this->root = nullptr;
    this->hide_node = new Tree_node;
    this->hide_node->parent = nullptr;
    this->hide_node->left = nullptr;
    this->hide_node->right = nullptr;
    this->count_of_elem = 0;
    copy(this, other.root);
}

template <class T>
Binary_tree<T>::Binary_tree(Binary_tree && other) {  // MOVE constructor
    this->hide_node = other.hide_node;
    this->root = other.root;
    this->count_of_elem = other.count_of_elem;
    other.root = nullptr;
    other.hide_node = nullptr;
    other.count_of_elem = 0;
}

template<class T>
void Binary_tree<T>::copy(Binary_tree<T> * res, Tree_node * temp) {
    if (temp) {
        res->insert_in_tree(temp->data);
        this->copy(res, temp->left);
        this->copy(res, temp->right);
    }
}

template <class T>
Binary_tree<T>::~Binary_tree() {  //  DESTRUCTOR
    this->delete_tree(root);
    if (hide_node) {
        delete hide_node;
        hide_node = nullptr;
        this->count_of_elem = 0;
        this->root = nullptr;
    }
    this->count_of_elem = 0;
    this->root = nullptr;
}

template <class T>
void Binary_tree<T>::delete_tree(Tree_node * curr) {
    if (curr != nullptr) {
        if (curr->left != nullptr)
            delete_tree(curr->left);
        if (curr->right != nullptr)
            delete_tree(curr->right);
        if (curr != nullptr) {
            delete curr;
            curr = nullptr;
        }
    }
}

template <class T>
typename Binary_tree<T>::Tree_node * Binary_tree<T>::find_in_tree(T key) {
    Tree_node * curr = root;
    while (curr && curr->data != key) {
        if (curr->data > key) {
            curr = curr->left;
        } else {
            curr = curr->right;
        }
    }
    return curr == nullptr ? nullptr : curr;
}

template <class T>
void Binary_tree<T>::fix_after_insert(Tree_node * temp) {
    if (temp != root) {
        while (temp->parent->color == 0) {
            if ((temp->parent->left == temp || temp->parent->right == temp) && temp->parent->color == 0 &&
                ((temp->parent->parent->left == temp->parent) ||
                (temp->parent->parent->right == temp->parent))) {
                if (temp->parent->parent->right && temp->parent != temp->parent->parent->right &&
                temp->parent->parent->right->color == 0) {
                    temp->parent->parent->right->set_color(1);
                    temp->parent->set_color(1);
                    temp->parent->parent->set_color(0);
                    if (temp->parent->parent == root) {
                        root->set_color(1);
                    } else {
                        temp = temp->parent->parent;
                    }
                } else if (temp->parent->parent->left && temp->parent != temp->parent->parent->left &&
                temp->parent->parent->left->color == 0) {
                    temp->parent->parent->left->set_color(1);
                    temp->parent->set_color(1);
                    temp->parent->parent->set_color(0);
                    if (temp->parent->parent == root) {
                        root->set_color(1);
                    } else {
                        temp = temp->parent->parent;
                    }
                }
            }
            if (temp->parent->color == 0 && temp->parent->parent->left &&
            temp->parent == temp->parent->parent->left) {  //  отец левый сын
                if (!(temp->parent->parent->right) || (temp->parent->parent->right &&
                temp->parent->parent->right->color == 1)) {  //  дядя черный или его нет
                    if (temp->parent->right && temp->parent->right == temp) {  //  temp  правый сын
                        temp = temp->parent;
                        left_rotate(temp);
                    } else if (temp->parent->left && temp->parent->left == temp) {  //  temp  левый сын
                        temp->parent->set_color(1);
                        temp->parent->parent->set_color(0);
                        right_rotate(temp->parent->parent);
                    }
                }
            } else if (temp->parent->color == 0 && temp->parent == temp->parent->parent->right) {
                // отец правый сын
                if (!(temp->parent->parent->left) || (temp->parent->parent->left &&
                temp->parent->parent->left->color == 1)) {  //  дядя черный или его нет
                    if (temp == temp->parent->left) {  //  temp - левый сын
                        temp = temp->parent;
                        right_rotate(temp);
                    } else if (temp == temp->parent->right) {  //  temp  правый сын
                        temp->parent->set_color(1);
                        temp->parent->parent->set_color(0);
                        left_rotate(temp->parent->parent);
                    }
                }
            }
            root->set_color(1);
        }
    } else {
        temp->set_color(1);
    }
}

template <class T>
bool Binary_tree<T>::insert_in_tree(T key) {
    bool result_of_insert = false;
    bool value_exist = false;
    Tree_node * temp = new Tree_node();
    temp->Tree(key, 0, nullptr, nullptr);
    if (root == nullptr) {
        root = temp;
        temp->set_color(1);
        temp->parent = nullptr;
        this->count_of_elem++;
        result_of_insert = true;
    } else {
        Tree_node * p = root;
        Tree_node * q = nullptr;
        while (p != nullptr && !value_exist) {
            q = p;
            if (p->data < temp->data) {
                p = p->right;
            } else if (p->data > temp->data) {
                p = p->left;
            } else {
                delete temp;
                value_exist = true;
            }
        }
        if (!value_exist) {
            temp->parent = q;
            if (q->data < temp->data) {
                q->right = temp;
            } else {
                q->left = temp;
            }
            fix_after_insert(temp);
            this->count_of_elem++;
            result_of_insert = true;
        }
    }
    return result_of_insert;
}

template <class T>
void Binary_tree<T>::right_rotate(Tree_node * x) {
    Tree_node * temp = x->left;
    if (x->left->right) {
        x->left = x->left->right;
        temp->right->parent = x;
    } else {
        x->left = nullptr;
    }
    temp->right = x;
    temp->parent = x->parent;
    if (x != root) {
        if (x->parent->left && x->parent->left == x) {
            x->parent->left = temp;
        } else if (x->parent->right && x->parent->right == x) {
            x->parent->right = temp;
        }
    } else {
        root = temp;
    }
    x->parent = temp;
}

template <class T>
void Binary_tree<T>::left_rotate(Tree_node * x) {
    Tree_node * temp = x->right;
    if (x->right->left) {
        x->right = x->right->left;
        x->right->parent = x;
    } else {
        x->right = nullptr;
    }
    temp->left = x;
    temp->parent = x->parent;
    if (x!= root) {
        if (x->parent->left && x == x->parent->left) {
            x->parent->left = temp;
        } else if (x->parent->right && x == x->parent->right) {
            x->parent->right = temp;
        }
    } else {
        root = temp;
    }
    x->parent = temp;
}

template <class T>
void Binary_tree<T>::delete_black_node_with_one_chield(Tree_node * temp, Tree_node * chield,
                                                        bool* flag_delete) {
    swap_nodes(temp, chield);
}

template <class T>
void Binary_tree<T>::swap_nodes(Tree_node * a, Tree_node * b) {
    swap_color(a, b);
    Tree_node *temp_parent = new Tree_node();
    if (!a->parent) a->parent = temp_parent;
    if (!b->parent) b->parent = temp_parent;

    if (a->parent->left == a) {
        if (a->parent != b) a->parent->left = b;
    } else if (a->parent->right == a) {
        if (a->parent != b) a->parent->right = b;
    }

    if (b->parent->left == b) {
        if (b->parent != a) b->parent->left = a;
    } else if (b->parent->right == b) {
        if (b->parent != a) b->parent->right = a;
    }

    if (a->left != nullptr) {
        if (a->left != b) a->left->parent = b;
    }
    if (a->right != nullptr) {
        if (a->right != b) a->right->parent = b;
    }
    if (b->left != nullptr) {
        if (b->left != a) b->left->parent = a;
    }
    if (b->right != nullptr) {
        if (b->right != a) b->right->parent = a;
    }

    Tree_node * temp = new Tree_node();
    temp->parent = a->parent;
    temp->left = a->left;
    temp->right = a->right;
    if (b->parent != a) {
        a->parent = b->parent;
    } else {
        a->parent = b;
    }
    if (b->left != a) {
        a->left = b->left;
    } else {
        a->left = b;
    }
    if (b->right != a) {
        a->right = b->right;
    } else {
        a->right = b;
    }

    if (temp->parent != b) {
        b->parent = temp->parent;
    } else {
        b->parent = a;
    }
    if (temp->left != b) {
        b->left = temp->left;
    } else {
        b->left = a;
    }
    if (temp->right != b) {
        b->right = temp->right;
    } else {
        b->right = a;
    }

    delete temp;

    if (a->parent == temp_parent) {
        a->parent = nullptr;
        this->root = a;
    }
    if (b->parent == temp_parent) {
        b->parent = nullptr;
        this->root = b;
    }
    delete temp_parent;
}

template <class T>
void Binary_tree<T>::swap_color(Tree_node * a, Tree_node * b) {
    if (a && !b) {
        a->set_color(1);
    } else if (!a && b) {
        b->set_color(1);
    } else if (a && b) {
        int temp = a->color;
        a->set_color(b->color);
        b->set_color(temp);
    }
}

template <class T>
void Binary_tree<T>::righ_children_brothers_is_red(Tree_node * temp, Tree_node * bro) {
    //  правый ребенок брата красный
    bool flag = (temp == temp->parent->left);
    bro->set_color(temp->parent->color);
    temp->parent->set_color(1);
    if (flag) {
        bro->right->set_color(1);
    } else {
        bro->left->set_color(1);
    }
    if (flag) {
        left_rotate(temp->parent);
    } else {
        right_rotate(temp->parent);
    }
}

template <class T>
void Binary_tree<T>::rebalance_after_hard_delete(Tree_node * temp) {
    if (temp->parent->left && temp->parent->left == temp) {  //  если темп левый ребенок
        if (temp->parent->right && temp->parent->right->color == 1) {  // есть черный брат
            if (temp->parent->right->right && temp->parent->right->right->color == 0) {
                righ_children_brothers_is_red(temp, temp->parent->right);
                    // правый ребенок брата красный
            } else if (temp->parent->right->left && temp->parent->right->left->color == 0
                        && ((temp->parent->right->right && temp->parent->right->right->color == 1)
                        || !(temp->parent->right->right))) {
                            // левый ребенок брата красный, правый черный
                        swap_color(temp->parent->right->left, temp->parent->right);
                        right_rotate(temp->parent->right);
                        righ_children_brothers_is_red(temp, temp->parent->right);
            } else if (((!temp->parent->right->left) ||
                (temp->parent->right->left && temp->parent->right->left->color == 1))
                && ((!temp->parent->right->right) ||
                (temp->parent->right->right && temp->parent->right->right->color == 1))) {
                //  оба ребенка брата черные
                temp->parent->right->set_color(0);
                if (temp->parent->color == 1) {
                    if (temp->parent != root)
                        rebalance_after_hard_delete(temp->parent);
                } else {
                    temp->parent->set_color(1);
                }
            }
        } else if (temp->parent->right && temp->parent->right->color == 0) {  // есть красный брат
            delete_black_node_with_no_cheild(temp);
        } else if (!temp->parent->right) {
            //  оба ребенка брата черные
            if (temp->parent->color == 1) {
                // temp->parent->left = nullptr;
                if (temp->parent != root)
                    rebalance_after_hard_delete(temp->parent);
            } else {
                temp->parent->set_color(1);
            }
        }
    } else if (temp->parent->right && temp->parent->right == temp) {  //  если темп правый ребенок
        if (temp->parent->left && temp->parent->left->color == 1) {  // есть черный брат
            if (temp->parent->left->left && temp->parent->left->left->color == 0) {
                //  левый ребенок брата красный
                righ_children_brothers_is_red(temp, temp->parent->left);
            } else if (((!temp->parent->left->left) ||
                        (temp->parent->left->left && temp->parent->left->left->color == 1))
                        && temp->parent->left->right && temp->parent->left->right->color == 0) {
                            // правый ребенок брата красный, левый черный
                        swap_color(temp->parent->left->left, temp->parent->left);
                        left_rotate(temp->parent->left);
                        righ_children_brothers_is_red(temp, temp->parent->left);
            }  else if ((!temp->parent->left->left) ||
            (temp->parent->left->left && temp->parent->left->left->color == 1)
            && ((!(temp->parent->left->right)) ||
            (temp->parent->left->right && temp->parent->left->right->color == 1))) {
                //  оба ребенка брата черные
                temp->parent->left->set_color(0);
                if (temp->parent->color == 1) {
                    if (temp->parent != root)
                        rebalance_after_hard_delete(temp->parent);
                } else {
                    temp->parent->set_color(1);
                }
            }
        } else if (temp->parent->left && temp->parent->left->color == 0) {  // есть красный брат
            delete_black_node_with_no_cheild(temp);
        } else if (!temp->parent->left) {
            //  оба ребенка брата черные
            if (temp->parent->color == 1) {
                if (temp->parent != root)
                    rebalance_after_hard_delete(temp->parent);
            } else {
                temp->parent->set_color(1);
            }
        }
    }
}

template <class T>
void Binary_tree<T>::delete_black_node_with_no_cheild(Tree_node * temp) {
    if (temp->parent->left == temp) {
        //  темп левый сын
        if (!temp->parent->right || temp->parent->right->color == 1) {
            //  и у него есть правый черный брат
            rebalance_after_hard_delete(temp);  //  this
        } else if (temp->parent->right->color == 0) {
            //  и у него есть правый красный брат
            temp->parent->set_color(0);
            temp->parent->right->set_color(1);
            left_rotate(temp->parent);
            rebalance_after_hard_delete(temp);
        }
    } else if (temp->parent->right == temp) {
        //  темп правый сын
        if (!temp->parent->left || temp->parent->left->color == 1) {
            //  и у него есть левый черный брат
            rebalance_after_hard_delete(temp);
        } else if (temp->parent->left->color == 0) {
            //  и у него есть левый красный брат
            temp->parent->set_color(0);
            temp->parent->left->set_color(1);
            right_rotate(temp->parent);
            rebalance_after_hard_delete(temp);
        }
    }
}

template <class T>
void Binary_tree<T>::delete_without_find(Tree_node * temp) {
    bool flag_delete = 1;
    if (flag_delete && temp->left && temp->right) {  //  есть оба ребенка
        Tree_node * swap_node = temp->left;
        while (swap_node) {
            if (swap_node->right) {
                swap_node = swap_node->right;
            } else {
                break;
            }
        }
        swap_nodes(temp, swap_node);
        if (temp->color != 0) {
            delete_black_node_with_no_cheild(temp);
        }
    } else if (flag_delete && temp->color == 1) {  //  если темп черный
        if (!(temp->left) && temp->right && temp->right->color == 0) {
            //  есть правый ребенок красный и нет левого
            delete_black_node_with_one_chield(temp, temp->right, &flag_delete);
        } else if (!(temp->right) && temp->left && temp->left->color == 0) {
            //  есть левый ребенок красный и нет правого
            delete_black_node_with_one_chield(temp, temp->left, &flag_delete);
        } else if (!(temp->left) && !(temp->right)) {  //  без детей
            if (temp == root) {
                delete root;
                root = nullptr;
                flag_delete = 0;
                this->count_of_elem--;
            } else {
                delete_black_node_with_no_cheild(temp);
            }
        }
    }
    if (flag_delete && temp != nullptr) {
        if (temp == root) {
            delete root;
            root = nullptr;
            flag_delete = 0;
        } else if (temp->parent->left == temp) {
            temp->parent->left = nullptr;
            delete temp;
            temp = nullptr;
        } else if (temp->parent->right == temp) {
            temp->parent->right = nullptr;
            delete temp;
            temp = nullptr;
        }
        this->count_of_elem--;
    }
}


template <class T>
typename Binary_tree<T>::Tree_node * Binary_tree<T>:: find_most_left_elem() {
    Tree_node * temp = root;
    while (temp) {
        if (temp->left) {
            temp = temp->left;
        } else {
            break;
        }
    }
    return temp;
}

template <class T>
typename Binary_tree<T>::Tree_node * Binary_tree<T>:: find_most_right_elem() {
    Tree_node * temp = root;
    while (temp != nullptr && temp != hide_node) {
        if (temp->right) {
            temp = temp->right;
        } else {
            break;
        }
    }
    return temp;
}

template <class T>
void Binary_tree<T>::Tree_node::Tree(T _data, bool _color, Tree_node * _left, Tree_node * _right) {
    set_data(_data);
    left = _left;
    right = _right;
    set_color(_color);
}

template <class T>
T Binary_tree<T>::Tree_node::get_data() {
    return data;
}

template <class T>
bool Binary_tree<T>::Tree_node::get_color() {
    return color;
}

template <class T>
void Binary_tree<T>::Tree_node::set_color(bool curr_color) {
    color = curr_color;
}

template <class T>
void Binary_tree<T>::Tree_node::set_data(T key) {
    data = key;
}

template <class T>
typename Binary_tree<T>::Tree_node* Binary_tree<T>::Tree_node::minimum() {
    Tree_node * res = nullptr;
    if (this->left == nullptr) {
        res = this;
    } else {
        res = this->left->minimum();
    }
    return res;
}

template <class T>
typename Binary_tree<T>::Tree_node* Binary_tree<T>::Tree_node::maximum() {
    Tree_node * res = nullptr;
    if (this->right == nullptr) {
        res = this;
    } else  {
        res = this->right->maximum();
    }
    return res;
}

template <class T>
typename Binary_tree<T>::Tree_node * Binary_tree<T>::Tree_node::operator=(Tree_node * b) {
    if (b->parent)
        parent = b->parent;
    else
        parent = nullptr;
    if (b->left)
        left = b->left;
    else
        left = nullptr;
    if (b->right)
        right = b->right;
    else
        right = nullptr;
}

template <class T>
bool Binary_tree<T>::Tree_node::operator==(Tree_node * b) {
    return data == b->data;
}

template <class T>
size_type Binary_tree<T>::size_of_tree() {
    return this->count_of_elem;
}

template <class T>
void Binary_tree<T>::delete_hide_node() {
    if (hide_node->parent)
        hide_node->parent->right = nullptr;
}

template <class T>
void Binary_tree<T>::add_hide_node() {
    hide_node->parent = find_most_right_elem();
    find_most_left_elem()->right = hide_node;
}
}  //  namespace s21
