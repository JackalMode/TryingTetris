#include <SFML/Graphics.hpp>
#include "Engine.h"
#include <cstdlib>

using namespace sf;
using namespace std;

Engine::Engine() : window(VideoMode(2 * TILE_SIZE * GRID_WIDTH * RESIZE, TILE_SIZE * GRID_HEIGHT * RESIZE), "Tetris") {
    Grid();
    spawnTetr();
    gameClock.restart();
}

void Engine::Grid(){
    for (int y = 0; y < GRID_HEIGHT; y++){
        for (int x = 0; x < GRID_WIDTH; x++){
            grid[y][x] = 0;
            gridColor[y][x] = Color::Black;
        }
    }
}

void Engine::spawnTetr() {
    int randomShape = rand() % 7;

    switch(randomShape){
        case 0:
            //I-shape
            currentTetromino.blocks = {{4, 0}, {5, 0}, {6, 0}, {7, 0}};
            currentTetromino.color = Color::Cyan;
            break;
        case 1:
            //O-shape
            currentTetromino.blocks = {{4, 0}, {5, 0}, {4, 1}, {5, 1}};
            currentTetromino.color = Color::Yellow;
            break;
        case 2:
            //S-shape
            currentTetromino.blocks = {{4, 0}, {5, 0}, {3, 1}, {4, 1}};
            currentTetromino.color = Color::Red;
            break;
        case 3:
            //Z-shape
            currentTetromino.blocks = {{3, 0}, {4, 0}, {4, 1}, {5, 1}};
            currentTetromino.color = Color::Green;
            break;
        case 4:
            //L-shape
            currentTetromino.blocks = {{3, 0}, {3, 1}, {3, 2}, {4, 2}};
            currentTetromino.color = Color{255, 165, 0, 255};
            break;
        case 5:
            //J-shape
            currentTetromino.blocks = {{4, 0}, {4, 1}, {4, 2}, {3, 2}};
            currentTetromino.color = Color(255, 141, 161, 255);
            break;
        case 6:
            //T-Shape
            currentTetromino.blocks = {{3, 0}, {4, 0}, {5, 0}, {4, 1}};
            currentTetromino.color = Color(127, 0, 255, 255);
            break;
    }

}

void Engine::run(){
    window.setView(View(FloatRect(0, 0, 2 * TILE_SIZE * GRID_WIDTH, TILE_SIZE * GRID_HEIGHT)));
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
    window.clear(Color::White);
    for (int y = 0; y < GRID_HEIGHT; ++y) {
        for (int x = 0; x < GRID_WIDTH; ++x) {
            RectangleShape cell(Vector2f(TILE_SIZE - 1, TILE_SIZE -1));
            cell.setPosition(x * TILE_SIZE, y * TILE_SIZE);
            cell.setFillColor(grid[y][x] == 0 ? Color::Black : gridColor[y][x]);
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
    horizontalAccumulator += dT;
    float moveDelay = 0.09f;
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
            spawnTetr();
        }

        time = 0.0f;
    }

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
    float downDelay = 0.1f;
    downAccumulator += dT;
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

