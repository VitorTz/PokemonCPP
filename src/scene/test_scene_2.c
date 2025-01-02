#include "scene.h"


static ECS* ecs = NULL;


void scene_test_2_init() {
	ecs = ecs_manager_get_ecs_instance(TestScene2ID);

	if (ecs != NULL) {
		return;
	}

	ecs = ecs_manager_create_ecs_instance(TestScene2ID);
}

void scene_test_2_update(const float dt) {
	if (IsKeyPressed(KEY_SPACE)) {
		scene_manager_change_scene(TestScene3ID);
	}
	ecs_update(ecs, dt);
}

void scene_test_2_draw() {
	ecs_draw(ecs);
}
