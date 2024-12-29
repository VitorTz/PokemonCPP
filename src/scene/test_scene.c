#include "scene.h"
#include "../ecs/ecs_manager.h"

static ecs_t* ecs = NULL;
static float speed[MAX_ENTITIES];

void scene_test_init() {
	ecs_manager_create_ecs_instance(TitleScreenID);
	ecs = ecs_manager_get_ecs_instance(TitleScreenID);

	for (int i = 0; i < MAX_ENTITIES; i++) {
		speed[i] = (float) GetRandomValue(20, 200);
	}

	for (int i = 0; i < MAX_ENTITIES; i++) {
		ecs_create_sprite(
			ecs,
			1,
			GetRandomValue(0, SCREEN_W),
			GetRandomValue(0, SCREEN_H) - SCREEN_H,
			ICONS_PATH "Atrox.png"
		);
	}
}

void scene_test_update(const float dt) {
	ecs_manager_set_current_ecs_instance(TitleScreenID);
	set_t* set = system_manager_get_set_by_component(&ecs->system, SPRITE_ID);
	for (vector_t* v = set_begin(set); v < set_end(set); v++) {		
		for (char* p = vector_begin(v); p < vector_end(v); p += v->type_size) {
			entity_t* e = (entity_t*)p;
			transform_t* transform = ecs_get_transform(ecs, *e);
			transform->pos.y += dt * speed[*e];
			if (transform->pos.y > (float) SCREEN_H) {
				ecs_destroy_entity(ecs, *e);
			}
		}
	}
	ecs_update(ecs, dt);
}

void scene_test_draw() {
	ecs_manager_set_current_ecs_instance(TitleScreenID);
	ecs_draw(ecs);
}