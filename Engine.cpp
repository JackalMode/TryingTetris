#include <SFML/Graphics.hpp>
#include "player.h"
#include "Engine.h"

using namespace sf;
using namespace std;

Engine::Engine() : window(VideoMode(GRID_WIDTH * TILE_SIZE, GRID_HEIGHT * TILE_SIZE), "Tetris") {
    Grid();
}

void Engine::Grid(){
    for (auto & y : grid){
        for (int & x : y){
            x = 0;
        }
    }
}

void Engine::run(){
    while(window.isOpen()){
        Event event;
        while(window.pollEvent(event)){
            if(event.type == Event::KeyPressed){
                if(event.key.code == Keyboard::Escape) {
                    window.close();
                }
            }
        }
        update();
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
            cell.setFillColor(grid[y][x] == 0 ? Color::Blue : Color::White);
            window.draw(cell);
        }
    }
    window.display();
}

void Engine::update(){

}