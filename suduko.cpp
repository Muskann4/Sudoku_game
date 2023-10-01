#include <iostream>
using namespace std;

const int N = 9; // Size of the Sudoku grid

// Function to print the Sudoku grid
void printGrid(int grid[N][N]) {
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            cout << grid[row][col] << " ";
        }
        cout << endl;
    }
}

// Function to check if it's safe to place a number in a specific cell
bool isSafe(int grid[N][N], int row, int col, int num) {
    // Check if the number is already present in the current row or column
    for (int i = 0; i < N; i++) {
        if (grid[row][i] == num || grid[i][col] == num) {
            return false;
        }
    }

    // Check if the number is already present in the current 3x3 grid
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (grid[startRow + i][startCol + j] == num) {
                return false;
            }
        }
    }

    return true;
}

// Function to solve the Sudoku puzzle using backtracking
bool solveSudoku(int grid[N][N]) {
    int row, col;

    // Find an empty cell
    bool isEmpty = false;
    for (row = 0; row < N; row++) {
        for (col = 0; col < N; col++) {
            if (grid[row][col] == 0) {
                isEmpty = true;
                break;
            }
        }
        if (isEmpty) {
            break;
        }
    }

    // If no empty cell is found, the puzzle is solved
    if (!isEmpty) {
        return true;
    }

    // Try placing numbers from 1 to 9 in the empty cell
    for (int num = 1; num <= 9; num++) {
        if (isSafe(grid, row, col, num)) {
            grid[row][col] = num;
            if (solveSudoku(grid)) {
                return true;
            }

            // backtrack
            grid[row][col] = 0;
        }
    }

    // backtrack
    return false;
}

int main() {
    int grid[N][N] = {
        {0, 0, 0, 0, 8, 6, 0, 2, 0},
        {0, 0, 6, 4, 0, 0, 0, 0, 0},
        {5, 0, 3, 0, 0, 0, 0, 0, 0},
        {0, 0, 4, 6, 0, 0, 7, 0, 8},
        {7, 0, 0, 1, 0, 0, 4, 9, 0},
        {0, 0, 0, 3, 0, 0, 5, 0, 0},
        {0, 0, 0, 8, 0, 0, 2, 7, 0},
        {6, 0, 0, 2, 0, 3, 1, 5, 0},
        {2, 0, 0, 0, 9, 1, 0, 0, 0}
    };

    if (solveSudoku(grid)) {
        cout << "Solved Sudoku:" << endl;
        printGrid(grid);
    } else {
        cout << "No solution exists" << endl;
    }

    return 0;
}