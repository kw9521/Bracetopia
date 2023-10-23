#define _DEFAULT_SOURCE

#include <stdlib.h>             // to use srandom(). random()
#include <time.h>               // to use time()
#include <stdio.h>              // to use printf()
#include "initializingGrid.h"

void fisherYatesShuffle(char *flattenedGrid, int lengthOfFlattenedGrid) {
    for (int i = 0; i <= lengthOfFlattenedGrid - 2; i++) {
        int j = i + (random() % (lengthOfFlattenedGrid - i));

        // Swap elements at index i and index j
        char temp = flattenedGrid[i];
        flattenedGrid[i] = flattenedGrid[j];
        flattenedGrid[j] = temp;
    }
}

int calcNumOfVacCells(int totalNumOfCells, int vacancyRate ){
    int numOfVacancy = (int)(totalNumOfCells * ((float)vacancyRate/100));              // truncates 
    return numOfVacancy;
}

int calcNumOfEndlines(int totalNumOfCells, int endlinePercentage){
    int numOfEndlines = (int)(totalNumOfCells * ((float)endlinePercentage/100));       // truncates 
    return numOfEndlines;
}

void makeGrid(int dimensionOfGrid, char initialGrid[][dimensionOfGrid], int vacancyRate, int endlinePercentage) {
    
    // shuffling method
    int numOfCells = dimensionOfGrid * dimensionOfGrid;
    int numOfVacancy = calcNumOfVacCells(dimensionOfGrid, vacancyRate);
    int numOfCellsAfterVac = numOfCells - numOfVacancy; 
    int numOfEndlines = calcNumOfEndlines(numOfCellsAfterVac, endlinePercentage);       // truncates 

    // length of the 1D array is the same as total # of cells in 2D array
    int lengthOfFlattenedGrid = numOfCells;
    char flattenedGrid[lengthOfFlattenedGrid];
    
    int currIndex = 0;
    // set everything to be 'n' cells first
    for (int i = 0; i < (lengthOfFlattenedGrid); i++){
        flattenedGrid[i] = 'n';
    }

    int x = numOfVacancy;
    // change the first x amount to be '.' cells
    for (int i = 0; i < (lengthOfFlattenedGrid) && x > 0; i++){
        flattenedGrid[i] = '.';
        x--;
        currIndex++;
    }

    int y = numOfEndlines;
    // change the next y amount to be 'e' cells
    for (int i = currIndex; i < (lengthOfFlattenedGrid) && y > 0; i++){
        flattenedGrid[i] = 'e';
        y--;
        currIndex++;
    }

    // Seed the random number generator
    srand(time(NULL));



    // testing, print flattenedgrid PRESHUFFLED
    for(int i = 0; i < lengthOfFlattenedGrid; i++){
        printf("%c ", flattenedGrid[i]);
    }
    printf("\nNum of Cells: %d\n", numOfCells);
    printf("Num of Vacancy: %d\n", numOfVacancy);
    printf("Num of EndLines: %d\n", numOfEndlines);




    // Shuffle the flatArray using Fisher-Yates shuffle
    fisherYatesShuffle(flattenedGrid, lengthOfFlattenedGrid);

    // Reconstruct the 2D array with the shuffled elements
    for (int i = 0; i < dimensionOfGrid; i++) {
        for (int j = 0; j < dimensionOfGrid; j++) {
            initialGrid[i][j] = flattenedGrid[i * dimensionOfGrid + j];
        }
    }

}

