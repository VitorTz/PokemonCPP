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
	int mouse_zoom_is_enable;
	SceneID scene_id;	
} ECS;

ECS* ecs_create(SceneID scene_id);

void ecs_destroy(ECS* ecs);

entity_t ecs_create_entity(const ECS* ecs, zindex_t zindex, int should_add_to_camera);

entity_t ecs_create_sprite(const ECS* ecs, zindex_t zindex, const char* filepath);

entity_t ecs_create_ground_sprite(const ECS* ecs, const char* filepath);

entity_t ecs_create_player(const ECS* ecs, float pos_x, float pos_y);

void ecs_enable_mouse_zoom(ECS* ecs);

void ecs_disable_mouse_zoom(ECS* ecs);

void ecs_add_shadow(const ECS* ecs, entity_t e, float x_offset, float y_offset);

void ecs_destroy_entity(const ECS* ecs, entity_t e);

void ecs_destroy_all_entities(ECS* ecs);

void* ecs_add_component(const ECS* ecs, entity_t e, component_t component_id);

void* ecs_get_component(const ECS* ecs, entity_t e, component_t component_id);

void ecs_rmv_component(const ECS* ecs, entity_t e, component_t component_id);

void ecs_add_static_collision(const ECS* ecs, float x, float y, float width, float height);

SetIterator* ecs_get_entities_by_component(const ECS* ecs, component_t component_id);

int ecs_check_static_collision(const ECS* ecs, Rectangle rect);

void ecs_update(ECS* ecs, float dt);

void ecs_draw(const ECS* ecs);

EntityTransform* ecs_get_transform(const ECS* ecs, entity_t e);


#endif // !POKE_ECS_H
