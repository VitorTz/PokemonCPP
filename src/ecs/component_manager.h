#pragma once
#include <stdlib.h>
#include "../constants.h"
#include "components.h"


typedef struct component_array {
	char* data;
	size_t v_size;
} component_array_t;


typedef struct component_manager {
	component_array_t components[NUM_COMPONENTS];
} component_manager_t;


component_manager_t* component_manager_create();

void component_manager_destroy(component_manager_t* c);

void* component_manager_at(component_manager_t* c, entity_t e, component_t id);
