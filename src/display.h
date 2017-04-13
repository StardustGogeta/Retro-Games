#ifndef DISPLAY
#define DISPLAY

#include "presets.h"

#include <SDL2/SDL.h>

SDL_Rect box;
SDL_Event event, keyEvent;
SDL_version compiled, linked;
SDL_DisplayMode current;
SDL_Window* disp;
SDL_Renderer* renderer;

int pause, fullscreen, fullscreenFlag, preFullscreen, grid[GRIDH][GRIDW];
void initializeWindow(), drawBox(int, int, char), resizeWindow(), rewriteScreen(), renderScreen();

#endif // DISPLAY
