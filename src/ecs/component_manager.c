#include "component_manager.h"
#include "components.h"
#include "../constants.h"


void component_manager_init(component_manager_t* c) {
	c->components = (component_array_t*)malloc(sizeof(component_array_t) * NUM_COMPONENTS);
	// TRANSFORM
	c->components[TRANSFORM_ID].data = malloc(sizeof(transform_t) * MAX_ENTITIES);
	c->components[TRANSFORM_ID].type_size = sizeof(transform_t);

	// SPRITE
	c->components[SPRITE_ID].data = malloc(sizeof(sprite_t) * MAX_ENTITIES);
	c->components[SPRITE_ID].type_size = sizeof(sprite_t);

	// SPRITE ANIMATION
	c->components[SPRITE_ANIMATION_ID].data = malloc(sizeof(sprite_animation_t) * MAX_ENTITIES);
	c->components[SPRITE_ANIMATION_ID].type_size = sizeof(sprite_animation_t);
	
}

void component_manager_close(component_manager_t* c) {
	for (int i = 0; i < NUM_COMPONENTS; i++) {
		free(c->components[i].data);
	}
}

void* component_manager_get_component(
	component_manager_t* c,
	const entity_t e,
	const component_t id
) {
	component_array_t* arr = c->components + id;
	return arr->data + arr->type_size * e;
}