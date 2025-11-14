//
// Created by Mitchell Steenbergen on 11/6/2024.
//

#ifndef M4OEP_ENGINE_H
#define M4OEP_ENGINE_H
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <vector>
#include "../tetromino/Tetromino.h"
#include "Constants.h"

using namespace sf;


class Engine {
public:
    // Constructs an Engine object
    Engine();
    // Main game loop
    void run();
    // Clears full rows from the grid
    void clearRows();
    // Prints the current state of the grid to the console
    void printGrid();

private:
    Font font;
    // Game clock for tracking time between updates.
    Clock gameClock;
    // Game window to display the game
    RenderWindow window;
    // The game grid representing the current state of the blocks
    int grid[GRID_HEIGHT][GRID_WIDTH];
    // Color representation of each position in the gird
    Color gridColor[GRID_HEIGHT][GRID_WIDTH];
    // Data for the current tetromino being manipulated
    TetrominoData currentTetromino;
    // Tetromino object used for managing tetrmonio operations
    Tetromino Tetro;
    // Checks if you can place the Tetromino
    bool canPlace(const TetrominoData& tetro) const;
    // Initializes the game grid
    void Grid();
    // Updates the game state
    void update(float deltaTime);
    // Renders the current state of the game
    void render();
    // Game view
    View gameView;
    // Hud View
    View hudView;
    // Upcoming piece (not falling yet)
    TetrominoData nextTetromino;
    // Hud helping hand thingy
    void drawNextPreviewHUD();
    // Score
    int score;
    // Score Text
    Text scoreText;
    // Line text
    Text lineText;
    // Line clear number
    int line;
};







#endif //M4OEP_ENGINE_H
