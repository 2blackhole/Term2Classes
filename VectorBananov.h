//
// Created by Lenovo on 2025-03-17.
//

#ifndef VECTORBANANOV_H
#define VECTORBANANOV_H
#include <iostream>
#include "VecIterator.h"

template <typename T>
class VectorBananov {
public:
    using value_type = T;
    using pointer_type = T*;
    using reference_type = T&;
    using Iterator = VecIterator<VectorBananov<T>>;

    void Realloc(size_t capacity) {

        if (capacity == m_capacity) return;

        if (capacity < m_size) {
            ::operator delete[](m_data + m_size, m_data + m_capacity);
            m_size = capacity - 1;
            m_capacity = capacity;
            return;
        }

        auto new_chunk = static_cast<pointer_type>(::operator new(capacity * sizeof(value_type)));

        if (m_data != nullptr) {
            for (size_t i = 0; i < m_size; i++) {
                new_chunk[i] = m_data[i];
            }
        }

        ::operator delete[](m_data, m_capacity * sizeof(value_type));
        m_data = new_chunk;
        m_capacity = capacity;
    }


private:
    pointer_type m_data = nullptr;
    size_t m_size = 0;
    size_t m_capacity = 0;

public:
    VectorBananov() = default;

    VectorBananov(std::initializer_list<T> init_list) {
        Realloc(init_list.size() * 2 + 2);
        m_size = init_list.size();
        if (m_size > 0) {
            std::copy(init_list.begin(), init_list.end(), m_data);
        }
    }

    VectorBananov(size_t size, value_type init_value) {
        Realloc(size * 2 + 2);
        m_size = size;
        for (size_t i = 0; i < m_size; i++) {
            m_data[i] = init_value;
        }
    }

    VectorBananov(pointer_type start, pointer_type end) {
        if (start > end) throw std::invalid_argument("The start pointer must be before the end pointer");
        m_size = end - start;
        Realloc((end - start) * 2);
        for (size_t i = 0; i < m_size; i++) {
            m_data[i] = *start++;
        }
    }

    VectorBananov(Iterator start, Iterator end) {
        if (start > end) throw std::invalid_argument("The start pointer must be before the end pointer");
        m_size = end - start;
        Realloc((end - start) * 2);
        for (size_t i = 0; i < m_size; i++) {
            m_data[i] = *start++;
        }
    }

    VectorBananov(const VectorBananov& other) {
        if (other.m_data == nullptr) return;
        Realloc(other.m_capacity);
        m_size = other.m_size;
        for (size_t i = 0; i < m_size; i++) {
            m_data[i] = other.m_data[i];
        }
    }

    VectorBananov(VectorBananov&& other)  noexcept : m_data(other.m_data), m_size(other.m_size), m_capacity(other.m_capacity){
        other.m_data = nullptr;
        other.m_size = 0;
        other.m_capacity = 0;
    }

    VectorBananov& operator=(const VectorBananov& other) {
        if (this == &other) return *this;
        Realloc(other.m_capacity);
        for (size_t i = 0; i < other.m_size; i++) {
            this->m_data[i] = other.m_data[i];
        }
        this->m_size = other.m_size;
        this->m_data[this->m_size] = '\0';
        return *this;
    }

    VectorBananov& operator=(VectorBananov &&other)  noexcept {
        m_data = other.m_data;
        m_size = other.m_size;
        m_capacity = other.m_capacity;

        other.m_data = nullptr;
        other.m_size = 0;
        other.m_capacity = 1;

        return *this;
    }

    ~VectorBananov() {
        ::operator delete[](m_data, m_capacity * sizeof(T));
    }

    Iterator begin() {
        return Iterator(m_data);
    }

    Iterator end() {
        return Iterator(m_data + m_size);
    }

    reference_type operator[](size_t index) {
        return m_data[index];
    };
    value_type operator[](size_t index) const {
        return m_data[index];
    }

    // element access with bound checking
    reference_type at(size_t index) {
        if (index >= m_size) {
            throw std::out_of_range("Index out of range :)");
        }
        return m_data[index];
    }
    value_type at(size_t index) const {
        if (index >= m_size) {
            throw std::out_of_range("Index out of range :)");
        }
        return m_data[index];
    }

    // raw data access
    const pointer_type c_str() const {return m_data;}
    pointer_type data() {return m_data;}
    const pointer_type data() const {return m_data;}

