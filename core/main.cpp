#include <utils/casts.h>
#include <iostream>

using namespace manticore::utils;

struct test {
    int ival;
    std::string sval;

    test(int i, std::string const &s) : ival(i), sval(s) {}

    int ToInt() const { return ival; }
    std::string ToString() const { return sval; }
};

int main() {
    test a(1, "1"), b(2, "2"), c(3, "3");

    std::cout << case_cast(a) << " : " << string_cast(a) << std::endl;
    std::cout << case_cast(b) << " : " << string_cast(b) << std::endl;
    std::cout << case_cast(c) << " : " << string_cast(c) << std::endl;

    return 0;
}
