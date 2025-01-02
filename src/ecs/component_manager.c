#include "component_manager.h"


ComponentManager* component_manager_create() {
	ComponentManager* c = (ComponentManager*) malloc(sizeof(ComponentManager));
	assert(c != NULL);
	return c;
}

void component_manager_destroy(ComponentManager* c) {
	for (int i = 0; i < NUM_COMPONENTS; i++) {
		vector_close(c->component + i);
	}
}

void component_manager_register_component(ComponentManager* c, const component_t component_id, const size_t component_size) {
	vector_init(c->component + component_id, component_size, MAX_ENTITIES);
}

void* component_manager_at(ComponentManager* c, const entity_t e, const component_t component_id) {
	return vector_at(c->component + component_id, e);
}