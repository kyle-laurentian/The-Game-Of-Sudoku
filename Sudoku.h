// Kyle Fynn
// 0409075

#ifndef SUDOKU_H
#define SUDOKU_H

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

class Sudoku {
public:
    Sudoku();  // Initialize a fixed 9x9 Sudoku board
    void generateBoard();
    void displayBoard() const;
    bool isUserMoveValid(int row, int col, int num) const;
    std::vector<std::vector<int>>& getBoard();  // Returns board as a reference
    bool isBoardFull() const;
    bool fillBoard(int row, int col);

private:
    int size;
    std::vector<std::vector<int>> board;
    bool isValidMove(int row, int col, int num) const;
};

#endif
