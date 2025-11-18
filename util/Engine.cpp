#include <SFML/Graphics.hpp>
#include "Engine.h"
#include "../tetromino/Tetromino.h"
#include "../Screens/Screens.h"
#include <iostream>
#include <climits>
#include <algorithm>
#include <fstream>
#include<functional>

enum GameState { START, PLAY, PAUSE, GAME_OVER};
GameState currentGameState = START;

using namespace sf;
using namespace std;

/**
 * Constructs the Engine object and initializes the game window
*/
Engine::Engine() : window(VideoMode(TILE_SIZE * GRID_WIDTH * RESIZE * 2, TILE_SIZE * GRID_HEIGHT * RESIZE), "Tetris") {
    // Load the font
    if(!font.loadFromFile("C:/Users/Mitchell Steenbergen/CLionProjects/Tetris/Font/JetBrainsMonoNL-Regular.ttf")){
        std::cout << "Error loading font" << endl;
    }
    // Initialize the grid with default values
    Grid();
    score = 0;
    line = 0;

    highScores.fill(0);
    loadHighScores();
    // Initializing the Score Text
    initHudLabel(scoreText, "Score:");
    // Initializing the Score Text
    initHudLabel(lineText, "Lines:");
    // Initializing the Next text
    initHudLabel(nextLabel, "Next:");

    // Spawn the first Tetromino
    Tetro.spawnTetr(currentTetromino);

    // Spawns the next Tetromino that will fall
    Tetro.spawnTetr(nextTetromino);

    // Set it to false, so it doesn't fall as it is the upcoming one
    nextTetromino.isFalling = false;

    const auto worldW = static_cast<float>(TILE_SIZE * GRID_WIDTH);
    const auto worldH = static_cast<float>(TILE_SIZE * GRID_HEIGHT);
    // Game View is set to the left side of the window
    gameView.reset(FloatRect(0.f, 0.f, worldW, worldH));
    gameView.setViewport(FloatRect(0.f, 0.f, 0.5f, 1.f));

    // Hud view covers the right side of the window
    hudView = window.getDefaultView();
    hudView.setViewport(FloatRect(0.5f, 0.f, 0.5f, 1.f));
    hudView.reset(sf::FloatRect(0.f, 0.f, worldW, worldH));
    // Restart the game clock for accurate delta time
    gameClock.restart();
}

/**
 * Initialize the HUD text
*/
void Engine::initHudLabel(sf::Text &text, const std::string &label) {
     text.setFont(font);
     text.setString(label);
     text.setFillColor(Color(230, 230, 230));
     text.setCharacterSize(20);
}

/**
  * Loading the scores from the txt file
*/
void Engine::loadHighScores() {
    std::ifstream inFile("highscores.txt");
    if(!inFile.is_open()){
        highScores.fill(0);
        return;
    }
    for(int i = 0; i < 4 && inFile; i++){
        inFile >> highScores[i];
        if(!inFile){
            highScores[i] = 0;
        }
    }
    std::sort(highScores.begin(), highScores.end(), std::greater<>());
}

/**
 * Saving the scores to a txt file
 */
void Engine::saveHighScores() {
    std::ofstream outFile("highscores.txt", std::ios::trunc);
    if(!outFile.is_open()){
        return;
    }
    for(size_t i = 0; i < highScores.size(); i++){
        outFile << highScores[i];
        if(i + 1 < highScores.size()){
            outFile << "\n";
        }
    }
}


/**
 * Initialize the grid with default values
 */
void Engine::Grid(){
    for (int y = 0; y < GRID_HEIGHT; y++){
        for (int x = 0; x < GRID_WIDTH; x++){
            // Set all grid cells to 0 (empty)
            grid[y][x] = 0;
            // Set the default colors for the empty grid cells
            gridColor[y][x] = Color{0, 219, 255};
        }
    }
}
/**
 * Updates the High Scores
 */
 void Engine::updateHighScores(int finalScore) {
     if (finalScore <= 0) {
         return;
     }
     highScores.back() = std::max(highScores.back(), finalScore);
     for(size_t i = 0; i < highScores.size(); i++){
         for (size_t j = i + 1; j < highScores.size(); j++){
             if(highScores[j] > highScores[i]) {
                 std::swap(highScores[i], highScores[j]);
             }
         }
     }
     saveHighScores();
 }
