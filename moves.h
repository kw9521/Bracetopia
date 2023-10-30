#ifndef _MOVES_H
#define _MOVES_H

bool canMoveHere(int dimensionOfGrid, int grid[][dimensionOfGrid], int trackCurrCoord[2]);
void printOutGridNData(int totalOccupiedCells, int dimensionOfGrid, char currGrid[][dimensionOfGrid], int movesThisCycle, int strengthThreshold, int vacancyRate, int endlinePercentage, int numOfCyclesDone);
int moveCells(int totalOccupiedCells, bool infiniteMode, int dimensionOfGrid, char initialGrid[][dimensionOfGrid], int vacancyRate, int endlinePercentage, int strengthThreshold, int numOfCyclesDone);

#endif