#include "grid.hpp"

/********************************
// Implementation of class 'Grid'
********************************/

// get a square index of least counts of true
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

//TODO: update algurithm for a better search
bool Grid::search(/*std::vector<Possible> &_s*/) {
    if (isSolved()) {
        return true;
    }
    std::vector<Possible> _temp(81);
    
    int least = getIndexOfSquareWithLeastCountOfTrues();
    Possible p = possible(least);

    for (int value = 1; value <= 9; value++) {
        if (p.isTrueForValueInPossibles(value)) {
            _temp = _squares;
            if (assign(least, value)) {
                _temp = _squares;
                if (search()) 
                {
                    return true;
                } else {
                    std::cout << "Time machine..." << std::endl;
                    _squares = _temp;
                }

            } else {
                _squares = _temp;
                if (!eliminatePossibleFromSquare(least, value)) {
                    std::cout << "Time machine..." << std::endl;
                    _squares = _temp;
                    std::cout << "SAME CONTRADICTION REPEATED TWICE WHILE SEARCHING, ENDED UP WITH " << searchingCounter << " SEARCHES, AND RESULT:" << std::endl;
                    print(std::cout);
                    return true;
                }
            }
        }
    }

    return true;
};

// Sudoku is solved only when every square has one one true in its 'possible'
bool Grid::isSolved() const {
    for (int k = 0; k < _squares.size(); k++) {
        if (_squares[k].countTrueInPossibles() != 1) {
            return false;
        }
    }
    return true;
};

// pretty print on the screen
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

// eliminate a value from square k and do propagation to its peers
bool Grid::eliminatePossibleFromSquare (int k, int value) {
    // if the value has already been eliminated, return true i.e. successful.
    if (!_squares[k].isTrueForValueInPossibles(value)) {
        return true;
    }

    // set possible for index k as 'false' for the value 
    _squares[k].eliminatefromPossiblesOfValue(value);

    const int count = _squares[k].countTrueInPossibles();
    if (count == 0) {
        searchingCounter ++;
        std::cout << "Constradiction occured when eliminate " << value <<" in row: " << (k/9) << ", col: " << (k%9) << std::endl;
        return false;
    } else if (count == 1) {// if only one possible value

    // Apply the 1st rule of norvig's constraint propagation to eliminate this 'true' value from all peers
        int v = _squares[k].valueOfFirstTrueInPossibles();
        for (int row = 0; row < 9; row++) {
            for (int col = 0; col < 9; col++) {
                // k%9 is the col and k/9 is the row for the square
                if ((col == k % 9)||(row == k / 9) || isInBoxOf(row, col, k)) {
                    if (!((9*row+col) == k)) {
                        if (!eliminatePossibleFromSquare(9*row+col, v)) {
                            return false;
                        }
                    }
                }
            }
        }
    }

    // Apply the 2nd rule of prapagation to put the uniq value in the unit of square k.
    // kUnique stands for the unique index to put THE value 
    int cnt = 0, kUnique;
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            if (isInBoxOf(row, col, k)) {
                if (_squares[9*row + col].isTrueForValueInPossibles(value)) {
                    cnt++, kUnique = 9*row + col;
                }
            }
        }
    }
    if (cnt == 0) {
        return false;
    } else if (cnt == 1) {
        if (!assign(kUnique, value)) return false;
    }
    return true;
};

// this func is to find out if a combination of row&col are in the Box of a square
// thus peers in the Box can be found out for it
bool Grid::isInBoxOf(int row, int col, int k) const {

    // Calculate and match range of row&col in 2D where 'k' is. 
    int rowRange = ((k/9)/3)*3;
    int colRange = (k%9)/3;

    if (((row/3)*3 == rowRange) && (col/3 == colRange)) {
        return true;
    }
    return false;
};

// this func is to assign a value into k-square
bool Grid::assign(int k, int value) {
    // std::vector<Possible> _temp(81);
    
    for (int i = 1; i <= 9; i++) {
        if (i != value) {
            // _temp = _squares;
            if (!eliminatePossibleFromSquare(k, i)) {
                // print(std::cout);
                // std::cout << "Time mechane to restore to previous grid...\n" << std::endl;
                // _squares = _temp;
                return false;
            }
        }
    }
    return true;
};

// init a grid of 'EVERYTHING IS POSSIBLE' and assign values from a string to it and propagate constraints. 
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

// constructor with the init function
Grid::Grid(std::string s) : _squares(81) {
    for (int i = 0; i < 81; i++) {
        _squares[i] = Possible();
    }
    searchingCounter = 0;
    initSudoku(s);
};