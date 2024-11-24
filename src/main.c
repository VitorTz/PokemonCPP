#include <raylib.h>
#include "constants.h"
#include "util/texture_pool.h"


int main() {
	InitWindow(SCREEN_W, SCREEN_H, WINDOW_TITLE);
	SetTargetFPS(FPS);

	texture_pool_init();
	
	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(BLACK);		
		EndDrawing();
	}

	texture_pool_close();
	CloseWindow();	
	return 0;
}