#include <raylib.h>
#include <stdio.h>
#include "util/config.h"
#include "scene/scene.h"
#include "constants.h"


int main() {
	InitWindow(SCREEN_W, SCREEN_H, WINDOW_TITLE);	
	SetTargetFPS(FPS);

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
	
	CloseWindow();
	return 0;
}
