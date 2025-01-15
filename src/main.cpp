#include <raylib.h>
#include "scene/Scene.hpp"
#include "util/TexturePool.hpp"
#include "constants.hpp"


int main() {		
	SetConfigFlags(FLAG_MSAA_4X_HINT);
	SetConfigFlags(FLAG_VSYNC_HINT);
	InitWindow(pk::SCREEN_WIDTH, pk::SCREEN_HEIGHT, pk::WINDOW_TITLE);
	
	pk::gSceneManager.init();

	while (!WindowShouldClose()) {
		pk::gSceneManager.update(GetFrameTime());
		BeginDrawing();
		ClearBackground(BLACK);
			pk::gSceneManager.draw();
		EndDrawing();
	}

	pk::gTexturePool.clear();
	CloseWindow();
	return 0;
}
