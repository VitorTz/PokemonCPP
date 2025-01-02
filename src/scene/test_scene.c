#include "scene.h"

static ECS* ecs = NULL;

static float speed[MAX_ENTITIES];


// Test Scene 2
void scene_test_1_init() {
	ecs_manager_create_ecs_instance(TestScene1ID);
	ecs_manager_set_ecs_instance(TestScene1ID);
	ecs = ecs_manager_get_ecs_instance();

	for (int i = 0; i < MAX_ENTITIES; i++) {
		speed[i] = GetRandomValue(20, 200);
		const entity_t e = ecs_create_sprite(
			ecs, 
			GetRandomValue(CAMERA_ZINDEX_MIN, CAMERA_ZINDEX_MAX), 
			ICONS_PATH "Atrox.png"
		);
		EntityTransform* transform = ecs_get_transform(ecs, e);
		transform->pos.x = GetRandomValue(0, SCREEN_W);
		transform->pos.y = GetRandomValue(0, SCREEN_H);	
	}
}

void scene_test_1_update(const float dt) {
	SetIterator* iter = ecs_get_entities_by_component(ecs, SPRITE_ID);
	entity_t* entity = NULL;		
	while ((entity = (entity_t*)set_iter_next(iter)) != NULL) {		
		EntityTransform* transform = ecs_get_transform(ecs, *entity);
		transform->pos.y += dt * speed[*entity];
		if (transform->pos.y > SCREEN_H) {
			ecs_destroy_entity(ecs, *entity);
		}
	}	
	ecs_update(ecs, dt);
}

void scene_test_1_draw() {
	ecs_draw(ecs);
}


// Test Scene 2
void scene_test_2_init() {

}

void scene_test_2_update(const float dt) {

}

void scene_test_2_draw() {

}


// Test Scene 3
void scene_test_3_init() {

}

void scene_test_3_update(const float dt) {

}

void scene_test_3_draw() {

}
