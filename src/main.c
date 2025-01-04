#include "constants.h"
#include "scene/scene.h"
#include "ecs/ecs_manager.h"
#include "util/texture_pool.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>


int main() {
	srand(time(NULL));

	SetConfigFlags(FLAG_MSAA_4X_HINT);
	SetConfigFlags(FLAG_VSYNC_HINT);
	InitWindow(SCREEN_W, SCREEN_H, WINDOW_TITLE);

	texture_pool_init();
	ecs_manager_init();
	scene_manager_init();

	while (!WindowShouldClose()) {
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