    // auxiliary
    bool empty() const {
        if (m_size == 0) return true;
        return false;
    }

    size_t size() const {
        return m_size;
    }

    size_t capacity() const {
        return m_capacity;
    }

    size_t insert(size_t pos, value_type ch) {
        if (pos > m_size) {
            throw std::out_of_range("Index out of range");
        }
        if (m_size + 1 == m_capacity) {
            Realloc(m_size * 2 + 2);
        }
        m_size++;
        m_data[m_size - 1] = ch;
        for(size_t i = pos; i < m_size; i++) {
            std::swap(m_data[pos], m_data[i]);
        }
        return pos;
    }

    size_t insert(size_t pos, const VectorBananov &other) {
        if (pos > m_size) {
            throw std::out_of_range("Index out of range");
        }

        const size_t required_size = m_size + other.m_size;

        if (required_size >= m_capacity) {
            Realloc(required_size * 2 + 1);
        }

        for (size_t i = m_size; i > pos; --i) {
            m_data[i + other.m_size - 1] = m_data[i - 1];
        }

        for (size_t i = 0; i < other.m_size; ++i) {
            m_data[pos + i] = other.m_data[i];
        }

        m_size += other.m_size;
        return pos;
    }

    Iterator insert(Iterator pos, const VectorBananov& other) {
        if (begin() > pos || pos > end()) throw std::out_of_range("Index out of range");
        insert(pos - begin(), other);
        return pos;
    }

    Iterator insert(Iterator it, value_type ch) {
        if (begin() > it || it > end()) throw std::out_of_range("Index out of range");
        size_t pos = it - begin();
        insert(pos, ch);
        return it;
    }

    size_t erase(size_t pos) {
        if (m_size == 0) throw std::invalid_argument("Vector must not be null");
        if (pos > m_size - 1)
            throw std::out_of_range("Pos out of range");
        size_t it = m_size - 1;
        while(it >= pos) {
            std::swap(m_data[m_size - 1], m_data[it]);
            if (it == 0) break;
            it--;
        }
        m_size--;
        return pos;
    }

    size_t erase(size_t pos, size_t count) {
        if (m_size == 0) {
            throw std::invalid_argument("String is empty");
        }
        if (pos >= m_size) {
            throw std::out_of_range("Position out of range");
        }
        if (count == 0 || pos + count > m_size) {
            count = m_size - pos;
        }
        for (size_t i = pos; i < m_size - count; ++i) {
            m_data[i] = m_data[i + count];
        }
        m_size -= count;
        return pos;
    }

    Iterator erase(Iterator st, Iterator e) {
        if (st > e) throw std::invalid_argument("start must be before than end");
        if (begin() > st || st > end()) throw std::out_of_range("Index out of range");
        size_t count = e - st;
        size_t pos = st - begin();
        erase(pos, count);
        return st;
    }

    Iterator erase(Iterator iter) {
        if (begin() > iter || iter > end()) throw std::out_of_range("Index out of range");
        size_t pos = iter - begin();
        erase(pos);
        return iter;
    }

    void push_back(value_type&& ch) {
        if (m_size + 1 == m_capacity) {
            Realloc(m_size * 2 + 2);
        }
        m_data[m_size] = ch;
        m_size++;
    }

    bool empty() {
        return m_size == 0;
    }

    void push_back(const reference_type ch) {
        if (m_size + 1 == m_capacity) {
            Realloc(m_size * 2 + 2);
        }
        m_data[m_size] = ch;
        m_size++;
    }

    void pop_back() {
        if (m_size == 0) return;
        m_size--;
    }

    void swap(VectorBananov& other) noexcept {
        std::swap(other.m_data, m_data);
        std::swap(other.m_size, m_size);
        std::swap(other.m_capacity, m_capacity);
    }

    void clear() {
        m_size = 0;
    }

    void resize(size_t count) {
        m_size = count;
    }

    // void delete_VectorBananov();
    friend std::ostream& operator<<(std::ostream& out, const VectorBananov& vec) {
        if (vec.m_size == 0) {
            out << "[ ]";
            return out;
        }
        out << "[ ";
        for (size_t i = 0; i < vec.size() - 1; i++) {
            out << vec[i] << ", ";
        }
        out << vec[vec.size() - 1] << " ]";
        return out;
    }
};



#endif //VECTORBANANOV_H
