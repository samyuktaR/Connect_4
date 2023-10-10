#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "slist.h"

// Create a new node for the linked list with the provided game board, player, and column.
struct Node* createNode(char board[ROWS][COLS], char player, int column) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));// Allocate memory for the new node
    if (newNode == NULL) {// Check if memory allocation was successful
        fprintf(stderr, "Memory allocation failed.\n");
        exit(1);
    }
    // Copy the game board data from the source 'board' to the destination 'newNode->board'.
    memcpy(newNode->board, board, sizeof(char) * ROWS * COLS);//memcpy is used to copy the contents of one memory location to another
    // Assign the player ('R' or 'Y') who made the move to the new node.
    newNode->player = player;
    // Assign the column (1-7) in which the move was made to the new node.
    newNode->column = column;
    // Set the 'next' pointer of the new node to NULL, indicating the end of the linked list.
    newNode->next = NULL;

    return newNode;// Return the newly created node with copied game board data, player, and column information.
}

// Insert a new node at the end of the linked list with the provided game board, player, and column.
void insertNode(struct Node** head, char board[ROWS][COLS], char player, int column) {
    struct Node* newNode = createNode(board, player, column);// Create a new node with the provided data

    // If the linked list is empty, set the new node as the hea
    if (*head == NULL) {
        *head = newNode;
    } else {// Find the last node in the linked list
        struct Node* current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        // Insert the new node at the end
        current->next = newNode;
    }
}

// Free the memory allocated for the linked list and its nodes.
void freeList(struct Node** head) {
    struct Node* current = *head;// Initialize a pointer 'current' to the head of the linked list
    while (current != NULL) {// Loop through the linked list until 'current' reaches the end.
        struct Node* next = current->next;// Create a pointer 'next' to store the reference to the next node in the list.
        free(current);// Free the memory allocated for the current node.
        current = next;// Move 'current' to the next node in the list.
    }
    *head = NULL;// Set the head pointer to NULL to indicate an empty list
}
