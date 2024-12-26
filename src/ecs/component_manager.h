#ifndef POKE_COMPONENT_MANAGER_H
#define POKE_COMPONENT_MANAGER_H
#include <stddef.h>
#include <stdlib.h>
#include "components.h"
#include "../constants.h"
#include "../util/types.h"


typedef struct component_array {
	void* data;
	size_t v_size;
} component_array_t;


typedef struct component_manager {
	component_array_t component_array[NUM_COMPONENTS];
} component_manager_t;


void component_manager_init(component_manager_t* c);

void component_manager_close(component_manager_t* c);

void* component_manager_get_component(
	component_manager_t* c,
	entity_t e,
	component_t component_id
);


#endif