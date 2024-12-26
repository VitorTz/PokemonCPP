#include "scene.h"
#include "../ecs/ecs_manager.h"


static ecs_t* ecs = NULL;


void scene_test_init() {
	ecs_manager_create_intance(TitleScreenID);
	ecs = ecs_manager_get_instance(TitleScreenID);
}

void scene_test_update(const float dt) {
	ecs_update(ecs, dt);
}

void scene_test_draw() {
	ecs_draw(ecs);
}