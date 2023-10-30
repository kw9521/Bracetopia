/// @file bracetopia.c
/// @author KUNLIN WEN, KW9521
/// The file containing main() function must be named bracetopia.c


#define _DEFAULT_SOURCE        
#include <unistd.h>             // to use usleep()
#include <stdlib.h>             // to use srandom() and random()
#include <curses.h>             // allows you to do cursor-controlled output management
#include <stdbool.h>            // allows for use of booleans
#include <stdio.h>              // to use printf()

#include "processCommandLines.h"
#include "initializingGrid.h"
#include "happyMeasure.h"
#include "supportFuncs.h"
#include "moves.h"

int main( int argc, char * argv[] ) {

    // Example: $bracetopia -c9 -d 10 -s50 -v 15 -e50
    if (argc == 0){
        fprintf(stderr, "No arguments");
        return 1; 
    }

    int dimensionOfGrid = 15;
    int strengthThreshold = 50;
    int vacancyRate = 20;
    int endlinePercentage = 60;
    int sleepDelay = 900000;
    int numOfPrintOnCycles;
    bool infiniteMode = true;           // default is infinite mode, if user enters -c then this will be false bc it'll be print mode 

    // process command line arguments
    int letter;
    char *ptr;
    while((letter = getopt(argc, argv, "hd:s:v:e:c:t")) != -1){
        int value;
        if(optarg){
            value = (int)strtol(optarg, &ptr, 10);
        }

        switch(letter){
            case('h'):
                printHelpMessage();
                break;
            case('d'):          // sets dimensions
                if(optarg){
                    setDimensionOfGrid(&dimensionOfGrid, value);
                } else {
                    fprintf(stderr, "option requires an argument -- '%c'\n", letter);
                    fprintf(stderr,"usage:\n");
                    fprintf(stderr,"bracetopia [-h] [-t N] [-c N] [-d D] [-s S] [-v V] [-e E]\n");
                    exit(EXIT_FAILURE);
                }
                break;
            case('c'):          // set the cycle count amd turns on print mode
                if(optarg){
                    setNumOfPrintCycles(&numOfPrintOnCycles, value);
                    infiniteMode = false; 
                } else {
                    fprintf(stderr, "option requires an argument -- '%c'\n", letter);
                    fprintf(stderr,"usage:\n");
                    fprintf(stderr,"bracetopia [-h] [-t N] [-c N] [-d D] [-s S] [-v V] [-e E]\n");
                }
                break;
            case('s'):          // sets strength threshold
                if(optarg){
                    setStrengthThreshold(&strengthThreshold, value);
                } else {
                    fprintf(stderr, "option requires an argument -- '%c'\n", letter);
                    fprintf(stderr,"usage:\n");
                    fprintf(stderr,"bracetopia [-h] [-t N] [-c N] [-d D] [-s S] [-v V] [-e E]\n");
                    exit(EXIT_FAILURE);
                }
                break;
            case('v'):          // sets vacancy rate
                if(optarg){
                    setVacancyRate(&vacancyRate, value);
                } else {
                    fprintf(stderr, "option requires an argument -- '%c'\n", letter);
                    fprintf(stderr,"usage:\n");
                    fprintf(stderr,"bracetopia [-h] [-t N] [-c N] [-d D] [-s S] [-v V] [-e E]\n");
                    exit(EXIT_FAILURE);
                }
                break;
            case('e'):          // sets endline percentage
                if(optarg){
                    setEndlinePercentage(&endlinePercentage, value);
                } else {
                    fprintf(stderr, "option requires an argument -- '%c'\n", letter);
                    fprintf(stderr,"usage:\n");
                    fprintf(stderr,"bracetopia [-h] [-t N] [-c N] [-d D] [-s S] [-v V] [-e E]\n");
                    exit(EXIT_FAILURE); 
                }
                break;
            case('t'):          // sets sleep delay
                setSleepDelay(&sleepDelay, value);
                break;
        }
    }

    // keeping track of how many cells were occupied
    int totalCells = dimensionOfGrid*dimensionOfGrid;
    // 100 total cells, 20% of that is vac = 20 vac cells
    int numOfVacCells = calcNumOfVacCells(totalCells, vacancyRate); 
    // Of the rest 80 cells, 60% are endline cells = 80 * 0.6 = 48 'e' cells
    int numOfEndlineCells = calcNumOfEndlines((totalCells - numOfVacCells), endlinePercentage);
    // rest are 'n' cells
    int numOfNewlineCells = totalCells - numOfVacCells - numOfEndlineCells;

    // calculating everyones' happiness
    int totalOccupiedCells = numOfEndlineCells+numOfNewlineCells;    

    // Initialize all internal data structures (the grid, etc.)
    char initialGrid[dimensionOfGrid][dimensionOfGrid];
    makeGrid(strengthThreshold, totalOccupiedCells, dimensionOfGrid, initialGrid, vacancyRate, endlinePercentage);
    
    // !infiniteMode = is in PRINT mode
    if (!infiniteMode){
        for (int numOfCyclesDone = 1; numOfCyclesDone <= numOfPrintOnCycles; numOfCyclesDone++){
            moveCells(totalOccupiedCells, infiniteMode, dimensionOfGrid, initialGrid, vacancyRate, endlinePercentage, strengthThreshold, numOfCyclesDone);
        }
    } else {
        float overallHappiness;
        int movesMadeInThisCycle = 0;
        int numOfCyclesDone = 0;

        WINDOW* window = NULL;
        window = initscr();

        printCurrGridWithCurses(dimensionOfGrid, initialGrid);
        refresh(); 

        overallHappiness = overallHappy(totalOccupiedCells, dimensionOfGrid, initialGrid);
        int row = getcury(window);
        mvprintw(row, 0, "cycle: %d\n", 0);
        row++; 
        mvprintw(row, 0, "moves this cycle: %d\n", movesMadeInThisCycle);
        row++;
        mvprintw(row, 0, "overall \"happiness\": %0.4f\n", overallHappiness);
        row++;
        mvprintw(row+1, 0, "dim: %d, threshold: %d%%, vacancy: %d%%, endlines: %d%%\n", dimensionOfGrid, strengthThreshold, vacancyRate, endlinePercentage);
        mvprintw(row+1, 0, "Use Control-C to quit.");
        refresh();
        
        usleep(sleepDelay);
        clear();

        // loops infinitely and updates grid
        while(infiniteMode){
            int movesMadeInThisCycle = moveCells(totalOccupiedCells, infiniteMode, dimensionOfGrid, initialGrid, vacancyRate, endlinePercentage, strengthThreshold, numOfCyclesDone);
            numOfCyclesDone++;

            printCurrGridWithCurses(dimensionOfGrid, initialGrid);
            refresh();

            float overallHappiness  = overallHappy(totalOccupiedCells, dimensionOfGrid, initialGrid);
            int row = getcury(window);
            mvprintw(row, 0, "cycle: %d\n", numOfCyclesDone);
            row++; 
            mvprintw(row, 0, "moves this cycle: %d\n", movesMadeInThisCycle);
            row++;
            mvprintw(row, 0, "overall \"happiness\": %0.4f\n", overallHappiness);
            row++;
            mvprintw(row, 0, "dim: %d, threshold: %d%%, vacancy: %d%%, endlines: %d%%\n", dimensionOfGrid, strengthThreshold, vacancyRate, endlinePercentage);
            mvprintw(row+1, 0, "Use Control-C to quit.");
            refresh();
            usleep(sleepDelay);
            clear();
        }
        delwin(window);
        endwin();
        refresh();
    }
        
}
