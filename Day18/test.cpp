#include <iostream>

const int g = 9;
int main() {
    enum e {g = g, a = g, t};
    std::cout << t << std::endl;
    return 0;
}