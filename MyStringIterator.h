//
// Created by Lenovo on 2025-03-16.
//

#ifndef MYSTRINGITERATOR_H
#define MYSTRINGITERATOR_H
#include <compare>
#include <iterator>


class MyStringIterator {
private:
    char* m_ptr = nullptr;
public:
    using difference_type   = std::ptrdiff_t;
    using pointer = char*;
    using reference = char&;
    using iterator_category = std::random_access_iterator_tag;
    using value_type = char;


    MyStringIterator(char* ptr) : m_ptr(ptr) {};
    MyStringIterator(const MyStringIterator& it) : m_ptr(it.m_ptr) {};

    MyStringIterator& operator++() {
        m_ptr++;
        return *this;
    }

    MyStringIterator operator++(int) {

        MyStringIterator it = *this;
        ++(*this);
        return it;
    }

    MyStringIterator& operator--() {
        m_ptr--;
        return *this;
    }

    MyStringIterator operator--(int) {
        MyStringIterator it = *this;
        --(*this);
        return it;
    }
    MyStringIterator& operator+=(difference_type n) {
        m_ptr += n; return *this;
    }
    MyStringIterator& operator-=(difference_type n) {
        m_ptr -= n; return *this;
    }

    friend MyStringIterator operator+(MyStringIterator it, difference_type n) {
        return it += n;
    }
    friend MyStringIterator operator+(difference_type n, MyStringIterator it) {
        return it += n;
    }
    friend MyStringIterator operator-(MyStringIterator it, difference_type n) {
        return it -= n;
    }
    friend difference_type operator-(const MyStringIterator& a, const MyStringIterator& b) {
        return a.m_ptr - b.m_ptr;
    }

    MyStringIterator& operator=(const MyStringIterator& other) {
        if (this != &other) {
            m_ptr = other.m_ptr;
        }
        return *this;
    }

    value_type operator[](int index)  {
        return *(m_ptr + index);
    }

    pointer operator->() {
        return m_ptr;
    }

    reference operator*() {
        return *m_ptr;
    }

    bool operator==(const MyStringIterator& other) const {
        return m_ptr == other.m_ptr;
    }

    bool operator!=(const MyStringIterator& other) const {
        return m_ptr != other.m_ptr;
    }

    auto operator<=>(const MyStringIterator& other) const {
        return m_ptr <=> other.m_ptr;
    }


};



#endif //MYSTRINGITERATOR_H
