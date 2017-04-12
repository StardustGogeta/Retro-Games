#ifndef DISPLAY
#define DISPLAY

#include <SDL2/SDL.h>

SDL_Rect box;
SDL_Event event, keyEvent;
SDL_version compiled, linked;
SDL_DisplayMode current;
SDL_Window* disp;
SDL_Renderer* renderer;

int pause, fullscreen, fullscreenFlag, preFullscreen, handleEvents(int**);
void initializeWindow(), drawGraphics(), refreshKeyboard(), rewriteScreen(), renderScreen();

#endif // DISPLAY
