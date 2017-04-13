#include "main.h"
#include "display.h"
#include "snake.h"

int main(int argc, char* argv[]) {
    initializeWindow(BOXSIZE);
    printf("Successfully loaded game.\n\nPress [ESC] to quit.\n"
        "Press [SPACE] to pause, [R] to restart, or [L] to enter full-screen.\n"
        "Use W,A,S,D to control movement.\n\n");
    if (!strcmp(GAME, "Snake")) {
		playSnake();
    }
    printf("\nWindow successfully closed.\n");
    return 0;
}