/**
 * Runs the main game loop
 */
void Engine::run(){
    Screens screens;
    while (window.isOpen()) {
        Event event{};
        // Calculate Delta Time
        float dT = gameClock.restart().asSeconds();
        // Poll for events such as closing the window or pressing keys
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
            // Handle events based on the current game state
            if(currentGameState == START){
                if(event.type == Event::KeyPressed && event.key.code == Keyboard::P){
                    currentGameState = PLAY;
                } else if (event.key.code == Keyboard::Escape){
                    window.close();
                }
            } else if (currentGameState == PLAY) {
                if (event.type == Event::KeyPressed && event.key.code == Keyboard::P) {
                    currentGameState = PAUSE;
                } else if (event.key.code == Keyboard::Escape) {
                    window.close();
                }
            } else if (currentGameState == PAUSE) {
                if (event.type == Event::KeyPressed && event.key.code == Keyboard::P) {
                    currentGameState = PLAY;
                } else if (event.key.code == Keyboard::Escape) {
                    window.close();
                } else if (event.key.code == Keyboard::R) {
                    Tetro.resetGame(grid, currentTetromino);
                    // Clearing the line and line text
                    // Clearing the score and score text as well
                    clearScoreLine();
                    currentGameState = PLAY;
                }
            } else if (currentGameState == GAME_OVER){
                if(event.type == Event::KeyPressed){
                    if(event.key.code == Keyboard::Escape){
                        window.close();
                    } else if (event.key.code == Keyboard::R){
                        Tetro.resetGame(grid, currentTetromino);
                        // Clearing the line and line text
                        clearScoreLine();
                        currentGameState = PLAY;
                    } else if (event.key.code == Keyboard::M){
                        Tetro.resetGame(grid, currentTetromino);
                        // Clearing the line and line text
                        clearScoreLine();
                        currentGameState = START;
                    }
                }
            }
        }

        // Clear the window with black color
        window.clear(Color::Black);

        // Render the appropriate screen based on the current game state
        if(currentGameState == START) {
            screens.startScreen(window, font, highScores);
        } else if (currentGameState == PAUSE){
            screens.pauseScreen(window, font);
        } else if (currentGameState == PLAY){
            // Set the initial view of the window to math the grid dimensions
            //window.setView(View(FloatRect(0, 0, TILE_SIZE * GRID_WIDTH, TILE_SIZE * GRID_HEIGHT)));
            window.setView(gameView);
            update(dT);
            render();
        } else if (currentGameState == GAME_OVER){
            screens.gamerOverScreen(window, font, highScores);
        }

        // Add a slight delay to control the game speed
        sleep(sf::milliseconds(1));
    }
}
/**
 * Renders the game grid and current tetromino to the game window
 */
