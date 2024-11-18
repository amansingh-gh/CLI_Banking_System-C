#include <stdio.h>
#include <stdlib.h>

// Function prototypes
void displayBoard(char grid[3][3]);
int checkWin(char grid[3][3]);
int isTie(char grid[3][3]);
void getPlayerInput(char grid[3][3], char player);
void resetGrid(char grid[3][3]);

int main() {
    char grid[3][3];
    char playAgain;
    int winner;

    do {
        resetGrid(grid);
        winner = 0;

        printf("Welcome to Tic-Tac-Toe!\n\n");

        // Main game loop
        for (int turn = 0; turn < 9 && !winner; ++turn) {
            displayBoard(grid);
            char currentPlayer = (turn % 2 == 0) ? 'X' : 'O';
            printf("Player %c, it's your turn!\n", currentPlayer);

            getPlayerInput(grid, currentPlayer);

            winner = checkWin(grid);
            if (winner) {
                displayBoard(grid);
                printf("Player %c wins!\n", currentPlayer);
                break;
            }
        }

        if (!winner && isTie(grid)) {
            displayBoard(grid);
            printf("It's a tie!\n");
        }

        printf("Do you want to play again? (y/n): ");
        scanf(" %c", &playAgain);

    } while (playAgain == 'y' || playAgain == 'Y');

    printf("Thanks for playing!\n");
    return 0;
}

// Function to reset the grid
void resetGrid(char grid[3][3]) {
    char start = '1';
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            grid[i][j] = start++;
        }
    }
}

// Function to display the board
void displayBoard(char grid[3][3]) {
    printf("\n");
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            printf(" %c ", grid[i][j]);
            if (j < 2) printf("|");
        }
        printf("\n");
        if (i < 2) printf("---+---+---\n");
    }
    printf("\n");
}

// Function to check if a player has won
int checkWin(char grid[3][3]) {
    // Check rows and columns
    for (int i = 0; i < 3; ++i) {
        if (grid[i][0] == grid[i][1] && grid[i][1] == grid[i][2]) return 1;
        if (grid[0][i] == grid[1][i] && grid[1][i] == grid[2][i]) return 1;
    }
    // Check diagonals
    if (grid[0][0] == grid[1][1] && grid[1][1] == grid[2][2]) return 1;
    if (grid[0][2] == grid[1][1] && grid[1][1] == grid[2][0]) return 1;

    return 0;
}

// Function to check if the game is a tie
int isTie(char grid[3][3]) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (grid[i][j] != 'X' && grid[i][j] != 'O') return 0;
        }
    }
    return 1;
}

// Function to get and validate player input
void getPlayerInput(char grid[3][3], char player) {
    int choice;
    int row, col;

    while (1) {
        printf("Enter the number of the cell (1-9): ");
        scanf("%d", &choice);

        if (choice < 1 || choice > 9) {
            printf("Invalid input! Please choose a number between 1 and 9.\n");
            continue;
        }

        // Map choice to grid coordinates
        row = (choice - 1) / 3;
        col = (choice - 1) % 3;

        if (grid[row][col] == 'X' || grid[row][col] == 'O') {
            printf("Cell already taken! Choose another cell.\n");
        } else {
            grid[row][col] = player;
            break;
        }
    }
}