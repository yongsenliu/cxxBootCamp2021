#include <iostream>

int main() {
    int sizeX, sizeY, sizeZ;
    //int *arrPX = new int[sizeX], *arrPY = new int[sizeY], *arrPZ = new int[sizeZ];
    unsigned int ***arrP = new int[sizeX][sizeY][sizeZ];
    int array[sizeX][sizeY][sizeZ];

    std::cin >> sizeX;
    std::cin >> sizeY;
    std::cin >> sizeZ;

    // for (int i = 0; i < size; i++) {
    //     *(arrP+i) = std::rand() % 10;
    //     std::cout << *(arrP+i) << std::endl;
    // }

    for (int i = 0; i < sizeX; i++) {
        for (int j = 0; j < sizeY; j++) {
            for (int k = 0; k < sizeZ; k++) {
                ***arrP = rand() % 10;
                std::cout << ***arrP << "\t";
            }
        }
        std::cout << "\n";
    }

    delete [] arrP;

    return 0;
}