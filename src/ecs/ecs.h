#ifndef POKE_ECS_H
#define POKE_ECS_H
#include "entity_manager.h"
#include "component_manager.h"
#include "system_manager.h"
#include "../util/entity_pair.h"
#include "../scene/scene_id.h"
#include "../util/camera.h"


typedef struct ecs {
	entity_manager_t entity;
	component_manager_t component;
	system_manager_t system;
	camera_t camera;
	vector_t entities_to_destroy;
	int should_destroy_all_entities;
	SceneID scene_id;
} ecs_t;


ecs_t* ecs_create(SceneID scene_id);

void ecs_destroy(ecs_t* ecs);

entity_t ecs_create_entity(ecs_t* ecs, zindex_t zindex, int should_add_to_camera);

void ecs_destroy_entity(ecs_t* ecs, entity_t e);

void ecs_destroy_all_entities(ecs_t* ecs);

float ecs_entity_centery(ecs_t* ecs, entity_t e);

void* ecs_add_component(ecs_t* ecs, entity_t e, component_t component_id);

void* ecs_get_component(ecs_t* ecs, entity_t e, component_t component_id);

void ecs_rmv_component(ecs_t* ecs, entity_t e, component_t component);

void ecs_update(ecs_t* ecs, float dt);

void ecs_draw(ecs_t* ecs);

transform_t* ecs_get_transform(ecs_t* ecs, entity_t e);

size_t ecs_num_entities_on_camera(ecs_t* ecs);

size_t ecs_num_alive_entities(ecs_t* ecs);


#endif