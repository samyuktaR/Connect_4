#ifndef SLIST_H
#define SLIST_H

// Define constants for the dimensions of the Connect Four game board
#define ROWS 6
#define COLS 7

// Define a structure for a node in the linked list
struct Node {
    char board[ROWS][COLS];// The game board configuration with rows and columns
    char player;// The player who made the move ('R'(Red) or 'Y'(Yellow))
    int column;// The column in which the user chose to make the move (1-7)
    struct Node* next;// Pointer to the next node in the linked list
};

// Function prototypes for linked list operations
struct Node* createNode(char board[ROWS][COLS], char player, int column);// Creates a new node with the provided game board, player, and column.
void insertNode(struct Node** head, char board[ROWS][COLS], char player, int column);// Inserts a new node at the beginning of the linked list with the provided game board, player, and column.
void freeList(struct Node** head);// Frees the memory allocated for the linked list and its nodes.

#endif
