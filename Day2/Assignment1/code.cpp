#include <iostream>

int main() {
    int size;
    int *arrP = new int[size];

    std::cin >> size;

    for (int i = 0; i < size; i++) {
        *(arrP+i) = std::rand() % 10;
        std::cout << *(arrP+i) << std::endl;
    }

    delete [] arrP;

    return 0;
}