cmake_minimum_required(VERSION 3.29)
project(norm)

set(CMAKE_CXX_STANDARD 20)

add_executable(Term2Classes
        complex.h
        main.cpp
        ArithmVectorN.cpp
        ArithmVectorN.h
        VeryUsefulAllocator.cpp
        VeryUsefulAllocator.h
        MyString.h
        MyString.cpp
        MyStringIterator.cpp
        MyStringIterator.h
        #VectorBananov.cpp
        VectorBananov.h
        VecIterator.h
)
