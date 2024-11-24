#include "SudokuGame.h"
#include "SudokuBoard.h"
#include <iostream>
#include "Solver.h"
#include <fstream>

//SudokuGame constructor initializes all buttons and text on the board
SudokuGame::SudokuGame()
    : window(sf::VideoMode(540, 600), "Sudoku Game"), currentState(INTRO) {
    window.setFramerateLimit(60);

    // Completion text
    completionText.setFont(sudokuBoard.getFont());  // Assuming 'font' is loaded
    completionText.setString("Congratulations! \n" "You completed the puzzle!");
    completionText.setCharacterSize(25);
    completionText.setFillColor(sf::Color::Black);
    completionText.setStyle(sf::Text::Bold);
    completionText.setPosition(50, 200);  // Centered position

    // Play Again button
    playAgainButton.setSize(sf::Vector2f(200, 50));
    playAgainButton.setFillColor(sf::Color::Blue);
    playAgainButton.setPosition(100, 300);

    playAgainText.setFont(sudokuBoard.getFont());
    playAgainText.setString("Play Again");
    playAgainText.setCharacterSize(20);
    playAgainText.setFillColor(sf::Color::White);
    playAgainText.setPosition(130, 310);

    // Exit button
    exitGameButton.setSize(sf::Vector2f(200, 50));
    exitGameButton.setFillColor(sf::Color::Red);
    exitGameButton.setPosition(100, 400);

    exitGameText.setFont(sudokuBoard.getFont());
    exitGameText.setString("Exit");
    exitGameText.setCharacterSize(20);
    exitGameText.setFillColor(sf::Color::White);
    exitGameText.setPosition(160, 410);


    // Initialize Back Button (added new button)
    backButton.setSize(sf::Vector2f(100, 40));
    backButton.setFillColor(sf::Color(100, 100, 200));
    backButton.setPosition(300, 550);  // Position it next to the Quit button

    // Set the Back button text
    backButtonText.setFont(sudokuBoard.getFont());  // Assuming the font is loaded
    backButtonText.setString("Back");
    backButtonText.setCharacterSize(20);
    backButtonText.setFillColor(sf::Color::White);
    backButtonText.setPosition(310, 560);  // Center the text on the button

    // Initialize new buttons and texts
    saveButton.setSize(sf::Vector2f(100, 40));
    saveButton.setPosition(135, 550);
    saveText.setFont(sudokuBoard.getFont());
    saveText.setString("Save");
    saveText.setPosition(145, 560);
    saveText.setCharacterSize(20);
    saveButton.setFillColor(sf::Color(100, 200, 100));

    quitButton.setSize(sf::Vector2f(100, 40));
    quitButton.setPosition(425, 550);
    quitText.setFont(sudokuBoard.getFont());
    quitText.setString("Quit");
    quitText.setCharacterSize(20);
    quitText.setPosition(435, 560);
    quitButton.setFillColor(sf::Color(200, 100, 100));

    theGame.setString("The Game Of Sudoku!");
    theGame.setFont(sudokuBoard.getFont());
    theGame.setCharacterSize(30);
    theGame.setFillColor(sf::Color::Black);
    theGame.setPosition(120, 100);

    // Setup intro screen buttons
    playButton.setSize(sf::Vector2f(100, 40));
    playButton.setFillColor(sf::Color(100, 200, 100));
    playButton.setPosition(220, 200);

    loadButton.setSize(sf::Vector2f(100, 40));
    loadButton.setFillColor(sf::Color(100, 100, 200));
    loadButton.setPosition(220, 300);

    exitButton.setSize(sf::Vector2f(100, 40));
    exitButton.setFillColor(sf::Color(200, 100, 100));
    exitButton.setPosition(220, 400);

    // Instructions button
    instructionsButton.setSize(sf::Vector2f(100, 40));
    instructionsButton.setFillColor(sf::Color(200, 200, 100));
    instructionsButton.setPosition(220, 500);

    playText.setFont(sudokuBoard.getFont());
    playText.setString("Play");
    playText.setCharacterSize(20);
    playText.setFillColor(sf::Color::White);
    playText.setPosition(240, 210);

    loadText.setFont(sudokuBoard.getFont());
    loadText.setString("Load");
    loadText.setCharacterSize(20);
    loadText.setFillColor(sf::Color::White);
    loadText.setPosition(240, 310);

    exitText.setFont(sudokuBoard.getFont());
    exitText.setString("Exit");
    exitText.setCharacterSize(20);
    exitText.setFillColor(sf::Color::White);
    exitText.setPosition(240, 410);

    // Instructions text
    instructionsText.setFont(sudokuBoard.getFont());
    instructionsText.setString("The rules for sudoku are simple. A 9×9 square must be filled in"
        "\nwith numbers from 1-9 with no repeated numbers in each line"
        "\n, horizontally or vertically. To challenge you more,"
        "there are 3×3"
        "\nsquares marked out in the grid, and each of these squares "
        "\ncan't have any repeat numbers either."
        "\n\n\n\n\n\n\n\n\n\n\n"
        "                            Click anywhere to go back");
    instructionsText.setCharacterSize(18);
    instructionsText.setFillColor(sf::Color::Black);
    instructionsText.setPosition(20, 20);  // Position of the popup text

    instructionsText2.setFont(sudokuBoard.getFont());
    instructionsText2.setString("Rules");
    instructionsText2.setCharacterSize(20);
    instructionsText2.setFillColor(sf::Color::White);
    instructionsText2.setPosition(240, 510);  // Adjust this to fit your needs

    // Setup solve button for game screen
    solveButton.setSize(sf::Vector2f(100, 40));
    solveButton.setFillColor(sf::Color(100, 200, 100));
    solveButton.setPosition(20, 550);

    solveText.setFont(sudokuBoard.getFont());
    solveText.setString("Solve");
    solveText.setCharacterSize(20);
    solveText.setFillColor(sf::Color::White);
    solveText.setPosition(40, 560);

    instructionsText3.setFont(sudokuBoard.getFont());
    instructionsText3.setString("");
    instructionsText3.setCharacterSize(20);
    instructionsText3.setFillColor(sf::Color::Black);
    instructionsText3.setPosition(130, 560);
}

