#include "system_manager.h"


static size_t hash_component(const void* k) {
	const component_t c = *((component_t*)(k));
	return c;
}


system_manager_t* system_manager_create() {
	system_manager_t* s = (system_manager_t*)malloc(sizeof(system_manager_t));
	
	for (int i = 0; i < NUM_COMPONENTS; i++) {
		avl_tree_create(s->component_to_entities_maps + i, sizeof(set_t), hash_component);
	}
}