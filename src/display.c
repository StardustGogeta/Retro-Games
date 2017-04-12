#include "presets.h"
#include "display.h"
#include "main.h"

const int GRID_DIMS[2] = {GRIDH,GRIDW};

void initializeWindow(uint64_t pixelSize, uint64_t* gridDims) {
    SDL_Init(SDL_INIT_EVERYTHING);
    atexit(SDL_Quit);
    disp = SDL_CreateWindow("Stardust - "GAME,
            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            GRID_DIMS[1]*BOXSIZE, GRID_DIMS[0]*BOXSIZE, SDL_WINDOW_RESIZABLE);
    renderer = SDL_CreateRenderer(disp, -1, SDL_RENDERER_ACCELERATED);
    SDL_ShowCursor(0);
}

int handleEvents(int** grid) {
    while(SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                return 0;
            case SDL_KEYDOWN:
            switch (event.key.keysym.sym) {
                case SDLK_ESCAPE:
                    return 0;
                case SDLK_SPACE:
                    pause ^= 1;
                    printf("The game has been %spaused.\n",pause?"":"un");
                    break;
                case SDLK_l:
                    fullscreen ^= 1;
                    if (fullscreen) { // Remember screen size
                    	int w, h;
						SDL_GetWindowSize(disp, &w, &h);
						preFullscreen = round(w/GRID_DIMS[1]);
                    }
                    SDL_SetWindowFullscreen(disp,fullscreen?SDL_WINDOW_FULLSCREEN_DESKTOP:0);
                    if (!fullscreen) {
						fullscreenFlag = 1;
						resizeWindow(disp,preFullscreen,preFullscreen,grid);
                    }
                    printf("The game has been set to %s.\n",fullscreen?"fullscreen":"windowed mode");
                    break;
            }
        }
        switch (event.window.event)
        {
            case SDL_WINDOWEVENT_MAXIMIZED:
            case SDL_WINDOWEVENT_RESIZED: {
            	if (fullscreenFlag) fullscreenFlag = 0; // Ignore full-screen events
            	else {
					int w = round(event.window.data1/GRID_DIMS[1]);
					resizeWindow(disp,w,w,grid);
					break;
            	}
            }
        }
    }
    return 1;
}

void resizeWindow(SDL_Window* disp, int w, int h, int grid[GRID_DIMS[0]][GRID_DIMS[1]]) {
	SDL_SetWindowSize(disp,w*GRID_DIMS[1],w*GRID_DIMS[0]);
	rewriteScreen(grid);
    renderScreen();
}

void drawBox(int y, int x, char color) {
	int w, h;
	SDL_GetWindowSize(disp, &w, &h);
	w = round(w/GRID_DIMS[1]);
    box.h = w, box.w = w;
    switch (color) {
		case 'W':
			SDL_SetRenderDrawColor(renderer, 255,255,255,0);
			break;
		case 'B':
			SDL_SetRenderDrawColor(renderer, 0,0,0,0);
			break;
    }
	box.y = w * y;
    box.x = w * x;
    SDL_RenderFillRect(renderer,&box);
}

void renderScreen() {
	SDL_RenderPresent(renderer);
}

void rewriteScreen(int grid[GRID_DIMS[0]][GRID_DIMS[1]]) {
	int w, h;
	SDL_GetWindowSize(disp, &w, &h);
	w = round(w/GRID_DIMS[1]);
    box.h = w, box.w = w;

	SDL_SetRenderDrawColor(renderer, 0,0,0,0);
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 255,255,255,0);

    for (int Y=0; Y<GRID_DIMS[0]; Y++) {
		for (int X=0; X<GRID_DIMS[1]; X++) {
			if (grid[Y][X]) {
				box.y = w * Y;
				box.x = w * X;
				SDL_RenderFillRect(renderer,&box);
			}
		}
    }
}
