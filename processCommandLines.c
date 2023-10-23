#define _DEFAULT_SOURCE
#include "processCommandLines.h"

// prints out a help message, no need to check for validity 
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

/// -d D: set dimension.
/// Sets the height and width of the grid (in characters) to D. 
/// The simulation space is always square (D by D), and every cell is either vacant or occupied by an endline or a newline agent. 
/// The minimum allowed dimension is 5 (for a 5x5 grid); the maximum is 39; and the default dimension is 15. 
/// An invalid dimension is an error.
void setDimensionOfGrid(int *dimensionOfGrid, int number){
    // minimum allowed dimension is 5 (for a 5x5 grid); the maximum is 39
    if (5 <= number && number <= 39) {
        *dimensionOfGrid = number;
    } else {
        fprintf(stderr, "dimension (%d) must be a value in [5..39]", number);
        exit(1 + EXIT_FAILURE);
    }
}

/// -c N: set the cycle count.
/// Turns on print mode, in which the program will perform N simulation cycles, printing out the state of the grid each cycle. 
/// This mode does not use cursor-controlled output; instead, it just prints the grid directly. The value of N must be a non-negative integer; there is no default value. 
/// A negative value is considered to be an error. 
void setNumOfPrintCycles(int *numOfPrintOnCycles, int number) {
    if (number < 0) {
        fprintf(stderr, "count (%d) must be a non-negative integer", number);
        exit(1 + EXIT_FAILURE);
    } else {
        *numOfPrintOnCycles = number;
        // TBD TBD TBD: TURN ON PRINT MODE HERE
    }
}



/// -s S: set strength threshold.
/// Specifies an override (S) to the default strength threshold as a percentage expressed as an integer. 
/// For example, a strength of 60 means that each agent will be satisfied and happy only if the proportion of its neighbors sharing their strength of preference is ≥ 60%. 
/// Valid thresholds are in the range [1..99]; the default is 50. 
/// An invalid threshold is an error.
void setStrengthThreshold(int *strengthThreshold, int number){
    // Valid thresholds are in the range [1..99]
    if (1 <= number && number <= 99) {
        *strengthThreshold = number; 
    } else {
        fprintf(stderr, "preference strength (%d) must be a value in [1..99]", number);
        exit(1 + EXIT_FAILURE);
    }
}

/// -v V: set vacancy rate.
/// Specifies an override (V) to the default vacancy rate as a percentage value expressed as an integer. 
/// The program interprets this value as the percentage of the entire space that is to be vacant, with all other cells occupied by agents. 
/// Valid vacancy rates are [1..99]; the default is 20. 
/// An invalid vacancy rate is an error.

/// For example, a vacancy rate of 10 means that the percentage of vacant locations is 10%. For a 10x10 grid, this means 10 cells will be vacant and 90 will contain agents. 
/// For grid dimensions that are not evenly divisible by the percentage of vacancy, use the truncated value for the number of vacant locations. 
/// If the grid dimension is 5x5, and the vacancy rate is 10%, then the number of vacant locations would be 25/10 (or (int) (25 * 0.10)) which is 2.
void setVacancyRate(int *vacancyRate, int number){
    if (1 <= number && number <= 99) {
        *vacancyRate = number;
    } else {
        fprintf(stderr, "vacancy (%d) must be a value in [1..99]", number);
        exit(1 + EXIT_FAILURE);
    }
}

/// -e E: set Endline percentage.
/// Specifies an override (E) to the default proportion of e agents to n agents; this is the percentage of endline agents expressed as an integer.
/// Remaining occupied cells will contain newline agents. Valid percentages are [1..99]; the default is 60
/// An invalid percentage is an error
void setEndlinePercentage(int *endlinePercentage, int number){
    if (1 <= number && number <= 99) {
        *endlinePercentage = number;
    } else {
        fprintf(stderr, "endline proportion (%d) must be a value in [1..99]", number);
        exit(1 + EXIT_FAILURE);
    }
}

/// -t N: set the sleep delay.
/// Specifies the delay, in microseconds (µsec), between simulation cycles when running in infinite mode; has no effect in print mode. 
/// The value of N must be a positive integer; the default value is 900,000 µsec. 
/// A value less than 1 is ignored (i.e., is not treated as an error).
void setSleepDelay(int *sleepDelay, int number){
    if (number >= 1) {
        *sleepDelay = number;
    }
}