void Engine::render(){
    // Clear the window with a black background
    window.clear(Color::Black);
    // Set view to game
    window.setView(gameView);
    // Render each cell in the grid
    for (int y = 0; y < GRID_HEIGHT; ++y) {
        for (int x = 0; x < GRID_WIDTH; ++x) {
            // Define a cell with size adjusted for spacing
            RectangleShape cell(Vector2f(TILE_SIZE - 1, TILE_SIZE -1));
            // Set the position of each cell
            cell.setPosition(x * TILE_SIZE, y * TILE_SIZE);
            // Set cell color based on whether it's occupied
            cell.setFillColor(grid[y][x] == 0 ? Color(36, 36, 85) : gridColor[y][x]);
            window.draw(cell);
        }
    }

    // ADD GHOST LOGIC
    if (currentTetromino.isFalling && !currentTetromino.blocks.empty()){
        int drop = INT_MAX;

        for(const auto& block : currentTetromino.blocks){
            int localDrop = 0;
            while (true) {
                int newY = block.y + localDrop + 1;
                if(newY >= GRID_HEIGHT || grid[newY][block.x] != 0){
                    break;
                }
                localDrop++;
            }
            drop = std::min(drop, localDrop);
        }
        if(drop > 0 && drop != INT_MAX){
            // Matching the ghost Tetro with the current one and making it transparent
            Color ghostColor = currentTetromino.color;
            ghostColor.a = 80;

            for(const auto& block : currentTetromino.blocks){
                RectangleShape ghostCell(Vector2f(TILE_SIZE - 1, TILE_SIZE - 1));
                ghostCell.setPosition(block.x * TILE_SIZE, (block.y + drop) * TILE_SIZE);
                ghostCell.setFillColor(ghostColor);
                window.draw(ghostCell);
            }
        }
    }

    // Render the current Tetromino blocks
    for(const auto& block : currentTetromino.blocks){
        // Define a tetromino block with adjusted size
        RectangleShape cell(Vector2f(TILE_SIZE - 1, TILE_SIZE - 1));
        // Set position for each tetromino block
        cell.setPosition(block.x * TILE_SIZE, block.y * TILE_SIZE);
        // set the color of the tetromino block
        cell.setFillColor(currentTetromino.color);
        // Draw the block to the window
        window.draw(cell);
    }

    // Set view to Right
    drawNextPreviewHUD();

    // Display everything rendered on the screen
    window.display();
}
/**
 * Updates the game state
 * @param dTa
 */
void Engine::update(float dT){\
    // The speed at which the game is played at the start.
    vela = 1.0f;
    // Updates the game speed after every 10 lines cleared
    if(line >= lastSpeedTrigger + 10){
        vela += 1.f;
        lastSpeedTrigger = line;
    }
    // Handles the falling movement of the tetromino (add the other movement)
    int steps = Tetro.falling(dT, currentTetromino, grid, gridColor, vela);
    if (steps > 0) {
        score += 1;
        scoreText.setString("Score:" + std::to_string(score));
    }
    // Check if the current tetromino has stopped falling
    if (!currentTetromino.isFalling) {
        // Print grid state for debugging
        //printGrid();
        // Clear any full rows
        clearRows();

        // Spawn a new Tetromino by setting current to next
        currentTetromino = nextTetromino;
        currentTetromino.isFalling = true;
        // Checking if it can place.
        if(!canPlace(currentTetromino)){
            updateHighScores(score);
            currentGameState = GAME_OVER;
            cout << "Game Over" << endl;
        }

        // Spawning the upcoming tetromino.
        Tetro.spawnTetr(nextTetromino);
        nextTetromino.isFalling = false;

    }
}
/**
 * Checks if you are able to put the blocks down
 */
bool Engine::canPlace(const TetrominoData &tetro) const {
    for(const auto& blo : tetro.blocks) {
        if (blo.y < 0 || blo.y >= GRID_HEIGHT || blo.x < 0 || blo.x >= GRID_WIDTH){
            return false;
        }
        if (grid[blo.y][blo.x] != 0){
            return false;
        }
    }
    return true;
}
/**
 * Clears any full rows from the gird and shifts rows above down
 */
