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

int Possible::val() const {
    auto it = find(_boolens.begin(), _boolens.end(), true);
    return (it != _boolens.end() ? 1 + (it - _boolens.begin()) : -1);
};

string Possible::str(int width) const {
    string s(width, ' ');
    int k = 0;
    for (int i = 1; i <= 9; i++) {
        if (isTrue(i)) {
            s[k++] = '0' + 1;
        }
    }
    return s;
};

/*****************************
// Declaration of class 'Grid'
*****************************/
class Grid {
    vector<Possible> _squares;
    vector<vector<int>> _unit, _peers, _unitsOf;

public:
    Possible possible(int k) const { return _squares[k]; }
    Grid();
    void init();
    bool isSolved() const;
    int leastCount() const;
    void print(ostream & s) const;

    // eliminate a possible from a square, 'value' is par for eliminating, 
    //'k' is the index
    bool eliminatePossibleFromSquare (int k, int value);
    bool assign(int k, int value);
};

// vector<vector<int>> Grid :: _unit(27), _unitsOf(81), _peers(81);

// void Grid::Grid(int **arry) : _squares(81) {
    //     int k = 0;
    //     for (int i = 0; i < 9; i++) {
    //         for (int j = 0; j < 9; j++) {
    //             if (!assign(k, arry[i][j])) {
    //                 cerr << "error" << endl;
    //                 return;
    //             }
    //             k++;
    //         }
    //         k++;
    //     }
    // }


/*****************************
// Implementation of class 'Grid'
*****************************/
void Grid::init() {
    // this->_peers.resize();
    //vector<Possible> _squares(81);
    //vector<vector<int>> _unit(27), _unitsOf(81), _peers(81);

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            const int k = i*9 + j;
            const int x[3] = {i, 9 + j, 18 + (i/3)*3 + j/3};
            for (int g = 0; g < 3; g++) {
                auto & refvec = _unit[x[g]];
                refvec.push_back(k);
                _unitsOf[k].push_back(x[g]);
            }
        }
    }

    for (int k = 0; k < _peers.size(); k++) {
        for (int x = 0; x < _unitsOf[k].size(); x++) {
            for (int j = 0; j < 9; j++) {
                int k2 = _unit[_unitsOf[k][x]][j];
                if (k2 != k) _peers[k].push_back(k2);
            }
        }
    }
};

bool Grid::isSolved() const {
    for (int k = 0; k < _squares.size(); k++) {
        if (_squares[k].countTrue() != 1) {
            return false;
        }
    }
    return true;
};

int Grid::leastCount() const {
    int k = -1;
    int min;
    for (int i = 0; i< _squares.size(); i++) {
        int m = _squares[i].countTrue();
        if (m > 1 && (k == -1 || m < min)) {
            min = m;
            k = i;
        }
    }
    return k;
};

void Grid::print(ostream & s) const{
    //s << "ytr";
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
    int x = 2;
    if (!_squares[k].isTrue(value)) {
        int x;
        x = 1;
        return true;
    }

    _squares[k].eliminate(value);

    if (_squares[k].countTrue() == 0) {
        return false;
    } else if (_squares[k].countTrue() == 1) {
        int v = _squares[k].val();
        for (int i = 0; i < _peers[k].size(); i++) {
            if (!eliminatePossibleFromSquare(_peers[k][i], v)) {
                return false;
            }
        }
    }

    for (int i = 0; i < _unitsOf[k].size(); i++) {
        int x = _unitsOf[k][i];
        int n = 0, ks;
        for (int j = 0; j < 9; j++) {
            int p = _unit[k][i];
            if (_squares[p].isTrue(value)) {
                n++;
                ks = p;
            }
        }

        if (n == 0) {
            return false;
        } else if (n == 1) {
            if (!assign(ks, value)) {
                return false;
            }
        }
    }
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

// Grid::Grid() : _squares(81) {
//     vector<vector<int>> _unit(27), _unitsOf(81), _peers(81);
//     for (int i = 0; i < 81; i++) {
//         if (!assign(i, 0)) {
//             cerr << "error" << endl;
//             return;
//         }
//     }
// };

Grid::Grid() : _squares(81) {
    _unit = std::vector<std::vector<int>>(27,std::vector<int>());
    _unitsOf = std::vector<std::vector<int>>(81,std::vector<int>());
    _peers = std::vector<std::vector<int>>(81,std::vector<int>());
    // std::cout << _unit.size() << '\n';
    // std::cout << _unit[0].size() << '\n';
    init();
    // std::cout << _unitsOf.size() << '\n';
    // std::cout << _unitsOf[0].size() << '\n';
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

// unique_ptr<Grid> solve(unique_ptr<Grid> S) {
//    if (S == nullptr || S->isSolved()) {
//       return S;
//    }
//    int k = S->leastCount();
//    Possible p = S->possible(k);
//    for (int i = 1; i <= 9; i++) {
//       if (p.isTrue(i)) {
//          unique_ptr<Grid> S1(new Grid(*S));
//          if (S1->assign(k, i)) {
//             if (auto S2 = solve(std::move(S1))) {
//                return S2;
//             }
//          }
//       }
//    }
//    return {};
// }


/*****************
//main entry point
*****************/

int main() {
    std::cout << "---------------" << std::endl;

    Grid grid;

    // grid.init();
    // Grid *grid = new Grid;
    // grid->init();

    //grid.init();
    
    for (int i = 1; i <= 9; i++) {
        for (int j = 1; j <= 9; j++) {
            grid.print(cout);
            int k = sudoku[i][j];
            grid.eliminatePossibleFromSquare(i*j, k);
            grid.print(cout);
        }
    }

    // delete grid;

    std::cout << "++++++++++++++++++" << std::endl;
    return 0;
}