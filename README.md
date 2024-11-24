# The-Game-Of-Sudoku
Sudoku game for which you can save and load files

This is a README file for the installation and execution of "The Game Of Sudoku" by group 4
The code is typically ran in Microsoft Visual Studio on windows machines
To start you will need to have all of the files, they are listed below: 
- main.cpp
- Sudoku.h
- Sudoku.cpp
- SudokuBoard.h
- SudokuBoard.cpp
- SudokuGame.h
- SudokuGame.cpp
- saved_game.txt

  Ensure the saved_game.txt is in the file path for the VS code project

Next you will need to download and install the SFML library for visual studio code
The version we used was 2.6.2 and instructions can be found through this link: https://www.sfml-dev.org/tutorials/2.6/start-vc.php

After downloading SFML's 2.6.2 version follow the guide instructions in order to implement it properly in microsft VS

The two key instructions are:

1. In the project's properties, add:
- The path to the SFML headers (<sfml-install-path>/include) to C/C++ » General » Additional Include Directories
- The path to the SFML libraries (<sfml-install-path>/lib) to Linker » General » Additional Library Directories
These paths are the same in both Debug and Release configuration, so you can set them globally for your project ("All configurations").
2. Libraries must be added in the project's properties, in Linker » Input » Additional Dependencies. Add the following: "sfml-graphics.lib", "sfml-window.lib" and "sfml-system.lib".

If these instructions aren't adequate the earlier provided link goes into further detail on the installation steps

After these steps are completed run the VS code project with all of the files present and you should be good to go



