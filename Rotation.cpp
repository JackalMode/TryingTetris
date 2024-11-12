//
// Created by Mitchell Steenbergen on 11/12/2024.
//

#include "Rotation.h"

using namespace sf;

void Rotation::rotate(TetrominoData &currentTetromino, int (*grid)[10], int &rotationState, TetrominoType type) {
    static bool wasUpPressed = true;

    if(Keyboard::isKeyPressed(Keyboard::Up) && !wasUpPressed){
        wasUpPressed = true;
        bool canRotate = true;
        std::vector<Vector2i> newPosition(4);
        Vector2i pivot = currentTetromino.blocks[1];
        Vector2i pivot0 = currentTetromino.blocks[0];

        switch(type) {
            case T_SHAPE:
                switch(rotationState){
                    case 0:
                        newPosition = {
                                {pivot.x, pivot.y - 1},
                                pivot,
                                {pivot.x - 1, pivot.y},
                                {pivot.x, pivot.y + 1}
                        };
                        break;
                    case 1:
                        newPosition = {
                                {pivot.x - 1, pivot.y},
                                pivot,
                                {pivot.x + 1, pivot.y},
                                {pivot.x, pivot.y - 1}
                        };
                        break;
                    case 2:
                        newPosition = {
                                {pivot.x, pivot.y + 1},
                                pivot,
                                {pivot.x + 1, pivot.y},
                                {pivot.x, pivot.y - 1}
                        };
                        break;
                    case 3:
                        newPosition = {
                                {pivot.x - 1, pivot.y},
                                pivot,
                                {pivot.x + 1, pivot.y},
                                {pivot.x, pivot.y + 1}
                        };
                        break;
                }
                break;
            case I_SHAPE:// Third block
                if (rotationState % 2 == 0) {
                    newPosition = {
                            {pivot.x - 1, pivot.y},    // Left block
                            pivot,                     // Pivot stays the same
                            {pivot.x + 1, pivot.y},    // Right block
                            {pivot.x + 2, pivot.y}     // Far right block
                    };
                } else {
                    newPosition = {
                            {pivot.x, pivot.y - 1},    // Top block
                            pivot,                     // Pivot stays the same
                            {pivot.x, pivot.y + 1},    // Bottom block
                            {pivot.x, pivot.y + 2}     // Far bottom block
                    };
                }
                break;
            case O_SHAPE:
                return;

            case S_SHAPE:
                switch (rotationState) {
                    case 0: // Default position (horizontal)
                        newPosition = {
                                pivot0,                         // Pivot block (4, 0)
                                {pivot0.x + 1, pivot0.y},        // Block to the right (5, 0)
                                {pivot0.x - 1, pivot0.y + 1},    // Block bottom left (3, 1)
                                {pivot0.x, pivot0.y + 1}         // Block directly below (4, 1)
                        };
                        break;

                    case 1: // Rotated 90 degrees clockwise (vertical)
                        newPosition = {
                                pivot0,                         // Pivot block (4, 0)
                                {pivot0.x, pivot0.y + 1},        // Block directly below (4, 1)
                                {pivot0.x - 1, pivot0.y - 1},    // Block above left (3, -1)
                                {pivot0.x - 1, pivot0.y}         // Block to the left (3, 0)
                        };
                        break;

                    case 2: // Rotated 180 degrees (horizontal, mirrored)
                        newPosition = {
                                pivot0,                         // Pivot block (4, 0)
                                {pivot0.x - 1, pivot0.y},        // Block to the left (3, 0)
                                {pivot0.x + 1, pivot0.y - 1},    // Block top right (5, -1)
                                {pivot0.x, pivot0.y - 1}         // Block directly above (4, -1)
                        };
                        break;

                    case 3: // Rotated 270 degrees clockwise (vertical again)
                        newPosition = {
                                pivot0,                         // Pivot block (4, 0)
                                {pivot0.x, pivot0.y - 1},        // Block directly above (4, -1)
                                {pivot0.x + 1, pivot0.y + 1},    // Block below right (5, 1)
                                {pivot0.x + 1, pivot0.y}         // Block to the right (5, 0)
                        };
                        break;
                }
                break;
            case Z_SHAPE:
                switch(rotationState){
                    case 0:
                        newPosition = {
                                {pivot.x, pivot.y - 1},
                                pivot,
                                {pivot.x - 1, pivot.y},
                                {pivot.x - 1, pivot.y + 1}
                        };
                        break;
                    case 1:
                        newPosition = {
                                {pivot.x - 1, pivot.y},
                                pivot,
                                {pivot.x, pivot.y + 1},
                                {pivot.x + 1, pivot.y + 1}
                        };
                        break;
                    case 2:
                        newPosition = {
                                {pivot.x, pivot.y + 1},
                                pivot,
                                {pivot.x + 1, pivot.y},
                                {pivot.x + 1, pivot.y - 1}
                        };
                        break;
                    case 3:
                        newPosition = {
                                {pivot.x + 1, pivot.y},
                                pivot,
                                {pivot.x, pivot.y - 1},
                                {pivot.x - 1, pivot.y - 1}
                        };
                        break;
                }
                break;
            case L_SHAPE:
                switch(rotationState){
                    case 0:
                        newPosition = {
                                {pivot.x, pivot.y - 1},       // Top
                                pivot,                        // Pivot
                                {pivot.x, pivot.y + 1},       // Bottom
                                {pivot.x + 1, pivot.y + 1}    // Bottom right
                        };
                        break;
                    case 1:
                        newPosition = {
                                {pivot.x - 1, pivot.y},       // Left
                                pivot,                        // Pivot
                                {pivot.x + 1, pivot.y},       // Right
                                {pivot.x + 1, pivot.y - 1}    // Top right
                        };
                        break;
                    case 2:
                        newPosition = {
                                {pivot.x, pivot.y + 1},       // Bottom
                                pivot,                        // Pivot
                                {pivot.x, pivot.y - 1},       // Top
                                {pivot.x - 1, pivot.y - 1}    // Top left
                        };
                        break;
                    case 3:
                        newPosition = {
                                {pivot.x + 1, pivot.y},       // Right
                                pivot,                        // Pivot
                                {pivot.x - 1, pivot.y},       // Left
                                {pivot.x - 1, pivot.y + 1}    // Bottom left
                        };
                        break;
                }
                break;
            case J_SHAPE:
                switch(rotationState){
                    case 0:
                        newPosition = {
                                {pivot.x, pivot.y - 1},
                                pivot,
                                {pivot.x, pivot.y + 1},
                                {pivot.x - 1, pivot.y + 1}
                        };
                        break;
                    case 1:
                        newPosition = {
                                {pivot.x - 1, pivot.y},
                                pivot,
                                {pivot.x + 1, pivot.y},
                                {pivot.x + 1, pivot.y + 1}
                        };
                        break;
                    case 2:
                        newPosition = {
                                {pivot.x, pivot.y + 1},
                                pivot,
                                {pivot.x, pivot.y - 1},
                                {pivot.x + 1, pivot.y - 1}
                        };
                        break;
                    case 3:
                        newPosition = {
                                {pivot.x + 1, pivot.y},
                                pivot,
                                {pivot.x - 1, pivot.y},
                                {pivot.x - 1, pivot.y - 1}
                        };
                        break;
                }
                break;
        }

        for (const auto& pos : newPosition) {
            if (pos.x < 0 || pos.x >= GRID_WIDTH || pos.y < 0 || pos.y >= GRID_HEIGHT || grid[pos.y][pos.x] != 0) {
                canRotate = false;
                break;
            }
        }
        if (canRotate) {
            for (int i = 0; i < currentTetromino.blocks.size(); ++i) {
                currentTetromino.blocks[i] = newPosition[i];
            }

            // Update to the next rotation state
            rotationState = (rotationState + 1) % 4; // Cycle through 0, 1, 2, 3
        }
    }
    if (!Keyboard::isKeyPressed(Keyboard::Up)) {
        wasUpPressed = false;
    }
}
