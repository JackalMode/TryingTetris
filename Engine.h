//
// Created by Mitchell Steenbergen on 11/6/2024.
//

#ifndef M4OEP_ENGINE_H
#define M4OEP_ENGINE_H
#include <SFML/Graphics.hpp>
#include <vector>
using namespace sf;

const int GRID_WIDTH = 10;
const int GRID_HEIGHT = 20;
const int TILE_SIZE = 8;
const int RESIZE = 4;

struct Tetromino {
    std::vector<Vector2i> blocks;
    Color color;
};

class Engine {
public:
    Engine();
    void run();
private:
    Clock gameClock;
    float velocityX = 5.0f;
    float horizontalAccumulator = 0.0f;
    float downAccumulator = 0.0f;
    RenderWindow window;
    int grid[GRID_HEIGHT][GRID_WIDTH];
    Color gridColor[GRID_HEIGHT][GRID_WIDTH];
    Tetromino currentTetromino;
    void spawnTetr();
    void Grid();
    void update(float deltaTime);
    void render();
};


#endif //M4OEP_ENGINE_H
