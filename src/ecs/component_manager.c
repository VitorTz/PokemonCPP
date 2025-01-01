#include "component_manager.h"


ComponentManager* component_manager_create() {
	ComponentManager* c = (ComponentManager*)malloc(sizeof(ComponentManager*));
	return c;
}

void component_manager_destroy(ComponentManager* c) {
	for (int i = 0; i < NUM_COMPONENTS; i++) {
		vector_close(c->component + i);
	}
}

void component_manager_register_component(ComponentManager* c, const component_id id, const size_t component_size) {
	vector_init(c->component + id, component_size, MAX_ENTITIES);
}

void* component_manager_at(ComponentManager* c, const entity_id e, const component_id id) {
	return vector_at(c->component + id, e);
}