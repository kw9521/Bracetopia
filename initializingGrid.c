/// @file initializingGrid.c
/// @author KUNLIN WEN, KW9521
/// All functions related to initializin grid
#define _DEFAULT_SOURCE

#include <stdlib.h>             // to use srandom(). random()
#include <time.h>               // to use time()
#include <stdio.h>              // to use printf()
#include <stdbool.h> 
#include "initializingGrid.h"
#include "moves.h"

/// @brief shuffles an array using the Fisher-Yates algo
/// @param flattenedGrid array to be shuffled
/// @param lengthOfFlattenedGrid length of array
void fisherYatesShuffle(char *flattenedGrid, int lengthOfFlattenedGrid) {
    for (int i = 0; i <= lengthOfFlattenedGrid - 2; i++) {
        int j = i + (random() % (lengthOfFlattenedGrid - i));

        // Swap elements at index i and index j
        char temp = flattenedGrid[i];
        flattenedGrid[i] = flattenedGrid[j];
        flattenedGrid[j] = temp;
    }
}

/// @brief Calculates the number of vacant cells based on the total number of cells and vacancy rate
/// @param totalNumOfCells The total number of cells.
/// @param vacancyRate The vacancy rate as an integer out of 100.
/// @return The number of vacant cell
int calcNumOfVacCells(int totalNumOfCells, int vacancyRate ){
    int numOfVacancy = (int)(totalNumOfCells * ((float)vacancyRate/100));              // truncates 
    return numOfVacancy;
}

/// @brief Calculates the number of endline cells based on the total number of cells and endline percentage
/// @param totalNumOfCells The total number of cells.
/// @param vacancyRate The vacancy rate as an integer out of 100.
/// @return The number of endline cell
int calcNumOfEndlines(int totalNumOfCells, int endlinePercentage){
    int numOfEndlines = (int)(totalNumOfCells * ((float)endlinePercentage/100));       // truncates 
    return numOfEndlines;
}

/// @brief Creates the initial grid with a specified vacancy rate and endline percentage
/// @param strengthThreshold the min bound for cell to be happy w/ curr placement
/// @param totalOccupiedCells 'e' cells + 'n' cells
/// @param dimensionOfGrid num of cells in each row/col
/// @param initialGrid 2D array we are working with
/// @param vacancyRate the % of vacant cells (given as an INTEGER out of 100)
/// @param endlinePercentage the % of endline cells (given as an INTEGER out of 100)
void makeGrid(int strengthThreshold, int totalOccupiedCells, int dimensionOfGrid, char initialGrid[][dimensionOfGrid], int vacancyRate, int endlinePercentage) {
    
    // shuffling method
    int numOfCells = dimensionOfGrid * dimensionOfGrid;
    int numOfVacancy = calcNumOfVacCells(numOfCells, vacancyRate);
    int numOfCellsAfterVac = numOfCells - numOfVacancy; 
    int numOfEndlines = calcNumOfEndlines(numOfCellsAfterVac, endlinePercentage);       // truncates 

    // length of the 1D array is the same as total # of cells in 2D array
    int lengthOfFlattenedGrid = dimensionOfGrid * dimensionOfGrid;
    char flattenedGrid[lengthOfFlattenedGrid];
    
    int currIndex = 0;
    // set everything to be 'n' cells first
    for (int i = 0; i < (lengthOfFlattenedGrid); i++){
        flattenedGrid[i] = 'n';
    }

    int x = numOfVacancy;
    // change the first x amount to be '.' cells
    for (int i = 0; i < (lengthOfFlattenedGrid) && x > 0; i++){
        flattenedGrid[i] = '.';
        x--;
        currIndex++;
    }

    int y = numOfEndlines;
    // change the next y amount to be 'e' cells
    for (int i = currIndex; i < (lengthOfFlattenedGrid) && y > 0; i++){
        flattenedGrid[i] = 'e';
        y--;
        currIndex++;
    }

    // Seed the random number generator
    srandom(41);

    // Shuffle the flatArray using Fisher-Yates shuffle
    fisherYatesShuffle(flattenedGrid, lengthOfFlattenedGrid);

    // Reconstruct the 2D array with the shuffled elements
    for (int i = 0; i < dimensionOfGrid; i++) {
        for (int j = 0; j < dimensionOfGrid; j++) {
            initialGrid[i][j] = flattenedGrid[i * dimensionOfGrid + j];
        }
    }

    printOutGridNData(totalOccupiedCells, dimensionOfGrid, initialGrid, 0, strengthThreshold, vacancyRate, endlinePercentage, 0);

}

