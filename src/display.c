#include "display.h"
#include "main.h"

void initializeWindow(uint64_t pixelSize) {
    SDL_Init(SDL_INIT_EVERYTHING);
    atexit(SDL_Quit);
    disp = SDL_CreateWindow("Stardust - "GAME,
            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            GRIDH*BOXSIZE, GRIDW*BOXSIZE, SDL_WINDOW_RESIZABLE);
    renderer = SDL_CreateRenderer(disp, -1, SDL_RENDERER_ACCELERATED);
    SDL_ShowCursor(0);
}

void resizeWindow(SDL_Window* disp, int w, int h, int grid[GRIDH][GRIDW]) {
	SDL_SetWindowSize(disp,w*GRIDW,w*GRIDH);
	rewriteScreen(grid);
    renderScreen();
}

void drawBox(int y, int x, char color) {
	int w, h;
	SDL_GetWindowSize(disp, &w, &h);
	w = round(w/GRIDW);
    box.h = w, box.w = w;
    switch (color) {
		case 'W':
			grid[y][x] = 1;
			SDL_SetRenderDrawColor(renderer, 255,255,255,0);
			break;
		case 'B':
			grid[y][x] = 0;
			SDL_SetRenderDrawColor(renderer, 0,0,0,0);
			break;
		default:
			printf("Coloring failure!\n");
    }
	box.y = w * y;
    box.x = w * x;
    SDL_RenderFillRect(renderer,&box);
}

void renderScreen() {
	SDL_RenderPresent(renderer);
}

void rewriteScreen(int grid[GRIDH][GRIDW]) {
	int w, h;
	SDL_GetWindowSize(disp, &w, &h);
	w = round(w/GRIDW);
    box.h = w, box.w = w;

	SDL_SetRenderDrawColor(renderer, 0,0,0,0);
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 255,255,255,0);

    for (int Y=0; Y<GRIDH; Y++) {
		for (int X=0; X<GRIDW; X++) {
			if (grid[Y][X]) {
				box.y = w * Y;
				box.x = w * X;
				SDL_RenderFillRect(renderer,&box);
			}
		}
    }
}
