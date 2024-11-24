// Kyle Fynn
// 0409075

#include "Sudoku.h"
#include <iostream>
#include <ctime>
#include <cmath>
#include <vector>

// Constructor - Initialize board
Sudoku::Sudoku() : size(9), board(9, std::vector<int>(9, 0)) {
    srand(time(0));
}

// Generate the Sudoku board
void Sudoku::generateBoard() {
    fillBoard(0, 0);
}

// Fill the board with valid numbers
bool Sudoku::fillBoard(int row, int col) {
    if (row == size) return true;
    if (col == size) return fillBoard(row + 1, 0);

    //loop through board placing numbers using isValidMove check, return true if completed
    for (int num = 1; num <= size; num++) {
        if (isValidMove(row, col, num)) {
            board[row][col] = num;
            if (fillBoard(row, col + 1)) return true;
            board[row][col] = 0;
        }
    }
    return false;
}

// User move validation
bool Sudoku::isUserMoveValid(int row, int col, int num) const {
    if (board[row][col] != 0) return false;
    for (int c = 0; c < size; c++) {
        if (board[row][c] == num) return false;
    }
    for (int r = 0; r < size; r++) {
        if (board[r][col] == num) return false;
    }
    int gridSize = std::sqrt(size);
    int startRow = row / gridSize * gridSize;
    int startCol = col / gridSize * gridSize;
    for (int r = 0; r < gridSize; r++) {
        for (int c = 0; c < gridSize; c++) {
            if (board[startRow + r][startCol + c] == num) return false;
        }
    }
    return true;
}

// Display the Sudoku board
void Sudoku::displayBoard() const {
    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            std::cout << board[row][col] << " ";
        }
        std::cout << std::endl;
    }
}

// Check if the board is full
bool Sudoku::isBoardFull() const {
    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            if (board[row][col] == 0) return false;
        }
    }
    return true;
}

// Validate if the user move is correct
bool Sudoku::isValidMove(int row, int col, int num) const {
    for (int c = 0; c < size; c++) {
        if (board[row][c] == num) return false;
    }
    for (int r = 0; r < size; r++) {
        if (board[r][col] == num) return false;
    }
    int gridSize = std::sqrt(size);
    int startRow = row / gridSize * gridSize;
    int startCol = col / gridSize * gridSize;
    for (int r = 0; r < gridSize; r++) {
        for (int c = 0; c < gridSize; c++) {
            if (board[startRow + r][startCol + c] == num) return false;
        }
    }
    return true;
}

// Get the current board state
std::vector<std::vector<int>>& Sudoku::getBoard() {
    return board;
}
