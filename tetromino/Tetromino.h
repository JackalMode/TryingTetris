//
// Created by Mitchell Steenbergen on 11/8/2024.
//
#include <SFML/Graphics.hpp>
#include <vector>
#include "../util/Constants.h"

#ifndef M4OEP_TETROMINO_H
#define M4OEP_TETROMINO_H

// Enum to represent different types of tetromino shapes
enum TetrominoType {
    I_SHAPE,
    O_SHAPE,
    T_SHAPE,
    S_SHAPE,
    Z_SHAPE,
    L_SHAPE,
    J_SHAPE
};

// Struct to hold data about tetromino, including, block position, color, type, and state.
struct TetrominoData {
    std::vector<sf::Vector2i> blocks;
    sf::Color color;
    bool isFalling = true;
    TetrominoType type;
    int rotationState = 0;
};
class Tetromino{
public:
    //Spawns a new tetromino at the top of the game grid
    void spawnTetr(TetrominoData &currentTetromino);
    // Handles the constant downward movement  of the tetromino, including collision checking
    int falling(float deltaTime, TetrominoData &currentTetromino, int grid[][GRID_WIDTH], sf::Color gridColor[][GRID_WIDTH], float velo);
    // Moves the tetromino to the left, checks for collisions and boundaries
    void moveLeft(float deltaTime, TetrominoData &currentTetromino, int grid[][GRID_WIDTH]);
    // Moves the tetromino to the right, checks for collisions and boundaries
    void moveRight(float deltaTime, TetrominoData &currentTetromino, int gird[][GRID_WIDTH]);
    // Moves the tetromino downward more quickly from user
    bool moveDown(float deltaTime, TetrominoData &currentTetrominom, int grid[][GRID_WIDTH]);
    // Resets the game state, which clears the grid and respawning tetromino,
    void resetGame(int grid[][GRID_WIDTH], TetrominoData &currentTetromino);

private:
    // Accumulates time for horizontal movement
    float horizontalAccumulator = 0.0f;
    // Accumulates time for downward movement
    float downAccumulator = 0.0f;
    // Stores the current rotation state of the tetromino
    int rotationState = 0;
    // Delay between horizontal moves (left and right)
    float moveDelay = 0.15f;
    // Delay between downward moves
    float downDelay = 0.1f;
};





#endif //M4OEP_TETROMINO_H
