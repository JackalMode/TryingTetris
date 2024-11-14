#include <SFML/Graphics.hpp>
#include "Engine.h"
#include "Tetromino.h"
#include <iostream>
using namespace sf;
using namespace std;

/*
 * Constructs the Engine object and initializes the game window
 */
Engine::Engine() : window(VideoMode(TILE_SIZE * GRID_WIDTH * RESIZE, TILE_SIZE * GRID_HEIGHT * RESIZE), "Tetris") {
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
    // Set the initial view of the window to math the grid dimensions
    window.setView(View(FloatRect(0, 0, TILE_SIZE * GRID_WIDTH, TILE_SIZE * GRID_HEIGHT)));
    while(window.isOpen()){
        // Calculate Delta Time
        float dT = gameClock.restart().asSeconds();
        Event event;
        // Poll for evens such as closing the window or pressing keys
        while(window.pollEvent(event)){
            // Closes window if the close even it triggered
            if(event.type == Event::Closed){
                window.close();
            }
            // Close the window if the escape key is pressed
            if(event.type == Event::KeyPressed){
                if(event.key.code == Keyboard::Escape) {
                    window.close();
                }
            }
        }
        // Update the game based on elapsed time
        update(dT);
        // Render the current state of the game
        render();
        // Add a slight delay to the control game speed
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
 * @param dT
 */
void Engine::update(float dT){
    // Hnadles the falling movement of the tetromino (add the other movement)
    Tetro.falling(dT, currentTetromino, grid, gridColor);
    // Check if the current tetromino has stopped falling
    if (!currentTetromino.isFalling) {
        // Print grid state for debugging
        //printGrid();
        // Clear any full rows
        clearRows();
        // Spawn a new tetromino
        Tetro.spawnTetr(currentTetromino, grid);
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
