#ifndef POKE_SYSTEM_MANAGER_H
#define POKE_SYSTEM_MANAGER_H
#include "components.h"
#include "../util/iterator.h"
#include "../util/hash_set.h"
#include "../util/types.h"
#include "../util/util.h"
#include "../constants.h"


typedef struct system {
	void (*update)(iterator_t*, float);
	void (*draw)(entity_t);
} system_t;


typedef struct system_manager {
	system_t system[NUM_COMPONENTS];
	hash_set_t* component_to_entities;
	hash_set_t* entities_to_drawable_components;	
} system_manager_t;


void system_manager_init(system_manager_t* s);

void system_manager_close(system_manager_t* s);

void system_manager_insert(system_manager_t* s, entity_t e, component_t id);

void system_manager_erase(system_manager_t* s, entity_t e, component_t id);

void system_manager_entity_destroy(system_manager_t* s, entity_t e);

void system_manager_update(system_manager_t* s, float dt);

void system_manager_draw(system_manager_t* s);


#endif // !POKE_SYSTEM_MANAGER_H
