#include "presets.h"
#include "main.h"
#include "display.h"
#include "snake.h"

int main(int argc, char* argv[]) {
    initializeWindow(BOXSIZE);
    printf("Successfully loaded game.\n\nPress [ESC] to quit.\n"
        "Press [SPACE] to pause or [L] to enter fullscreen.\n\n");
    if (!strcmp(GAME, "Snake")) {
		playSnake();
    }
    printf("\nWindow successfully closed.\n");
    return 0;
}
