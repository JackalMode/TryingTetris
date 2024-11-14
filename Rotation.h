//
// Created by Mitchell Steenbergen on 11/12/2024.
//

#ifndef M4OEP_ROTATION_H
#define M4OEP_ROTATION_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Tetromino.h"
#include "Constants.h"

class Rotation {
public:
    // Rotates the given tetromino based on the specific rotation state and type
    static void rotate(TetrominoData &currentTetromino, int grid[][GRID_WIDTH], int &rotationState, TetrominoType type);
};


#endif //M4OEP_ROTATION_H
