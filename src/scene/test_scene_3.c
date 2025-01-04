#include "scene.h"
#include "../ecs/ecs_manager.h"
#include "../util/tiled_map.h"


static ECS* ecs = NULL;


void scene_test_3_init() {
	ecs = ecs_manager_get_ecs_instance(TestScene3ID);
	if (ecs != NULL) { return; }
	ecs = ecs_manager_create_ecs_instance(TestScene3ID);
	load_tiled_map(ecs, MAPS_PATH "world.bin");
}

void scene_test_3_update(const float dt) {
	// ECS UPDATE
	ecs_update(ecs, dt);

	// CHANGE SCENE
	if (IsKeyPressed(KEY_SPACE)) {
		scene_manager_change_scene(TestScene1ID);
	}

}

void scene_test_3_draw() {
	ecs_draw(ecs);
}
