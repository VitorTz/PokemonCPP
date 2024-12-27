#ifndef POKE_SYSTEM_MANAGER_H
#define POKE_SYSTEM_MANAGER_H
#include "../util/types.h"
#include "../util/set.h"
#include "../util/vector.h"


typedef struct __system {
	void (*update)(set_iterator_t, float);
	void (*draw)(entity_t);
} system_t;


typedef struct __system_manager {
	system_t* system_arr;
	set_t* component_to_entities;
	vector_t* entities_to_drawable_components;		
} system_manager_t;


void system_manager_init(system_manager_t* s);

void system_manager_close(system_manager_t* s);

void system_manager_insert(system_manager_t* s, entity_t e, component_t id);

void system_manager_erase(system_manager_t* s, entity_t e, component_t id);

set_iterator_t system_manager_entities_by_component(system_manager_t* s, component_t id);

void system_manager_destroy_entity(system_manager_t* s, entity_t e);

void system_manager_clear(system_manager_t* s);


#endif