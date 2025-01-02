#ifndef POKE_ECS_H
#define POKE_ECS_H
#include "entity_manager.h"
#include "component_manager.h"
#include "system_manager.h"
#include "../util/camera.h"
#include "../util/vector.h"


typedef struct _ecs {
	EntityManager* entity;
	ComponentManager* component;
	SystemManager* system;
	PokeCamera* camera;
	Vector* entities_to_destroy;
	Vector* static_collisions;
	int should_destroy_all_entities;
} ECS;

ECS* ecs_create();

void ecs_destroy(ECS* ecs);

entity_t ecs_create_entity(ECS* ecs, zindex_t zindex, int should_all_to_camera);

void ecs_destroy_entity(ECS* ecs, entity_t e);

void ecs_destroy_all_entities(ECS* ecs);

void* ecs_add_component(ECS* ecs, entity_t e, component_t component_id);

void* ecs_get_component(ECS* ecs, entity_t e, component_t component_id);

void ecs_rmv_component(ECS* ecs, entity_t e, component_t component_id);

void ecs_add_static_collision(ECS* ecs, Rectangle rect);

int ecs_check_static_collision(ECS* ecs, Rectangle rect);

void ecs_update(ECS* ecs, float dt);

void ecs_draw(ECS* ecs);

EntityTransform* ecs_get_transform(ECS* ecs, entity_t e);


#endif // !POKE_ECS_H