//Draws buttons on the board and runs the game
void SudokuGame::run() {
    while (window.isOpen()) {
        handleEvents();
        window.clear(sf::Color::White);
        if (currentState == COMPLETION) {
            sudokuBoard.draw(window);
        }

        if (currentState == INTRO) {
            // Draw intro screen elements
            window.draw(playButton);
            window.draw(playText);
            window.draw(loadButton);
            window.draw(loadText);
            window.draw(exitButton);
            window.draw(exitText);
            window.draw(instructionsButton);
            window.draw(instructionsText2); // Draw instructions button
            window.draw(theGame);
        }
        else if (currentState == GAME) {
            // Draw game elements
            sudokuBoard.draw(window);
            window.draw(solveButton);
            window.draw(solveText);
            window.draw(instructionsText3);
            window.draw(saveButton);  // Draw save button
            window.draw(saveText);    // Draw save button text
            window.draw(quitButton);  // Draw quit button
            window.draw(quitText);    // Draw quit button text
            window.draw(backButton);  // Draw the Back button
            window.draw(backButtonText);  // Draw the Back button text
        }
        else if (currentState == INSTRUCTIONS) {
            // Draw instructions popup
            sf::RectangleShape popup(sf::Vector2f(500, 300));  // Popup background size
            popup.setFillColor(sf::Color(255, 255, 255, 200)); // White with transparency
            popup.setPosition(20, 150);  // Popup position
            window.draw(popup);
            window.draw(instructionsText);  // Draw the instructions text
        }

        window.display();
    }
}

//showEndScreen function builds small popup when the game is finished giving the user two options
//play again or exit
void SudokuGame::showEndScreen() {
    sf::RenderWindow endScreenWindow(sf::VideoMode(300, 200), "Puzzle Solved!", sf::Style::Titlebar | sf::Style::Close);

    // Text for the end screen
    sf::Font font;
    font.loadFromFile("C:\\Windows\\Fonts\\Arial.ttf");

    sf::Text messageText("Puzzle Solved!", font, 24);
    messageText.setFillColor(sf::Color::Black);
    messageText.setPosition(50, 40);

    sf::Text playAgainText("Play Again", font, 20);
    playAgainText.setFillColor(sf::Color::Blue);
    playAgainText.setPosition(50, 100);

    sf::Text exitText("Exit", font, 20);
    exitText.setFillColor(sf::Color::Blue);
    exitText.setPosition(180, 100);

    // Event loop for the end screen
    while (endScreenWindow.isOpen()) {
        sf::Event event;
        while (endScreenWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                endScreenWindow.close();
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                if (playAgainText.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    endScreenWindow.close();
                    sudokuBoard.clear();  // Clear and generate a new puzzle
                    currentState = GAME;  // Switch back to the game state
                    return;
                }
                else if (exitText.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    endScreenWindow.close();
                    window.close();  // Close the main game window
                    return;
                }
            }
        }

        // Draw the end screen contents
        endScreenWindow.clear(sf::Color::White);
        endScreenWindow.draw(messageText);
        endScreenWindow.draw(playAgainText);
        endScreenWindow.draw(exitText);
        endScreenWindow.display();
    }
}


