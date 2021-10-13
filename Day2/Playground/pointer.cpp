#include <iostream>

int main() {
    int a = 7, b, *p = new int, *p1;

    p1 = &a;

    std::cout << p <<std::endl;
    std::cout << p1 <<std::endl;

    return 0;
}