#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
#include <chrono>

#include "grid.hpp"

std::string sudokuStr = "..84...3....3.....9....157479...8........7..514.....2...9.6...2.5....4......9..56";

int main() {
    std::cout << "-------- START CONSTRAINT PROPAGATION -------" << std::endl;
    auto start = std::chrono::high_resolution_clock::now();
    // constraint propagation is included inside constructor
    Grid grid(sudokuStr);
    grid.print(std::cout);
    std::cout << "-------- END CONSTRAINT PROPAGATION -------\n\n" << std::endl; 

    // std::cout << "-------- START BRUTE FORCE -------" << std::endl;
    // while (!grid.bruteForce())
    // {
    //     int i = 0;
    //     std::cout << "Brute force times: " << i+1 << std::endl;
    //     grid.print(std::cout);
    //     std::cout << "\n" << std::endl;
    // }
    // std::cout << "-------- END BRUTE FORCE -------" << std::endl;

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "Time of execution: " << duration.count() << " microseconds" << std::endl;
    return 0;
    
}