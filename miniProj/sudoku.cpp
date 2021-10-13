#include <iostream>
#define N 9
using namespace std;
// int grid[N][N] = {
//    {3, 1, 0, 5, 0, 8, 3, 0, 2},
//    {5, 0, 5, 0, 0, 0, 0, 0, 0},
//    {0, 8, 7, 0, 0, 0, 0, 3, 1},
//    {0, 0, 3, 0, 1, 0, 0, 8, 0},
//    {9, 0, 0, 8, 6, 3, 0, 0, 5},
//    {0, 5, 0, 0, 9, 0, 6, 0, 0},
//    {1, 3, 0, 0, 0, 0, 2, 5, 0},
//    {0, 0, 0, 0, 0, 0, 0, 7, 4},
//    {0, 0, 5, 2, 0, 6, 3, 0, 0}
// };

int grid[N][N]{};

bool isPresentInCol(int col, int num){ //check whether num is present in col or not
   for (int row = 0; row < N; row++)
      if (grid[row][col] == num)
         return true;
   return false;
}

bool isPresentInRow(int row, int num){ //check whether num is present in row or not
   for (int col = 0; col < N; col++)
      if (grid[row][col] == num)
         return true;
   return false;
}

bool isPresentInBox(int boxStartRow, int boxStartCol, int num){
//check whether num is present in 3x3 box or not
   for (int row = 0; row < 3; row++)
      for (int col = 0; col < 3; col++)
         if (grid[row+boxStartRow][col+boxStartCol] == num)
            return true;
   return false;
}

/**
 * For checking if a number is only present in rows, columns and sub-grids once.
**/
bool isOnlyPresentInRowOnce(int row, int num) {
    int cnt = 0;
    for (int col = 0; col < N; col++) {
        if (grid[row][col] == num) {
            cnt ++;
        }
        if (cnt > 1) return false;
    }
    return true;
}

bool isOnlyPresentInColOnce(int col, int num) {
    int cnt = 0;
    for (int row = 0; row < N; row++) {
        if (grid[row][col] == num) {
            cnt ++;
        }
        if (cnt > 1) return false;
    }
    return true;
}

bool isOnlyPresentInBoxsOnce(int boxStartRow, int boxStartCol, int num) {
    int cnt = 0;
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            if (grid[row+boxStartRow][col+boxStartCol] == num) cnt++;
            if (cnt >1) return false;
        }  
    }
    return true;
}

//How to take array as parameters?
bool isValidSudokuGrid() {
    //int cnt = 0;
    for (int num = 0; num < N + 1; num++) {
        for (int i = 0; i < 9; i++) {
            //FIXME: Not yet include checking of boxes.
            return !isOnlyPresentInRowOnce(i, num) && !isOnlyPresentInColOnce(i, num)/* && !isOnlyPresentInBoxsOnce(row - row%3 ,col - col%3, num)*/;
        }
    }
    return false;
}

void sudokuGrid(){ //print the sudoku grid after solve
   for (int row = 0; row < N; row++){
      for (int col = 0; col < N; col++){
         if(col == 3 || col == 6)
            cout << " | ";
         cout << grid[row][col] <<" ";
      }
      if(row == 2 || row == 5){
         cout << endl;
         for(int i = 0; i<N; i++)
            cout << "---";
      }
      cout << endl;
   }
}

bool findEmptyPlace(int &row, int &col){ //get empty location and update row and column
   for (row = 0; row < N; row++)
      for (col = 0; col < N; col++)
         if (grid[row][col] == 0) //marked with 0 is empty
            return true;
   return false;
}

bool isValidPlace(int row, int col, int num){
   //when item not found in col, row and current 3x3 box
   return !isPresentInRow(row, num) && !isPresentInCol(col, num) && !isPresentInBox(row - row%3 ,
col - col%3, num);
}
 
bool solveSudoku(){
   int row, col;
   if (!findEmptyPlace(row, col))
      return true; //when all places are filled
   for (int num = 1; num <= 9; num++){ //valid numbers are 1 - 9
      if (isValidPlace(row, col, num)){ //check validation, if yes, put the number in the grid
         grid[row][col] = num;
         if (solveSudoku()) //recursively go for other rooms in the grid
            return true;
         grid[row][col] = 0; //turn to unassigned space when conditions are not satisfied
      }
   }
   return false;
}

int textReader() {

    int sudoku [9][9]{};    // Entrer file to solve here:
    //Change to cin for user to add file name

    std::ifstream sudokufile ("EasySudoku.txt");    // Read input file into array
    if (sudokufile.is_open()) {        
        
        // Fill sudoku array with elements from text file
        for(int i{}; i !=9; ++i){
            for(int j{}; j !=9; ++j){
                sudokufile >> sudoku[i][j];
            }
        }        
    
        // Print the sudoku
        std::cout<< "This is the sudoku to solve:" << std::endl;

        for (int i=0; i!=9; ++i){
            for (int j=0; j!=9; ++j){
                std::cout << sudoku[i][j] << " ";
            }
            std::cout << std::endl;
        }   
         
    } else {
        std::cout << "Can't open the file" << std::endl;
    }

    return sudoku[9][9];
}

int main(){

    grid[9][9] = textReader();

    if (!isValidSudokuGrid) {
        cout << "The input grid is not a valid sudoku grid.";
        return 0;
    }

   if (solveSudoku() == true)
      sudokuGrid();
   else
      cout << "No solution exists";
}