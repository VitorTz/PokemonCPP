#include "component_manager.h"


void component_manager_init(component_manager_t* c) {
	c->component_array[TRANSFORM_ID] = (component_array_t){
		malloc(sizeof(transform_t) * MAX_ENTITIES),
		sizeof(transform_t)
	};

	c->component_array[SPRITE_ID] = (component_array_t){
		malloc(sizeof(sprite_t) * MAX_ENTITIES),
		sizeof(sprite_t)
	};

	c->component_array[SPRITE_ANIMATION_ID] = (component_array_t){
		malloc(sizeof(sprite_animation_t) * MAX_ENTITIES),
		sizeof(sprite_animation_t)
	};
}

void component_manager_close(component_manager_t* c) {
	for (int i = 0; i < NUM_COMPONENTS; i++) {
		if (c->component_array[i].data != NULL) {
			free(c->component_array[i].data);
		}
	}
}

void* component_manager_get_component(
	component_manager_t* c,
	const entity_t e,
	const component_t id
) {
	component_array_t* arr = &c->component_array[id];
	return (char*)arr->data + arr->v_size * e;
}