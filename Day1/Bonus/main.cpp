
//Bonus assignment - Day1
#include <iostream>

int main() {

    unsigned int guess = 128;

    for (int counter = 1; counter < 8; counter ++) {
        
        bool ans = false;
        std::cout << "Smaller than: " << guess << "?" << std::endl;
        std::cin >> ans;
        if (ans == true) {
            guess /= 2;
        } else {
            guess = guess - guess/2;
        }
    }
    return 0;
}