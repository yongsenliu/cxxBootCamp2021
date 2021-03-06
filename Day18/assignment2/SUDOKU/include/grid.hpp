#ifndef GRID_HPP
#define GRID_HPP

#include <iostream>
#include <vector>
#include <algorithm>

#include "possible.hpp"

class Grid {

    /*A square is 1 of 81 cells in a grid*/
    std::vector<Possible> _squares;
public:
    int searchingCounter;
    Possible possible(int k) const { return _squares[k]; }
    Grid();
    void loadAndPropagate(std::string s);
    int getIndexOfSquareWithLeastCountOfTrues() const;
    bool searching();
    bool isSolved() const;
    
    void print(std::ostream & s) const;

    // eliminate a possible from a square, 'value' is par for eliminating, 
    //'k' is the index
    bool eliminatePossibleFromSquare (int k, int value);
    bool assign(int k, int value);
    bool isInBoxOf(int row, int col, int k) const;
    void initSudoku(std::string s);
};

#endif