#ifndef POSSIBLE_HPP
#define POSSIBLE_HPP

#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
#include <chrono>

class Possible {
private:
    std::vector<bool> _boolens;
public:
    Possible();
    int countTrueInPossibles() const;
    bool isTrueForValueInPossibles(int i) const;
    void eliminatefromPossiblesOfValue(int i);
    int valueOfFirstTrueInPossibles() const;
    std::string getString(int width) const;
};

#endif