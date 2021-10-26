#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
#include <chrono>
#define N 9
using namespace std;

/**************************************************************
// Two dimentional array for passing numbers to sovler one by one
**************************************************************/

std::string sudokuStr = "4.....8.5.3..........7......2.....6.....8.4......1.......6.3.7.5..2.....1.4......";

/********************************
// Declaration of class 'Possible'
*********************************/
class Possible {
    // Create an array of 9 for boolens 
    vector<bool> _boolens;
public:
    Possible();
    int countTrueInPossibles() const;
    bool isTrueForValueInPossibles(int i) const;
    void eliminatefromPossiblesOfValue(int i);
    int valueOfFirstTrueInPossibles() const;
    string getString(int width) const;
};

/*************************************
// Implementations of class 'Possible'
*************************************/
Possible::Possible() : _boolens(9, true) {};

int Possible::countTrueInPossibles() const {
    //FIXME....
    return count(_boolens.begin(), _boolens.end(), true);
};

//get boolen value
bool Possible::isTrueForValueInPossibles(int i) const {
    return _boolens[i-1];
};

//eliminate one possilbe by setting false
void Possible::eliminatefromPossiblesOfValue(int i) {
    _boolens[i-1] = false; 
};

//returns an iterator to the first element in the range [first,last) 
//that compares equal to val. If no such element is found, the function 
//returns last.
// iterator is radom accessing
int Possible::valueOfFirstTrueInPossibles() const {
    auto iterator = find(_boolens.begin(), _boolens.end(), true);
    return (iterator != _boolens.end() ? (iterator - _boolens.begin()) + 1 : -1);
};

string Possible::getString(int width) const {
    string s(width, ' ');
    int k = 0;
    for (int i = 1; i <= 9; i++) {
        if (isTrueForValueInPossibles(i)) {
            s[k++] = '0' + i;
        }
    }
    return s;
};

/*****************************
// Declaration of class 'Grid'
*****************************/
class Grid {

    /*A square is 1 of 81 cells in a grid*/
    vector<Possible> _squares;
    // vector<Possible> _backup;

public:
    Possible possible(int k) const { return _squares[k]; }
    Grid();
    int getIndexOfSquareWithLeastCountOfTrues() const;
    bool search();
    bool isSolved() const;
    
    void print(ostream & s) const;

    // eliminate a possible from a square, 'value' is par for eliminating, 
    //'k' is the index
    bool eliminatePossibleFromSquare (int k, int value);
    bool assign(int k, int value);
    bool isInBoxOf(int row, int col, int k);
    void initSudoku(string s);
};

/********************************
// Implementation of class 'Grid'
********************************/

int Grid::getIndexOfSquareWithLeastCountOfTrues() const {
   int k = -1, min;
   for (int i = 0; i < 81; i++) {
      const int m = _squares[i].countTrueInPossibles();
      if (m > 1 && (k == -1 || m < min)) {
         min = m, k = i;
      }
   }
   return k;
};

bool Grid::search() {
    
    if (isSolved()) {
        return true;
    }

    vector<Possible> _temp1(81);
    
    int l = getIndexOfSquareWithLeastCountOfTrues();

    Possible p = possible(l);

    for (int i = 1; i <= 9; i++) {
        
        if (p.isTrueForValueInPossibles(i)/*_squares[l].isTrue(i)*/) {

            _temp1 = _squares;

            if (!assign(l, i)) {

                _squares = _temp1;

                if (!eliminatePossibleFromSquare(l, i)) {
                    _squares = _temp1;
                    std::cout << "No solution" << std::endl;
                    return false;
                }

            } else {

                // if (bruteForce()) {
                //     return true;
                // }
            }
        }
    }
    return false;
};

bool Grid::isSolved() const {
    for (int k = 0; k < _squares.size(); k++) {
        if (_squares[k].countTrueInPossibles() != 1) {
            return false;
        }
    }
    return true;
};

void Grid::print(ostream & s) const {
    int width = 1;
    for (int k = 0; k < _squares.size(); k++) {
        width = max(width, 1 + _squares[k].countTrueInPossibles());
    }

    string str(3*width, '-');
    for (int i = 0; i < 9; i++) {
        if (i == 3 || i == 6) {
            s << str << "+-" << str << "+" << str << endl;
        }
        for (int j = 0; j < 9; j++) {
            if (j == 3 || j == 6) s << "| ";
            s << _squares[i*9 + j].getString(width);
        }
        s << endl;
    }
};

bool Grid::eliminatePossibleFromSquare (int k, int value) {
    // if the value has already been eliminated, return true i.e. successful.
    if (!_squares[k].isTrueForValueInPossibles(value)) {
        return true;
    }

    // set possible for index k as 'false' for the value 
    _squares[k].eliminatefromPossiblesOfValue(value);

    // if no possibles exist in index k, it means no solution, return 'false' to the function
    if (_squares[k].countTrueInPossibles() == 0) {

        std::cout << "Below empty square error occured when eliminate " << value <<" in row: " << (k/9) << ", col: " << (k%9) << std::endl;
        return false;
    } else if (_squares[k].countTrueInPossibles() == 1) {// if only one possible value
        // apply the principle 1 to eliminate this 'true' value from all peers
        int value = _squares[k].valueOfFirstTrueInPossibles();

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
    // vector<Possible> _temp(81);
    
    for (int i = 1; i <= 9; i++) {
        if (i != value) {
            // _temp = _squares;
            if (!eliminatePossibleFromSquare(k, i)) {
                // print(cout);
                // std::cout << "Time mechane to restore to previous grid...\n" << std::endl;
                // _squares = _temp;
                return false;
            }
        }
    }
    return true;
};

void Grid::initSudoku(string s) {
    int k = 0;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] >= '1' && s[i] <= '9') {
            if (!assign(k, s[i] - '0')) {
                cerr << "error" << endl;
                return;
            }
            k++;
        } else if (s[i] == '0' || s[i] == '.') {
            k++;
        }
    }
};

Grid::Grid() : _squares(81) {
    for (int i = 0; i < 81; i++) {
        _squares[i] = Possible();
    }
    initSudoku(sudokuStr);
};


/*****************
//main entry point
*****************/
int main() {
    std::cout << "-------- START CONSTRAINT PROPAGATION -------" << std::endl;
    auto start = std::chrono::high_resolution_clock::now();
    // constraint propagation is included inside constructor
    Grid grid;
    grid.print(cout);
    std::cout << "-------- END CONSTRAINT PROPAGATION -------\n\n" << std::endl; 

    std::cout << "-------- START BRUTE FORCE -------" << std::endl;
    while (!grid.search())
    {
        int i = 0;
        std::cout << "Brute force times: " << i+1 << std::endl;
        grid.print(cout);
        std::cout << "\n" << std::endl;
    }
    
    // // for (int i = 0; i < 20; i++) {
    // //     if (grid.bruteForce()) {
    // //         break;
    // //     }
    // //     std::cout << "Brute force times: " << i+1 << std::endl;
    // //     grid.print(cout);
    // //     std::cout << "\n" << std::endl;
    // // }
    
    // grid.print(cout);
    std::cout << "-------- END BRUTE FORCE -------" << std::endl;

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "Time of execution: " << duration.count() << " microseconds" << std::endl;
    return 0;
    
}