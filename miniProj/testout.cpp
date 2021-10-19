#include <iostream>
#include <vector>
// #include <memory>
// #include <algorithm>

//using namespace std;

int main() {

    std::vector<std::vector<int>> _group, _groups_of;

    for (int i = 0; i < 9; i++) {
      for (int j = 0; j < 9; j++) {
         const int k = i*9 + j;
         const int x[3] = {i, 9 + j, 18 + (i/3)*3 + j/3};
         for (int g = 0; g < 3; g++) {
            _group[x[g]].push_back(k);
            _groups_of[k].push_back(x[g]);
            std::cout << _group[x[g]] << std::endl;
         }
      }
   }

   // std::cout << _group << std::endl;

   return 0;

}