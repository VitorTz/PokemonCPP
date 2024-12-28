#ifndef POKE_COMPONENT_MANAGER_H
#define POKE_COMPONENT_MANAGER_H
#include "../util/vector.h"
#include "../util/types.h"


typedef struct _component_manager {
	vector_t* component;
} component_manager_t;


void component_manager_init(component_manager_t* c);

void component_manager_close(component_manager_t* c);

void* component_manager_get_component(component_manager_t* c, entity_t e, component_t component_id);


#endif // !POKE_COMPONENT_MANAGER_H
