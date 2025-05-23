#ifndef MYSDLPROJECT_CONSTANTS_H
#define MYSDLPROJECT_CONSTANTS_H
#pragma once
#include <SDL.h>

namespace Constants {
    const int DEFAULT_WIDTH = 80;
    const int DEFAULT_HEIGHT = 60;
    const int DEFAULT_CELL_SIZE = 10;
    const int DEFAULT_SPEED = 100; // ms между обновлениями
    const SDL_Color GRID_COLOR = {50, 50, 50, 255};
    const SDL_Color CELL_COLOR = {255, 255, 255, 255};
    const SDL_Color BG_COLOR = {0, 0, 0, 255};
}
#endif //MYSDLPROJECT_CONSTANTS_H
