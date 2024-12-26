#include <raylib.h>
#include <stdio.h>
#include "util/hash_map.h"
#include "util/texture_pool.h"
#include "util/config.h"
#include "util/util.h"
#include "util/globals.h"
#include "scene/scene.h"
#include "constants.h"


int main() {
	InitWindow(SCREEN_W, SCREEN_H, WINDOW_TITLE);	
	SetTargetFPS(FPS);

	globals_init();
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
	globals_close();
	CloseWindow();
	return 0;
}
