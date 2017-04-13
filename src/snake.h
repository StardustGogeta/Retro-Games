#ifndef SNAKE
#define SNAKE

int snake[GRIDH*GRIDW][2], direction, score, game, snakeLen;

void playSnake(), spawnFood();
int handleEvents(int grid[GRIDH][GRIDW]);

#endif // SNAKE
