#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>

#define N 9
using namespace std;

int grid[N][N] = {
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
};

//class for a Sudoku grid
class Grid {
    private:
    vector<Possible> _squares;
    
    static vector<vector<int>> _unit;
    static vector<vector<int>> _peers;
    static vector<vector<int>> _unitsOf;

    bool isSolved() {
        for (int k = 0; k < _squares.size(); k++) {
            if (_squares[k].countTrue() != 1) {
                return false;
            }
        }
        return true;
    };

public:
//constructor
    Grid() {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
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

// 
    bool eliminate (int k, int val) {
        if (!_squares[k].isTrue(val)) {
            return true;
        }

        _squares[k].eliminate(val);
        if (_squares[k].countTrue() == 0) {
            return false;
        } else if (_squares[k].countTrue() == 1) {
            int v = _squares[k].val();
        }
    }

};

//main entry point
int main() {

    return 0;
}