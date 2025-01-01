#ifndef POKE_SYSTEM_MANAGER_H
#define POKE_SYSTEM_MANAGER_H
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
} SystemManager;


SystemManager* system_manager_create();

void system_manager_destroy(SystemManager* s);

void system_manager_insert(SystemManager* s, entity_id e, component_id id);

void system_manager_erase(SystemManager* s, entity_id e, component_id id);

void system_manager_destroy_entity(SystemManager* s, entity_id e);

void system_manager_update(float dt);

void system_manager_draw(EntityPair* begin, EntityPair* end);

void system_manager_clear(SystemManager* s);


#endif // !POKE_SYSTEM_MANAGER_H
