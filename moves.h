#ifndef _MOVES_H
#define _MOVES_H

void flatten2DArr(int dimensionOfGrid, char source2DArr[][dimensionOfGrid], char flattened1DArr[]);
void findAllVacSpots(int sizeOfFlatGrid, char flattenedGrid[sizeOfFlatGrid], int vacSpots, int listOfAvaliSpots[vacSpots]);
void movingAgents(int movesThisCycle, int dimensionOfGrid, char currGrid[][dimensionOfGrid], int vacSpots, int strengthThreshold);
void printOutGridNData(int dimensionOfGrid, char currGrid[][dimensionOfGrid], int movesThisCycle, float overallHappiness, int strengthThreshold, int vacancyRate, int endlinePercentage, int numOfCycles); 
void moveXNumOfTimes(int totalOccupiedCells, int numOfPrintOnCycles, int dimensionOfGrid, char initialGrid[][dimensionOfGrid], int numOfVacCells, int vacancyRate, int endlinePercentage, int strengthThreshold );

#endif