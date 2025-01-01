#include <raylib.h>
#include "constants.h"
#include "scene/scene.h"
#include "ecs/ecs_manager.h"
#include "util/texture_pool.h"


int main() {
	InitWindow(SCREEN_W, SCREEN_H, WINDOW_TITLE);
	SetTargetFPS(WINDOW_FPS);

	texture_pool_init();
	ecs_manager_init();
	scene_manager_init();

	while (!WindowShouldClose()) {
		scene_manager_update(GetFrameTime());
		BeginDrawing();
		ClearBackground(BLACK);			
			scene_manager_draw();
			if (DEBUG_MODE) {
				DrawFPS(20, 20);
			}
		EndDrawing();		
	}
	
	ecs_manager_close();
	texture_pool_close();
	CloseWindow();
	return 0;
}