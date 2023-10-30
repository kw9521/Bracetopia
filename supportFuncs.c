#define _DEFAULT_SOURCE

#include <stdio.h>      // allows for use of printf()
#include <curses.h>
#include "supportFuncs.h"

/// prints out current grid, given a 2D array
/// @param dimensionOfGrid num of cells in each row/col
/// @param initialGrid 2d array we are dealing with
void printOutCurrGrid(int dimensionOfGrid, char initialGrid[][dimensionOfGrid]){
    for (int i = 0; i < dimensionOfGrid; i++) {
        for (int j = 0; j < dimensionOfGrid; j++) {
            printf("%c", initialGrid[i][j]);
        }
        printf("\n");
    }
}

/// @brief prints current grid with curses 
/// @param dimensionOfGrid num of cells in each row/col
/// @param initialGrid  2d array we are dealing with
void printCurrGridWithCurses(int dimensionOfGrid, char initialGrid[][dimensionOfGrid]){
    for (int i = 0; i < dimensionOfGrid; i++) {
        for (int j = 0; j < dimensionOfGrid; j++) {
            mvaddch(i, j, initialGrid[i][j]);
        }
    } 
}
