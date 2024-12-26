#include "scene.h"
#include "../ecs/ecs_manager.h"


static ecs_t* ecs_instance = NULL;


void scene_test_init() {
	ecs_manager_create_intance(TitleScreenID);
	ecs_instance = ecs_manager_get_instance(TitleScreenID);	
	ecs_create_sprite(ecs_instance, ASSETS_PATH "test.png", 20.0f, 20.0f, 1);
}

void scene_test_update(const float dt) {
	ecs_manager_set_current_ecs_instance(TitleScreenID);
	ecs_update(ecs_instance, dt);
}

void scene_test_draw() {
	ecs_manager_set_current_ecs_instance(TitleScreenID);
	ecs_draw(ecs_instance);
}