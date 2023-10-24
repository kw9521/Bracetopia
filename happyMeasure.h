#ifndef _HAPPY_MEASURE_H
#define _HAPPY_MEASURE_H

float measureHappyOfCurrCell(char currCellPreference, int row, int col, int dimensionOfGrid, char initialGrid[][dimensionOfGrid]);
float overallHappy(int occupiedCells, int dimensionOfGrid, char initialGrid[][dimensionOfGrid]);

#endif