#include "main.h"
#include "display.h"
#include "presets.h"

void playSnake() {
	int grid[GRID_DIMS[0]][GRID_DIMS[1]];
	memset(grid,0,GRID_DIMS[0]*GRID_DIMS[1]*sizeof(int));
	resizeWindow(disp, BOXSIZE, BOXSIZE, grid);
	while (handleEvents(grid)) {
		// printf("It's working!");

	}
}
