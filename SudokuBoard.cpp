#include "SudokuBoard.h"
#include <iostream>
#include <random>
#include <algorithm>
#include <numeric>


//SudokuBoard constructor Initializes grid size and isvalid/board members
SudokuBoard::SudokuBoard() {
    board.resize(gridSize, std::vector<int>(gridSize, 0));
    isValid.resize(gridSize, std::vector<bool>(gridSize, true)); // Initialize validity tracking
    generateRandomBoard();

    if (!font.loadFromFile("C:\\Windows\\Fonts\\Arial.ttf")) {
        std::cerr << "Failed to load font!" << std::endl;
    }
}

// Draw the Sudoku grid and numbers
void SudokuBoard::draw(sf::RenderWindow& window) {
    for (int row = 0; row < gridSize; ++row) {
        for (int col = 0; col < gridSize; ++col) {
            sf::RectangleShape cell(sf::Vector2f(cellSize, cellSize));
            cell.setPosition(col * cellSize, row * cellSize);

            // Draw thick lines for 3x3 grids
            for (int i = 1; i <= 2; ++i) {
                sf::RectangleShape horizontalLine(sf::Vector2f(gridSize + 600, 4));  // Increase thickness to 5
                horizontalLine.setFillColor(sf::Color::Black);  // Set color to red
                horizontalLine.setPosition(0, i * 3 * cellSize);
                window.draw(horizontalLine);

                sf::RectangleShape verticalLine(sf::Vector2f(4, gridSize + 532));  // Increase thickness to 5
                verticalLine.setFillColor(sf::Color::Black);  // Set color to red
                verticalLine.setPosition(i * 3 * cellSize, 0);
                window.draw(verticalLine);
            }

            // Set cell color based on selection and validity
            if (row == selectedRow && col == selectedCol)
                cell.setFillColor(sf::Color(200, 200, 250)); // Selected cell
            else if (!isValid[row][col]) // Invalid cell
                cell.setFillColor(sf::Color(255, 0, 0)); // Red for invalid
            else
                cell.setFillColor(sf::Color::White); // Default cell color

            cell.setOutlineThickness(2);
            cell.setOutlineColor(sf::Color::Black);
            window.draw(cell);

            // Draw the number in the cell
            if (board[row][col] != 0) {
                sf::Text num;
                num.setFont(font);
                num.setString(std::to_string(board[row][col]));
                num.setCharacterSize(24);
                num.setFillColor(sf::Color::Black); // Number color
                num.setPosition(col * cellSize + 20, row * cellSize + 10);
                window.draw(num);
            }
        }
    }
}

// Select a cell
void SudokuBoard::selectCell(int row, int col) {
    selectedRow = row;
    selectedCol = col;
}

// Set a value in the selected cell
void SudokuBoard::setValue(int value) {
    if (selectedRow != -1 && selectedCol != -1) {
        if (isSafe(selectedRow, selectedCol, value)) {
            board[selectedRow][selectedCol] = value;
            isValid[selectedRow][selectedCol] = true; // Valid entry
        }
        else {
            isValid[selectedRow][selectedCol] = false; // Invalid entry
        }
    }
}

//loads values from saved file onto the board
void SudokuBoard::setLoadValue(int row, int col, int value) {
    if (row >= 0 && row < 9 && col >= 0 && col < 9) {
        board[row][col] = value;
    }else{
            isValid[row][col] = true;  // Empty cells are considered valid
        }
}

//clear function clears and resets the board if the user wishes to play again
void SudokuBoard::clear() {
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            board[row][col] = 0;             // Reset the value of the cell
            isValid[row][col] = true;       // Mark the cell as valid
        }
    }
    selectedRow = -1;                      // Reset the selected cell
    selectedCol = -1;
    std::cout << "Board cleared!" << std::endl;
    generateRandomBoard();
}


// Accessor for the board
std::vector<std::vector<int>>& SudokuBoard::getBoard() {
    return board;
}

// Accessor for the font
const sf::Font& SudokuBoard::getFont() const {
    return font;
}

// Helper function to check if it's safe to place a number in a cell
bool SudokuBoard::isSafe(int row, int col, int num) {
    for (int x = 0; x < gridSize; x++) {
        if (board[row][x] == num || board[x][col] == num)
            return false;
    }

    int startRow = row - row % 3, startCol = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i + startRow][j + startCol] == num)
                return false;
        }
    }
    return true;
}

// Recursive function to fill the board with a valid Sudoku solution
bool SudokuBoard::fillBoard(int row, int col, std::vector<int>& numbers) {
    if (row == gridSize) return true;  // Completed the board
    if (col == gridSize) return fillBoard(row + 1, 0, numbers);  // Move to next row

    for (int num : numbers) {
        if (isSafe(row, col, num)) {
            board[row][col] = num;

            // Recur to fill the rest of the board
            if (fillBoard(row, col + 1, numbers)) {
                return true;
            }

            // Backtrack if not solvable
            board[row][col] = 0;
        }
    }

    return false;  // No valid number found
}

// Generate a random Sudoku board
void SudokuBoard::generateRandomBoard() {
    // Clear the board
    for (int row = 0; row < gridSize; ++row) {
        for (int col = 0; col < gridSize; ++col) {
            board[row][col] = 0;
        }
    }

    // Random device for seeding
    std::random_device rd;
    std::mt19937 gen(rd());

    // Shuffle numbers for randomness
    std::vector<int> numbers(gridSize);
    //using std::iota generate numbers 1 to 9 (iota is part of the numeric library for generating random numbers)
    std::iota(numbers.begin(), numbers.end(), 1);  // Fill with numbers 1 to 9
    std::shuffle(numbers.begin(), numbers.end(), gen);

    // Fill the board with randomness
    fillBoard(0, 0, numbers);

    // Randomly remove numbers to create the puzzle
    int cellsToRemove = 40 + (gen() % 11);  // Remove between 40 to 50 cells

    for (int i = 0; i < cellsToRemove; i++) {
        int row = gen() % gridSize;
        int col = gen() % gridSize;
        board[row][col] = 0;  // Set cell to 0 (empty) to create the puzzle
    }

    std::cout << "New random Sudoku puzzle generated!" << std::endl;
}