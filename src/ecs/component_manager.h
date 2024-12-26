#ifndef POKE_COMPONENT_MANAGER_H
#define POKE_COMPONENT_MANAGER_H
#include "../util/types.h"
#include <stdlib.h>
#include <stddef.h>


typedef struct __component_array {
	char* data;
	size_t type_size;
} component_array_t;


typedef struct __component_manager {
	component_array_t* components;
} component_manager_t;


void component_manager_init(component_manager_t* c);

void component_manager_close(component_manager_t* c);

void* component_manager_get_component(component_manager_t* c, entity_t e, component_t id);


#endif