#include "s21_vector.h"
namespace s21 {
    template <typename T>
    Vector<T>::Vector() {
        current_capacity = 1;
        current_size = 0;
        current_value = new value_type[current_capacity];
    }

    template <typename T>
    Vector<T>::Vector(size_type n) {
        current_capacity = n;
        current_size = n;
        current_value = new value_type[current_capacity ];
    }

    template <typename T>
    Vector<T>::Vector(std::initializer_list<value_type> const &items) {
        current_capacity = items.size();
        current_size = items.size();
        current_value = new value_type[current_capacity];
        for (size_type i = 0; i < current_size; i++) {
            current_value[i] = (value_type)items.begin()[i];
        }
    }

    template <typename T>
    Vector<T>::Vector(const Vector &v) {
        current_value = new value_type[v.current_capacity];
        for (size_type i = 0; i < v.current_size; i++) {
            current_value[i] = v.current_value[i];
        }
        current_size = v.current_size;
        current_capacity = v.current_capacity;
    }

    template <typename T>
    Vector<T>::Vector(Vector &&v) {
        current_value = v.current_value;
        current_size = v.current_size;
        current_capacity = v.current_capacity;
        v.current_value = nullptr;
        v.current_capacity = 0;
        v.current_size = 0;
    }

    template <typename T>
    Vector<T> Vector<T>::operator=(Vector &&v) {
        delete[] current_value;
        current_size = v.current_size;
        current_capacity = v.current_capacity;
        current_value = new value_type[current_capacity];
        for (int i = 0; i < current_size; i++) {
            current_value[i] = v.current_value[i];
        }
        return *this;
    }

    template <typename T>
    Vector<T>::~Vector() {
        if (current_value) {
            delete[] current_value;
            current_value = nullptr;
            current_size = 0;
            current_capacity = 0;
        }
    }

    template <typename T>
    typename Vector<T>::reference Vector<T>::at(size_type pos) {
        if (pos >= current_size || pos < 0)  {
            throw std::invalid_argument("Invalid argument");
        } else if (current_size == 0) {
            throw std::invalid_argument("Vector empty");
        }
        return current_value[pos];
    }

    template <typename T>
    typename Vector<T>::reference Vector<T>::operator[](size_type pos) {
        return current_value[pos];
    }

    template <typename T>
    typename Vector<T>::const_reference Vector<T>::front() {
        if (current_size == 0)  {
            throw std::invalid_argument("Invalid argument");
        }
        return current_value[0];
    }

    template <typename T>
    typename Vector<T>::const_reference Vector<T>::back() {
        if (current_size == 0)  {
            throw std::invalid_argument("Invalid argument");
        }
        return current_value[current_size - 1];
    }

    template <typename T>
    typename Vector<T>::iterator Vector<T>::data() {
        return current_value;
    }

    template <typename T>
    typename Vector<T>::iterator Vector<T>::begin() {
        return current_value;
    }

    template <typename T>
    typename Vector<T>::iterator Vector<T>::end() {
        iterator result = current_value;
        if (current_size != 0) {
            result = &(current_value[current_size]);
        }
        return result;
    }

    template <typename T>
    bool Vector<T>::empty() {
        bool result = false;
        if (begin() == end()) {
            result = true;
        }
        return result;
    }

    template <typename T>
    typename Vector<T>::size_type Vector<T>::size() {
        return current_size;
    }

    template <typename T>
    typename Vector<T>::size_type Vector<T>::max_size() {
        return 4294967292 / sizeof(value_type);
    }

    template <typename T>
    void Vector<T>::reserve(size_type size) {
        if (size > current_capacity) {
            if (size > max_size()) {
                throw std::length_error("Size > max_size");
            }
            value_type* tmp = new value_type[current_size];
            for (size_type i = 0; i < current_size; i++) {
                tmp[i] = current_value[i];
            }
            delete[] current_value;
            current_value = new value_type[size];
            for (size_type i = 0; i < current_size; i++) {
                current_value[i] = tmp[i];
            }
            current_capacity = size;
            delete[] tmp;
        }
    }

