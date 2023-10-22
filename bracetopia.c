// The file containing your main() function must be named bracetopia.c.

#define _DEFAULT_SOURCE        
#include <unistd.h>             // to use usleep()
#include <stdlib.h>             // to use srandom(). random()
#include <curses.h>             // Allows you to do cursor-controlled output management


void printHelpMessage(){
    printf("usage:\n"
           "bracetopia [-h] [-t N] [-c N] [-d D] [-s S] [-v V] [-e E]\n"
            "Option      Default   Example   Description \n"
            "'-h'        n/a       -h        print this usage message.\n"
            "'-t N'      900000    -t 5000   cycle delay, in microseconds.\n"
            "'-c N'      n/a       -c4       cycle count maximum value.\n"
            "'-d D'      15        -d    7   width and height dimension.\n"
            "'-s S'      50        -s 30     strength of preference.\n"
            "'-v V'      20        -v30      percent vacancies.\n"
            "'-e E'      60        -e75      percent of braces that are Endline.\n");
}

int main( int argc, char * argv[] ) {

    // Example: $bracetopia -c9 -d 10 -s50 -v 15 -e50
    if (argc == 0){
        fprintf(stderr, "No arguments");
        return 1; 
    }

    // default values, will be overridden 
    int dimensionOfGrid = 15;
    int strengthThreshold = 50;
    int vacancyRate = 20;
    int endLinePercentage = 60;
    int numOfPrintOnCycles;
    int sleepDelay = 900000;

    unsigned int countCyclePrintMode;

    // first parse by "-"
    char *token = strtok(argv[0], "-");
    // [c9 ] [d 10 ] [s50 ] [v 15 ] [e50]
    while (token != NULL) {
        char letter = token[0];

        char *ptr;

        // [d 10 ] will become ['10']
        char *token2 = strtok(token, " abcdefghijklmnopqrstuvwxyz");
        
        // casts the the '10' into a long 10  
        long theNumber = strtol(token2, &ptr, 10);
        
        switch(letter){
            case('h'):
                printHelpMessage;
                break;
            case('d'):
                dimensionOfGrid = theNumber;
                break;
            case('c'):
                // turn on PRINT MODE HEREEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE TBD TBD TBD TBD TBD TBD
                
                // cycle cannot be negative 
                if(theNumber < 0){
                    fprintf(stderr, "Number of cycle in print mode is less than 0");
                    return 1;
                } 
                countCyclePrintMode = theNumber; 
                break;
            case('s'):
                strengthThreshold = theNumber;
                break;
            case('v'):
                vacancyRate = theNumber;
                break;
            case('e'):
                endLinePercentage = theNumber;
                break;
            case('t'):
                sleepDelay = theNumber;
                break;
        }

        token = strtok(NULL, "-");
    }



}