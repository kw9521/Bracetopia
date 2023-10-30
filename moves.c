/// @file moves.c
/// @author KUNLIN WEN, KW9521
/// All functions related moving cells around 
#define _DEFAULT_SOURCE
#include <stdio.h>              // allows for use of printf()
#include <stdbool.h> 
#include <curses.h>

#include "moves.h"
#include "happyMeasure.h"       // Use measureHappyOfCurrCell() and overallHappy()
#include "supportFuncs.h"       // use printOutCurrGrid()

/// checks if curr spot is avali for moving other cells here
/// @param dimensionOfGrid num of cells in each row/col
/// @param currGrid 2d array we are dealing with
/// @param trackCurrCoord  ize 2 array to track the current coordinates
/// @return true if curr spot is VACANT and other cells can move here
bool canMoveHere(int dimensionOfGrid, int currGrid[][dimensionOfGrid], int* trackCurrCoord){
    for (int row = 0; row < dimensionOfGrid; row++) {
        for (int col = 0; col < dimensionOfGrid; col++) {
            
            // if grid's curr pos is a 0 = vacant spot and other cells CAN move here
            if(currGrid[row][col] == 0){ 
                trackCurrCoord[0] = row; 
                trackCurrCoord[1] = col;
                return true;
            }
        }
    }
    return false;
}

/// @brief Prints the grid and its data 
/// @param totalOccupiedCells 'e' cells + 'n' cells
/// @param dimensionOfGrid num of cells in each row/col
/// @param currGrid 2D array representing the current grid
/// @param movesThisCycle Number of moves made in the current cycle
/// @param strengthThreshold minimum bound for a cell to be happy with its current placement
/// @param vacancyRate percentage of vacant cells (given as an INTEGER out of 100)
/// @param endlinePercentage percentage of endline cells (given as an INTEGER out of 100)
/// @param numOfCyclesDone Number of cycles this grid has been through
void printOutGridNData(int totalOccupiedCells, int dimensionOfGrid, char currGrid[][dimensionOfGrid], int movesThisCycle, int strengthThreshold, int vacancyRate, int endlinePercentage, int numOfCyclesDone){
    printOutCurrGrid(dimensionOfGrid, currGrid);
    float overallHappiness = overallHappy(totalOccupiedCells, dimensionOfGrid, currGrid);
    printf("cycle: %d\n", numOfCyclesDone);
    printf("moves this cycle: %d\n", movesThisCycle);
    printf("overall \"happiness\": %0.4f\n", overallHappiness);
    printf("dim: %d, threshold: %d%%, vacancy: %d%%, endlines: %d%%\n", dimensionOfGrid, strengthThreshold, vacancyRate, endlinePercentage);

}

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
int moveCells(int totalOccupiedCells, bool infiniteMode, int dimensionOfGrid, char initialGrid[][dimensionOfGrid], int vacancyRate, int endlinePercentage, int strengthThreshold, int numOfCyclesDone){
    int movesMadeInThisCycle = 0;

    // tracks which cell should move, stay, are empty
    // 0 = cell is empty,  1 = cell needs to move, 2 = cell dont need to move 
    int copyofGrid[dimensionOfGrid][dimensionOfGrid];
    for (int row = 0; row < dimensionOfGrid; row++) { 
        for (int col = 0; col < dimensionOfGrid; col++) {

            // checks what is at curr cell... either 'e' 'n' or '.'
            if(initialGrid[row][col] == '.'){ 
                copyofGrid[row][col] = 0;           // cell is empty and other cells can move here 
            } else { 
                char currCellPreference = initialGrid[row][col]; 
                float currCellHappiness = measureHappyOfCurrCell(currCellPreference, row, col, dimensionOfGrid, initialGrid); // gets its happiness
                
                float strThsIntoFloat = (float) strengthThreshold/100;
                if( currCellHappiness < strThsIntoFloat ){
                    copyofGrid[row][col] = 1;           // curr cell is NOT happy with its neighbors and NEEDS to move... same as X* an O* in write up
                } else if (currCellHappiness == strThsIntoFloat){
                    copyofGrid[row][col] = 2;       
                }
                else { 
                    copyofGrid[row][col] = 2;       // curr cell is the majority and IS HAPPY with its neighbors...DOES NOT need to move
                }
            }
        }
    }
    
    for (int i = 0; i < dimensionOfGrid; i++) {
        for (int j = 0; j < dimensionOfGrid; j++) {
            
            int trackCurrCoord[2]; 
            bool canOrCant = canMoveHere(dimensionOfGrid, copyofGrid, trackCurrCoord);
            
            // Is curr cell UUNAPPY?, If 1 then it is unhappy and needs to move
            if(copyofGrid[i][j] == 1){
                
                // Cannot move to this position
                if (!canOrCant) {
                    return movesMadeInThisCycle;
                } else {
                    // move curr cell to that open cell
                    initialGrid[trackCurrCoord[0]][trackCurrCoord[1]] = initialGrid[i][j]; 
                    // changes curr cell location to be empty
                    initialGrid[i][j] = '.';

                    // changes curr spot to 2 so others cannot move here during this cycle but is still technically vacant 
                    copyofGrid[i][j] = 2;
                    // changes that previously vac spot to 2 to make sure next moves CANNOT move there
                    copyofGrid[trackCurrCoord[0]][trackCurrCoord[1]] = 2;

                    movesMadeInThisCycle++;
                }
            }
        }
    }
    if(!infiniteMode){
        printOutGridNData(totalOccupiedCells, dimensionOfGrid, initialGrid, movesMadeInThisCycle, strengthThreshold, vacancyRate, endlinePercentage, numOfCyclesDone);
    }
    return movesMadeInThisCycle;
}