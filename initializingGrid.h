/// @file initializingGrid.c
/// @author KUNLIN WEN, KW9521
/// All functions related to initializin grid but in .h format
#ifndef _INITIALIZING_GRID_H
#define _INITIALIZING_GRID_H

/// @brief shuffles an array using the Fisher-Yates algo
/// @param flattenedGrid array to be shuffled
/// @param lengthOfFlattenedGrid length of array
void fisherYatesShuffle(char *flattenedGrid, int lengthOfFlattenedGrid);

/// @brief Calculates the number of vacant cells based on the total number of cells and vacancy rate
/// @param totalNumOfCells The total number of cells.
/// @param vacancyRate The vacancy rate as an integer out of 100.
/// @return The number of vacant cell
int calcNumOfVacCells(int totalNumOfCells, int vacancyRate );

/// @brief Calculates the number of endline cells based on the total number of cells and endline percentage
/// @param totalNumOfCells The total number of cells.
/// @param vacancyRate The vacancy rate as an integer out of 100.
/// @return The number of endline cell
int calcNumOfEndlines(int totalNumOfCells, int endlinePercentage);

/// @brief Creates the initial grid with a specified vacancy rate and endline percentage
/// @param strengthThreshold the min bound for cell to be happy w/ curr placement
/// @param totalOccupiedCells 'e' cells + 'n' cells
/// @param dimensionOfGrid num of cells in each row/col
/// @param initialGrid 2D array we are working with
/// @param vacancyRate the % of vacant cells (given as an INTEGER out of 100)
/// @param endlinePercentage the % of endline cells (given as an INTEGER out of 100)
void makeGrid(int strengthThreshold, int totalOccupiedCells, int dimensionOfGrid, char initialGrid[][dimensionOfGrid], int vacancyRate, int endlinePercentage);


#endif 