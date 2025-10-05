#ifndef TICTACTOE_H
#define TICTACTOE_H

#include <stdio.h>
#include <stdlib.h>


void initializeBoard(char **board, int n);

void printBoard(char **board, int n, FILE *logFile);

int checkWin(char **board, int n, char player);

int checkDraw(char **board, int n);

int isValidMove(char **board, int row, int col, int n);

void computerMove(char **board, int n);

#endif 

