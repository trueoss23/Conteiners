#include "s21_array.h"
namespace s21 {
    template <typename T, size_t N>
    array<T, N>::array() {
        size_ = N;
        data_ = new value_type[size_];
    }

    template <typename T, size_t N>
    array<T, N>::array(std::initializer_list<value_type> const &items) {
        size_ = N;
        data_ = new value_type[size_];
        for (int i = 0; i < size_; i++) {
            data_[i] = (value_type)items.begin()[i];
        }
    }

    template <typename T, size_t N>
    array<T, N>::array(const array &v) {
        size_ = v.size_;
        data_ = new value_type[size_];
        for (int i = 0; i < size_; i++) {
            data_[i] = v.data_[i];
        }
    }

    template <typename T, size_t N>
    array<T, N>::array(array &&a) {
        data_ = a.data_;
        size_ = a.size_;
        a.data_ = nullptr;
        a.size_ = 0;
    }

    template <typename T, size_t N>
    array<T, N>::~array() {
        if (data_) {
            delete[] data_;
            data_ = nullptr;
            size_ = 0;
        }
    }

    template <typename T, size_t N>
    array<T, N> array<T, N>::operator=(array &&a) {
        size_ = a.size_;
        delete[] data_;
        data_ = new value_type[size_];
        for (int i = 0; i < size_; i++) {
            data_[i] = a.data_[i];
        }
        return *this;
    }

    template <typename T, size_t N>
    typename array<T, N>::reference array<T, N>::at(size_type pos) {
        if (pos >= N || pos < 0) {
            throw std::out_of_range("Invalid argument");
        }
        return data_[pos];
    }

    template <typename T, size_t N>
    typename array<T, N>::reference array<T, N>::operator[](size_type pos) {
        return data_[pos];
    }

    template <typename T, size_t N>
    typename array<T, N>::const_reference array<T, N>::front() {
        return data_[0];
    }

    template <typename T, size_t N>
    typename array<T, N>::const_reference array<T, N>::back() {
        return data_[size_ - 1];
    }

    template <typename T, size_t N>
    typename array<T, N>::iterator array<T, N>::data() {
        return data_;
    }

    template <typename T, size_t N>
    typename array<T, N>::iterator array<T, N>::begin() {
        return data_;
    }

    template <typename T, size_t N>
    typename array<T, N>::iterator array<T, N>::end() {
        return &(data_[size_]);
    }

    template <typename T, size_t N>
    bool array<T, N>::empty() {
        return N == 0 ? 1 : 0;
    }

    template <typename T, size_t N>
    typename array<T, N>::size_type array<T, N>::size() {
        return size_;
    }

    template <typename T, size_t N>
    typename array<T, N>::size_type array<T, N>::max_size() {
        return size_;
    }

    template <typename T, size_t N>
    void array<T, N>::swap(array& other) {
        array<T, N> temp(other);
        iterator iter = begin();

        delete[] other.data_;
        other.size_ = size_;
        other.data_ = new value_type[other.size_];

        int i = 0;
        while (iter != end()) {
            other.data_[i] = data_[i];
            i++;
            iter++;
        }
        i = 0;
        iter = temp.begin();
        size_ = temp.size_;
        delete[] data_;
        data_ = new value_type[size_];
        while (iter != temp.end()) {
            data_[i] = temp.data_[i];
            i++;
            iter++;
        }
    }

    template <typename T, size_t N>
    void array<T, N>::fill(const_reference value) {
        for (int i = 0; i < size_; i++) {
            data_[i] = value;
        }
    }
}  // namespace s21
