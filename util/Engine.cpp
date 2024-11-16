#include <SFML/Graphics.hpp>
#include "Engine.h"
#include "../tetromino/Tetromino.h"
#include "../Screens/Screens.h"
#include <iostream>

enum GameState { START, PLAY, PAUSE, GAME_OVER};
GameState currentGameState = START;

using namespace sf;
using namespace std;

/*
 * Constructs the Engine object and initializes the game window
*/
Engine::Engine() : window(VideoMode(TILE_SIZE * GRID_WIDTH * RESIZE, TILE_SIZE * GRID_HEIGHT * RESIZE), "Tetris") {
    // Load the font
    if(!font.loadFromFile("C:/Users/Mitchell Steenbergen/CLionProjects/M4OEP-msteenbe/Font/Courier Regular.ttf")){
        std::cout << "Error loading font" << endl;
    }
    // Initialize the grid with default values
    Grid();
    // Spawn the first tetromino
    Tetro.spawnTetr(currentTetromino, grid);
    // Restart the game clock for accurate delta time
    gameClock.restart();
}

/*
 * Initialize the grid with default values
 */
void Engine::Grid(){
    for (int y = 0; y < GRID_HEIGHT; y++){
        for (int x = 0; x < GRID_WIDTH; x++){
            // Set all grid cells to 0 (empty)
            grid[y][x] = 0;
            // Set the default colors for the empty grid cells
            gridColor[y][x] = Color{0, 219, 255};
        }
    }
}
/*
 * Runs the main game loop
 */
void Engine::run(){
    Screens screens;
    while (window.isOpen()) {
        Event event;
        // Calculate Delta Time
        float dT = gameClock.restart().asSeconds();
        // Poll for events such as closing the window or pressing keys
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
            // Handle events based on the current game state
            if(currentGameState == START){
                if(event.type == Event::KeyPressed && event.key.code == Keyboard::P){
                    currentGameState = PLAY;
                } else if (event.key.code == Keyboard::Escape){
                    window.close();
                }
            } else if (currentGameState == PLAY) {
                if (event.type == Event::KeyPressed && event.key.code == Keyboard::P) {
                    currentGameState = PAUSE;
                } else if (event.key.code == Keyboard::Escape) {
                    window.close();
                }
            } else if (currentGameState == PAUSE) {
                if (event.type == Event::KeyPressed && event.key.code == Keyboard::P) {
                    currentGameState = PLAY;
                } else if (event.key.code == Keyboard::Escape) {
                    window.close();
                }
            } else if (currentGameState == GAME_OVER){
                if(event.type == Event::KeyPressed){
                    if(event.key.code == Keyboard::Escape){
                        window.close();
                    } else if (event.key.code == Keyboard::R){
                        Tetro.resetGame(grid, currentTetromino);
                        currentGameState = PLAY;
                    } else if (event.key.code == Keyboard::M){
                        Tetro.resetGame(grid, currentTetromino);
                        currentGameState = START;
                    }
                }
            }
        }

        // Clear the window with black color
        window.clear(Color::Black);

        // Render the appropriate screen based on the current game state
        if(currentGameState == START) {
            screens.startScreen(window, font);
        } else if (currentGameState == PAUSE){
            screens.pauseScreen(window, font);
        } else if (currentGameState == PLAY){
            // Set the initial view of the window to math the grid dimensions
            window.setView(View(FloatRect(0, 0, TILE_SIZE * GRID_WIDTH, TILE_SIZE * GRID_HEIGHT)));
            update(dT);
            render();
        } else if (currentGameState == GAME_OVER){
            screens.gamerOverScreen(window, font);
        }

        // Add a slight delay to control the game speed
        sleep(sf::milliseconds(10));
    }
}
/**
 * Renders the game grid and current tetromino to the game window
 */
void Engine::render(){
    // Clear the window with a black background
    window.clear(Color::Black);
    // Render each cell in the grid
    for (int y = 0; y < GRID_HEIGHT; ++y) {
        for (int x = 0; x < GRID_WIDTH; ++x) {
            // Define a cell with size adjusted for spacing
            RectangleShape cell(Vector2f(TILE_SIZE - 1, TILE_SIZE -1));
            // Set the position of each cell
            cell.setPosition(x * TILE_SIZE, y * TILE_SIZE);
            // Set cell color based on whether it's occupied
            cell.setFillColor(grid[y][x] == 0 ? Color(36, 36, 85) : gridColor[y][x]);
            window.draw(cell);
        }
    }

    // Render the current Tetromino blocks
    for(const auto& block : currentTetromino.blocks){
        // Define a tetromino block with adjusted size
        RectangleShape cell(Vector2f(TILE_SIZE - 1, TILE_SIZE - 1));
        // Set position for each tetromino block
        cell.setPosition(block.x * TILE_SIZE, block.y * TILE_SIZE);
        // set the color of the tetromino block
        cell.setFillColor(currentTetromino.color);
        // Draw the block to the window
        window.draw(cell);
    }

    // Display everything rendered on the screen
    window.display();
}
/**
 * Updates the game state
 * @param dTa
 */
void Engine::update(float dT){
    // Handles the falling movement of the tetromino (add the other movement)
    Tetro.falling(dT, currentTetromino, grid, gridColor);
    // Check if the current tetromino has stopped falling
    if (!currentTetromino.isFalling) {
        // Print grid state for debugging
        //printGrid();
        // Clear any full rows
        clearRows();
        // Spawn a new tetromino
        if(!Tetro.spawnTetr(currentTetromino, grid)){
            currentGameState = GAME_OVER;
            cout << "Game Over" << endl;
        }

    }

}
/*
 * Clears any full rows from the gird and shifts rows above down
 */
void Engine::clearRows() {
    // Iterate over the rows from bottom to top
    for (int y = GRID_HEIGHT - 1; y >= 0; y--){
        bool isFull = true;
        // Check if the row is full
        for(int x = 0; x < GRID_WIDTH; x++){
            if(grid[y][x] == 0){
                isFull = false;
                break;
            }
        }
        if(isFull){
            // Shift rows above downward
            for (int row = y; row > 0; row--){
                for(int x = 0; x < GRID_WIDTH; x++){
                    // Move the cell value down
                    grid[row][x] = grid[row - 1][x];
                    // Move the cell color down
                    gridColor[row][x] = gridColor[row - 1][x];
                }
            }
            // Clear the top row
            for(int x = 0; x < GRID_WIDTH; x++){
                // set cells to empty
                grid[0][x] = 0;
                // Set cell color
                gridColor[0][x] = Color::Black;
            }
            y++;
        }
    }
}
/**
 * Prints the current state of the grid to the console
 */
void Engine::printGrid() {
    std::cout << "Current Grid State:" << std::endl;
    for (int y = 0; y < GRID_HEIGHT; ++y) {
        for (int x = 0; x < GRID_WIDTH; ++x) {
            // Print each cell in the row.
            std::cout << grid[y][x] << " ";
        }
        std::cout << std::endl;
    }
}


