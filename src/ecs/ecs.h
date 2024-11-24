#pragma once
#include "entity_manager.h"
#include "component_manager.h"
#include "system_manager.h"
#include "camera.h"
#include "transition.h"


typedef struct ecs {
	entity_manager_t* entity;
	component_manager_t* component;
	system_manager_t* system;
	camera_t* camera;
	vector_t* entities_to_destroy;
	vector_t* collisions;
	vector_t* transitions;
	int should_destroy_all_entities;
} ecs_t;


ecs_t* ecs_create();

void ecs_destroy(ecs_t* ecs);

void ecs_init(ecs_t* ecs);

void ecs_close(ecs_t* ecs);

entity_t ecs_create_entity(ecs_t* ecs, zindex_t z, int add_to_camera);

void ecs_destroy_entity(ecs_t* ecs, entity_t e);

void ecs_add_collisions(ecs_t* ecs, float x, float y, float width, float height);

void ecs_add_transition(ecs_t* ecs, enum SceneID scene_id, float x, float y, float width, float height);

void* ecs_component_at(ecs_t* ecs, entity_t e, component_t id);

transform_t* ecs_get_transform(ecs_t* ecs, entity_t e);

void* ecs_component_insert(ecs_t* ecs, entity_t e, component_t id);

void ecs_update(ecs_t* ecs, float dt);

void ecs_draw(ecs_t* ecs);

void ecs_destroy_all_entities(ecs_t* ecs);