void Engine::clearRows() {
    // Iterate over the rows from bottom to top
    for (int y = GRID_HEIGHT - 1; y >= 0; y--){
        bool isFull = true;
        // Check if the row is full
        for(int x = 0; x < GRID_WIDTH; x++){
            if(grid[y][x] == 0){
                isFull = false;
                break;
            }
        }
        if(isFull){
            // Adding 100 for every line cleared
            score += 100;
            scoreText.setString("Score:" + std::to_string(score));
            // Keeping track of how many lines cleared
            line += 1;
            lineText.setString("Lines:" + std::to_string(line));
            // Shift rows above downward
            for (int row = y; row > 0; row--){
                for(int x = 0; x < GRID_WIDTH; x++){
                    // Move the cell value down
                    grid[row][x] = grid[row - 1][x];
                    // Move the cell color down
                    gridColor[row][x] = gridColor[row - 1][x];
                }
            }
            // Clear the top row
            for(int x = 0; x < GRID_WIDTH; x++){
                // set cells to empty
                grid[0][x] = 0;
                // Set cell color
                gridColor[0][x] = Color::Black;
            }
            y++;
        }
    }
}
/**
 * Prints the current state of the grid to the console THIS IS FOR TESTING
 */
void Engine::printGrid() {
    std::cout << "Current Grid State:" << std::endl;
    for (int y = 0; y < GRID_HEIGHT; ++y) {
        for (int x = 0; x < GRID_WIDTH; ++x) {
            // Print each cell in the row.
            std::cout << grid[y][x] << " ";
        }
        std::cout << std::endl;

        std::cout << line << std::endl;
    }
}
/**
 * Draws the next tetromino in a HUD that will be spawning in
 */
void Engine::drawNextPreviewHUD() {
    // Switch to HUD view (right side)
    window.setView(hudView);

    const auto worldW = static_cast<float>(TILE_SIZE * GRID_WIDTH);
    const auto worldH = static_cast<float>(TILE_SIZE * GRID_HEIGHT);

    // Preview box
    const float pad = 24.f;
    const FloatRect previewBox(pad, 56.f, worldW - 1.5f * pad, worldH - 80.f - pad);

    RectangleShape box({previewBox.width, previewBox.height});
    box.setPosition(previewBox.left - 10.f, previewBox.top - 30.f);
    box.setFillColor(sf::Color(28, 28, 56));
    box.setOutlineThickness(1.f);
    box.setOutlineColor(sf::Color(90, 90, 160));
    window.draw(box);


    // Compute bounding box (in block units) of the next tetromino
    int minX = INT_MAX, maxX = INT_MIN, minY = INT_MAX, maxY = INT_MIN;
    for (const auto& b : nextTetromino.blocks) {
        minX = std::min(minX, b.x);
        maxX = std::max(maxX, b.x);
        minY = std::min(minY, b.y);
        maxY = std::max(maxY, b.y);
    }
    const int wBlocks = (maxX - minX + 1);
    const int hBlocks = (maxY - minY + 1);

    // Use the same TILE_SIZE so it matches game scale (looks crisp)
    const auto blockSize = static_cast<float>(TILE_SIZE);

    const float shapeWpx = wBlocks * blockSize;
    const float shapeHpx = hBlocks * blockSize;

    // Center the shape inside the preview box
    const float startX = (previewBox.left - 10.f) + (previewBox.width  - shapeWpx) * 0.5f;
    const float startY = (previewBox.top - 30.f)  + (previewBox.height - shapeHpx) * 0.5f;

    // Draw the tetromino blocks
    for (const auto& b : nextTetromino.blocks) {
        sf::RectangleShape cell({blockSize - 1.f, blockSize - 1.f});
        auto localX = static_cast<float>(b.x - minX);
        auto localY = static_cast<float>(b.y - minY);
        cell.setPosition(startX + localX * blockSize, startY + localY * blockSize);
        cell.setFillColor(nextTetromino.color);
        window.draw(cell);
    }
    scoreText.setPosition(375, worldH + 170);
    lineText.setPosition(375, worldH + 200);
    nextLabel.setPosition(375, worldH - 100);
    window.setView(window.getDefaultView());
    window.draw(scoreText);
    window.draw(nextLabel);
    window.draw(lineText);
}

/**
* Clears the Score and Line numbers
*/
void Engine::clearScoreLine() {
    line = 0;
    lineText.setString("Lines:");
    score = 0;
    scoreText.setString("Score:");
}