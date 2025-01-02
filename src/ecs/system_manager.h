#ifndef POKE_SYSTEM_MANAGER_H
#define POKE_SYSTEM_MANAGER_H
#include <assert.h>
#include "components.h"
#include "system.h"
#include "../util/types.h"
#include "../constants.h"
#include "../util/set.h"
#include "../util/map.h"


typedef struct _system_manager {
	System system[NUM_COMPONENTS];
	Set entities[NUM_COMPONENTS];
	Set drawable_components[MAX_ENTITIES];
	int8_t is_drawable_component[NUM_COMPONENTS];
} SystemManager;


SystemManager* system_manager_create();

void system_manager_destroy(SystemManager* s);

void system_manager_register_system(
	SystemManager* s, 
	component_t id,
	void (*update)(SetIterator*, float),
	void (*draw)(entity_t)
);

void system_manager_insert(SystemManager* s, entity_t e, component_t component_id);

void system_manager_erase(SystemManager* s, entity_t e, component_t component_id);

void system_manager_destroy_entity(SystemManager* s, entity_t e);

void system_manager_update(SystemManager* s, float dt);

void system_manager_draw(SystemManager* s, EntityPair* begin, EntityPair* end);

void system_manager_clear(SystemManager* s);


#endif // !POKE_SYSTEM_MANAGER_H
