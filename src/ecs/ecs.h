#pragma once
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "entity_manager.h"
#include "component_manager.h"
#include "system_manager.h"
#include "camera.h"
#include "../util/scene_id.h"
#include "../util/tile.h"


typedef struct ecs {
	entity_manager_t* entity;
	component_manager_t* component;
	system_manager_t* system;
	camera_t* camera;
	vector_t* entities_to_destroy;
	vector_t* collisions;
	vector_t* aux_vec;
	enum SceneID scene_id;
	int should_destroy_all_entities;
} ecs_t;


ecs_t* ecs_create(enum SceneID scene_id);

void ecs_destroy(ecs_t* ecs);

void ecs_init(ecs_t* ecs, enum SceneID scene_id);

void ecs_close(ecs_t* ecs);

entity_t ecs_create_entity(ecs_t* ecs, zindex_t z, int add_to_camera);

entity_t ecs_create_entity_with_tile(ecs_t* ecs, const tile_t* tile, int add_to_camera);

entity_t ecs_create_entity_with_pos(ecs_t* ecs, const zindex_t z, const int add_to_camera, float x, float y);

entity_t ecs_create_sprite(ecs_t* ecs, zindex_t z, const char* image_path, float x, float y);

entity_t ecs_create_sprite_with_tile(ecs_t* ecs, const tile_t* tile, const char* image_path);

void ecs_destroy_entity(ecs_t* ecs, entity_t e);

void ecs_add_collisions(ecs_t* ecs, float x, float y, float width, float height);

void* ecs_component_at(ecs_t* ecs, entity_t e, component_t id);

void ecs_set_camera_target(ecs_t* ecs, float x, float y);

transform_t* ecs_get_transform(ecs_t* ecs, entity_t e);

void* ecs_component_insert(ecs_t* ecs, entity_t e, component_t id);

void ecs_update(ecs_t* ecs, float dt);

void ecs_draw(ecs_t* ecs);

void ecs_destroy_all_entities(ecs_t* ecs);

int ecs_check_collision(ecs_t* ecs, Rectangle rect);
