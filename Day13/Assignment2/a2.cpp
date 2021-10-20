#include <iostream>
#include <map>


int main() {
    std::map<std::string, int> hitmap;

    for (int i = 1; i <= 33; i++) {
        hitmap[std::to_string(i)] = 0;
        
    }

    for (int j = 0; j < 10000; j++) {
        int v = rand() % 34;
        hitmap[std::to_string(v)]++;
    }

    for (int k = 1; k <= 33; k++) {
        std::cout << k << "--" << hitmap[std::to_string(k)] << std::endl;
    }

    return 0;
}