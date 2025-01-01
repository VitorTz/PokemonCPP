#ifndef POKE_COMPONENT_MANAGER_H
#define POKE_COMPONENT_MANAGER_H
#include "components.h"
#include "../constants.h"
#include "../util/vector.h"


typedef struct _component_manager {
	Vector component[NUM_COMPONENTS];
} ComponentManager;


ComponentManager* component_manager_create();

void component_manager_destroy(ComponentManager* c);

void component_manager_register_component(ComponentManager* c, component_id id, size_t component_size);

void* component_manager_at(ComponentManager* c, entity_id e, component_id id);


#endif // !POKE_COMPONENT_MANAGER_H
