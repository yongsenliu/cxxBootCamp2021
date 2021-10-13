#include <iostream>
#pragma 1

int fact(int n = 1) {
    int ret = 1;
    std::cout << n << std::endl;
    std::cout << "-------------------" << std::endl;
    if (n > 1) ret = n * fact(n-1);
    std::cout << n << " " << ret << std::endl;
    std::cout << "-------------------" << std::endl;
    return ret;
}

int main() {
    std::cout << fact(4) << std::endl;

    return 0;
}