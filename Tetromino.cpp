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


    currentTetromino.isFalling = true;
    currentTetromino.rotationState = 0;
    bool canPlace = true;
    for (const auto& block : currentTetromino.blocks){
        if(grid[block.y][block.x] != 0) {
            canPlace = false;
            break;
        }
    }
    if(!canPlace) {
        resetGame(grid, currentTetromino);
    }
}

void Tetromino::falling(float dT, TetrominoData &currentTetromino, int grid[][GRID_WIDTH], sf::Color gridColor[][GRID_WIDTH]) {
    if (!currentTetromino.isFalling) {
        return; // Do nothing if the current tetromino is not falling
    }
    horizontalAccumulator += dT;
    static float time = 0.0f;
    time += dT;
    float veloY = 1.0f;
    if(time >= 0.5f / veloY){
        bool goDown = true;
        for(const auto& block : currentTetromino.blocks){
            int newY = block.y + 1;
            if(newY >= GRID_HEIGHT || grid[newY][block.x] != 0){
                goDown = false;
                break;
            }
        }
        if(goDown) {
            for (auto& block : currentTetromino.blocks){
                block.y++;
            }
        } else {
            for (const auto& block : currentTetromino.blocks){
                grid[block.y][block.x] = 1;
                gridColor[block.y][block.x] = currentTetromino.color;
            }
            currentTetromino.isFalling = false;
            engine.printGrid();

        }

        time = 0.0f;
    }

    moveLeft(dT, currentTetromino, grid);
    moveRight(dT, currentTetromino, grid);
    moveDown(dT, currentTetromino, grid);
    Rotation::rotate(currentTetromino, grid, currentTetromino.rotationState, currentTetromino.type);
}

void Tetromino::moveLeft(float deltaTime, TetrominoData &currentTetromino, int grid[][GRID_WIDTH]) {
    horizontalAccumulator += deltaTime;
    if (Keyboard::isKeyPressed(sf::Keyboard::Left) && horizontalAccumulator >= moveDelay) {
        bool canMove = true;

        for (const auto& block : currentTetromino.blocks) {
            int newX = block.x - 1;
            if (newX < 0 || grid[block.y][newX] != 0) {
                canMove = false;
                break;
            }
        }
        if (canMove) {
            for (auto& block : currentTetromino.blocks) {
                block.x -= 1; // Move left by one full grid unit
            }
        }
        horizontalAccumulator = 0.0f; // Reset the accumulator
    }
}

void Tetromino::moveDown(float deltaTime, TetrominoData &currentTetromino, int grid[][GRID_WIDTH]) {
    downAccumulator += deltaTime;
    if(Keyboard::isKeyPressed(Keyboard::Down) && downAccumulator >= downDelay) {
        bool canMove = true;
        for (const auto& block: currentTetromino.blocks) {
            int newY = block.y + 1;
            if (newY >= GRID_HEIGHT || grid[newY][block.x] != 0){
                canMove = false;
                break;
            }
        }
        if(canMove){
            for(auto& block : currentTetromino.blocks){
                block.y++;
            }
        }
        downAccumulator = 0.0f;
    }
}

void Tetromino::moveRight(float deltaTime, TetrominoData &currentTetromino, int grid[][GRID_WIDTH]) {
    horizontalAccumulator += deltaTime;
    if (Keyboard::isKeyPressed(Keyboard::Right) && horizontalAccumulator >= moveDelay) {
        bool canMove = true;

        for (const auto& block : currentTetromino.blocks) {
            int newX = block.x + 1;
            if (newX >= GRID_WIDTH || grid[block.y][newX] != 0) {
                canMove = false;
                break;
            }
        }
        if (canMove) {
            for (auto& block : currentTetromino.blocks) {
                block.x += 1; // Move right by one full grid unit
            }
        }
        horizontalAccumulator = 0.0f; // Reset the accumulator
    }
}

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

