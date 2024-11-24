#pragma once
#include "components.h"
#include "../constants.h"
#include "../util/avl_tree.h"
#include "../util/set.h"
#include "../util/vector.h"
#include "../util/types.h"


typedef struct system {
	void (*update)(float, iterator_t);
	void (*draw)(entity_t);
} system_t;


typedef struct system_manager {
	system_t systems[NUM_COMPONENTS];
	set_t* entities_set_by_component;
	set_t* drawable_components_by_entity;
	set_t* drawable_components_set;
	component_t update_order[NUM_UPDATABLE_COMPONENTS];	
} system_manager_t;


void system_sprite_draw(entity_t e);
void system_sprite_animation_update(float dt, iterator_t);
void system_sprite_animation_draw(entity_t e);


system_manager_t* system_manager_create();

void system_manager_destroy(system_manager_t* s);

void system_manager_insert(system_manager_t* s, entity_t e, component_t id);

void system_manager_erase(system_manager_t* s, entity_t e, component_t id);

void system_manager_update(system_manager_t* s, float dt);

void system_manager_draw(system_manager_t* s, iterator_t iter);

void system_manager_destroy_entity(system_manager_t* s, entity_t e);

void system_manager_clear(system_manager_t* s);