#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
#include <chrono>
#include <fstream>

#include "grid.hpp"

// Use string lines from txt file instead
//std::string sudokuStr = ".....6....59.....82....8....45........3........6..3.54...325..6..................";

int main() {

    std::ifstream file("sudokus.txt");
    std::string sudokuStringLine;
    int c = 0;
    while (getline(file, sudokuStringLine)) {
        c++;//:P
        std::cout << "                             Sudoku- " << c << std::endl;
        std::cout << "\n-------- START CONSTRAINT PROPAGATION RULE 1 AND 2 -------" << std::endl;
        auto start = std::chrono::high_resolution_clock::now();

        Grid grid(sudokuStringLine);
        grid.print(std::cout);
        std::cout << "-------- END CONSTRAINT PROPAGATION -------\n\n" << std::endl; 

        std::cout << "-------- START SEARCHING -------" << std::endl;
        while (!grid.searching())
        {
            // std::cout << "SAME CONTRADICTION WAS REPEATED TWICE WHILE SEARCHING, ENDED UP WITH " << grid.searchingCounter << " SEARCHES, AND RESULT:" << std::endl;
            // grid.print(std::cout);

        }
        std::cout << "-------- END SEARCHING-------" << std::endl;

        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
        std::cout << "Time of execution: " << duration.count() << " microseconds\n\n" << std::endl;
    }

    
    return 0;
    
}