#pragma once
#include <SDL.h>
#include <vector>
#include <string>
#include "Constants.h"

class GameOfLife {
public:
    GameOfLife(int width = Constants::DEFAULT_WIDTH,
               int height = Constants::DEFAULT_HEIGHT,
               int cellSize = Constants::DEFAULT_CELL_SIZE,
               int speed = Constants::DEFAULT_SPEED);
    ~GameOfLife();

    void Initialize();
    void Run();
    void TogglePause();
    void ClearGrid();
    void Randomize();
    void HandleMouseClick(int x, int y);

private:
    void Update();
    void Render();
    void RenderGrid();
    void RenderCells();
    int CountLiveNeighbors(int x, int y);
    void ProcessEvents();

    SDL_Window* window;
    SDL_Renderer* renderer;

    int width;
    int height;
    int cellSize;
    int speed;

    std::vector<std::vector<bool>> grid;
    std::vector<std::vector<bool>> nextGrid;

    bool running;
    bool paused;
    bool mouseDown;
};