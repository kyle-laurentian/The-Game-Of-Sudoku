//Mohammed
//Kyle Fynn

#include "Solver.h"

Solver::Solver() {}

//using backtracking solves the board with the is safe conditon and recursion
bool Solver::solve(std::vector<std::vector<int>>& board) {
    int row, col;
    if (!findEmptyCell(board, row, col)) return true;

    for (int num = 1; num <= 9; num++) {
        if (isSafe(board, row, col, num)) {
            board[row][col] = num;
            if (solve(board)) return true;
            board[row][col] = 0;
        }
    }

    return false;
}

//checks for same numbers in each row/coloumn
bool Solver::isSafe(const std::vector<std::vector<int>>& board, int row, int col, int num) {
    for (int x = 0; x < 9; x++) {
        if (board[row][x] == num || board[x][col] == num) return false;
    }

    int startRow = row - row % 3, startCol = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i + startRow][j + startCol] == num) return false;
        }
    }

    return true;
}

//finds empty cells for check condition
bool Solver::findEmptyCell(const std::vector<std::vector<int>>& board, int& row, int& col) {
    for (row = 0; row < 9; row++) {
        for (col = 0; col < 9; col++) {
            if (board[row][col] == 0) return true;
        }
    }
    return false;
}