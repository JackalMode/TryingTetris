//
// Created by Mitchell Steenbergen on 11/8/2024.
//
#include <SFML/Graphics.hpp>
#include "Tetromino.h"
#include "Engine.h"
#include "Rotation.h"
#include <cstdlib>



using namespace sf;
using namespace std;
Engine engine;
/**
 * Spaws a new tetromino shapes on the game grid
 * @param currentTetromino
 * @param grid
 */
void Tetromino::spawnTetr(TetrominoData &currentTetromino, int grid[][GRID_WIDTH]) {
    int randomShape = rand() % 7;

    switch(randomShape){
        case 0:
            //I-shape
            currentTetromino.blocks = {{4, 0}, {5, 0}, {6, 0}, {7, 0}};
            currentTetromino.color = Color(0, 219, 255);
            currentTetromino.type = I_SHAPE;
            break;
        case 1:
            //O-shape
            currentTetromino.blocks = {{4, 0}, {5, 0}, {4, 1}, {5, 1}};
            currentTetromino.color = Color(255, 219, 0);
            currentTetromino.type = O_SHAPE;
            break;
        case 2:
            //S-shape
            currentTetromino.blocks = {{4, 0}, {5, 0}, {3, 1}, {4, 1}};
            currentTetromino.color = Color(0, 219, 0);
            currentTetromino.type = S_SHAPE;
            break;
        case 3:
            //Z-shape
            currentTetromino.blocks = {{3, 0}, {4, 0}, {4, 1}, {5, 1}};
            currentTetromino.color = Color(219, 0, 0);
            currentTetromino.type = Z_SHAPE;
            break;
        case 4:
            //L-shape
            currentTetromino.blocks = {{3, 0}, {3, 1}, {3, 2}, {4, 2}};
            currentTetromino.color = Color(255, 146, 0);
            currentTetromino.type = L_SHAPE;
            break;
        case 5:
            //J-shape
            currentTetromino.blocks = {{4, 0}, {4, 1}, {4, 2}, {3, 2}};
            currentTetromino.color = Color(0, 36, 255);
            currentTetromino.type = J_SHAPE;
            break;
        case 6:
            //T-Shape
            currentTetromino.blocks = {{3, 0}, {4, 0}, {5, 0}, {4, 1}};
            currentTetromino.color = Color(146, 9, 255);
            currentTetromino.type = T_SHAPE;
            break;
    }

    // Set the tetromino to be falling
    currentTetromino.isFalling = true;
    // Resets the rotation state
    currentTetromino.rotationState = 0;
    bool canPlace = true;
    // Check if there is space to place the tetromino on the grid
    for (const auto& block : currentTetromino.blocks){
        if(grid[block.y][block.x] != 0) {
            canPlace = false;
            break;
        }
    }
    // If there is no space, reset the game
    if(!canPlace) {
        resetGame(grid, currentTetromino);
    }
}

/**
 * Handles the downward/falling movement of a tetromino
 * And if it reaches the bottom or collides, it will place the tetromino on the grid
 * @param dT
 * @param currentTetromino
 * @param grid
 * @param gridColor
 */
void Tetromino::falling(float dT, TetrominoData &currentTetromino, int grid[][GRID_WIDTH], sf::Color gridColor[][GRID_WIDTH]) {
    if (!currentTetromino.isFalling) {
        return; // Do nothing if the current tetromino is not falling
    }
    horizontalAccumulator += dT;
    static float time = 0.0f;
    time += dT;
    float veloY = 1.0f;
    // Move the tetromino down after a certain delay
    if(time >= 0.5f / veloY){
        bool goDown = true;
        // Check if the tetromino can move down
        for(const auto& block : currentTetromino.blocks){
            int newY = block.y + 1;
            if(newY >= GRID_HEIGHT || grid[newY][block.x] != 0){
                goDown = false;
                break;
            }
        }
        // Move the tetromino down if possible
        if(goDown) {
            for (auto& block : currentTetromino.blocks){
                block.y++;
            }
        } else {
            // If it can't move down, add the tetromino to the gird
            for (const auto& block : currentTetromino.blocks){
                grid[block.y][block.x] = 1;
                gridColor[block.y][block.x] = currentTetromino.color;
            }
            currentTetromino.isFalling = false;

        }

        time = 0.0f;
    }
    // Call movement functions
    moveLeft(dT, currentTetromino, grid);
    moveRight(dT, currentTetromino, grid);
    moveDown(dT, currentTetromino, grid);
    Rotation::rotate(currentTetromino, grid, currentTetromino.rotationState, currentTetromino.type);
}
/**
 * Moves the tetromino to the left
 * @param deltaTime
 * @param currentTetromino
 * @param grid
 */
