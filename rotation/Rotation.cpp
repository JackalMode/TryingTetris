//
// Created by Mitchell Steenbergen on 11/12/2024.
//


#include "Rotation.h"

using namespace sf;
using namespace std;

/**
 * Define the rotate function to handle the rotation logic for the Tetrominos based on current rotation state and type
 * @param currentTetromino
 * @param grid
 * @param rotationState
 * @param type
 */
void Rotation::rotate(TetrominoData &currentTetromino, int (*grid)[10], int &rotationState, TetrominoType type) {
    // Track whether the up key was pressed in the previous frame
    static bool wasUpPressed = true;

    // Check if the up key is pressed and ensure that the key was not pressed in the previous frame
    if(Keyboard::isKeyPressed(Keyboard::Up) && !wasUpPressed){
        wasUpPressed = true;
        bool canRotate = true;
        // Stores the new positions after rotation.
        std::vector<Vector2i> newPosition(4);
        // Sets the pivot block for some
        Vector2i pivot = currentTetromino.blocks[1];
        // Sets the pivot block for some
        Vector2i pivot0 = currentTetromino.blocks[0];

        // Switch based on the type of tetromino to apply appropriate rotation
        switch(type) {
            case T_SHAPE:
                switch(rotationState){
                    case 0:
                        newPosition = {
                                // Above (4, -1)
                                {pivot.x, pivot.y - 1},
                                // pivot block (4, 0)
                                pivot,
                                // Left (3, 0)
                                {pivot.x - 1, pivot.y},
                                // Below (4, 1)
                                {pivot.x, pivot.y + 1}
                        };
                        break;
                    case 1:
                        newPosition = {
                                // Left (3, 0)
                                {pivot.x - 1, pivot.y},
                                // Pivot Block (4, 0)
                                pivot,
                                // Right (5, 0)
                                {pivot.x + 1, pivot.y},
                                // Above (4, -1)
                                {pivot.x, pivot.y - 1}
                        };
                        break;
                    case 2:
                        newPosition = {
                                // Below (4, 1)
                                {pivot.x, pivot.y + 1},
                                // Pivot Block (4, 0)
                                pivot,
                                // Right (5, 0)
                                {pivot.x + 1, pivot.y},
                                // Above (4, -1)
                                {pivot.x, pivot.y - 1}
                        };
                        break;
                    case 3:
                        newPosition = {
                                // Left (3, 0)
                                {pivot.x - 1, pivot.y},
                                // Pivot Block (4, 0)
                                pivot,
                                // Right (5, 0)
                                {pivot.x + 1, pivot.y},
                                // Below (4, 1)
                                {pivot.x, pivot.y + 1}
                        };
                        break;
                }
                break;
            case I_SHAPE:
                if (rotationState % 2 == 0) {
                    newPosition = {
                            // Left (4, 0)
                            {pivot.x - 1, pivot.y},
                            // Pivot Block (5, 0)
                            pivot,
                            // Right (6, 0)
                            {pivot.x + 1, pivot.y},
                            // Right (7, 0)
                            {pivot.x + 2, pivot.y}
                    };
                } else {
                    newPosition = {
                            // Above (5, -1)
                            {pivot.x, pivot.y - 1},
                            // Pivot Block (5, 0)
                            pivot,
                            // Below (5, 1)
                            {pivot.x, pivot.y + 1},
                            // Below (5, 2)
                            {pivot.x, pivot.y + 2}
                    };
                }
                break;
            case O_SHAPE:
                return;
            case S_SHAPE:
                switch (rotationState) {
                    case 0:
                        newPosition = {
                                // Pivot block (4, 0)
                                pivot0,
                                // Right (5, 0)
                                {pivot0.x + 1, pivot0.y},
                                // Left (3, 1)
                                {pivot0.x - 1, pivot0.y + 1},
                                // Below (4, 1)
                                {pivot0.x, pivot0.y + 1}
                        };
                        break;

                    case 1:
                        newPosition = {
                                // Pivot block (4, 0)
                                pivot0,
                                // Below (4, 1)
                                {pivot0.x, pivot0.y + 1},
                                // Left and Above (3, -1)
                                {pivot0.x - 1, pivot0.y - 1},
                                // Left (3, 0)
                                {pivot0.x - 1, pivot0.y}
                        };
                        break;

                    case 2:
                        newPosition = {
                                // Pivot block (4, 0)
                                pivot0,
                                // Left (3, 0)
                                {pivot0.x - 1, pivot0.y},
                                // Right (5, -1)
                                {pivot0.x + 1, pivot0.y - 1},
                                // Above (4, -1)
                                {pivot0.x, pivot0.y - 1}
                        };
                        break;

                    case 3:
                        newPosition = {
                                // Pivot block (4, 0)
                                pivot0,
                                // Above (4, -1)
                                {pivot0.x, pivot0.y - 1},
                                // Below and Right (5, 1)
                                {pivot0.x + 1, pivot0.y + 1},
                                // Right (5, 0)
                                {pivot0.x + 1, pivot0.y}
                        };
                        break;
                }
                break;
            case Z_SHAPE:
                switch(rotationState){
                    case 0:
                        newPosition = {
                                // Above (4, -1)
                                {pivot.x, pivot.y - 1},
                                // Pivot Block (4, 0)
                                pivot,
                                // Left (3, 0)
                                {pivot.x - 1, pivot.y},
                                // Left and Below (3, 1)
                                {pivot.x - 1, pivot.y + 1}
                        };
                        break;
                    case 1:
                        newPosition = {
                                // Left (3, 0)
                                {pivot.x - 1, pivot.y},
                                // Pivot Block (4, 0)
                                pivot,
                                // Below (4, 1)
                                {pivot.x, pivot.y + 1},
                                // Below and Right (5, 1)
                                {pivot.x + 1, pivot.y + 1}
                        };
                        break;
                    case 2:
                        newPosition = {
                                // Below (4, 1)
                                {pivot.x, pivot.y + 1},
                                // Pivot Block (4, 0)
                                pivot,
                                // Right (5, 0)
                                {pivot.x + 1, pivot.y},
                                // Above and Right (5, -1)
                                {pivot.x + 1, pivot.y - 1}
                        };
                        break;
                    case 3:
                        newPosition = {
                                // Right (5, 0)
                                {pivot.x + 1, pivot.y},
                                // Pivot Block (4, 0)
                                pivot,
                                // Above (4, -1)
                                {pivot.x, pivot.y - 1},
                                // Above and Left (5, -1)
                                {pivot.x - 1, pivot.y - 1}
                        };
                        break;
                }
                break;
            case L_SHAPE:
                switch(rotationState){
                    case 0:
                        newPosition = {
                                // Above (3, 0)
                                {pivot.x, pivot.y - 1},
                                // Pivot Block (3, 1)
                                pivot,
                                // Below (3, 2)
                                {pivot.x, pivot.y + 1},
                                // Below and Right (4, 2)
                                {pivot.x + 1, pivot.y + 1}
                        };
                        break;
                    case 1:
                        newPosition = {
                                // Left (2, 1)
                                {pivot.x - 1, pivot.y},
                                // Pivot Block (3, 1)
                                pivot,
                                // Right (4, 1)
                                {pivot.x + 1, pivot.y},
                                // Right and Above (4, 0)
                                {pivot.x + 1, pivot.y - 1}
                        };
                        break;
                    case 2:
                        newPosition = {
                                // Below (3, 2)
                                {pivot.x, pivot.y + 1},
                                // Pivot Block (3, 1)
                                pivot,
                                // Above (3, 0)
                                {pivot.x, pivot.y - 1},
                                // Above and left (2, 0)
                                {pivot.x - 1, pivot.y - 1}
                        };
                        break;
                    case 3:
                        newPosition = {
                                // Right (4, 1)
                                {pivot.x + 1, pivot.y},
                                // Pivot Block (3, 1)
                                pivot,
                                // Left (2, 1)
                                {pivot.x - 1, pivot.y},
                                // Left and Below (2, 2)
                                {pivot.x - 1, pivot.y + 1}
                        };
                        break;
                }
                break;
            case J_SHAPE:
                switch(rotationState){
                    case 0:
                        newPosition = {
                                // Above (4, 0)
                                {pivot.x, pivot.y - 1},
                                // Pivot Block (4, 1)
                                pivot,
                                // Below (4, 2)
                                {pivot.x, pivot.y + 1},
                                // Left and Below (3, 2)
                                {pivot.x - 1, pivot.y + 1}
                        };
                        break;
                    case 1:
                        newPosition = {
                                // Left (3, 1)
                                {pivot.x - 1, pivot.y},
                                // Pivot Block (4, 1)
                                pivot,
                                // Right (5, 1)
                                {pivot.x + 1, pivot.y},
                                // Right and Below (5, 2)
                                {pivot.x + 1, pivot.y + 1}
                        };
                        break;
                    case 2:
                        newPosition = {
                                // Below (4, 2)
                                {pivot.x, pivot.y + 1},
                                // Pivot Block (4, 1)
                                pivot,
                                // Above (4, 0)
                                {pivot.x, pivot.y - 1},
                                // Right and Above (5, 0)
                                {pivot.x + 1, pivot.y - 1}
                        };
                        break;
                    case 3:
                        newPosition = {
                                // Right (5, 1)
                                {pivot.x + 1, pivot.y},
                                // Pivot Block (4, 1)
                                pivot,
                                // Left (3, 1)
                                {pivot.x - 1, pivot.y},
                                // left and above (3, 0)
                                {pivot.x - 1, pivot.y - 1}
                        };
                        break;
                }
                break;
        }
        // Check if new positions are within bounds and unoccupied
        for (const auto& pos : newPosition) {
            if (pos.x < 0 || pos.x >= GRID_WIDTH || pos.y < 0 || pos.y >= GRID_HEIGHT || grid[pos.y][pos.x] != 0) {
                canRotate = false;
                break;
            }
        }
        // If rotation is not possible, we attempt a wall kick
        if(!canRotate) {
            // Define possible wall kick offsets
            vector<Vector2i> wallKick = {
                    {{-1, 0}, {1, 0}, {-2, 0}, {2, 0}}
            };
            for(const auto& offset : wallKick){
                bool kickSuccess = true;
                for (int i = 0; i < newPosition.size(); i++) {
                    Vector2i kickPos = newPosition[i] + offset;
                    // Check if the wall kick offset is within boundaries
                    if(kickPos.x < 0 || kickPos.x >= GRID_WIDTH || kickPos.y < 0 || kickPos.y >= GRID_HEIGHT || grid[kickPos.y][kickPos.x] != 0){
                        kickSuccess = false;
                        break;
                    }
                }
                if (kickSuccess){
                    // Apply wall kick offset
                    for (int i = 0; i < newPosition.size(); i++){
                        newPosition[i] += offset;
                    }
                    canRotate = true;
                    break;
                }
            }
        }

        // Apply rotation if it is possible
        if (canRotate) {
            for (int i = 0; i < currentTetromino.blocks.size(); ++i) {
                currentTetromino.blocks[i] = newPosition[i];
            }

            // Update to the next rotation state
            rotationState = (rotationState + 1) % 4; // Cycle through 0, 1, 2, 3
        }
    }
    // Reset the flag once the Up key is released
    if (!Keyboard::isKeyPressed(Keyboard::Up)) {
        wasUpPressed = false;
    }
}
