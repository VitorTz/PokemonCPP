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

	const entity_t e = ecs_create_sprite(ecs, CAMERA_ZINDEX_WORLD, ICONS_PATH "Atrox.png");
	EntityTransform* transform = ecs_get_transform(ecs, e);
	transform->pos.x = 1200.0f;
	transform->pos.y = 1200.0f;
	ecs_add_shadow(ecs, e, transform->size.x / 2.0f, transform->size.y - 5);

	player_entity = e;
}

void scene_test_3_update(const float dt) {
	// PLAYER UPDATE
	EntityTransform* transform = ecs_get_transform(ecs, player_entity);
	Vector2 direction = Vector2Zero();

	if (IsKeyDown(POKE_UP_KEY)) {
		direction.y = -1.f;
	}
	else if (IsKeyDown(POKE_DOWN_KEY)) {
		direction.y = 1.f;
	}

	if (IsKeyDown(POKE_LEFT_KEY)) {
		direction.x = -1.f;
	}
	else if (IsKeyDown(POKE_RIGHT_KEY)) {
		direction.x = 1.f;
	}

	direction = Vector2Normalize(direction);

	transform->pos.x += dt * direction.x * 150.0f;
	transform->pos.y += dt * direction.y * 150.0f;

	// Camera target	
	camera_set_target(
		ecs->camera,
		transform->pos.x + transform->size.x / 2.0f,
		transform->pos.y + transform->size.y / 2.0f
	);

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