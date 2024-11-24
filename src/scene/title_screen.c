#include "scene.h"


static Texture2D background;


void scene_title_screen_init() {
	background = texture_pool_get(BACKGROUNDS_PATH "title-screen-bg.png");
}


void scene_title_screen_update(const float dt) {
	if (IsKeyPressed(KEY_SPACE)) {
		scene_manager_change_scene(WorldSceneID);
	}
}


void scene_title_screen_draw() {
	DrawTexture(background, 0, 0, WHITE);
}