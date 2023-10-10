#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "slist.h"

#define ROWS 6
#define COLS 7

// Function to initialize the game board
void initializeBoard(char board[ROWS][COLS]) {
	// Initialize each cell of the game board to a space character.
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            board[i][j] = ' ';
        }
    }
}

// Function to display the game board
void displayBoard(char board[ROWS][COLS]) {
	// Display the current state of the game board, including player tokens and separators.
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("|%c", board[i][j]);
        }
        printf("|\n");
    }
    printf("===================\n");
}

// Function to check if the current player has won
int checkWin(char board[ROWS][COLS], char player, int row, int col) {
    // Check horizontally
    int count = 0;
    for (int i = col - 3; i <= col + 3; i++) {
        if (i >= 0 && i < COLS && board[row][i] == player) {
            count++;
            if (count == 4) return 1;// A win is detected.
        } else {
            count = 0;// Reset the count if an empty or different player's token is encountered
        }
    }

    // Check vertically
    count = 0;
    for (int i = row - 3; i <= row + 3; i++) {
        if (i >= 0 && i < ROWS && board[i][col] == player) {
            count++;
            if (count == 4) return 1;
        } else {
            count = 0;
        }
    }

    // Check diagonally (bottom-left to top-right)
    count = 0;
    for (int i = -3; i <= 3; i++) {
        int r = row + i;
        int c = col - i;
        if (r >= 0 && r < ROWS && c >= 0 && c < COLS && board[r][c] == player) {
            count++;
            if (count == 4) return 1;
        } else {
            count = 0;
        }
    }

    // Check diagonally (top-left to bottom-right)
    count = 0;
    for (int i = -3; i <= 3; i++) {
        int r = row - i;
        int c = col - i;
        if (r >= 0 && r < ROWS && c >= 0 && c < COLS && board[r][c] == player) {
            count++;
            if (count == 4) return 1;
        } else {
            count = 0;
        }
    }

    return 0;// No win detected.
}

// Function to reset the game for a new round
void resetGame(char board[ROWS][COLS], struct Node** movesList, char* currentPlayer) {
	// Reset the game board, free the linked list of moves, and set the current player to 'R'.
    initializeBoard(board);
    freeList(movesList);
    *currentPlayer = (currentPlayer == 'R') ? 'R' : 'Y';// Ensures R always makes the first move
}

int main() {
    char board[ROWS][COLS];
    char currentPlayer = 'R'; // Start with 'R'
    int column;
    int moveCount = 0;
    struct Node* movesList = NULL;

    printf("Welcome! Press any key to continue or 'q' to quit.\n");
    char startChoice;
    scanf(" %c", &startChoice);

    if (startChoice != 'q') {
        while (1) {
            initializeBoard(board); // Initialize a new game board
            displayBoard(board);

            while (1) {
                printf("%c to play. Pick a column (1-7): ", currentPlayer);
                scanf("%d", &column);
                column--; // Adjust for 0-based indexing

                // Check if the column is valid and not full
                if (column < 0 || column >= COLS || board[0][column] != ' ') {
                    printf("Invalid move. Try again.\n");
                    continue;
                }

                // Find the empty row in the chosen column
                int row;
                for (row = ROWS - 1; row >= 0; row--) {
                    if (board[row][column] == ' ') {
                        board[row][column] = currentPlayer;
                        break;
                    }
                }

                // Add the move to the linked list
                insertNode(&movesList, board, currentPlayer, column);

                displayBoard(board);

                // Check for a win
                if (checkWin(board, currentPlayer, row, column)) {
                    printf("You win, %c!\n", currentPlayer);
                    printf("Good game!\n");

                    // Prompt for replay or quit
                    char choice;
                    printf("Press 'q' to quit, 'r' to replay, or any other key to continue: ");
                    scanf(" %c", &choice);

                    if (choice == 'q') {
                        freeList(&movesList); // Free the linked list
                        exit(0); // Quit the program
                    } else if (choice == 'r') {
                        // Replay logic here
                        struct Node* currentMove = movesList;
                        while (currentMove != NULL) {
                            displayBoard(currentMove->board);
                            currentMove = currentMove->next;
                        }
                        printf("Press 'q' to quit or any other key to continue: ");
                        char replayChoice;
                        scanf(" %c", &replayChoice);
                        if (replayChoice == 'q') {
                            freeList(&movesList); // Free the linked list
                            exit(0); // Quit the program
                        }
                        resetGame(board, &movesList, &currentPlayer);
                        displayBoard(board);
                    } else {
                        resetGame(board, &movesList, &currentPlayer);
                        displayBoard(board);
                    }
                }

                // Switch players
                currentPlayer = (currentPlayer == 'R') ? 'Y' : 'R';
                moveCount++;

                // Check for a draw
                if (moveCount == ROWS * COLS) {
                    printf("It's a draw!\n");
                    break;
                }
            }
        }
    }

    return 0;
}
