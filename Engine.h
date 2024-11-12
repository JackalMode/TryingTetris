//
// Created by Mitchell Steenbergen on 11/6/2024.
//

#ifndef M4OEP_ENGINE_H
#define M4OEP_ENGINE_H
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <vector>
#include "Tetromino.h"
#include "Constants.h"
using namespace sf;


class Engine {
public:
    Engine();
    void run();
    void clearRows();
    void printGrid();

private:
    Clock gameClock;
    float horizontalAccumulator = 0.0f;
    float downAccumulator = 0.0f;
    int rotationState = 0;
    RenderWindow window;
    void Grid();
    int grid[GRID_HEIGHT][GRID_WIDTH];
    Color gridColor[GRID_HEIGHT][GRID_WIDTH];TetrominoData currentTetromino;
    Tetromino Tetro;
    void update(float deltaTime);
    void render();
};







#endif //M4OEP_ENGINE_H
