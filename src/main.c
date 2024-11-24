#include <raylib.h>
#include <stdio.h>
#include "constants.h"
#include "scene/scene.h"
#include "util/texture_pool.h"
#include "ecs/ecs_manager.h"


int main() {
	InitWindow(SCREEN_W, SCREEN_H, WINDOW_TITLE);
	SetTargetFPS(FPS);

	ecs_manager_init();
	texture_pool_init();

	scene_manager_init();

;	while (!WindowShouldClose()) {
		scene_manager_update(GetFrameTime());
		BeginDrawing();
		ClearBackground(BLACK);
		scene_manager_draw();
		EndDrawing();
	}
	
	ecs_manager_close();
	texture_pool_close();
	CloseWindow();
	return 0;
}