#define _DEFAULT_SOURCE

#include <stdio.h>      // allows for use of printf()
#include "supportFuncs.h"

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
