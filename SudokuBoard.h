//Kyle Fynn
//0409075

#ifndef SUDOKUBOARD_H
#define SUDOKUBOARD_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <fstream>

class SudokuBoard {
public:
    SudokuBoard();
    void draw(sf::RenderWindow& window);
    void selectCell(int row, int col);
    void setValue(int value);
    std::vector<std::vector<int>>& getBoard();
    const sf::Font& getFont() const; // Getter for font
    bool isSafe(int row, int col, int num);
    bool fillBoard(int row, int col, std::vector<int> &numbers);
    void generateRandomBoard();
    void setLoadValue(int row, int col, int value);
    void clear();

private:
    const int gridSize = 9;
    const int cellSize = 60;
    std::vector<std::vector<int>> board;
    int selectedRow = -1;
    int selectedCol = -1;
    sf::Font font;
    sf::Text instructionText;
    sf::Text statusText;
    sf::RectangleShape instructionsButton;
    sf::RectangleShape solveButton;
    std::vector<std::vector<bool>> isValid;

   
};

#endif

