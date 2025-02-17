#include <iostream>
#include "ArithmVectorN.h"

int main() {
    double initVal[10] = {1, 3, 4, 5, 1, 3, 4, 1, 9, 14};
    ArithmVectorN vec1(initVal);
    std::cout << vec1;
}
