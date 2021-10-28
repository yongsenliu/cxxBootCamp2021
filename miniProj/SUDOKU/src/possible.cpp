#include "possible.hpp"

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

std::string Possible::getString(int width) const {
    std::string s(width, ' ');
    int k = 0;
    for (int i = 1; i <= 9; i++) {
        if (isTrueForValueInPossibles(i)) {
            s[k++] = '0' + i;
        }
    }
    return s;
};