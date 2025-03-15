//
// Created by Lenovo on 2025-03-11.
//

#include "MyString.h"

#include <cfloat>

void MyString::Realloc(const size_t capacity) {

    if (capacity == m_capacity) return;

    if (capacity < m_size) {
        ::operator delete[](m_data + capacity, m_data + m_size);
        m_size = capacity - 1;
        m_capacity = capacity;
        return;
    }

    auto new_chunk = static_cast<char *>(::operator new(capacity * sizeof(char)));

    if (m_data != nullptr) {
        for (size_t i = 0; i < m_size; i++) {
            new_chunk[i] = m_data[i];
        }
    }

    ::operator delete[](m_data, m_capacity * sizeof(char));
    m_data = new_chunk;
    m_capacity = capacity;
}

void MyString::push_back(const char& ch) {
    if (ch == '\0') throw std::invalid_argument("Character must not be null");
    if (m_size + 1 == m_capacity) {
        Realloc(m_size * 2 + 2);
    }
    m_size++;
    m_data[m_size - 1] = ch;
    m_data[m_size] = '\0';
}

void MyString::pop_back() {
    if (m_size == 0) return;
    m_size--;
    m_data[m_size] = '\0';
}

// size_t MyString::find(const MyString &substr, size_t pos) {
//
// }


MyString& MyString::operator=(const MyString& str) {
    if (this == &str) return *this;
    Realloc(str.m_capacity);
    for (size_t i = 0; i < str.m_size; i++) {
        this->m_data[i] = str.m_data[i];
    }
    this->m_size = str.m_size;
    this->m_data[this->m_size] = '\0';
    return *this;
}

MyString &MyString::operator=(MyString &&str)  noexcept {
    m_data = str.m_data;
    m_size = str.m_size;
    m_capacity = str.m_capacity;

    str.m_data = nullptr;
    str.m_size = 0;
    str.m_capacity = 1;

    return *this;
}

size_t MyString::insert(size_t pos, char ch) {
    if (ch == '\0') ch = ' ';
    if (m_size == 0) return pos;
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
    m_data[m_size] = '\0';
    return pos;
}

size_t MyString::insert(size_t pos, const MyString &substr) {
    if (m_size == 0) return pos;
    if (pos > this->m_size) {
        throw std::out_of_range("Index out of range");
    }
    if ((this->m_size + substr.m_size) >= this->m_capacity) {
        Realloc(this->m_size + substr.m_size * 2);
    }

    for(size_t i = pos; i < this->m_size; i++) {
        this->m_data[this->m_size + i + 1] = this->m_data[i];
    }

    for (size_t i = 0; i < substr.m_size; i++) {
        this->m_data[i + pos] = substr.m_data[i];
    }
    this->m_size += substr.m_size;
    this->m_data[this->m_size] = '\0';
    return pos;
}

size_t MyString::erase(size_t pos) {
    if (m_size == 0) return pos;
    if (pos > m_size - 1)
        throw std::out_of_range("Pos out of range");
    size_t it = m_size - 1;
    while(it >= pos) {
        std::swap(m_data[m_size - 1], m_data[it]);
        if (it == 0) break;
        it--;
    }
    m_size--;
    m_data[m_size] = '\0';

    return pos;
}

size_t MyString::erase(const size_t pos, size_t count) {
    if ((pos + count) > m_size - 1)
        count = m_size - pos;
    size_t it = 0;
    while (m_data[pos + count + it] != '\0') {
        m_data[pos + it] = m_data[pos + count + it];
        it++;
    }
    while (m_data[pos + it] != '\0') {
        m_data[pos + it] = '\0';
        it++;
    }
    m_size -= count;
    m_data[m_size] = '\0';
    return pos;
}

int MyString::compare(const MyString &str) const  {
    size_t it = 0;
    while (m_data[it] != '\0' && str.m_data[it] != '\0') {
        if (m_data[it] < str.m_data[it]) {
            return -1;
        }
        if( m_data[it] != str.m_data[it]) {
            return 1;
        }
        it++;
    }
    if (m_data[it] != '\0' && str.m_data[it] == '\0') return 1;
    if (m_data[it] == str.m_data[it] && m_data[it] == '\0') return 0;
    return -1;
}



