//mohammed

#ifndef SOLVER_H
#define SOLVER_H

#include <vector>

class Solver {
public:
    Solver();
    bool solve(std::vector<std::vector<int>>& board);
    bool isSafe(const std::vector<std::vector<int>>& board, int row, int col, int num);

private:
    bool findEmptyCell(const std::vector<std::vector<int>>& board, int& row, int& col);
};

#endif