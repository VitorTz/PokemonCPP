#ifndef POKE_ECS_H
#define POKE_ECS_H
#include "components.h"
#include "entity_manager.h"
#include "component_manager.h"
#include "system_manager.h"
#include "camera.h"
#include "../util/vector.h"


typedef struct _ecs {
	entity_manager_t entity;
	component_manager_t component;
	system_manager_t system;
	camera_t camera;
	vector_t entities_to_destroy;
	int should_destroy_all_entities;
} ecs_t;


void ecs_init(ecs_t* ecs);

void ecs_close(ecs_t* ecs);

entity_t ecs_create_entity(ecs_t* ecs, zindex_t zindex, int should_add_to_camera);

entity_t ecs_create_sprite(ecs_t* ecs, zindex_t zindex, float pos_x, float pos_y, const char* imagepath);

void ecs_destroy_entity(ecs_t* ecs, entity_t e);

void ecs_destroy_all_entities(ecs_t* ecs);

void* ecs_add_component(ecs_t* ecs, entity_t e, component_t component_id);

void* ecs_get_component(ecs_t* ecs, entity_t e, component_t component_id);

void ecs_rmv_componetn(ecs_t* ecs, entity_t e, component_t component_id);

void ecs_update(ecs_t* ecs, float dt);

void ecs_draw(ecs_t* ecs);

void ecs_reset(ecs_t* ecs);

transform_t* ecs_get_transform(ecs_t* ecs, entity_t e);

#endif // !POKE_ECS_H
