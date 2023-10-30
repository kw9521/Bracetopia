/// @file moves.c
/// @author KUNLIN WEN, KW9521
/// All functions related moving cells around but in .h format
#ifndef _MOVES_H
#define _MOVES_H

/// checks if curr spot is avali for moving other cells here
/// @param dimensionOfGrid num of cells in each row/col
/// @param currGrid 2d array we are dealing with
/// @param trackCurrCoord  ize 2 array to track the current coordinates
/// @return true if curr spot is VACANT and other cells can move here
bool canMoveHere(int dimensionOfGrid, int currGrid[][dimensionOfGrid], int* trackCurrCoord);

/// @brief Prints the grid and its data 
/// @param totalOccupiedCells 'e' cells + 'n' cells
/// @param dimensionOfGrid num of cells in each row/col
/// @param currGrid 2D array representing the current grid
/// @param movesThisCycle Number of moves made in the current cycle
/// @param strengthThreshold minimum bound for a cell to be happy with its current placement
/// @param vacancyRate percentage of vacant cells (given as an INTEGER out of 100)
/// @param endlinePercentage percentage of endline cells (given as an INTEGER out of 100)
/// @param numOfCyclesDone Number of cycles this grid has been through
void printOutGridNData(int totalOccupiedCells, int dimensionOfGrid, char currGrid[][dimensionOfGrid], int movesThisCycle, int strengthThreshold, int vacancyRate, int endlinePercentage, int numOfCyclesDone);

/// @brief Moves cells based on their happiness
/// @param totalOccupiedCells 'e' cells + 'n' cells
/// @param infiniteMode true if we are running infinite mode, false is we are running print mode
/// @param dimensionOfGrid num of cells in each row/col
/// @param initialGrid 2D array we are working with
/// @param numOfPrintOnCycles number of cycles the user WANTS...given in command line by argument -c
/// @param numOfVacCells number of '.' cells
/// @param vacancyRate the % of vacant cells (given as an INTEGER out of 100)
/// @param endlinePercentage the % of endline cells (given as an INTEGER out of 100)
/// @param strengthThreshold the min bound for cell to be happy w/ curr placement
/// @param numOfCycles num of cycles this grid has been through
int moveCells(int totalOccupiedCells, bool infiniteMode, int dimensionOfGrid, char initialGrid[][dimensionOfGrid], int vacancyRate, int endlinePercentage, int strengthThreshold, int numOfCyclesDone);


#endif