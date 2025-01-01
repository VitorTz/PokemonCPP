#include <raylib.h>
#include "constants.h"
#include "util/texture_pool.h"


int main() {
	InitWindow(SCREEN_W, SCREEN_H, WINDOW_TITLE);
	SetTargetFPS(WINDOW_FPS);

	texture_pool_init();

	Texture2D* texture = NULL;

	while (!WindowShouldClose()) {
		texture = texture_pool_get(ICONS_PATH "Atrox.png");
		BeginDrawing();
		ClearBackground(BLACK);
			DrawTexture(*texture, 0, 0, WHITE);
			if (DEBUG_MODE) {
				DrawFPS(20, 20);
			}
		EndDrawing();		
	}
	
	texture_pool_close();
	CloseWindow();
	return 0;
}