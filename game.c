#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to initialize the board with empty spaces
void initializeBoard(char **board, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            board[i][j] = ' ';  // Fill the board with empty spaces
        }
    }
}

// Function to print the current board
void printBoard(char **board, int n, FILE *logFile) {
    // Display the current state of the board
    printf("   ");
    for (int i = 0; i < n; i++) {
        printf(" %d ", i);  // Print column numbers at the top
    }
    printf("\n");

    for (int i = 0; i < n; i++) {
        printf("  ---");  // Print the separator line
    }
    printf("\n");

    for (int i = 0; i < n; i++) {
        printf("%d |", i);  // Print row numbers on the left
        for (int j = 0; j < n; j++) {
            printf(" %c |", board[i][j]);  // Print the board content
        }
        printf("\n");

        printf("  ---");  // Print the separator line after each row
        for (int j = 0; j < n; j++) {
            printf("---");
        }
        printf("\n");
    }

    // Log the current board state to the file after each move
    fprintf(logFile, "Current board state:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fprintf(logFile, "%c ", board[i][j]);  // Write each cell to the file
        }
        fprintf(logFile, "\n");  // Newline after each row
    }
    fprintf(logFile, "\n");  // Add a blank line after the board for clarity
    fflush(logFile);  // Ensure data is immediately written to the file after each move
}

// Function to check if the current player has won
int checkWin(char **board, int n, char player) {
    // Check rows
    for (int i = 0; i < n; i++) {
        int win = 1;
        for (int j = 0; j < n; j++) {
            if (board[i][j] != player) {
                win = 0;  // If a cell does not match, it's not a win
                break;
            }
        }
        if (win) return 1;  // If any row matches the player's symbol, return 1
    }

    // Check columns
    for (int j = 0; j < n; j++) {
        int win = 1;
        for (int i = 0; i < n; i++) {
            if (board[i][j] != player) {
                win = 0;
                break;
            }
        }
        if (win) return 1;
    }

    // Check diagonals
    int win = 1;
    for (int i = 0; i < n; i++) {
        if (board[i][i] != player) {
            win = 0;
            break;
        }
    }
    if (win) return 1;

    win = 1;
    for (int i = 0; i < n; i++) {
        if (board[i][n - i - 1] != player) {
            win = 0;
            break;
        }
    }
    if (win) return 1;

    return 0;  // No winner found
}

// Function to check for a draw
int checkDraw(char **board, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (board[i][j] == ' ') {
                return 0;  // If any cell is empty, it's not a draw
            }
        }
    }
    return 1;  // If no empty cells are found, it's a draw
}

// Function to validate player input
int isValidMove(char **board, int row, int col, int n) {
    if (row < 0 || row >= n || col < 0 || col >= n || board[row][col] != ' ') {
        return 0;  // Return 0 if move is out of bounds or the cell is occupied
    }
    return 1;
}

// Function for computer to generate random moves
void computerMove(char **board, int n) {
    int row, col;
    do {
        row = rand() % n;  // Random row
        col = rand() % n;  // Random column
    } while (board[row][col] != ' ');  // Repeat until an empty cell is found
    printf("Computer's move: %d %d\n", row, col);  // Print the computer's move
    board[row][col] = 'O';  // 'O' is the computer's symbol
}

// Main function to run the game
int main() {
    srand(time(0));  // Initialize random number generator for computer's moves
    int n;

    // Ask the user to choose the board size (3 <= N <= 10)
    do {
        printf("Enter board size N (3 <= N <= 10): ");
        scanf("%d", &n);  // Get the board size from the user
    } while (n < 3 || n > 10);  // Ensure board size is within the valid range

    char **board = (char **)malloc(n * sizeof(char *));  // Dynamically allocate memory for the board
    for (int i = 0; i < n; i++) {
        board[i] = (char *)malloc(n * sizeof(char));  // Allocate memory for each row
    }

    initializeBoard(board, n);  // Initialize the board with empty spaces

    // Open the log file to record the game state
    FILE *logFile = fopen("game_log.txt", "w");
    if (logFile == NULL) {
        printf("Error opening file for logging.\n");
        return 1;
    }

    int currentPlayer = 0;  // 0 for Player X, 1 for Player O, 2 for Player Z
    char players[3] = {'X', 'O', 'Z'};  // Array to store player symbols
    int row, col;
    int gameEnded = 0;
    int gameMode;

    // Select game mode: 1 for two-player, 2 for user vs computer, 3 for three players
    printf("Select Game Mode:\n1. Two Players (User vs User)\n2. User vs Computer\n3. Three Players\n");
    printf("Enter choice (1-3): ");
    scanf("%d", &gameMode);

    // Adjust player array for two-player mode
    if (gameMode == 1) {
        players[2] = ' ';  // Remove Player Z for two-player mode
    }

    while (!gameEnded) {
        printBoard(board, n, logFile);  // Display the current state of the board and log it

        if (gameMode == 1 || (gameMode == 2 && currentPlayer == 0)) {  // Human player's turn
            printf("Player %c, enter row and col (0..%d): ", players[currentPlayer], n - 1);
            scanf("%d %d", &row, &col);  // Get the player's move

            if (isValidMove(board, row, col, n)) {
                board[row][col] = players[currentPlayer];  // Make the move
            } else {
                printf("Invalid move. Try again.\n");
                continue;  // Prompt the user to try again if the move is invalid
            }
        } else if (gameMode == 2 && currentPlayer == 1) {  // Computer's turn in User vs Computer
            computerMove(board, n);  // Make computer's move
        } else if (gameMode == 3) {  // Three-player mode (handles all players cyclically)
            printf("Player %c, enter row and col (0..%d): ", players[currentPlayer], n - 1);
            scanf("%d %d", &row, &col);  // Get the player's move

            if (isValidMove(board, row, col, n)) {
                board[row][col] = players[currentPlayer];  // Make the move
            } else {
                printf("Invalid move. Try again.\n");
                continue;  // Prompt the user to try again if the move is invalid
            }
        }

        if (checkWin(board, n, players[currentPlayer])) {
            printBoard(board, n, logFile);
            printf("Player %c wins!\n", players[currentPlayer]);
            gameEnded = 1;
        } else if (checkDraw(board, n)) {
            printBoard(board, n, logFile);
            printf("It's a draw!\n");
            gameEnded = 1;
        } else {
            currentPlayer = (currentPlayer + 1) % (gameMode == 3 ? 3 : 2);  // Switch player turn cyclically (3 players) or alternate (2 players)
        }
    }

    // Close the log file
    fclose(logFile);

    // Free dynamically allocated memory
    for (int i = 0; i < n; i++) {
        free(board[i]);
    }
    free(board);

    return 0;
}

