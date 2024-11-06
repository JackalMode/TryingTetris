//
// Created by Mitchell Steenbergen on 11/6/2024.
//

#ifndef M4OEP_ENGINE_H
#define M4OEP_ENGINE_H
#include <SFML/Graphics.hpp>
using namespace sf;

const int GRID_WIDTH = 10;
const int GRID_HEIGHT = 20;
const int TILE_SIZE = 30;

class Engine {
public:
    Engine();
    void run();
private:
    RenderWindow window;
    int grid[GRID_HEIGHT][GRID_WIDTH];
    void Grid();
    void update();
    void render();
};


#endif //M4OEP_ENGINE_H
