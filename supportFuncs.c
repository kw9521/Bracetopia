#define _DEFAULT_SOURCE

#include "supportFuncs.h"


/// Reconstruct the EMPTY 2D array given the already populated 1D array
/// @param dimensionOfGrid 
/// @param initialGrid 
/// @param sizeOfFlatGrid 
/// @param flattenedGrid 
void turn1DInto2D(int dimensionOfGrid, char initialGrid[][dimensionOfGrid], int sizeOfFlatGrid , char flattenedGrid[sizeOfFlatGrid]){
    for (int i = 0; i < dimensionOfGrid; i++) {
        for (int j = 0; j < dimensionOfGrid; j++) {
            initialGrid[i][j] = flattenedGrid[i * dimensionOfGrid + j];
        }
    }
}

/// prints out current grid, given a 2D array
/// @param dimensionOfGrid 
/// @param initialGrid
void printOutCurrGrid(int dimensionOfGrid, char initialGrid[][dimensionOfGrid]){
    for (int i = 0; i < dimensionOfGrid; i++) {
        for (int j = 0; j < dimensionOfGrid; j++) {
            printf("%c", initialGrid[i][j]);
        }
        printf("\n");
    }
}


