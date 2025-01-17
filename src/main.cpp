#include <raylib.h>
#include "scene/Scene.hpp"
#include "util/TexturePool.hpp"
#include "shaders/ShaderPool.h"
#include "shaders/WaterShader.hpp"
#include "constants.hpp"


int main() {		
	SetConfigFlags(FLAG_MSAA_4X_HINT);
	SetConfigFlags(FLAG_VSYNC_HINT);
	InitWindow(pk::SCREEN_WIDTH, pk::SCREEN_HEIGHT, pk::WINDOW_TITLE);

	pk::gTexturePool.init();
	pk::gShaderPool.init();
	pk::gEcsManager.init();
	pk::gSceneManager.init();

	while (!WindowShouldClose()) {
		pk::gSceneManager.update(GetFrameTime());
		BeginDrawing();
		ClearBackground(BLACK);
			pk::gSceneManager.draw();
			if (pk::DEBUG_MODE) {
				DrawFPS(20, 20);
			}
		EndDrawing();
	}

	pk::gTexturePool.clear();
	pk::gShaderPool.clear();
	CloseWindow();
	return 0;
}
