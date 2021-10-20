#include <iostream>

template <typename T1, typename T2>
void compare(const T1 _a, const T2 _b) {
    if (_a > _b) std::cout << "a is greater than b" << std::endl;
    if (_a == _b) std::cout << "a is equal than b" << std::endl;
    if (_a < _b) std::cout << "a is less than b" << std::endl;
}