/*
 * Tic-Tac-Toe Game in C
 * A console-based two-player game
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// Global variables
char board[3][3];
char currentPlayer;

// Function prototypes
void initializeBoard();
void displayBoard();
int makeMove(int position);
int checkWin();
int checkDraw();
void switchPlayer();
void displayInstructions();

int main() {
    int position;
    int gameOver = 0;
    char playAgain;

    printf("========================================\n");
    printf("   WELCOME TO TIC-TAC-TOE GAME!\n");
    printf("========================================\n\n");
    
    displayInstructions();

    do {
        // Initialize game
        initializeBoard();
        currentPlayer = 'X';
        gameOver = 0;

        // Main game loop
        while (!gameOver) {
            displayBoard();
            
            // Get player move
            printf("\nPlayer %c's turn.\n", currentPlayer);
            printf("Enter position (1-9): ");
            
            // Input validation
            if (scanf("%d", &position) != 1) {
                // Clear invalid input
                while (getchar() != '\n');
                printf("Invalid input! Please enter a number between 1-9.\n");
                continue;
            }

            // Make the move
            if (makeMove(position)) {
                // Check for win
                if (checkWin()) {
                    displayBoard();
                    printf("\n🎉 CONGRATULATIONS! Player %c wins! 🎉\n\n", currentPlayer);
                    gameOver = 1;
                }
                // Check for draw
                else if (checkDraw()) {
                    displayBoard();
                    printf("\n🤝 It's a DRAW! Well played both! 🤝\n\n");
                    gameOver = 1;
                }
                // Continue game
                else {
                    switchPlayer();
                }
            } else {
                printf("Invalid move! Try again.\n");
            }
        }

        // Ask to play again
        printf("Do you want to play again? (y/n): ");
        scanf(" %c", &playAgain);
        playAgain = tolower(playAgain);
        printf("\n");

    } while (playAgain == 'y');

    printf("Thanks for playing! Goodbye!\n");
    return 0;
}

/*
 * Initialize the board with numbers 1-9
 */
void initializeBoard() {
    char num = '1';
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = num++;
        }
    }
}

/*
 * Display the current state of the board
 */
void displayBoard() {
    printf("\n");
    printf("     |     |     \n");
    printf("  %c  |  %c  |  %c  \n", board[0][0], board[0][1], board[0][2]);
    printf("_____|_____|_____\n");
    printf("     |     |     \n");
    printf("  %c  |  %c  |  %c  \n", board[1][0], board[1][1], board[1][2]);
    printf("_____|_____|_____\n");
    printf("     |     |     \n");
    printf("  %c  |  %c  |  %c  \n", board[2][0], board[2][1], board[2][2]);
    printf("     |     |     \n");
    printf("\n");
}

/*
 * Make a move on the board
 * Returns 1 if move is valid, 0 otherwise
 */
int makeMove(int position) {
    // Validate position range
    if (position < 1 || position > 9) {
        return 0;
    }

    // Convert position to row and column
    int row = (position - 1) / 3;
    int col = (position - 1) % 3;

    // Check if position is already taken
    if (board[row][col] == 'X' || board[row][col] == 'O') {
        return 0;
    }

    // Place the current player's mark
    board[row][col] = currentPlayer;
    return 1;
}

/*
 * Check if current player has won
 * Returns 1 if won, 0 otherwise
 */
int checkWin() {
    // Check rows
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == currentPlayer && 
            board[i][1] == currentPlayer && 
            board[i][2] == currentPlayer) {
            return 1;
        }
    }

    // Check columns
    for (int i = 0; i < 3; i++) {
        if (board[0][i] == currentPlayer && 
            board[1][i] == currentPlayer && 
            board[2][i] == currentPlayer) {
            return 1;
        }
    }

    // Check diagonal (top-left to bottom-right)
    if (board[0][0] == currentPlayer && 
        board[1][1] == currentPlayer && 
        board[2][2] == currentPlayer) {
        return 1;
    }

    // Check diagonal (top-right to bottom-left)
    if (board[0][2] == currentPlayer && 
        board[1][1] == currentPlayer && 
        board[2][0] == currentPlayer) {
        return 1;
    }

    return 0;
}

/*
 * Check if the game is a draw
 * Returns 1 if draw, 0 otherwise
 */
int checkDraw() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            // If any position is still a number, game is not over
            if (board[i][j] != 'X' && board[i][j] != 'O') {
                return 0;
            }
        }
    }
    return 1; // All positions filled, it's a draw
}

/*
 * Switch between Player X and Player O
 */
void switchPlayer() {
    currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
}

/*
 * Display game instructions
 */
void displayInstructions() {
    printf("HOW TO PLAY:\n");
    printf("- This is a two-player game\n");
    printf("- Player X goes first, followed by Player O\n");
    printf("- The board positions are numbered 1-9:\n\n");
    printf("     1 | 2 | 3\n");
    printf("    -----------\n");
    printf("     4 | 5 | 6\n");
    printf("    -----------\n");
    printf("     7 | 8 | 9\n\n");
    printf("- Enter a number (1-9) to place your mark\n");
    printf("- Get three in a row (horizontal, vertical, or diagonal) to win!\n");
    printf("- If all positions are filled with no winner, it's a draw\n\n");
    printf("Let's begin!\n");
    printf("========================================\n");
}
