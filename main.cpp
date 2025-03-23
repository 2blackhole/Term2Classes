#include <iomanip>
#include <iostream>
#include <string>
#include <cmath>
#include "MyString.h"
#include "VectorBananov.h"

std::string formatResult(size_t result, size_t expected) {
    if (result == MyString::npos && expected == MyString::npos) return "npos";
    if (result == MyString::npos) return "npos (expected: " + std::to_string(expected) + ")";
    return std::to_string(result) + (result == expected ? "" : " (expected: " + std::to_string(expected) + ")");
}

void testFind() {
    std::cout << "\n=== Testing find ===\n";
    // Тест 1: Подстрока начинается ровно с pos
    MyString str1("hello world");
    MyString substr1("world");
    size_t res1 = str1.find(substr1, 6);
    std::cout << "[Test 1] Result: " << formatResult(res1, 6)
              << " - " << (res1 == 6 ? "OK" : "FAIL") << "\n";

    // Тест 2: Поиск после первого вхождения
    MyString str2("ababab");
    MyString substr2("ab");
    size_t res2 = str2.find(substr2, 2);
    std::cout << "[Test 2] Result: " << formatResult(res2, 2)
              << " - " << (res2 == 2 ? "OK" : "FAIL") << "\n";

    // Тест 3: Подстрока отсутствует
    MyString str3("test");
    MyString substr3("xyz");
    size_t res3 = str3.find(substr3, 0);
    std::cout << "[Test 3] Result: " << formatResult(res3, MyString::npos)
              << " - " << (res3 == MyString::npos ? "OK" : "FAIL") << "\n";

    // Тест 4: Пустая подстрока (корректный pos)
    MyString str4("example");
    MyString substr4("");
    size_t res4 = str4.find(substr4, 3);
    std::cout << "[Test 4] Result: " << formatResult(res4, MyString::npos)
              << " - " << (res4 == MyString::npos ? "OK" : "FAIL") << "\n";

    // Тест 5: Пустая подстрока (pos за пределами)
    size_t res5 = str4.find(substr4, 10);
    std::cout << "[Test 5] Result: " << formatResult(res5, MyString::npos)
              << " - " << (res5 == MyString::npos ? "OK" : "FAIL") << "\n";

    // Тест 6: Пустая исходная строка
    MyString str6("");
    MyString substr6("abc");
    size_t res6 = str6.find(substr6, 0);
    std::cout << "[Test 6] Result: " << formatResult(res6, MyString::npos)
              << " - " << (res6 == MyString::npos ? "OK" : "FAIL") << "\n";

    // Тест 7: Обе строки пусты
    MyString substr7("");
    size_t res7 = str6.find(substr7, 0);
    std::cout << "[Test 7] Result: " << formatResult(res7, 0)
              << " - " << (res7 == 0 ? "OK" : "FAIL") << "\n";

    // Тест 8: Подстрока длиннее исходной
    MyString str8("hi");
    MyString substr8("hello");
    size_t res8 = str8.find(substr8, 0);
    std::cout << "[Test 8] Result: " << formatResult(res8, MyString::npos)
              << " - " << (res8 == MyString::npos ? "OK" : "FAIL") << "\n";

    // Тест 9: Поиск внутри частичного совпадения
    MyString str9("abcabc");
    MyString substr9("abc");
    size_t res9 = str9.find(substr9, 1);
    std::cout << "[Test 9] Result: " << formatResult(res9, 3)
              << " - " << (res9 == 3 ? "OK" : "FAIL") << "\n";

    // Тест 10: Спецсимволы
    MyString str10("a\nb\tc");
    MyString substr10("\n");
    size_t res10 = str10.find(substr10, 0);
    std::cout << "[Test 10] Result: " << formatResult(res10, 1)
              << " - " << (res10 == 1 ? "OK" : "FAIL") << "\n";

    // Тест 11: Чувствительность к регистру
    MyString str11("CaseSensitive");
    MyString substr11("case");
    size_t res11 = str11.find(substr11, 0);
    std::cout << "[Test 11] Result: " << formatResult(res11, MyString::npos)
              << " - " << (res11 == MyString::npos ? "OK" : "FAIL") << "\n";
}

