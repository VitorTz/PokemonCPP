#include <raylib.h>
#include "util/texture_pool.h"
#include "scene/scene.h"
#include "util/config.h"
#include "constants.h"


int main() {
	InitWindow(SCREEN_W, SCREEN_H, WINDOW_TITLE);
	SetTargetFPS(WINDOW_FPS);	


	texture_pool_init();
	scene_init();

	while (!WindowShouldClose()) {
		scene_update(GetFrameTime());
		BeginDrawing();
			if (poke_config_should_clear_background()) {
				ClearBackground(BLACK);
			}
			scene_draw();
		EndDrawing();
	}
	
	texture_pool_close();
	CloseWindow();
	return 0;
}