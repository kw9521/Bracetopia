#define _DEFAULT_SOURCE

#include <stdlib.h>             // to use srandom(). random()
#include <time.h>               // to use time()
#include <stdio.h>              // to use printf()
#include "initializingGrid.h"

void fisherYatesShuffle(char *flattenedGrid, int lengthOfFlattenedGrid) {
    for (int i = lengthOfFlattenedGrid - 1; i > 0; i--) {
        int j = random() % (i + 1);

        // Swap elements at positions i and j
        char temp = flattenedGrid[i];
        flattenedGrid[i] = flattenedGrid[j];
        flattenedGrid[j] = temp;
    }
}

void makeGrid(int dimensionOfGrid, char initialGrid[][dimensionOfGrid], int vacancyRate, int endlinePercentage) {
    
    // shuffling method
    int numOfCells = dimensionOfGrid * dimensionOfGrid;
    int numOfVacancy = (int)(numOfCells * ((float)vacancyRate/100));              // truncates 
    int numOfCellsAfterVac = numOfCells - numOfVacancy; 
    int numOfEndlines = (int)(numOfCellsAfterVac * ((float)endlinePercentage/100));       // truncates 

    int lengthOfFlattenedGrid = dimensionOfGrid*dimensionOfGrid;
    char flattenedGrid[lengthOfFlattenedGrid];
    
    int currIndex = 0;
    for (int i = 0; i < (lengthOfFlattenedGrid); i++){
        flattenedGrid[i] = 'n';
    }

    int x = numOfVacancy;
    for (int i = 0; i < (lengthOfFlattenedGrid) && x > 0; i++){
        flattenedGrid[i] = '.';
        x--;
        currIndex++;
    }

    int y = numOfEndlines;
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