bool almostEqual(double a, double b, double epsilon = 1e-6) {
    return std::abs(a - b) < epsilon;
}

template <typename T>
std::string formatResult(T result, T expected) {
    if constexpr (std::is_same_v<T, double>) {
        return std::to_string(result) + (almostEqual(result, expected) ? "" : " (expected: " + std::to_string(expected) + ")");
    } else {
        return std::to_string(result) + (result == expected ? "" : " (expected: " + std::to_string(expected) + ")");
    }
}

void testConversions() {
    // Тесты для stoi_
    std::cout << "=== Testing stoi_ ===\n";
    MyString strInt1("123");
    int resInt1 = stoi_(strInt1, 10);
    std::cout << "[Test 1] stoi_('123', 10): " << formatResult(resInt1, 123)
              << " - " << (resInt1 == 123 ? "OK" : "FAIL") << "\n";

    MyString strInt2("-FF");
    int resInt2 = stoi_(strInt2, 16);
    std::cout << "[Test 2] stoi_('-FF', 16): " << formatResult(resInt2, -255)
              << " - " << (resInt2 == -255 ? "OK" : "FAIL") << "\n";

    MyString strInt3("1010");
    int resInt3 = stoi_(strInt3, 2);
    std::cout << "[Test 3] stoi_('1010', 2): " << formatResult(resInt3, 10)
              << " - " << (resInt3 == 10 ? "OK" : "FAIL") << "\n";


    // Тесты для stoll_
    std::cout << "\n=== Testing stoll_ ===\n";
    MyString strLL1("123456789012");
    long long resLL1 = stoll_(strLL1, 10);
    std::cout << "[Test 4] stoll_('123456789012', 10): " << formatResult(resLL1, 123456789012LL)
              << " - " << (resLL1 == 123456789012LL ? "OK" : "FAIL") << "\n";

    MyString strLL2("1A3F");
    long long resLL2 = stoll_(strLL2, 16);
    std::cout << "[Test 5] stoll_('1A3F', 16): " << formatResult(resLL2, 6719LL)
              << " - " << (resLL2 == 6719LL ? "OK" : "FAIL") << "\n";

    MyString strLL3("   -42");
    long long resLL3 = stoll_(strLL3, 10);
    std::cout << "[Test 6] stoll_('   -42', 10): " << formatResult(resLL3, -42LL)
              << " - " << (resLL3 == -42LL ? "OK" : "FAIL") << "\n";

    // Тесты для stod_
    std::cout << "\n=== Testing stod_ ===\n";
    MyString strDouble1("3.1415");
    double resDouble1 = stod_(strDouble1, 10);
    std::cout << "[Test 7] stod_('3.1415', 10): " << formatResult(resDouble1, 3.1415)
              << " - " << (almostEqual(resDouble1, 3.1415) ? "OK" : "FAIL") << "\n";

    MyString strDouble2("-12.34");
    double resDouble2 = stod_(strDouble2, 10);
    std::cout << "[Test 8] stod_('-12.34', 10): " << formatResult(resDouble2, -12.34)
              << " - " << (almostEqual(resDouble2, -12.34) ? "OK" : "FAIL") << "\n";

    MyString strDouble3("1010.11");
    double resDouble3 = stod_(strDouble3, 2);

    std::cout << "[Test 9] stod_('1010.11', 2): " << formatResult(resDouble3, 10.75)
              << " - " << (almostEqual(resDouble3, 10.75) ? "OK" : "FAIL") << "\n";

}