    template <typename T>
    typename Vector<T>::size_type Vector<T>::capacity() {
        return current_capacity;
    }

    template <typename T>
    void Vector<T>::shrink_to_fit() {
        if (current_capacity > current_size) {
            value_type* tmp = new value_type[current_size];
            for (size_type i = 0; i < current_size; i++) {
                tmp[i] = current_value[i];
            }
            delete[] current_value;
            current_value = new value_type[current_size];
            for (size_type i = 0; i < current_size; i++) {
                current_value[i] = tmp[i];
            }
            current_capacity = current_size;
            delete[] tmp;
        }
    }

    template <typename T>
    void Vector<T>::clear() {
        if (!empty()) {
            delete[] current_value;
            current_value = new value_type[1];
            current_size = 0;
            current_capacity = 1;
        }
    }

    template <typename T>
    typename Vector<T>::iterator Vector<T>::insert(iterator pos, const_reference value) {
        iterator it = begin();
        while (it != end() && it != pos) {
            it++;
        }
        if (it != pos) {
            throw std::invalid_argument("Incorrect position");
        }
        it = begin();
        iterator result;
        Vector<T> tmp(current_size + 1);
        int i = 0;
        while (it != pos) {
            tmp.current_value[i] = current_value[i];
            it++;
            i++;
        }
        tmp.current_value[i] = value;
        result = &(current_value[i]);
        i++;
        for (; i < current_size + 1; i++) {
            tmp.current_value[i] = current_value[i - 1];
        }


        if (current_size > current_capacity) {
            reserve(current_size * 2);
            current_size++;
        }
        for (i = 0; i < current_size; i++) {
            current_value[i] = tmp.current_value[i];
        }
        return result;
    }

    template <typename T>
    void Vector<T>::erase(iterator pos) {
        iterator it = begin();
        while (it != end() && it != pos) {
            it++;
        }
        if (it != pos) {
            throw std::invalid_argument("Incorrect position");
        }

        it = begin();
        int i = 0;
        while (it != pos) {
            it++;
            i++;
        }
        if (it != end()) {
            while (it != end() - 1) {
                current_value[i] = current_value[i + 1];
                it++;
                i++;
            }
        }
        current_size--;
    }

    template <typename T>
    void Vector<T>::push_back(const_reference value) {
        if (current_size + 1 > current_capacity) {
            reserve((current_size + 1) * 2);
        }
        current_size++;
        current_value[current_size - 1] = value;
    }

    template <typename T>
    void Vector<T>::pop_back() {
        current_size--;
    }

    template <typename T>
    void Vector<T>::swap(Vector& other) {
        Vector<T> temp(other);
        typename Vector<T>::iterator iter = begin();
        int i = 0;
        other.reserve(current_capacity);
        other.current_size = current_size;
        while (iter != end()) {
            other.current_value[i] = current_value[i];
            i++;
            iter++;
        }
        i = 0;
        iter = temp.begin();
        reserve(temp.current_capacity);
        current_size = temp.current_size;
        while (iter != temp.end()) {
            current_value[i] = temp.current_value[i];
            i++;
            iter++;
        }
    }

    template <typename T>
    template <typename ... Args>
    void Vector<T>::emplace_back(Args&&... args) {
        Vector<T> tmp_vector({args...});
        iterator i = tmp_vector.begin();
        while (i != tmp_vector.end()) {
            push_back(*i);
            i++;
        }
    }

    template <typename T>
    template <typename ... Args>
    typename Vector<T>::iterator Vector<T>::emplace(const_iterator pos, Args&&... args) {
        Vector<T> temp_args{args...};
        Vector<T> temp(*this);
        iterator iter_temp = temp.begin();
        iterator iter = begin();
        clear();
        int i = 1;
        while (iter != pos) {
            push_back(temp[i - 1]);
            i++;
            iter++;
        }
        int insert_index = i - 1;
        int j = 0;
        while (j < temp_args.size()) {
            push_back(temp_args[j]);
            j++;
        }
        while ((i - 1) < temp.size()) {
            push_back(temp[i - 1]);
            i++;
        }
        iterator result = &(*this)[insert_index];
        return result;
    }
}  // namespace s21
