#include <iostream>
#include <fstream>



int textReader() {

    int sudoku [9][9]{};    // Entrer file to solve here:
    //Change to cin for user to add file name

    std::ifstream sudokufile ("EasySudoku.txt");    // Read input file into array
    if (sudokufile.is_open()) {        
        
        // Fill sudoku array with elements from text file
         
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


