#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
#define N 9
using namespace std;

/**************************************************************
// Two dimentional array for passing numbers to sovler one by one
**************************************************************/
int sudoku[N][N] = {
   {0, 6, 0, 5, 0, 8, 0, 0, 2},
   {5, 0, 0, 0, 0, 0, 0, 0, 0},
   {0, 8, 7, 0, 0, 0, 0, 3, 1},
   {0, 0, 3, 0, 1, 0, 0, 8, 0},
   {9, 0, 0, 8, 6, 3, 0, 0, 5},
   {0, 5, 0, 0, 9, 0, 6, 0, 0},
   {1, 3, 0, 0, 0, 0, 2, 5, 0},
   {0, 0, 0, 0, 0, 0, 0, 7, 4},
   {0, 0, 5, 2, 0, 6, 3, 0, 0}
};

/********************************
// Declaration of class 'Possible'
*********************************/
class Possible {
    // Create an array of 9 for boolens 
    vector<bool> _boolens;
public:
    Possible();
    int countTrue() const;
    bool isTrue(int i) const;
    void eliminate(int i);
    int val() const;
    string str(int width) const;
};

/*************************************
// Implementations of class 'Possible'
*************************************/
Possible::Possible() : _boolens(9, true) {};

int Possible::countTrue() const {
    //FIXME....
    return count(_boolens.begin(), _boolens.end(), true);
};

//get boolen value
bool Possible::isTrue(int i) const {
    return _boolens[i-1];
};

//eliminate one possilbe by setting false
void Possible::eliminate(int i) {
    _boolens[i-1] = false; 
};

// Returns an iterator to the first element in the range [first,last) 
//that compares equal to val. If no such element is found, the function 
//returns last.
// iterator is radom accessing
int Possible::val() const {
    auto iterator = find(_boolens.begin(), _boolens.end(), true);
    return (iterator != _boolens.end() ? (iterator - _boolens.begin()) + 1 : -1);
};

string Possible::str(int width) const {
    string s(width, ' ');
    int k = 0;
    for (int i = 1; i <= 9; i++) {
        if (isTrue(i)) {
            s[k++] = '0' + i;
        }
    }
    return s;
};

/*****************************
// Declaration of class 'Grid'
*****************************/
class Grid {
    vector<Possible> _squares;

public:
    Possible possible(int k) const { return _squares[k]; }
    Grid();
    bool isSolved() const;
    void print(ostream & s) const;

    // eliminate a possible from a square, 'value' is par for eliminating, 
    //'k' is the index
    bool eliminatePossibleFromSquare (int k, int value);
    bool assign(int k, int value);
    bool isInBoxOf(int row, int col, int k);
};

/********************************
// Implementation of class 'Grid'
********************************/



bool Grid::isSolved() const {
    for (int k = 0; k < _squares.size(); k++) {
        if (_squares[k].countTrue() != 1) {
            return false;
        }
    }
    return true;
};

void Grid::print(ostream & s) const {
    int width = 1;
    for (int k = 0; k < _squares.size(); k++) {
        width = max(width, 1 + _squares[k].countTrue());
    }

    string str(3*width, '-');
    for (int i = 0; i < 9; i++) {
        if (i == 3 || i == 6) {
            s << str << "+-" << str << "+" << str << endl;
        }
        for (int j = 0; j < 9; j++) {
            if (j == 3 || j == 6) s << "| ";
            s << _squares[i*9 + j].str(width);
        }
        s << endl;
    }
};

bool Grid::eliminatePossibleFromSquare (int k, int value) {
    // if the value has already been eliminated, return true i.e. successful.
    if (!_squares[k].isTrue(value)) {
        return true;
    }

    // set possible for index k as 'false' for the value 
    _squares[k].eliminate(value);

    // if no possibles exist in index k, it means no solution, return 'false' to the function
    if (_squares[k].countTrue() == 0) {
        return false;
    } else if (_squares[k].countTrue() == 1) {// if only one possible value
        // apply the principle 1 to eliminate this 'true' value from all peers
        int value = _squares[k].val();

        for (int row = 0; row < 9; row++) {
            for (int col = 0; col < 9; col++) {
                // k%9 is the col and k/9 is the row for the square
                if ((col == k % 9)||(row == k / 9) || isInBoxOf(row, col, k)) {
                    if (!((9*row+col) == k)) {
                        if (!eliminatePossibleFromSquare(9*row+col, value)) {
                            return false;
                        }
                    }
                }
            }
        }
    }
    return true;
};

// this func is to find out if a combination of row&col are in the Box of a square
// thus peers in the Box can be found out for it
bool Grid::isInBoxOf(int row, int col, int k) {
    int ri = ((k/9)/3)*3;
    int ci = (k%9)/3;

    if (((row/3)*3 == ri) && (col/3 == ci)) {
        return true;
    }
    return false;
};

bool Grid::assign(int k, int value) {
    for (int i = 1; i <= 9; i++) {
        if (i != value) {
            if (!eliminatePossibleFromSquare(k, i)) {
                return false;
            }
        }
    }
    return true;
};

Grid::Grid() : _squares(81) {
    for (int i = 0; i < 81; i++) {
        _squares[i] = Possible();
    }
};


/*****************
//main entry point
*****************/
int main() {
    std::cout << "-------- START -------" << std::endl;

    Grid grid;

    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            int v = sudoku[row][col];
            if (v != 0) {
                grid.assign(9*row+col, v);
                grid.print(cout);
                std::cout << "\n\n" << std::endl;
            }  
        }
    }
    std::cout << "-------- END -------" << std::endl;
    return 0;
}