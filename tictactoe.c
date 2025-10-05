#include "tictactoe.h" 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Sets up the game board - fills everything with spaces initially
void initializeBoard(char **board, int n) {
    int i, j;  
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            board[i][j] = ' '; 
        }
    }
}

// Displays the board to player and saves to log file
void printBoard(char **board, int n, FILE *logFile) {
    int i, j, k;     
    // Show column numbers at the top
    printf("\n  ");
    for (i = 0; i < n; i++) {
        printf(" %d ", i); 
    }
    printf("\n");

    // Print each row with separators
    for (i = 0; i < n; i++) {
        printf("%d |", i);  // row number first
        for (j = 0; j < n; j++) {
            printf(" %c |", board[i][j]); 
        }
        printf("\n");
        
        // Add those horizontal lines between rows
        if (i < n - 1) {
            printf("  ");
            for (k = 0; k < n; k++) {
                printf("---|");
            }
            printf("\n");
        }
    }
    printf("\n");

    // Write current state to log file if we have one
    if (logFile != NULL) { 
        fprintf(logFile, "Current board state:\n");
        for (i = 0; i < n; i++) {
            for (j = 0; j < n; j++) {
                char symbol = board[i][j];
                                if (symbol == ' ') {
                    fprintf(logFile, "- ");
                } else {
                    fprintf(logFile, "%c ", symbol);
                }
            }
            fprintf(logFile, "\n"); 
        }
        fprintf(logFile, "\n"); 
        fflush(logFile); 
    }
}

// Check if won the game
int checkWin(char **board, int n, char player) {
    int i, j;
    int hasWon = 0;  
    
    // Check all rows first
    for (i = 0; i < n && !hasWon; i++) {
        int rowWin = 1;
        for (j = 0; j < n; j++) {
            if (board[i][j] != player) {
                rowWin = 0;
                break;
            }
        }
        if (rowWin) hasWon = 1;
    }

    // Check all columns 
    for (j = 0; j < n && !hasWon; j++) {
        int colWin = 1;
        for (i = 0; i < n; i++) {
            if (board[i][j] != player) {
                colWin = 0;
                break;
            }
        }
        if (colWin) hasWon = 1;
    }

    // Check main diagonal 
    if (!hasWon) {
        int diagWin = 1;
        for (i = 0; i < n; i++) {
            if (board[i][i] != player) {
                diagWin = 0;
                break;
            }
        }
        if (diagWin) hasWon = 1;
    }

    // Check other diagonal
    if (!hasWon) {
        int antiDiagWin = 1;
        for (i = 0; i < n; i++) {
            if (board[i][n - i - 1] != player) {
                antiDiagWin = 0;
                break;
            }
        }
        if (antiDiagWin) hasWon = 1;
    }

    return hasWon;
}

// See if the board is full
int checkDraw(char **board, int n) {
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (board[i][j] == ' ') {
                return 0; 
            }
        }
    }
    return 1; 
}


int isValidMove(char **board, int row, int col, int n) {
 
    if (row < 0 || row >= n || col < 0 || col >= n) {
        return 0; 
    }
    
 
    if (board[row][col] != ' ') {
        return 0; 
    }
    
    return 1; 
}


void computerMove(char **board, int n) {
    int row, col;
    
   
    
    do {
        row = rand() % n; 
        col = rand() % n; 
    } while (board[row][col] != ' '); 
    
    printf("Computer chooses: row %d, column %d\n", row, col);
    board[row][col] = 'O';
}
