#ifndef POKE_SYSTEM_MANAGER_H
#define POKE_SYSTEM_MANAGER_H
#include "components.h"
#include "system.h"
#include "../util/types.h"
#include "../constants.h"
#include "../util/set.h"


typedef struct _system_manager {
	System system[NUM_COMPONENTS];
	Set entities[NUM_COMPONENTS];
	Set drawable_components[MAX_ENTITIES];
	int8_t is_drawable_component[NUM_COMPONENTS];
} SystemManager;


SystemManager* system_manager_create();

void system_manager_destroy(SystemManager* system_manager);

void system_manager_register_system(
	SystemManager* system_manager,
	component_t component_id,
	void (*update)(SetIterator*, float),
	void (*draw)(entity_t)
);

void system_manager_insert(SystemManager* system_manager, entity_t e, component_t component_id);

void system_manager_erase(SystemManager* system_manager, entity_t e, component_t component_id);

void system_manager_destroy_entity(SystemManager* system_manager, entity_t e);

void system_manager_update(SystemManager* system_manager, float dt);

void system_manager_draw(SystemManager* system_manager, const EntityPair* begin, const EntityPair* end);

void system_manager_clear(SystemManager* system_manager);


#endif // !POKE_SYSTEM_MANAGER_H
