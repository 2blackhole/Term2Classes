#include <iostream>
#include "ArithmVectorN.h"

int main() {
    double initialValues1[10] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0};
    double initialValues2[10] = {10.0, 9.0, 8.0, 7.0, 6.0, 5.0, 4.0, 3.0, 2.0, 1.0};

    ArithmVectorN vec1(initialValues1);
    ArithmVectorN vec2(initialValues2);

    ArithmVectorN vec3;
    vec3 = vec1; // Use assignment operator
    std::cout << "vec3 after assignment: " << vec3 << std::endl;

    vec1[0] = 100.0;
    std::cout << "vec1 after modification: " << vec1 << std::endl;
    std::cout << "vec3 remains unchanged: " << vec3 << std::endl;

    ArithmVectorN vec4 = vec1 + vec2;
    ArithmVectorN vec5 = vec1 - vec2;
    ArithmVectorN vec6 = vec1 * 2.0;
    ArithmVectorN vec7 = vec1 / 2.0;

    std::cout << "vec1 + vec2: " << vec4 << std::endl;
    std::cout << "vec1 - vec2: " << vec5 << std::endl;
    std::cout << "vec1 * 2: " << vec6 << std::endl;
    std::cout << "vec1 / 2: " << vec7 << std::endl;

    std::cout << "Dot product of vec1 and vec2: " << vec1.getDot(vec2) << std::endl;
    std::cout << "Magnitude of vec1: " << vec1.getAbs() << std::endl;

    return 0;
}
