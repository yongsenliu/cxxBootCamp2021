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
   {3, 1, 0, 5, 0, 8, 3, 0, 2},
   {5, 0, 5, 0, 0, 0, 0, 0, 0},
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
};

/*****************************
// Implementation of class 'Grid'
*****************************/

bool Grid::isSolved() const {
    for (int k = 0; k < _squares.size(); k++) {
        if (_squares[k].countTrue() != 1) {
            return false;
        }
    }
    return true;
};

void Grid::print(ostream & s) const{
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

        for (int i = 0; i < 9; i++) {
            if ((i == k%9)||(i == k/9)) {
                if (!eliminatePossibleFromSquare(i, value)) {
                    return false;
                }
            }
        }


        // for (int col = 0; col < 9; col++) {
        //     for (int row = 0; row < 9; row++) {

        //         if ((col == k%9)||(row == k/9) {

        //         }
        //         if (!eliminatePossibleFromSquare())
        //     }
        // }

        // for (int i = 0; i < 20; i++) {
        //     if (!eliminatePossibleFromSquare(i, value)) {
        //         return false;
        //     }
        // }
    }
    // for (int i = 0; i < _unitsOf[k].size(); i++) {
    //     int x = _unitsOf[k][i];
    //     int n = 0, ks;
    //     for (int j = 0; j < 9; j++) {
    //         int p = _unit[k][i];
    //         if (_squares[p].isTrue(value)) {
    //             n++;
    //             ks = p;
    //         }
    //     }

    //     if (n == 0) {
    //         return false;
    //     } else if (n == 1) {
    //         if (!assign(ks, value)) {
    //             return false;
    //         }
    //     }
    // }
    return true;
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
    int k = 0;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (!assign(k, sudoku[i][j])) {
                cerr << "error" << endl;
                return;
            }
            k++;
        }
    }
};


/*****************
//main entry point
*****************/
int main() {
    std::cout << "---------------" << std::endl;
    Grid grid;

    for (int i = 1; i <= 9; i++) {
        for (int j = 1; j <= 9; j++) {
            grid.print(cout);
            int v = sudoku[i][j];
            grid.eliminatePossibleFromSquare(i*j, v);
            grid.print(cout);
        }
    }

    std::cout << "++++++++++++++++++" << std::endl;
    return 0;
}