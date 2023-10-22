// The file containing your main() function must be named bracetopia.c.

#define _DEFAULT_SOURCE        
#include <unistd.h>             // to use usleep()
#include <stdlib.h>             // to use srandom(). random()
#include <curses.h>             // Allows you to do cursor-controlled output management
#include "processCommandLines.c"

extern int numOfPrintOnCycles;

int main( int argc, char * argv[] ) {

    // Example: $bracetopia -c9 -d 10 -s50 -v 15 -e50
    if (argc == 0){
        fprintf(stderr, "No arguments");
        return 1; 
    }

    int letter;
    while(letter = getopt(argc, argv, "hd:s:v:e:c:t") != -1){
        switch(letter){
            case('h'):
                printHelpMessage();
                break;
            case('d'):          // sets dimensions
                if(optarg){
                    setDimensionOfGrid(optarg);
                } else {
                    fprintf(stderr, "Missing dimension values");
                }
                break;
            case('c'):          // set the cycle count amd turns on print mode
                if(optarg){
                    setNumOfPrintCycles(optarg);
                }
                break;
            case('s'):          // sets strength threshold
                if(optarg){
                    setStrengthThreshold(optarg);
                } else {
                    fprintf(stderr, "Missing strength threshold values");
                }
                break;
            case('v'):          // sets vacancy rate
                if(optarg){
                    setVacancyRate(optarg);
                } else {
                    fprintf(stderr, "Missing vacancy rate values");
                }
                break;
            case('e'):          // sets endline percentage
                if(optarg){
                    setEndlinePercentage(optarg);
                } else {
                    fprintf(stderr, "Missing endline percentage values");
                }
            case('t'):          // sets sleep delay
                setSleepDelay(optarg);
                break;
        }

    }
    

}