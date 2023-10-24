#define _DEFAULT_SOURCE

#include "happyMeasure.h"

float measureHappyOfCurrCell(char currCellPreference, int row, int col, int dimensionOfGrid, char initialGrid[][dimensionOfGrid]){    
    
float currCellHappiness;

    int happy = 0;
    int unhappy = 0;
    int totalNeighbors = 0;
    char currPref = currCellPreference;

    // top left corner
    if((row-1 >= 0) && (col-1 >= 0)){
        if(initialGrid[row-1][col-1] == currPref){
            happy++;
            totalNeighbors++;
        } else{
            unhappy++;
        }
    }
    
    // top middle
    if((col-1 >= 0)){
        if(initialGrid[row][col-1] == currPref){
            happy++;
            totalNeighbors++;
        } else{
            unhappy++;
        }
    }

    // top right
    if((row+1 < dimensionOfGrid) && (col-1 >= 0)){
        if(initialGrid[row+1][col-1] == currPref){
            happy++;
            totalNeighbors++;
        } else{
            unhappy++;
        }
    }

    // middle left
    if((row-1 >= 0)){
        if(initialGrid[row-1][col] == currPref){
            happy++;
            totalNeighbors++;
        } else{
            unhappy++;
        }
    }

    // middle right
    if((row+1 < dimensionOfGrid)){
        if(initialGrid[row+1][col] == currPref){
            happy++;
            totalNeighbors++;
        } else{
            unhappy++;
        }
    }

    // bottom left
    if((row-1 >= 0) && (col+1 < dimensionOfGrid)){
        if(initialGrid[row-1][col+1] == currPref){
            happy++;
            totalNeighbors++;
        } else{
            unhappy++;
        }
    }

    // bottom middle
    if((col+1 < dimensionOfGrid)){
        if(initialGrid[row][col+1] == currPref){
            happy++;
            totalNeighbors++;
        } else{
            unhappy++;
        }
    }

    // bottom right
    if((row+1 < dimensionOfGrid) && (col+1 < dimensionOfGrid)){
        if(initialGrid[row+1][col+1] == currPref){
            happy++;
            totalNeighbors++;
        } else{
            unhappy++;
        }
    }

    currCellHappiness = (float)happy/totalNeighbors;
    return currCellHappiness;
}


float overallHappy(int occupiedCells, int dimensionOfGrid, char initialGrid[][dimensionOfGrid]){

    // to keep track of every occupied cell's happiess so far
    float happyArray[occupiedCells];

    for (int i = 0; i < dimensionOfGrid; i++) {
        for (int j = 0; j < dimensionOfGrid; j++) {
            
            // initialGrid[i][j] = 'e';
            char currCellPreference = initialGrid[i][j];
            
            // checks if curren cell is a 'e' or a 'n'
            if (currCellPreference == '.'){
                break;
            } else {
                happyArray[i * dimensionOfGrid + j] = measureHappyOfCurrCell(currCellPreference, i, j, dimensionOfGrid, initialGrid);
            }
        }
    }

    float everyonesTotalHappiness;
    for (int i = 0; i< occupiedCells; i++){
        everyonesTotalHappiness += happyArray[i];
    }

    float avgHappiness = everyonesTotalHappiness/occupiedCells;
    return avgHappiness;
}