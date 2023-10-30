#ifndef _INITIALIZING_GRID_H
#define _INITIALIZING_GRID_H

int calcNumOfVacCells(int totalNumOfCells, int vacancyRate ); 
int calcNumOfEndlines(int totalNumOfCells, int endlinePercentage);
void fisherYatesShuffle(char *flattenedGrid, int lengthOfFlattenedGrid);
void makeGrid(int strengthThreshold, int totalOccupiedCells, int dimensionOfGrid, char initialGrid[][dimensionOfGrid], int vacancyRate, int endlinePercentage);

#endif 