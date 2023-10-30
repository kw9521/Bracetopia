/// @file supportFuncs.h
/// @author KUNLIN WEN, KW9521
/// Functions that will be called several times throughout this project

#ifndef _SUPPORT_FUNCS_H
#define _SUPPORT_FUNCS_H

/// @brief prints out current grid, given a 2D array
/// @param dimensionOfGrid num of cells in each row/col
/// @param initialGrid 2d array we are dealing with
void printOutCurrGrid(int dimensionOfGrid, char initialGrid[][dimensionOfGrid]);

/// @brief prints current grid with curses 
/// @param dimensionOfGrid num of cells in each row/col
/// @param initialGrid  2d array we are dealing with
void printCurrGridWithCurses(int dimensionOfGrid, char initialGrid[][dimensionOfGrid]);

#endif