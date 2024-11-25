#include "ecs.h"
#include "../scene/scene.h"


void ecs_init(ecs_t* ecs, const enum SceneID scene_id) {
	ecs->entity = entity_manager_create();
	ecs->component = component_manager_create();
	ecs->system = system_manager_create();
	ecs->camera = camera_create();
	ecs->entities_to_destroy = vector_create(sizeof(entity_t), MAX_ENTITIES / 4);
	ecs->should_destroy_all_entities = 0;
	ecs->collisions = vector_create(sizeof(Rectangle), 1024);
	ecs->aux_vec = vector_create(1, 512);
	ecs->scene_id = scene_id;
}


ecs_t* ecs_create(const enum SceneID scene_id) {
	ecs_t* ecs = (ecs_t*) malloc(sizeof(ecs_t));
	ecs_init(ecs, scene_id);
	return ecs;
}


void ecs_close(ecs_t* ecs) {
	entity_manager_destroy(ecs->entity);
	component_manager_destroy(ecs->component);
	system_manager_destroy(ecs->system);
	vector_destroy(ecs->entities_to_destroy);
	vector_destroy(ecs->collisions);
	vector_destroy(ecs->aux_vec);
}


void ecs_destroy(ecs_t* ecs) {
	ecs_close(ecs);
	free(ecs);
}


entity_t ecs_create_entity(ecs_t* ecs, const zindex_t z, const int add_to_camera) {
	const entity_t e = entity_manager_create_entity(ecs->entity);
	transform_t* t = (transform_t*) component_manager_at(ecs->component, e, TRANSFORM_ID);
	transform_init(t, z);
	if (add_to_camera) {
		camera_insert(ecs->camera, e, z);
	}
	return e;
}


entity_t ecs_create_entity_with_tile(ecs_t* ecs, const tile_t* tile, const int add_to_camera) {
	const entity_t e = ecs_create_entity(ecs, tile->zindex, add_to_camera);
	transform_t* t = ecs_get_transform(ecs, e);
	t->pos = (Vector2){ tile->x, tile->y };
	t->size = (Vector2){ tile->width, tile->height };
	return e;
}


entity_t ecs_create_entity_with_pos(ecs_t* ecs, const zindex_t z, const int add_to_camera, const float x, const float y) {
	const entity_t e = entity_manager_create_entity(ecs->entity);
	transform_t* t = (transform_t*)component_manager_at(ecs->component, e, TRANSFORM_ID);
	transform_init(t, z);
	t->pos = (Vector2){ x, y };
	if (add_to_camera) {
		camera_insert(ecs->camera, e, z);
	}
	return e;
}


entity_t ecs_create_sprite(ecs_t* ecs, const zindex_t z, const char* image_path, const float x, const float y) {
	const entity_t e = ecs_create_entity(ecs, z, 1);	
	sprite_t* sprite = (sprite_t*) ecs_component_insert(ecs, e, SPRITE_ID);
	sprite_init(sprite, image_path);
	transform_t* t = (transform_t*) component_manager_at(ecs->component, e, TRANSFORM_ID);
	t->pos = (Vector2){ x, y };
	t->size = (Vector2){ (float) sprite->texture.width, (float) sprite->texture.height };
	return e;
}


entity_t ecs_create_sprite_with_tile(ecs_t* ecs, const tile_t* tile, const char* image_path) {
	return ecs_create_sprite(ecs, tile->zindex, image_path, tile->x, tile->y);
}


void ecs_destroy_entity(ecs_t* ecs, const entity_t e) {
	vector_push_back(ecs->entities_to_destroy, &e);
}


void ecs_add_collisions(
	ecs_t* ecs, 
	const float x, 
	const float y,
	const float width, 
	const float height
) {
	Rectangle rect = (Rectangle){ x, y, width, height };
	vector_push_back(ecs->collisions, &rect);
}


void* ecs_component_at(ecs_t* ecs, const entity_t e, const component_t id) {
	return component_manager_at(ecs->component, e, id);
}


