// Caeser Cipher

# include <iostream>

int main() {

    unsigned int key;

    std::string cipher1 = "OSSLV";
    std::string cipher2 = "VKRIMHZKTIAR";



    //int base = 65;

    //std::cout << "Please enter the key for cipher" << std::endl;
    //std::cin >> key;

    for (char c: cipher1) {
        char a = c - 7;
        std::cout << a << std::endl;
    }

    std::cout << "-----------------------------" << std::endl;

    for (char c: cipher2) {
        char a = c-19;

        if (a <= 'A') a = 'Z' - ('A' - a - 1);

        else if (a > 'Z') a = 'A' + (a - 'Z' + 1);

        std::cout << a << std::endl;
    }

    //for (int i = 0; i < cipher2.size(); i++ ) {

        //if 

    //}

    //char(41)

    return 0;
}