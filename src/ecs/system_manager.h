#ifndef POKE_SYSTEM_MANAGER_H
#define POKE_SYSTEM_MANAGER_H
#include "../util/vector.h"
#include "../util/set.h"
#include "../util/entity_pair.h"
#include "system.h"


typedef struct _system_manager {
	system_t* system;
	set_t* entities;
	vector_t* drawable_components;
} system_manager_t;


void system_manager_init(system_manager_t* s);

void system_manager_close(system_manager_t* s);

void system_manager_insert(system_manager_t* s, entity_t e, component_t component_id);

void system_manager_update(system_manager_t* s, component_t component_id, float dt);

void system_manager_draw(system_manager_t* s, entity_pair_t* begin, entity_pair_t* end);

void system_manager_erase(system_manager_t* s, entity_t e, component_t component_id);

void system_manager_destroy_entity(system_manager_t* s, entity_t e);

void system_manager_clear(system_manager_t* s);


#endif // !POKE_SYSTEM_MANAGER_H
