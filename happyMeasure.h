/// @file happyMeasure.h
/// @author KUNLIN WEN, KW9521
/// All functions related to calcualting happiness but in .h format

#ifndef _HAPPY_MEASURE_H
#define _HAPPY_MEASURE_H

/// meaures the happiness of current cell by checking the preference of the neighbors around it 
/// @param currCellPreference current cell's identity...is either 'n' or 'e'
/// @param row curr cell's row
/// @param col curr cell's col
/// @param dimensionOfGrid # of cells in each row/col...square 2D array
/// @param initialGrid grid we are working with
/// @return the happiness of curr cell
float measureHappyOfCurrCell(char currCellPreference, int row, int col, int dimensionOfGrid, char initialGrid[][dimensionOfGrid]); 

/// goes thru every cell in 2D array, calcualtes their happiness, stores that number into happyArray[]
/// averages up every number in happyArray[] and returns that result
/// @param occupiedCells the number of 'n' and 'e' agents in initialGrid[][]
/// @param dimensionOfGrid number of cells in each row/col
/// @param initialGrid the grid we are wroking with 
/// @return the avg happiness of the grid passed in
float overallHappy(int occupiedCells, int dimensionOfGrid, char initialGrid[][dimensionOfGrid]);

#endif