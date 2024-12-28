#include "scene.h"
#include "../ecs/ecs_manager.h"

static ecs_t* ecs = NULL;

void scene_test_init() {
	ecs_manager_create_ecs_instance(TitleScreenID);
	ecs = ecs_manager_get_ecs_instance(TitleScreenID);
	ecs_create_sprite(
		ecs,
		1,
		40.0f,
		40.0f,
		ICONS_PATH "Atrox.png"
	);
}

void scene_test_update(const float dt) {
	ecs_manager_set_current_ecs_instance(TitleScreenID);
	ecs_update(ecs, dt);
}

void scene_test_draw() {
	ecs_manager_set_current_ecs_instance(TitleScreenID);
	ecs_draw(ecs);
}