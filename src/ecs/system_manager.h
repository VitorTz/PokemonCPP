#pragma once
#include "components.h"
#include "../util/avl_tree.h"
#include "../util/set.h"
#include "../util/vector.h"
#include "../util/types.h"


typedef struct system {
	void (*update)(float dt);
	void (*draw)();
} system_t;


typedef struct system_manager {
	system_t systems[NUM_COMPONENTS];
	avl_tree_t* component_to_entities_maps;
	avl_tree_t* entities_to_drawable_components;
	avl_tree_t* drawable_components;
	vector_t* update_order;
} system_manager_t;


system_manager_t* system_manager_create();


void system_manager_destroy(system_manager_t* s);