MyString &MyString::operator+=(const MyString &str) {
    MyString::insert(m_size, str);
    return *this;
}

int stoi_(const MyString &str, int base = 10) {
    if (base > 36 || base < 2) throw std::invalid_argument("Invalid base param");
    if (str.empty()) {
        throw std::invalid_argument("String must not be null");
    }
    int sign = 1, n = 0;
    char* ptr = str.m_data;

    if (*ptr == '-') {sign = -1; ptr++;}
    int d_ascii_ = base - 10;
    while (*ptr != '\0') {
        if (*ptr == '.') return n * sign;
        int ascii_ = *ptr - '0';
        if (ascii_ > 16) ascii_ -= 7;
        if (!((ascii_ > -1 && ascii_ < 10 + d_ascii_) || (ascii_ > 16 && ascii_ < (17 + d_ascii_)))) {
            throw std::invalid_argument("Invalid literal for that base");
        }
        if (INT_MAX / base < n) throw std::out_of_range("Number is too big for int");
        n = n * base + ascii_;
        ptr++;
    }
    return n * sign;
}

int stoll_(const MyString &str, int base = 10) {
    if (base > 36 || base < 2) throw std::invalid_argument("Invalid base param");
    if (str.empty()) {
        throw std::invalid_argument("String must not be null");
    }
    int sign = 1;
    long long n = 0;
    char* ptr = str.m_data;

    if (*ptr == '-') {sign = -1; ptr++;}
    int d_ascii_ = base - 10;
    while (*ptr != '\0') {
        if (*ptr == '.') return n * sign;
        int ascii_ = *ptr - '0';
        if (ascii_ > 16) ascii_ -= 7;
        if (!((ascii_ > -1 && ascii_ < 10 + d_ascii_) || (ascii_ > 16 && ascii_ < (17 + d_ascii_)))) {
            throw std::invalid_argument("Invalid literal for that base");
        }
        if (LONG_LONG_MAX / base < n) throw std::out_of_range("Number is too big for long long");
        n = n * base + ascii_;
        ptr++;
    }
    return n * sign;
}

double stod_(const MyString &str, int base = 10) {
    if (base > 36 || base < 2) throw std::invalid_argument("Invalid base param");
    if (str.empty()) {
        throw std::invalid_argument("String must not be null");
    }
    int sign = 1, p_index = 0;
    double n = 0;
    double d_n = 0;

    char* ptr = str.m_data;

    if (*ptr == '-') {sign = -1; ptr++;}
    int d_ascii_ = base - 10;
    while (*ptr != '\0') {
        if (*ptr != '.') p_index++;
        if (*ptr == '.') break;
        int ascii_ = *ptr - '0';
        if (ascii_ > 16) ascii_ -= 7;
        if (!((ascii_ > -1 && ascii_ < 10 + d_ascii_) || (ascii_ > 16 && ascii_ < (17 + d_ascii_)))) {
            throw std::invalid_argument("Invalid literal for that base");
        }
        if (DBL_MAX / base < n) throw std::out_of_range("Number is too big for double");
        n = n * base + ascii_;
        ptr++;
    }

    for (size_t i = str.m_size - 1; i + 1> p_index; i--) {
        if (str.m_data[i] == '.' && i == p_index)  {break;}
        if (str.m_data[i] == '.' && i != p_index) {continue;}
        int ascii_ = str.m_data[i] - '0';
        if (ascii_ > 16) ascii_ -= 7;
        if (!((ascii_ > -1 && ascii_ < 10 + d_ascii_) || (ascii_ > 16 && ascii_ < (17 + d_ascii_)))) {
            throw std::invalid_argument("Invalid literal for that base");
        }
        d_n = d_n / base + ascii_;
    }

    d_n /= base;
    double res = sign * (n + d_n);
    return res;
}