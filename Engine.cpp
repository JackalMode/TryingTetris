#include <SFML/Graphics.hpp>
#include "Engine.h"
#include "Tetromino.h"
#include "Rotation.h"
#include <cstdlib>
#include <iostream>
using namespace sf;
using namespace std;

Engine::Engine() : window(VideoMode(TILE_SIZE * GRID_WIDTH * RESIZE, TILE_SIZE * GRID_HEIGHT * RESIZE), "Tetris") {
    Grid();
    Tetro.spawnTetr(currentTetromino, grid);
    gameClock.restart();
    std::cout << "Grid initialized." << std::endl; // Debug: track grid initialization
}



void Engine::Grid(){
    std::cout << "Grid() function called." << std::endl; // Debug: Track calls to Grid
    for (int y = 0; y < GRID_HEIGHT; y++){
        for (int x = 0; x < GRID_WIDTH; x++){
            grid[y][x] = 0;
            gridColor[y][x] = Color{0, 219, 255};
        }
    }
}

void Engine::run(){
    window.setView(View(FloatRect(0, 0, TILE_SIZE * GRID_WIDTH, TILE_SIZE * GRID_HEIGHT)));
    while(window.isOpen()){
        float dT = gameClock.restart().asSeconds();
        Event event;
        while(window.pollEvent(event)){
            if(event.type == Event::Closed){
                window.close();
            }
            if(event.type == Event::KeyPressed){
                if(event.key.code == Keyboard::Escape) {
                    window.close();
                }
            }
        }
        update(dT);
        render();
        sleep(sf::milliseconds(10));
    }
}

void Engine::render(){
    window.clear(Color::Black);
    for (int y = 0; y < GRID_HEIGHT; ++y) {
        for (int x = 0; x < GRID_WIDTH; ++x) {
            RectangleShape cell(Vector2f(TILE_SIZE - 1, TILE_SIZE -1));
            cell.setPosition(x * TILE_SIZE, y * TILE_SIZE);
            cell.setFillColor(grid[y][x] == 0 ? Color(36, 36, 85) : gridColor[y][x]);
            window.draw(cell);
        }
    }
    for(const auto& block : currentTetromino.blocks){
        RectangleShape cell(Vector2f(TILE_SIZE - 1, TILE_SIZE - 1));
        cell.setPosition(block.x * TILE_SIZE, block.y * TILE_SIZE);
        cell.setFillColor(currentTetromino.color);
        window.draw(cell);
    }
    window.display();
}

void Engine::update(float dT){
    Tetro.falling(dT, currentTetromino, grid, gridColor);
    if (!currentTetromino.isFalling) {
        printGrid();
        clearRows();
        Tetro.spawnTetr(currentTetromino, grid);
    }

}

void Engine::clearRows() {
    for (int y = GRID_HEIGHT - 1; y >= 0; y--){
        bool isFull = true;

        for(int x = 0; x < GRID_WIDTH; x++){
            if(grid[y][x] == 0){
                isFull = false;
                break;
            }
        }
        if(isFull){
            for (int row = y; row > 0; row--){
                for(int x = 0; x < GRID_WIDTH; x++){
                    grid[row][x] = grid[row - 1][x];
                    gridColor[row][x] = gridColor[row - 1][x];
                }
            }

            for(int x = 0; x < GRID_WIDTH; x++){
                grid[0][x] = 0;
                gridColor[0][x] = Color::Black;
            }
            y++;
        }
    }
}

void Engine::printGrid() {
    std::cout << "Current Grid State:" << std::endl;
    for (int y = 0; y < GRID_HEIGHT; ++y) {
        for (int x = 0; x < GRID_WIDTH; ++x) {
            std::cout << grid[y][x] << " ";
        }
        std::cout << std::endl;
    }
}
