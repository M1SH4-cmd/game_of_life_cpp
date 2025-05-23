#include "GameOfLife.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

GameOfLife::GameOfLife(int width, int height, int cellSize, int speed)
        : width(width), height(height), cellSize(cellSize), speed(speed) {
    grid.resize(height, std::vector<bool>(width, false));
    nextGrid.resize(height, std::vector<bool>(width, false));
    paused = true;
    mouseDown = false;
    std::srand(std::time(nullptr));
}

GameOfLife::~GameOfLife() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void GameOfLife::Initialize() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! Error: " << SDL_GetError() << std::endl;
        exit(1);
    }

    window = SDL_CreateWindow("Game of Life",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              width * cellSize,
                              height * cellSize,
                              SDL_WINDOW_SHOWN);

    if (!window) {
        std::cerr << "Window could not be created! Error: " << SDL_GetError() << std::endl;
        exit(1);
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Renderer could not be created! Error: " << SDL_GetError() << std::endl;
        exit(1);
    }
}

void GameOfLife::Run() {
    Uint32 nextUpdate = SDL_GetTicks() + speed;

    while (running) {
        ProcessEvents();

        Uint32 now = SDL_GetTicks();
        if (!paused && now >= nextUpdate) {
            Update();
            nextUpdate = now + speed;
        }

        Render();
        SDL_Delay(10);
    }
}

void GameOfLife::ProcessEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                running = false;
                break;

            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_SPACE:
                        TogglePause();
                        break;
                    case SDLK_c:
                        ClearGrid();
                        break;
                    case SDLK_r:
                        Randomize();
                        break;
                    case SDLK_ESCAPE:
                        running = false;
                        break;
                }
                break;

            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT) {
                    mouseDown = true;
                    HandleMouseClick(event.button.x, event.button.y);
                }
                break;

            case SDL_MOUSEBUTTONUP:
                if (event.button.button == SDL_BUTTON_LEFT) {
                    mouseDown = false;
                }
                break;

            case SDL_MOUSEMOTION:
                if (mouseDown) {
                    HandleMouseClick(event.motion.x, event.motion.y);
                }
                break;
        }
    }
}

void GameOfLife::Update() {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int liveNeighbors = CountLiveNeighbors(x, y);
            nextGrid[y][x] = (liveNeighbors == 3) || (grid[y][x] && liveNeighbors == 2);
        }
    }
    grid = nextGrid;
}

void GameOfLife::Render() {
    SDL_SetRenderDrawColor(renderer,
                           Constants::BG_COLOR.r,
                           Constants::BG_COLOR.g,
                           Constants::BG_COLOR.b,
                           Constants::BG_COLOR.a);
    SDL_RenderClear(renderer);

    RenderGrid();
    RenderCells();

    SDL_RenderPresent(renderer);
}

void GameOfLife::RenderGrid() {
    SDL_SetRenderDrawColor(renderer,
                           Constants::GRID_COLOR.r,
                           Constants::GRID_COLOR.g,
                           Constants::GRID_COLOR.b,
                           Constants::GRID_COLOR.a);

    // Вертикальные линии
    for (int x = 0; x <= width; x++) {
        SDL_RenderDrawLine(renderer, x * cellSize, 0, x * cellSize, height * cellSize);
    }

    // Горизонтальные линии
    for (int y = 0; y <= height; y++) {
        SDL_RenderDrawLine(renderer, 0, y * cellSize, width * cellSize, y * cellSize);
    }
}

void GameOfLife::RenderCells() {
    SDL_SetRenderDrawColor(renderer,
                           Constants::CELL_COLOR.r,
                           Constants::CELL_COLOR.g,
                           Constants::CELL_COLOR.b,
                           Constants::CELL_COLOR.a);

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (grid[y][x]) {
                SDL_Rect rect = {x * cellSize + 1, y * cellSize + 1, cellSize - 1, cellSize - 1};
                SDL_RenderFillRect(renderer, &rect);
            }
        }
    }
}

int GameOfLife::CountLiveNeighbors(int x, int y) {
    int count = 0;
    for (int dy = -1; dy <= 1; dy++) {
        for (int dx = -1; dx <= 1; dx++) {
            if (dx == 0 && dy == 0) continue;

            int nx = (x + dx + width) % width;
            int ny = (y + dy + height) % height;

            if (grid[ny][nx]) count++;
        }
    }
    return count;
}

void GameOfLife::TogglePause() {
    paused = !paused;
}

void GameOfLife::ClearGrid() {
    for (auto& row : grid) {
        std::fill(row.begin(), row.end(), false);
    }
}

void GameOfLife::Randomize() {
    for (auto& row : grid) {
        for (auto&& cell : row) {
            cell = std::rand() % 2;
        }
    }
}

void GameOfLife::HandleMouseClick(int x, int y) {
    if (x < 0 || y < 0 || x >= width * cellSize || y >= height * cellSize) return;

    int gridX = x / cellSize;
    int gridY = y / cellSize;
    grid[gridY][gridX] = !grid[gridY][gridX];
}