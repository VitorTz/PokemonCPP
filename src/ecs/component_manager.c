#include "component_manager.h"


component_manager_t* component_manager_create() {
	component_manager_t* c = (component_manager_t*)malloc(sizeof(component_manager_t));
	
	c->components[TRANSFORM_ID] = (component_array_t){ NULL, sizeof(transform_t) };
	c->components[TRANSFORM_ID].data = (char*)malloc(sizeof(transform_t) * MAX_ENTITIES);	

	c->components[SPRITE_ID] = (component_array_t){ NULL, sizeof(sprite_t) };
	c->components[SPRITE_ID].data = (char*)malloc(sizeof(sprite_t) * MAX_ENTITIES);

	c->components[SPRITE_ANIMATION_ID] = (component_array_t){ NULL, sizeof(sprite_animation_t) };
	c->components[SPRITE_ANIMATION_ID].data = (char*)malloc(sizeof(sprite_animation_t) * MAX_ENTITIES);
	return c;
}


void component_manager_destroy(component_manager_t* c) {
	for (int i = 0; i < NUM_COMPONENTS; i++) {
		free(c->components[i].data);
	}
	free(c);
}


void* component_manager_at(component_manager_t* c, const entity_t e, const component_t id) {
	char* p = c->components[id].data;
	return p + e * c->components[id].v_size;
}