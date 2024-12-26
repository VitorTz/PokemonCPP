#include <raylib.h>
#include "ecs/ecs_manager.h"
#include "util/texture_pool.h"
#include "util/config.h"
#include "util/globals.h"
#include "scene/scene.h"


int main() {
	InitWindow(SCREEN_W, SCREEN_H, WINDOW_TITLE);	
	SetTargetFPS(FPS);

	globals_init();
	texture_pool_init();
	ecs_manager_init();
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
		
	ecs_manager_close();
	texture_pool_close();
	globals_close();
	CloseWindow();
	return 0;
}
