#include "main.h"
#include "display.h"
#include "snake.h"

int move() {
	int h[2] = {snake[snakeLen-1][0],snake[snakeLen-1][1]}, y = 0, x = 0;
	if (direction < 2) {
		y = h[0]-1+direction*2, x = h[1];
	}
	else {
        y = h[0], x = h[1]+5-direction*2;
	}
	y %= GRIDH, x %= GRIDW;
	if (y < 0) y += GRIDH; if (x < 0) x += GRIDW;
	for (int i=0; i<snakeLen; i++) if (snake[i][0] == y && snake[i][1] == x) return -1;
	if (grid[y][x]) {
		snake[snakeLen][0] = y, snake[snakeLen][1] = x;
		snakeLen++;
		spawnFood();
		return 1;
	}
	else {
		drawBox(y,x,'W');
		drawBox(snake[0][0],snake[0][1],'B');
		for (int i=0; i<snakeLen; i++) {
			snake[i][0] = snake[i+1][0];
			snake[i][1] = snake[i+1][1];
		}
		snake[snakeLen-1][0] = y, snake[snakeLen-1][1] = x;
		return 0;
	}
}

void spawnFood() {
	int foodY, foodX;
	foodLoop:
	foodY = rand()%GRIDH, foodX = rand()%GRIDW;
	for (int i=0; i<snakeLen; i++) {
		if (snake[i][0] == foodY && snake[i][1] == foodX) goto foodLoop;
	}
	drawBox(foodY,foodX,'W');
	renderScreen();
}

void initGame() {
	memset(grid,0,GRIDW*GRIDH*sizeof(int));
	memset(snake,0,GRIDW*GRIDH*sizeof(int));
    int snakeInitY = rand()%(GRIDH-1)+1;
    int snakeInitX = rand()%GRIDW;
    snake[0][0] = snakeInitY;
    snake[0][1] = snakeInitX;
    snake[1][0] = snakeInitY-1;
    snake[1][1] = snakeInitX;
    direction = 0, game = 1, score = 0, snakeLen = 2;
    spawnFood();
    rewriteScreen(grid);
}

int handleEvents(int grid[GRIDH][GRIDW]) {
	int dirChange = 0; // Ensure that only one direction change happens at a time.
    while(SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                return 0;
            case SDL_KEYDOWN:
            switch (event.key.keysym.sym) {
            	case SDLK_w:
                    if (direction != 1 && !dirChange) {
						direction = 0;
						dirChange = 1;
                    }
                    break;
				case SDLK_s:
                    if (direction != 0 && !dirChange) {
						direction = 1;
						dirChange = 1;
                    }
                    break;
				case SDLK_d:
                    if (direction != 3 && !dirChange) {
						direction = 2;
						dirChange = 1;
                    }
                    break;
				case SDLK_a:
                    if (direction != 2 && !dirChange) {
						direction = 3;
						dirChange = 1;
                    }
                    break;
                case SDLK_ESCAPE:
                    return 0;
                case SDLK_SPACE:
                    pause ^= 1;
                    printf("The game has been %spaused.\n",pause?"":"un");
                    break;
				case SDLK_r:
                    printf("Restarting game...\n");
                    initGame();
                    break;
                case SDLK_l:
                    fullscreen ^= 1;
                    if (fullscreen) { // Remember screen size
                    	int w, h;
						SDL_GetWindowSize(disp, &w, &h);
						preFullscreen = round(w/GRIDW);
                    }
                    SDL_SetWindowFullscreen(disp,fullscreen?SDL_WINDOW_FULLSCREEN_DESKTOP:0);
                    if (!fullscreen) {
						fullscreenFlag = 1;
						resizeWindow(disp,preFullscreen,preFullscreen,grid);
                    }
                    printf("The game has been set to %s.\n",fullscreen?"full-screen":"windowed mode");
                    break;
            }
        }
		switch (event.window.event)
        {
            case SDL_WINDOWEVENT_MAXIMIZED:
            case SDL_WINDOWEVENT_RESIZED: {
            	if (fullscreenFlag) fullscreenFlag = 0; // Ignore full-screen events
            	else {
					int w = round(event.window.data1/GRIDW);
					resizeWindow(disp,w,w,grid);
					break;
            	}
            }
        }
    }
    return 1;
}

void playSnake() {
	srand(time(NULL));
	resizeWindow(disp, BOXSIZE, BOXSIZE, grid);
	initGame();
	while (handleEvents(grid)) {
		if (!pause && game) {
			int movement = move();
			if (movement < 0) {
				game = 0;
				printf("You lost with %d points.",score);
			}
			else score += movement;
			renderScreen();
			SDL_Delay(1000/CLOCK_SPEED);
		}
	}
}