void Tetromino::moveLeft(float deltaTime, TetrominoData &currentTetromino, int grid[][GRID_WIDTH]) {
    horizontalAccumulator += deltaTime;
    if (Keyboard::isKeyPressed(sf::Keyboard::Left) && horizontalAccumulator >= moveDelay) {
        bool canMove = true;
        // Check if each block can move left
        for (const auto& block : currentTetromino.blocks) {
            int newX = block.x - 1;
            if (newX < 0 || grid[block.y][newX] != 0) {
                canMove = false;
                break;
            }
        }
        // Move each block to the left if possible
        if (canMove) {
            for (auto& block : currentTetromino.blocks) {
                // Move left by one full grid unit
                block.x -= 1;
            }
        }
        // Reset the accumulator
        horizontalAccumulator = 0.0f;
    }
}
/**
 * Moves the tetromino downward when the down key is pressed.
 * @param deltaTime
 * @param currentTetromino
 * @param grid
 */
void Tetromino::moveDown(float deltaTime, TetrominoData &currentTetromino, int grid[][GRID_WIDTH]) {
    downAccumulator += deltaTime;
    if(Keyboard::isKeyPressed(Keyboard::Down) && downAccumulator >= downDelay) {
        bool canMove = true;
        // Check if each block can move down
        for (const auto& block: currentTetromino.blocks) {
            int newY = block.y + 1;
            if (newY >= GRID_HEIGHT || grid[newY][block.x] != 0){
                canMove = false;
                break;
            }
        }
        // Move each block down if possible
        if(canMove){
            for(auto& block : currentTetromino.blocks){
                block.y++;
            }
        }
        // Reset the down movement accumulator
        downAccumulator = 0.0f;
    }
}
/**
 * Moves the tetromino to the right
 * @param deltaTime
 * @param currentTetromino
 * @param grid
 */
void Tetromino::moveRight(float deltaTime, TetrominoData &currentTetromino, int grid[][GRID_WIDTH]) {
    horizontalAccumulator += deltaTime;
    if (Keyboard::isKeyPressed(Keyboard::Right) && horizontalAccumulator >= moveDelay) {
        bool canMove = true;
        // Check if each block can move right
        for (const auto& block : currentTetromino.blocks) {
            int newX = block.x + 1;
            if (newX >= GRID_WIDTH || grid[block.y][newX] != 0) {
                canMove = false;
                break;
            }
        }
        // Move each block right if possible
        if (canMove) {
            for (auto& block : currentTetromino.blocks) {
                // Move right by one full grid unit
                block.x += 1;
            }
        }
        // Reset the accumulator
        horizontalAccumulator = 0.0f;
    }
}
/**
 * Resets the game grid and spaces a new tetromino.
 * @param grid
 * @param currentTetromino
 */
void Tetromino::resetGame(int grid[][GRID_WIDTH], TetrominoData &currentTetromino) {
    // Clear the grid
    for (int y = 0; y < GRID_HEIGHT; ++y) {
        for (int x = 0; x < GRID_WIDTH; ++x) {
            grid[y][x] = 0;
        }
    }

    // Spawn a new tetromino
    spawnTetr(currentTetromino, grid);
}