//New function to handle all events in the board which relate to buttons and text
void SudokuGame::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        if (currentState == COMPLETION) {
            showEndScreen();
          
        }

        if (currentState == INTRO) {
            // Handle intro screen button clicks
            if (event.type == sf::Event::MouseButtonPressed) {
                if (playButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    currentState = GAME;  // Transition to game screen
                }
                else if (exitButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    window.close();
                }
                else if (instructionsButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    currentState = INSTRUCTIONS;  // Show instructions
                }
                else if (loadButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    std::ifstream loadFile("saved_game.txt");
                    if (loadFile.is_open()) {
                        int value;
                        for (int row = 0; row < 9; ++row) {
                            for (int col = 0; col < 9; ++col) {
                                if (loadFile >> value) {
                                    sudokuBoard.setLoadValue(row, col, value);  // Load the value into the board
                                }
                            }
                        }
                        loadFile.close();
                        std::cout << "Game loaded successfully from saved_game.txt" << std::endl;
                        currentState = GAME;  // Transition to game screen after loading
                    }
                    else {
                        std::cerr << "Error: Unable to open saved_game.txt" << std::endl;
                    }
                }
            }
        }
        else if (currentState == GAME) {
            // Handle game screen events
            if (event.type == sf::Event::MouseButtonPressed) {
                int row = event.mouseButton.y / 60;
                int col = event.mouseButton.x / 60;

                if (solveButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    solveSudoku();
                }
                else if (saveButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    saveGame();  // Save game logic
                }
                else if (quitButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    quitGame();  // Quit game logic
                }
                else if (backButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    currentState = INTRO;  // Change state to go back to the intro screen
                }
                else if (row < 9 && col < 9) {
                    sudokuBoard.selectCell(row, col);
                }
            }

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code >= sf::Keyboard::Num1 && event.key.code <= sf::Keyboard::Num9) {
                    sudokuBoard.setValue(event.key.code - sf::Keyboard::Num0);
                }
                else if (event.key.code == sf::Keyboard::Num0) {
                    sudokuBoard.setValue(0);
                }
            }
        }
        else if (currentState == INSTRUCTIONS) {
            if (event.type == sf::Event::MouseButtonPressed) {
                // Close instructions popup when clicked anywhere in the window
                currentState = INTRO;
            }
        }
    }
}


//saveGame saves the values on the board and keeps them in a seperate saved txt file
void SudokuGame::saveGame() {
    std::ofstream outFile("saved_game.txt");  // Save the game with a fixed name
    if (outFile.is_open()) {
        // Write the current Sudoku board to the file
        for (int row = 0; row < 9; row++) {
            for (int col = 0; col < 9; col++) {
                outFile << sudokuBoard.getBoard()[row][col] << " ";
            }
            outFile << std::endl;
        }
        outFile.close();
        std::cout << "Game saved!" << std::endl;  // This line prints the message
    }
    else {
        std::cout << "Error saving the game!" << std::endl;
    }
}

// Load the game state from a file
void SudokuGame::loadGame() {
    std::ifstream loadFile("saved_game.txt");
    if (loadFile.is_open()) {
        int value;
        for (int row = 0; row < 9; ++row) {
            for (int col = 0; col < 9; ++col) {
                if (loadFile >> value) {
                    sudokuBoard.setLoadValue(row, col, value);
                }
            }
        }
        loadFile.close();
        std::cout << "Game loaded from saved_game.txt" << std::endl;
    }
    else {
        std::cerr << "Error: Could not load the game." << std::endl;
    }
}

// Quit the game
void SudokuGame::quitGame() {
    window.close();
}

//function for solving updated sudoku board
void SudokuGame::solveSudoku() {
    // Get a reference to the board from the SudokuBoard instance
    auto& board = sudokuBoard.getBoard();

    // Use the Solver class to solve the board
    if (solver.solve(board)) {
        // Update the board if a solution is found
        sudokuBoard.getBoard() = board;
        std::cout << "Puzzle solved!" << std::endl;
        currentState = COMPLETION;//set board to completed status to display options for user
    }
    else {
        std::cout << "No solution found!" << std::endl;
    }
}
