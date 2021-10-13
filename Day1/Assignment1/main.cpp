// Return positive random numbers to 3 dimensional array with static dimentions

#include <iostream>

int main() {
    unsigned int input;
    unsigned int a[8][9][11];

    //srand(time(0));

    std::cout << "Please input an unsigned integer here:" << std::endl;

    std::cin >> input;
    
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 9; j++) {
            for (int k = 0; k < 11; k++) {
                a[i][j][k] = rand() % input;
                std::cout << a[i][j][k] << "\t";
            }
        }
        std::cout << "\n";
    }
    return 0;
} 