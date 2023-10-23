// The file containing your main() function must be named bracetopia.c

#define _DEFAULT_SOURCE        
#include <unistd.h>             // to use usleep()
#include <stdlib.h>             // to use srandom() and random()
#include <curses.h>             // allows you to do cursor-controlled output management
#include <stdbool.h>            // allows for use of booleans
#include <stdio.h>              // to use printf()


#include "processCommandLines.h"
#include "initializingGrid.h"

int main( int argc, char * argv[] ) {

    // Example: $bracetopia -c9 -d 10 -s50 -v 15 -e50
    if (argc == 0){
        fprintf(stderr, "No arguments");
        return 1; 
    }

    srandom(41);
    int dimensionOfGrid = 15;
    int strengthThreshold = 50;
    int vacancyRate = 20;
    int endlinePercentage = 60;
    int sleepDelay = 900000;
    int numOfPrintOnCycles;
    // bool infiniteMode = true;           // default is infinite mode, if user enters -c then this will be false bc it'll be print mode 

    // process command line arguments
    int letter;
    char *ptr;
    while((letter = getopt(argc, argv, "hd:s:v:e:c:t")) != -1){
        int value;
        if(optarg){
            value = (int) strtol(optarg, &ptr, 10);
        }

        switch(letter){
            case('h'):
                printHelpMessage();
                break;
            case('d'):          // sets dimensions
                if(optarg){
                    setDimensionOfGrid(&dimensionOfGrid, value);
                } else {
                    fprintf(stderr, "Missing dimension values");
                    exit(EXIT_FAILURE);
                }
                break;
            case('c'):          // set the cycle count amd turns on print mode
                if(optarg){
                    setNumOfPrintCycles(&numOfPrintOnCycles ,value);
                    // infiniteMode = false; 
                }
                break;
            case('s'):          // sets strength threshold
                if(optarg){
                    setStrengthThreshold(&strengthThreshold, value);
                } else {
                    fprintf(stderr, "Missing strength threshold values");
                    exit(EXIT_FAILURE);
                }
                break;
            case('v'):          // sets vacancy rate
                if(optarg){
                    setVacancyRate(&vacancyRate, value);
                } else {
                    fprintf(stderr, "Missing vacancy rate values");
                    exit(EXIT_FAILURE);
                }
                break;
            case('e'):          // sets endline percentage
                if(optarg){
                    setEndlinePercentage(&endlinePercentage, value);
                } else {
                    fprintf(stderr, "Missing endline percentage values");
                    exit(EXIT_FAILURE); 
                }
                break;
            case('t'):          // sets sleep delay
                setSleepDelay(&sleepDelay, value);
                break;
        }
    }

    // Initialize all internal data structures (the grid, etc.)
    char initialGrid[dimensionOfGrid][dimensionOfGrid];
    makeGrid(dimensionOfGrid, initialGrid, vacancyRate, endlinePercentage);
    
    // testing, printing the initialGrid out
    printf("\nshuffled grid: \n");
    for (int i = 0; i < dimensionOfGrid; i++) {
        for (int j = 0; j < dimensionOfGrid; j++) {
            printf("%c", initialGrid[i][j]);
        }
        printf("\n");
    }


    

}