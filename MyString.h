#pragma once
#include <iostream>
#include <vector>
#include "MyStringIterator.h"

class MyString {
    char* m_data = nullptr;
    size_t m_size = 0;
    size_t m_capacity = 0;


    void Realloc(size_t capacity);

public:
    using Iterator = MyStringIterator;

    static const size_t npos = -1;

    Iterator begin() {
        return {m_data};
    }

    Iterator end() {
        return {m_data + m_capacity};
    }

    // constructors
    MyString() {
        Realloc(1);
        m_data[0] = '\0';
    }


    MyString(size_t count, char ch) {
        Realloc(count + 1);
        m_size = count;
        for (size_t i = 0; i < m_size; i++) {
            m_data[i] = ch;
        }
        m_data[m_size] = '\0';
    }

    MyString(const MyString& str) {
        if (str.m_data == nullptr) return;
        Realloc(str.m_capacity);
        m_size = str.m_size;
        for (size_t i = 0; i < m_size; i++) {
            m_data[i] = str.m_data[i];
        }
        m_data[m_size] = '\0';
    }

    explicit MyString(const char* str) {
        size_t str_size = 0;
        while (*(str + ++str_size) != '\0') {}
        m_size = str_size;
        Realloc(m_size + 1);
        for (size_t i = 0; i < m_size; i++) {
            m_data[i] = str[i];
        }
        m_data[m_size] = '\0';
    }

    MyString(MyString&& str)  noexcept : m_data(str.m_data), m_size(str.m_size), m_capacity(str.m_capacity){
        str.m_data = nullptr;
        str.m_size = 0;
        str.m_capacity = 1;
    }

    ~MyString() {
        ::operator delete[](m_data, m_capacity * sizeof(char));
    }
    
    // element access without bound checking
    char& operator[](size_t index) {
        return m_data[index];
    };
    char operator[](size_t index) const {
        return m_data[index];
    }

    // element access with bound checking
    char& at(size_t index) {
        if (index >= m_size) {
            throw std::out_of_range("Index out of range :)");
        }
        return m_data[index];
    }
    char at(size_t index) const {
        if (index >= m_size) {
            throw std::out_of_range("Index out of range :)");
        }
        return m_data[index];
    }
    
    // raw data access
    const char* c_str() const {return m_data;}
    char* data() {return m_data;}
    const char* data() const {return m_data;}
    
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

    void print() const {
        for (size_t i = 0; i < m_size; i++) {
            std::cout << m_data[i];
        }
    }

    // modifiers
    void clear() {
        for (size_t i = 0; i < m_size; i++) {
            m_data[i] = '\0';
        }
        m_size = 0;
    };

    void resize(size_t count) {
        Realloc(count + 1);
        m_data[m_size] = '\0';
    };
    size_t insert(size_t pos, char ch);  // aaa, insert(2, 'b') => aaba, return pos
    size_t insert(size_t pos, const MyString& substr); // aaa, insert(2, "bc") => aabca
    size_t erase(size_t pos);  // aaba, erase(2) => aaa
    size_t erase(size_t pos, size_t count);

    void push_back(const char& ch);

    void pop_back();  // erase from the end
    // concatenation, "aaa" + "bb" => "aaabb"
    MyString& operator+=(const MyString& str);
    
    // search
    size_t find(const MyString& substr, size_t pos = 0) const;  //KMP realization

    MyString& operator=(const MyString& str);
    MyString& operator=(MyString&& str) noexcept ;

    int compare(const MyString& str) const;

    bool operator==(const MyString& str) const {
        if (compare(str) == 0) return true;
        return false;
    }
    bool operator!=(const MyString& str) const {
        return !operator==(str);
    }
    bool operator<(const MyString& str) const {
        if (compare(str) == -1) return true;
        return false;
    }
    bool operator>(const MyString& str) const {
        if (compare(str) == 1) return true;
        return false;
    }
    bool operator<=(const MyString& str) const {
        if (compare(str) <= 0) return true;
        return false;
    }
    bool operator>=(const MyString& str) const {
        if (compare(str) >= 0) return true;
        return false;
    }


    friend std::ostream& operator<<(std::ostream& out, const MyString& str) {
        for (size_t i = 0; i < str.size(); i++) {
            out << str[i];
        }
        return out;
    }

    friend int stoi_(const MyString& str, int base);
    friend long long stoll_(const MyString& str, int base);
    friend double stod_(const MyString& str, int base);

    template <typename T>
    friend MyString to_string(T n);
};


MyString operator+(const MyString &str1, const MyString &str2);



std::vector<int> prefix_function(const MyString& str);


