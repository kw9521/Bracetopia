#define _DEFAULT_SOURCE
#include <stdio.h>      // allows for use of printf()

#include "moves.h"
#include "happyMeasure.h"       // Use measureHappyOfCurrCell() and overallHappy()
#include "supportFuncs.h"       // use printOutCurrGrid()

void flatten2DArr(int dimensionOfGrid, char source2DArr[][dimensionOfGrid], char flattened1DArr[]){
    for (int i = 0; i < dimensionOfGrid; i++) {
        for (int j = 0; j < dimensionOfGrid; j++) {
            flattened1DArr[i * dimensionOfGrid + j] = source2DArr[i][j]; 
        }
    }
}

/// detects the index of where all the '.' are located inside the 1D array and adds that index into the listOfAllAvaliSpots[]
/// @param sizeOfFlatGrid size of the grid that contains all of the 'e', 'n' and '.'s; should be dim*dim
/// @param flattenedGrid grid that contains all of the 'e', 'n' and '.'s
/// @param vacSpots the number of '.'s in the grid
/// @param listOfAvaliSpots an array to keep track of the indices where all the '.'s are located
void findAllVacSpots(int sizeOfFlatGrid, char flattenedGrid[sizeOfFlatGrid], int vacSpots, int listOfAvaliSpots[vacSpots]){
    int counter = 0;
    for(int i = 0; i<sizeOfFlatGrid; i++){
        if (flattenedGrid[i] == '.'){
            listOfAvaliSpots[counter] = i;
            counter++;
        }
    }
}

/// From current grid, moves the unhappy agents to the next vacant spot in a top-bottom, left-right sequence
/// @param movesThisCycle keeps track of how many agents moved in this cycle
/// @param dimensionOfGrid size of the row/col of 2D array, row = col = dimensionOfGrid 
/// @param currGrid current grid we are working with
/// @param vacSpots number of vacant spots ('.') n grid 
/// @param strengthThreshold threshold for agent to be happy in current spot 
void movingAgents(int movesThisCycle, int dimensionOfGrid, char currGrid[][dimensionOfGrid], int vacSpots, int strengthThreshold){

    int sizeOfFlatGrid = dimensionOfGrid*dimensionOfGrid; 
    char flattenedGrid[sizeOfFlatGrid];                   
    
    flatten2DArr(dimensionOfGrid, currGrid, flattenedGrid);
    
    // keeps track of all the avali spots in 1D array indexing
    int listOfAvaliSpots[vacSpots];    
    int currIndexOfAvaliSpots = 0;

    // finding all avali spots
    findAllVacSpots(sizeOfFlatGrid, flattenedGrid, vacSpots, listOfAvaliSpots); 

    // loops through the 1D array to check curr agent's happiness and updates thir spot
    for (int i = 0; i < sizeOfFlatGrid; i++) {
        float currCellHappy;

        // if i is at index 11 and dim = 10, it is basically row 1, 2nd # of 2D array which is [1][1]
        // if i is at 2, it is at row 0 index 2 of array or the 3rd # inserted into array
        // if i is at 9, it is at row 0, index 9
        // if i is 20, it is row 2, col 0 
        int row = i/(dimensionOfGrid);
        int col = i%(dimensionOfGrid);   

        char currCellPreference = currGrid[row][col];
        currCellHappy = measureHappyOfCurrCell(currCellPreference, row, col, dimensionOfGrid, currGrid);

        if(currCellHappy <= strengthThreshold){

            // check if the list of vac spots is exhuasted
            if (currIndexOfAvaliSpots < vacSpots){
                
                // sets curr index to be vac cell
                flattenedGrid[i] = '.';
                
                // sets the  vac spot to be whatever curr cell's pref is
                flattenedGrid[listOfAvaliSpots[currIndexOfAvaliSpots]] = currCellPreference;
                currIndexOfAvaliSpots++;
                movesThisCycle++;
            } else {
                // there are no more vac spots left in this grid, must exit loop
                break;
            }
            
        }

    }

}

void printOutGridNData(int dimensionOfGrid, char currGrid[][dimensionOfGrid], int movesThisCycle, float overallHappiness, int strengthThreshold, int vacancyRate, int endlinePercentage, int numOfCycles){

    // print out curr grid
    printOutCurrGrid(dimensionOfGrid, currGrid);

    printf("cycle: %d\n", numOfCycles);
    printf("moves this cycle: %d\n", movesThisCycle);
    printf("overall \"happiness\": %0.4f\n", overallHappiness);
    printf("dim: %d, threshold: %d%%, vacancy: %d%%, endlines: %d%%", dimensionOfGrid, strengthThreshold, vacancyRate, endlinePercentage);

}

// func that main will call
// calls movingAgents to calculate moving and etc
// calls printOutGridNData to print out the visual 
void moveXNumOfTimes(int totalOccupiedCells, int numOfPrintOnCycles, int dimensionOfGrid, char initialGrid[][dimensionOfGrid], int numOfVacCells, int vacancyRate, int endlinePercentage, int strengthThreshold ){
    int numOfCyclesDone = 0;
    
    // print out INITIAL UNCHANGED CYCLE 0 grid
    if(numOfCyclesDone == 0){
        float overallHappyness = overallHappy(totalOccupiedCells, dimensionOfGrid, initialGrid);
        printOutGridNData(dimensionOfGrid, initialGrid, 0, overallHappyness, strengthThreshold, vacancyRate, endlinePercentage, 0);
        numOfCyclesDone++;
    }

    // prints out the cycles AFTER initial 
    for (int i = 0; i < numOfPrintOnCycles; i++) {
        int movesThisCycle = 0; 
        movingAgents(movesThisCycle, dimensionOfGrid, initialGrid, numOfVacCells, strengthThreshold);
        
        float overallHappyness = overallHappy(totalOccupiedCells, dimensionOfGrid, initialGrid);
        printOutGridNData(dimensionOfGrid, initialGrid, movesThisCycle, overallHappyness, strengthThreshold, vacancyRate, endlinePercentage, numOfCyclesDone);
        numOfCyclesDone++;
    }
    


}
