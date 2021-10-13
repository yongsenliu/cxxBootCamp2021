#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>

#define N 9
using namespace std;

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

//class for possibles in a square
class Possible {
    vector<bool> _boolens;
public:
    Possible() : _boolens(9, true) {}
    int countTrue() {
        //FIXME....
        return count(_boolens.begin(), _boolens.end(), true);
    }

//get boolen value
    bool isTrue(int i) {
        return _boolens[i];
    }

//eliminate one possilbe by setting false
    void eliminate(int i) {
        _boolens[i] = false; 
    }

    int val() {
      auto it = find(_boolens.begin(), _boolens.end(), true);
      return (it != _boolens.end() ? 1 + (it - _boolens.begin()) : -1);
   }

   string str(int width) {
       string s(width, ' ');
        int k = 0;
        for (int i = 1; i <= 9; i++) {
            if (isTrue(i)) {
                s[k++] = '0' + 1;
            }
        }
        return s;
   }
};

//class for a Sudoku grid
class Grid {
    vector<Possible> _squares;
    
    vector<vector<int>> _unit;
    vector<vector<int>> _peers;
    vector<vector<int>> _unitsOf;

public:
    Possible possible(int k) const { return _squares[k]; }

//constructor
    Grid() {
        //this->_peers.resize();

        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                _squares[(i+1)*(j+1)] = possible((i+1)*(j+1));
                const int k = i*9 + j;
                const int x[3] = {i, 9 + j, 18 + (i/3)*3 + j/3};
                for (int g = 0; g < 3; g++) {
                    _unit[x[g]].push_back(k);
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

    Grid(int **arry) : _squares(81) {
        int k = 0;
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (!assign(k, arry[i][j])) {
                    cerr << "error" << endl;
                    return;
                }
                k++;
            }
            k++;
        }
    }

    bool isSolved() {
        for (int k = 0; k < _squares.size(); k++) {
            if (_squares[k].countTrue() != 1) {
                return false;
            }
        }
        return true;
    };

    int leastCount() {
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
    }

    void print(ostream & s) {
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
    }

// eliminate a possible from a square, 'value' is par for eliminating, 
//'k' is the index
    bool eliminatePossibleFromSquare (int k, int value) {
        if (!_squares[k].isTrue(value)) {
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
    }

// assign to peers
    bool assign(int k, int value) {
        for (int i = 1; i <= 9; i++) {
            if (i != value) {
                if (!eliminatePossibleFromSquare(k, i)) {
                    return false;
                }
            }
        }
        return true;
    }
};


unique_ptr<Grid> solve(unique_ptr<Grid> S) {
   if (S == nullptr || S->isSolved()) {
      return S;
   }
   int k = S->leastCount();
   Possible p = S->possible(k);
   for (int i = 1; i <= 9; i++) {
      if (p.isTrue(i)) {
         unique_ptr<Grid> S1(new Grid(*S));
         if (S1->assign(k, i)) {
            if (auto S2 = solve(std::move(S1))) {
               return S2;
            }
         }
      }
   }
   return {};
}

//main entry point
int main() {
    std::cout << "---------------" << std::endl;
    Grid grid;// = new Grid;
    
    for (int i = 1; i <= 9; i++) {
        for (int j = 1; j <= 9; j++) {
            // int num = sudoku[i][j];



            // if (auto S = solve(unique_ptr<Grid>(new Grid(sudoku)))) {
            //     S->print(cout);
            // } else {
            //     cout << "No solution";
            // }
            // cout << endl;
            int k = sudoku[i][j];
            grid.eliminatePossibleFromSquare(i*j, k);
            grid.print(cout);
        }
    }
    return 0;
}