void ecs_set_camera_target(ecs_t* ecs, const float x, const float y) {
	ecs->camera->camera2D.target.x = x;
	ecs->camera->camera2D.target.y = y;
}


transform_t* ecs_get_transform(ecs_t* ecs, const entity_t e) {
	return (transform_t*) component_manager_at(ecs->component, e, TRANSFORM_ID);
}


void* ecs_component_insert(ecs_t* ecs, const entity_t e, const component_t id) {
	system_manager_insert(ecs->system, e, id);
	return component_manager_at(ecs->component, e, id);
}


void ecs_update(ecs_t* ecs, const float dt) {
	system_manager_update(ecs->system, dt);

	if (ecs->should_destroy_all_entities) {
		ecs->should_destroy_all_entities = 0;
		vector_clear(ecs->entities_to_destroy);
		camera_clear(ecs->camera);
		entity_manager_clear(ecs->entity);
		system_manager_clear(ecs->system);
	}

	while (!vector_is_empty(ecs->entities_to_destroy)) {
		entity_t e;
		vector_pop_back(ecs->entities_to_destroy, &e);
		camera_erase(ecs->camera, e, ecs_get_transform(ecs, e)->zindex);
		entity_manager_destroy_entity(ecs->entity, e);
		system_manager_destroy_entity(ecs->system, e);
	}
}



static int comp_entity_pair(const void* l, const void* r) {
	const entity_pair_t* p1 = (entity_pair_t*)l;
	const entity_pair_t* p2 = (entity_pair_t*)r;
	if (p1->y == p2->y) return 0;
	else if (p1->y < p2->y) return -1;
	return 1;	
}


void ecs_draw(ecs_t* ecs) {
	BeginMode2D(ecs->camera->camera2D);
		for (int i = 0; i < CAMERA_ZINDEX_MAX; i++) {
			vector_t* vec = ecs->camera->entities + i;
			iterator_t iter = vector_iter(vec);			
			for (entity_pair_t* pair = iter.begin; pair < iter.end; pair++) {
				const transform_t* t = component_manager_at(ecs->component, pair->e, TRANSFORM_ID);
				pair->y = t->pos.y + t->size.y / 2.0f;
			}
			qsort(vec->data, vec->size, sizeof(entity_pair_t), comp_entity_pair);
			system_manager_draw(ecs->system, vector_iter(vec));
		}

		if (DEBUG_MODE) {
			// Collisions
			iterator_t iter = vector_iter(ecs->collisions);			
			for (Rectangle* rect = iter.begin; rect < iter.end; rect++) {
				DrawRectangleLinesEx(*rect, 2.0f, RED);
			}
			// Movement
			iter = set_iter(ecs->system->entities_set_by_component + MOVEMENT_ID);
			for (entity_t* e = iter.begin; e < iter.end; e++) {
				movement_t* movement = (movement_t*)ecs_component_at(ecs, *e, MOVEMENT_ID);
				DrawRectangleLinesEx(movement->collision_box, 2.0f, BLUE);
			}
			// Character
			iter = set_iter(ecs->system->entities_set_by_component + CHARACTER_ID);
			for (entity_t* e = iter.begin; e < iter.end; e++) {
				character_t* character = (character_t*)ecs_component_at(ecs, *e, CHARACTER_ID);
				DrawRectangleLinesEx(character->action_box, 2.0f, BLUE);
			}
		}

	EndMode2D();
	if (DEBUG_MODE) {
		DrawFPS(20, 20);
	}
}


void ecs_destroy_all_entities(ecs_t* ecs) {
	ecs->should_destroy_all_entities = 1;
}


int ecs_check_collision(ecs_t* ecs, const Rectangle rect) {
	iterator_t iter = vector_iter(ecs->collisions);
	Rectangle* begin = (Rectangle*) iter.begin;
	Rectangle* end = (Rectangle*) iter.end;

	for (Rectangle* r = begin; r < end; r++) {
		if (CheckCollisionRecs(rect, *r)) {
			return 1;
		}
	}
	return 0;
}
