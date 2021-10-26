#include "grid.hpp"

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

bool Grid::bruteForce() {
    
    if (isSolved()) {
        return true;
    }

    std::vector<Possible> _temp1(81);
    
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

void Grid::print(std::ostream & s) const {
    int width = 1;
    for (int k = 0; k < _squares.size(); k++) {
        width = std::max(width, 1 + _squares[k].countTrueInPossibles());
    }

    std::string str(3*width, '-');
    for (int i = 0; i < 9; i++) {
        if (i == 3 || i == 6) {
            s << str << "+-" << str << "+" << str << std::endl;
        }
        for (int j = 0; j < 9; j++) {
            if (j == 3 || j == 6) s << "| ";
            s << _squares[i*9 + j].getString(width);
        }
        s << std::endl;
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

void Grid::initSudoku(std::string s) {
    int k = 0;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] >= '1' && s[i] <= '9') {
            if (!assign(k, s[i] - '0')) {
                std::cerr << "error" << std::endl;
                return;
            }
            k++;
        } else if (s[i] == '0' || s[i] == '.') {
            k++;
        }
    }
};

Grid::Grid(std::string s) : _squares(81) {
    for (int i = 0; i < 81; i++) {
        _squares[i] = Possible();
    }
    initSudoku(s);
};