#include "component_manager.h"
#include "components.h"
#include "../constants.h"


void component_manager_init(component_manager_t* c) {
	c->component = (vector_t*)malloc(sizeof(vector_t) * NUM_COMPONENTS);
	vector_init(c->component + TRANSFORM_ID, sizeof(transform_t), MAX_ENTITIES);
	vector_init(c->component + SPRITE_ID, sizeof(sprite_t), MAX_ENTITIES);
	vector_init(c->component + SPRITE_ANIMATION_ID, sizeof(sprite_animation_t), MAX_ENTITIES);
	for (vector_t* v = c->component; v < c->component + NUM_COMPONENTS; v++) {
		v->size = MAX_ENTITIES;
	}
}

void component_manager_close(component_manager_t* c) {
	if (c != NULL) {
		for (vector_t* v = c->component; v < c->component + NUM_COMPONENTS; v++) {
			vector_close(v);
		}
		free(c->component);
	}
}

void* component_manager_get_component(
	component_manager_t* c,
	const entity_t e, 
	const component_t component_id
) {
	return vector_at(c->component + component_id, e);
}