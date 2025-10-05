#ifndef TICTACTOE_H
#define TICTACTOE_H

#include <stdio.h>  
#include <stdlib.h> 

/**
 * @brief Initializes the game board with empty spaces (' ').
 * @param board The game board array.
 * @param n The size of the board (n x n).
 */
void initializeBoard(char **board, int n);

/**
 * @brief Prints the current state of the board to the console and logs it to a file.
 * @param board The game board array.
 * @param n The size of the board (n x n).
 * @param logFile A pointer to the file stream for logging. Can be NULL if logging is disabled.
 */
void printBoard(char **board, int n, FILE *logFile);

/**
 * @brief Checks if the current player has won the game by checking rows, columns, and diagonals.
 * @param board The game board array.
 * @param n The size of the board (n x n).
 * @param player The symbol of the current player ('X', 'O', or 'Z').
 * @return 1 if the player has won, 0 otherwise.
 */
int checkWin(char **board, int n, char player);

/**
 * @brief Checks if the game is a draw (board is full with no winner).
 * @param board The game board array.
 * @param n The size of the board (n x n).
 * @return 1 if it's a draw, 0 otherwise.
 */
int checkDraw(char **board, int n);

/**
 * @brief Validates if the given move is within bounds and the cell is empty.
 * @param board The game board array.
 * @param row The row index of the move.
 * @param col The column index of the move.
 * @param n The size of the board (n x n).
 * @return 1 if the move is valid, 0 otherwise.
 */
int isValidMove(char **board, int row, int col, int n);

/**
 * @brief Generates a random, valid move for the computer ('O') and updates the board.
 * @param board The game board array.
 * @param n The size of the board (n x n).
 */
void computerMove(char **board, int n);

#endif 

