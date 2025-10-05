#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "tictactoe.h"   

int main() {
    srand(time(NULL));      
    int n = 0;          // Board size
    char **board = NULL;
    FILE *logFile = NULL;

  
    while (1) {
        printf("Enter board size N (between 3 and 10): ");
        if (scanf("%d", &n) != 1) {
            printf("Oops! That's not a number. Try again.\n");
            while (getchar() != '\n');  
            continue;
        }
        if (n >= 3 && n <= 10) break;
        printf("Invalid size! Please choose between 3 and 10.\n");
    }

    //  Allocate the board dynamically
    board = (char **)malloc(n * sizeof(char *));
    if (!board) {
        fprintf(stderr, "Memory allocation for board failed (rows)\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        board[i] = (char *)malloc(n * sizeof(char));
        if (!board[i]) {
            fprintf(stderr, "Memory allocation failed for row %d\n", i);
            // Free 
            for (int k = 0; k < i; k++) free(board[k]);
            free(board);
            return 1;
        }
    }

    initializeBoard(board, n);  
    // ogging to a file 
    logFile = fopen("game_log.txt", "w");
    if (!logFile) {
        printf("Couldn't open 'game_log.txt' for writing... continuing without log.\n");
    } else {
        fprintf(logFile, "=== Tic Tac Toe Log (Board %dx%d) ===\n\n", n, n);
    }

    // Players setup 
    char players[3] = {'X', 'O', 'Z'};   // third player
    int gameMode = 0;
    int currentPlayer = 0;
    int gameOver = 0;
    int row, col;

    // game mode selection 
    printf("\nSelect Game Mode:\n");
    printf("1. Two Players\n2. User vs Computer\n3. Three Players\n");

    while (1) {
        printf("Enter your choice (1-3): ");
        if (scanf("%d", &gameMode) != 1) {
            printf("Invalid input (need a number!)\n");
            while (getchar() != '\n');
            continue;
        }
        if (gameMode < 1 || gameMode > 3) {
            printf("Choice must be 1, 2, or 3.\n");
            continue;
        }
        break;
    }

    int totalPlayers = (gameMode == 3) ? 3 : 2;
    while (!gameOver) {
        printBoard(board, n, logFile);  // print the board

        if (gameMode == 2 && currentPlayer == 1) {
            // Computer's move
            printf("\nComputer ('O') is thinking...\n");
            computerMove(board, n);
            if (logFile) fprintf(logFile, "Computer made a move.\n");

        } else {
            // Human player move
            printf("Player %c, enter row and column (0-%d): ", players[currentPlayer], n - 1);

            if (scanf("%d %d", &row, &col) != 2) {
                printf("Invalid input. Please enter two integers.\n");
                while (getchar() != '\n');
                continue;
            }

            if (!isValidMove(board, row, col, n)) {
                printf("That spot is taken or out of range, try again.\n");
                continue;
            }

            board[row][col] = players[currentPlayer];  // mark move

            if (logFile) {
                fprintf(logFile, "Player %c moved to (%d, %d)\n", players[currentPlayer], row, col);
            }
        }

        // Check for a winner
        if (checkWin(board, n, players[currentPlayer])) {
            printBoard(board, n, logFile);
            printf("\n>>> Player %c wins! <<<\n", players[currentPlayer]);
            if (logFile) fprintf(logFile, "\n>>> Player %c wins! <<<\n", players[currentPlayer]);
            gameOver = 1;
        } 
        else if (checkDraw(board, n)) {
            printBoard(board, n, logFile);
            printf("\n>>> It's a draw! <<<\n");
            if (logFile) fprintf(logFile, "\n>>> It's a draw! <<<\n");
            gameOver = 1;
        } 
        else {
            currentPlayer = (currentPlayer + 1) % totalPlayers;  // move to next player
        }
    }

    // Cleanup and exit
    if (logFile) {
        fclose(logFile);
        printf("\nGame log saved to game_log.txt\n");
    }

    // Free memory 
    for (int i = 0; i < n; i++) {
        free(board[i]);
    }
    free(board);

    printf("All memory freed. Exiting...\n");


    // printf("Wanna play again? (TODO)\n");

    return 0;
}

