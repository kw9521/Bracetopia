#define _DEFAULT_SOURCE

#include <stdio.h>              // allows for use of printf()
#include "happyMeasure.h"

/// meaures the happiness of current cell by checking the preference of the neighbors around it 
/// @param currCellPreference current cell's identity...is either 'n' or 'e'
/// @param row curr cell's row
/// @param col curr cell's col
/// @param dimensionOfGrid # of cells in each row/col...square 2D array
/// @param initialGrid grid we are working with
/// @return the happiness of curr cell
float measureHappyOfCurrCell(char currCellPreference, int row, int col, int dimensionOfGrid, char initialGrid[][dimensionOfGrid]){    
    
    float currCellHappiness;

    int happy = 0;
    int totalNeighbors = 0;
    char currPref = currCellPreference;

    // if curr cell is '.', we dont need to calculate its happiness 
    if(currPref == '.'){ 
        return 0.0;
    }

    // top left corner
    if((row-1 >= 0) && (col-1 >= 0)){
        if(initialGrid[row-1][col-1] == currPref){ happy++; totalNeighbors++; } 
        else if (initialGrid[row-1][col-1] == '.'){ ; } 
        else { totalNeighbors++;} 
    }

    // top middle
    if((col-1 >= 0)){
        if(initialGrid[row][col-1] == currPref){ happy++; totalNeighbors++; } 
        else if (initialGrid[row][col-1] == '.'){ ; } 
        else { totalNeighbors++;}
    }

    // top right
    if((row+1 < dimensionOfGrid) && (col-1 >= 0)){
        if(initialGrid[row+1][col-1] == currPref){ happy++; totalNeighbors++; } 
        else if (initialGrid[row+1][col-1] == '.'){ ; } 
        else { totalNeighbors++; }
    }

    // middle left
    if((row-1 >= 0)){
        if(initialGrid[row-1][col] == currPref){ happy++; totalNeighbors++; } 
        else if (initialGrid[row-1][col] == '.'){ ; } 
        else{ totalNeighbors++; }
    }

    // middle right
    if((row+1 < dimensionOfGrid)){
        if(initialGrid[row+1][col] == currPref){ happy++; totalNeighbors++; } 
        else if (initialGrid[row+1 ][col] == '.'){ ; } 
        else{ totalNeighbors++; }
    }

    // bottom left
    if((row-1 >= 0) && (col+1 < dimensionOfGrid)){
        if(initialGrid[row-1][col+1] == currPref){ happy++; totalNeighbors++;} 
        else if (initialGrid[row-1][col+1] == '.'){ ; } 
        else{ totalNeighbors++; }
    }

    // bottom middle
    if((col+1 < dimensionOfGrid)){
        if(initialGrid[row][col+1] == currPref){ happy++; totalNeighbors++; } 
        else if (initialGrid[row][col+1] == '.'){ ; } 
        else{ totalNeighbors++; }
    }

    // bottom right
    if((row+1 < dimensionOfGrid) && (col+1 < dimensionOfGrid)){
        if(initialGrid[row+1][col+1] == currPref){ happy++; totalNeighbors++;} 
        else if (initialGrid[row+1][col+1] == '.'){ ; } 
        else{ totalNeighbors++; }
    }

    // if there are no neighbors around curr cell, the cell is automatically happy 
    if(totalNeighbors == 0){
        currCellHappiness = 1.0;
        return currCellHappiness;
    }

    currCellHappiness = (float)happy/totalNeighbors;
    return currCellHappiness;
}

/// goes thru every cell in 2D array, calcualtes their happiness, stores that number into happyArray[]
/// averages up every number in happyArray[] and returns that result
/// @param occupiedCells the number of 'n' and 'e' agents in initialGrid[][]
/// @param dimensionOfGrid number of cells in each row/col
/// @param initialGrid the grid we are wroking with 
/// @return the avg happiness of the grid passed in
float overallHappy(int occupiedCells, int dimensionOfGrid, char initialGrid[][dimensionOfGrid]){
    float everyonesTotalHappiness = 0.0;

    for (int i = 0; i < dimensionOfGrid; i++) {
        for (int j = 0; j < dimensionOfGrid; j++) {
            
            // initialGrid[i][j] = 'e';
            char currCellPreference = initialGrid[i][j];
            
            // checks if curren cell is a 'e' or a 'n', if not then skips
            if (currCellPreference == '.'){ ;
            } else {
                everyonesTotalHappiness += measureHappyOfCurrCell(currCellPreference, i, j, dimensionOfGrid, initialGrid);
            }
        }
    }

    // averages their happiness 
    float avgHappiness = everyonesTotalHappiness/occupiedCells;
    return avgHappiness;
}

