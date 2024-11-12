//
// Created by Mitchell Steenbergen on 11/8/2024.
//
#include <SFML/Graphics.hpp>
#include <vector>
#include "Constants.h"

#ifndef M4OEP_TETROMINO_H
#define M4OEP_TETROMINO_H

enum TetrominoType {
    I_SHAPE,
    O_SHAPE,
    T_SHAPE,
    S_SHAPE,
    Z_SHAPE,
    L_SHAPE,
    J_SHAPE
};

struct TetrominoData {
    std::vector<sf::Vector2i> blocks;
    sf::Color color;
    bool isFalling = true;
    TetrominoType type;
    int rotationState = 0;
};
class Tetromino{
public:
    void spawnTetr(TetrominoData &currentTetromino, int grid[][GRID_WIDTH]);
    void falling(float deltaTime, TetrominoData &currentTetromino, int grid[][GRID_WIDTH], sf::Color gridColor[][GRID_WIDTH]);
    void moveLeft(float deltaTime, TetrominoData &currentTetromino, int grid[][GRID_WIDTH]);
    void moveRight(float deltaTime, TetrominoData &currentTetromino, int gird[][GRID_WIDTH]);
    void moveDown(float deltaTime, TetrominoData &currentTetrominom, int grid[][GRID_WIDTH]);
    void resetGame(int grid[][GRID_WIDTH], TetrominoData &currentTetromino);

private:
    float horizontalAccumulator = 0.0f;
    float downAccumulator = 0.0f;
    int rotationState = 0;
    float moveDelay = 0.15f;
    float downDelay = 0.1f;
};





#endif //M4OEP_TETROMINO_H
