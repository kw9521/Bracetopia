#define _DEFAULT_SOURCE

#include <stdlib.h>             // to use srandom(). random()
#include "supportFunctions.h"

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
    int numOfVacancy = (int)(numOfCells * ((float)vacancyRate/100));              // truncates the float 
    int numOfEndlines = (int)(numOfCells * ((float)endlinePercentage/100));       // truncates 
    int numOfNewlines = numOfCells - (numOfVacancy + numOfEndlines);


    int lengthOfFlattenedGrid = dimensionOfGrid*dimensionOfGrid;
    char flattenedGrid[lengthOfFlattenedGrid];
    
    int currRow = 0;
    int currCol = 0; 
    
    // fill everything with 'n'
    for (int i = 0; i < dimensionOfGrid; i++){
        for (int j = 0; j < dimensionOfGrid; j++){
            flattenedGrid[i * dimensionOfGrid + j] = 'n';
        }
    }

    // Fill the first x cells with '.'
    int x = numOfVacancy;
    for (int i = 0; i < dimensionOfGrid && x > 0; i++) {
        for (int j = 0; j < dimensionOfGrid && x > 0; j++) {
            flattenedGrid[i * dimensionOfGrid + j] = '.';
            currCol +=1;
            x--;
        }
        currRow +=1;
        x--;
    }

    // Fill the next y cells with 'e'
    int y = numOfEndlines;
    for (int i = currRow; i < y && y > 0; i++) {
        for (int j = currCol; j < dimensionOfGrid && y > 0; j++) {
            flattenedGrid[i * dimensionOfGrid + j] = 'e';
            currCol +=1;
            y--;
        }
        currRow +=1;
        x--;
    }

    // Seed the random number generator
    srand(time(NULL));

    // Shuffle the flatArray using Fisher-Yates shuffle
    fisherYatesShuffle(&flattenedGrid, lengthOfFlattenedGrid);

    // Reconstruct the 2D array with the shuffled elements
    for (int i = 0; i < dimensionOfGrid; i++) {
        for (int j = 0; j < dimensionOfGrid; j++) {
            initialGrid[i][j] = flattenedGrid[i * dimensionOfGrid + j];
        }
    }

    return initialGrid;

}

