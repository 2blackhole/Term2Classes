#include <iostream>
#include "complex.h"

int main() {
    Complex a(3, 0);
    Complex b(4);
    bool c = a != b;
    std::cout << c;
}
