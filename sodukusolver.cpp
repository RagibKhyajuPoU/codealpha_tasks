#include <iostream>
using namespace std;

const int SIZE = 9;

// Function to display the Sudoku board
void displayBoard(int board[SIZE][SIZE]) {
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            cout << board[row][col] << " ";
        }
        cout << endl;
    }
}

// Function to check if a number is safe to place in a position
bool isSafe(int board[SIZE][SIZE], int row, int col, int num) {
    for (int x = 0; x < SIZE; x++) {
        if (board[row][x] == num || board[x][col] == num)
            return false;
    }

    int startRow = row - row % 3;
    int startCol = col - col % 3;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i + startRow][j + startCol] == num)
                return false;
        }
    }

    return true;
}

// Function to solve the Sudoku puzzle using backtracking
bool solveSudoku(int board[SIZE][SIZE]) {
    int row, col;
    bool emptySpot = false;
    
    for (row = 0; row < SIZE; row++) {
        for (col = 0; col < SIZE; col++) {
            if (board[row][col] == 0) {
                emptySpot = true;
                break;
            }
        }
        if (emptySpot) break;
    }

    if (!emptySpot) return true;

    for (int num = 1; num <= 9; num++) {
        if (isSafe(board, row, col, num)) {
            board[row][col] = num;
            if (solveSudoku(board))
                return true;
            board[row][col] = 0;
        }
    }
    return false;
}

int main() {
    int board[SIZE][SIZE];
    cout << "Enter the Sudoku puzzle (use 0 for empty spaces):" << endl;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            cin >> board[i][j];
        }
    }

    if (solveSudoku(board)) {
        cout << "Solved Sudoku:" << endl;
        displayBoard(board);
    } else {
        cout << "No solution exists for the given Sudoku." << endl;
    }

    return 0;
}
