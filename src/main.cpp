#include "gameoflife.h"

int main(int argc, char* argv[]) {
    const int WIDTH = 80;
    const int HEIGHT = 60;
    const int CELL_SIZE = 10;

    GameOfLife game(WIDTH, HEIGHT, CELL_SIZE);
    game.Initialize();
    game.Run();

    return 0;
}