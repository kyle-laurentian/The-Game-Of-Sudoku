#ifndef SUDOKUGAME_H
#define SUDOKUGAME_H

#include <SFML/Graphics.hpp>
#include "SudokuBoard.h"
#include "Solver.h"

enum GameState { INTRO, GAME, INSTRUCTIONS, COMPLETION }; // Add INSTRUCTIONS state

class SudokuGame {
public:
    SudokuGame();
    void run();
    void saveGame();  // Function to save the game
    void quitGame();  // Function to quit the game
    void loadGame();
    void showEndScreen();
    void solveSudoku(); //solve sudoku method

private:
    void handleEvents();

    Solver solver;
    sf::RenderWindow window;
    SudokuBoard sudokuBoard;

    GameState currentState;  // Track the current game state

    // Buttons for the intro screen
    sf::RectangleShape playButton;
    sf::RectangleShape loadButton;
    sf::RectangleShape exitButton;
    sf::RectangleShape instructionsButton; // Instructions button
    sf::Text playText;
    sf::Text loadText;
    sf::Text exitText;
    sf::Text instructionsText;
    sf::Text instructionsText2;// Text for instructions
    sf::Text theGame;

    // Button and text for solving in the game screen
    sf::RectangleShape solveButton;
    sf::Text solveText;
    sf::Text instructionsText3;

    sf::RectangleShape saveButton; // save button
    sf::RectangleShape quitButton; // quit button
    sf::Text saveText; // save text
    sf::Text quitText; //quit text

    sf::RectangleShape backButton; //button to return to homescreen
    sf::Text backButtonText; //text for backbutton

    sf::Text completionText;       // Text for the completion message
    sf::RectangleShape playAgainButton;  // Button to play again
    sf::Text playAgainText;        // Text on the "Play Again" button
    sf::RectangleShape exitGameButton;       // Button to exit
    sf::Text exitGameText;             // Text on the "Exit" button

};

#endif