void testIterator() {
    // ITERATOR USE
    std::cout <<"\n=== Testing Iterator ===\n";
    MyString str_1("banana");
    std::cout << "\nRange based loop:\n";
    for (char symb : str_1) {
        std::cout << symb;
    }
    std::cout << '\n';
    std::cout << "\nfor loop with iterator based loop:\n";
    for (MyString::Iterator it = str_1.begin(); it != str_1.end(); ++it) {
        std::cout << *it;
    }
    std::cout << "\n";
}

void testBase() {
        std::cout << "\n== Base func ==\n";
    MyString str_0;
    MyString str_1("banana");
    MyString str_2(5, 'c');

    MyString str_3 = str_1;

    std::cout << "String : "<<  str_0 << " \nSize: " << str_0.size() << " \nCapacity : " << str_0.capacity() << "\n";
    std::cout << "String : "<<  str_1 << " \nSize: " << str_1.size() << " \nCapacity : " << str_1.capacity() << "\n";
    std::cout << "String : "<<  str_2 << " \nSize: " << str_2.size() << " \nCapacity : " << str_2.capacity() << "\n";

    std::cout << "\n** Empty **\n";

    std::cout << (str_0.empty() ? "str_0 it empty" : "str_0 isn't empty");
    std::cout << "\n";
    std::cout << (str_1.empty() ? "str_1 it empty" : "str_1 isn't empty");
    std::cout << "\n";
    std::cout << "\n** Push back **\n";
    std::cout << "str_1 do : " << str_1 << " \nSize: " << str_1.size() << " \nCapacity : " << str_1.capacity() <<"\n";
    str_1.push_back('?');
    std::cout << "str_1 posle : " << str_1 << " \nSize: " << str_1.size() << " \nCapacity : " << str_1.capacity() <<"\n";

    std::cout << "\n** insert into end substring \"_XXX_pomidori_XXX_\"**\n";
    std::cout << "str_1 do : " << str_1 << " \nSize: " << str_1.size() << " \nCapacity : " << str_1.capacity() <<"\n";
    MyString substr("_XXX_pomidori_XXX_");
    str_1.insert(str_1.size(), substr);
    std::cout << "str_1 posle : " << str_1 << " \nSize: " << str_1.size() << " \nCapacity : " << str_1.capacity() <<"\n";

    std::cout << "\n** insert v dva substring \"_XXX_pomidori_XXX_\"**\n";
    std::cout << "str_1 do : " << str_1 << " \nSize: " << str_1.size() << " \nCapacity : " << str_1.capacity() <<"\n";
    MyString substr_another("_XXX_pomidori_XXX_");
    str_1.insert(2, substr);
    std::cout << "str_1 posle : " << str_1 << " \nSize: " << str_1.size() << " \nCapacity : " << str_1.capacity() <<"\n";


    std::cout << "\n** erase from size - 18 substring with length  18**\n";
    std::cout << "str_1 do : " << str_1 << " \nSize: " << str_1.size() << " \nCapacity : " << str_1.capacity() <<"\n";
    str_1.erase(str_1.size() - 18, 18);
    std::cout << "str_1 posle : " << str_1 << " \nSize: " << str_1.size() << " \nCapacity : " << str_1.capacity() <<"\n";

    std::cout << "\n** erase from v dva substring with length 18**\n";
    std::cout << "str_1 do : " << str_1 << " \nSize: " << str_1.size() << " \nCapacity : " << str_1.capacity() <<"\n";
    str_1.erase(2, 18);
    std::cout << "str_1 posle : " << str_1 << " \nSize: " << str_1.size() << " \nCapacity : " << str_1.capacity() <<"\n";

    std::cout << "\n** compare **\n";
    MyString str1 ("green apple");
    MyString str2("red apple");

    if (str1.compare(str2) != 0)
        std::cout << str1 << " is not " << str2 << '\n';

    std::cout << "\n** to_string func **\n";
    std::cout << "n = -87441:\n";
    MyString res;
    int num = -87441;
    res = to_string_(num);
    std::cout << res << "\n";

    std::cout << "\n** reverse func **\n";
    std::cout << "String : pomidori \n";
    MyString norm("pomidori");
    norm.reverse();
    std::cout <<"Result : " << norm;

}



