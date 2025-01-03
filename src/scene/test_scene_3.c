#include "scene.h"


static ECS* ecs = NULL;

static entity_t player_entity;


void scene_test_3_init() {
	ecs = ecs_manager_get_ecs_instance(TestScene3ID);

	if (ecs != NULL) {
		return;
	}

	ecs = ecs_manager_create_ecs_instance(TestScene3ID);

	// Ground
	ecs_create_ground_sprite(ecs, MAPS_PATH "world.png");
	
	entity_t player_entity = ecs_create_player(ecs, 1200.0f, 1200.0f);

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
