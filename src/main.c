#include <raylib.h>
#include "constants.h"
#include "scene/scene.h"
#include "ecs/ecs_manager.h"
#include "util/texture_pool.h"


static void debug();


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
				debug();
			}
		EndDrawing();		
	}
	
	ecs_manager_close();
	texture_pool_close();
	CloseWindow();
	return 0;
}


static void debug() {
	ECS* ecs = ecs_manager_get_ecs_instance();
	const int y = 10;
	const int y_offset = 18;

	DrawFPS(10, y);
	DrawText(
		TextFormat("ENTITIES: %d", ecs->entity->size),
		10,
		y + y_offset * 1,
		16,
		LIME
	);

	DrawText(
		TextFormat("CAMERA ENTITIES: %d", ecs->camera->size),
		10,
		y + y_offset * 2,
		16,
		LIME
	);

	DrawText(
		TextFormat("CAMERA ZOOM: %.2f, %.2f", ecs->camera->camera2D.zoom),
		10,
		y + y_offset * 3,
		16,
		LIME
	);

	DrawText(
		TextFormat("CAMERA TARGET: %.2f, %.2f", ecs->camera->camera2D.target.x, ecs->camera->camera2D.target.y),
		10,
		y + y_offset * 4,
		16,
		LIME
	);
}