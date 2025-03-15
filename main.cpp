#include <iomanip>
#include <iostream>
#include "MyString.h"
#include <string>


int main() {
    MyString str1("BSDF.A");
    double ans = stod_(str1, 36);
    std::cout << std::setprecision(16) << ans;
}