int main() {
    // MyString str("12.5.A");
    // MyString str2("12.5.A");
    //
    // MyString str3 = str + str2;
    // std::cout << str3;
    // testBase();
    // testIterator();
    // testConversions();
    // testFind();
    //
    VectorBananov<int> pomidorik = {1, 3, 23, 3};
    std::cout << "\nSize : " << pomidorik.size() << " Capacity: " << pomidorik.capacity() << "\n";
    std::cout << "\n" << pomidorik << "\n";

    pomidorik.push_back(1);
    std::cout << "\nSize : " << pomidorik.size() << " Capacity: " << pomidorik.capacity() << "\n";
    std::cout << "\n" << pomidorik << "\n";

    pomidorik.pop_back();
    std::cout << "\nSize : " << pomidorik.size() << " Capacity: " << pomidorik.capacity() << "\n";
    std::cout << "\n" << pomidorik << "\n";

    VectorBananov<char> pomidorik2 = {'1', 'f', 'c'};
    std::cout << "\nSize : " << pomidorik2.size() << " Capacity: " << pomidorik2.capacity() << "\n";
    std::cout << "\n" << pomidorik2 << "\n";

    pomidorik2.push_back('b');
    std::cout << "\nSize : " << pomidorik2.size() << " Capacity: " << pomidorik2.capacity() << "\n";
    std::cout << "\n" << pomidorik2 << "\n";

    pomidorik2.pop_back();
    std::cout << "\nSize : " << pomidorik2.size() << " Capacity: " << pomidorik2.capacity() << "\n";
    std::cout << "\n" << pomidorik2 << "\n";

    std::string pormizan = "a vse idet po planu";
    VectorBananov<char> na_pole_tanki_grohotali(pormizan.data(), pormizan.data() + pormizan.size());
    std::cout << na_pole_tanki_grohotali;

    VectorBananov<char> pomidor(na_pole_tanki_grohotali.begin(), na_pole_tanki_grohotali.end());
    std::cout << "\n" << pomidor;

    pomidorik2 = pomidor;
    std::cout << "\n" << pomidorik2;

    VectorBananov<char> ay_carumba = pomidor;
    pomidorik2 = std::move(ay_carumba);
    std::cout << "\n" << pomidorik2;

    pomidorik2.insert(pomidorik2.begin(), 'f');
    pomidorik2.erase(pomidorik2.begin() + 1);

    std::cout << "\nSize : " << pomidorik2.size() << " Capacity: " << pomidorik2.capacity() << "\n";
    std::cout << "\n" << pomidorik2 << "\n";

    pomidorik2.clear();
    std::cout << "\nSize : " << pomidorik2.size() << " Capacity: " << pomidorik2.capacity() << "\n";
    std::cout << "\n" << pomidorik2 << "\n";
    pomidorik2.push_back('f');
    std::cout << "\nSize : " << pomidorik2.size() << " Capacity: " << pomidorik2.capacity() << "\n";
    std::cout << "\n" << pomidorik2 << "\n";

    pomidorik2.insert(pomidorik2.begin() + 1, na_pole_tanki_grohotali);
    std::cout << "\nSize : " << pomidorik2.size() << " Capacity: " << pomidorik2.capacity() << "\n";
    std::cout << "\n" << pomidorik2 << "\n";

    pomidorik2.erase(4, 3);
    std::cout << "\nSize : " << pomidorik2.size() << " Capacity: " << pomidorik2.capacity() << "\n";
    std::cout << "\n" << pomidorik2 << "\n";

    pomidorik2.erase(pomidorik2.begin(), pomidorik2.end());
    std::cout << "\nSize : " << pomidorik2.size() << " Capacity: " << pomidorik2.capacity() << "\n";
    std::cout << "\n" << pomidorik2 << "\n";
    return 0;
}
