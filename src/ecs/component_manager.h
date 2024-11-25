#pragma once
#include <stdlib.h>
#include "components.h"
#include "../constants.h"
#include "../util/vector.h"


typedef struct component_manager {
	vector_t* components;	
} component_manager_t;


component_manager_t* component_manager_create();

void component_manager_destroy(component_manager_t* c);

void* component_manager_at(component_manager_t* c, entity_t e, component_t id);

