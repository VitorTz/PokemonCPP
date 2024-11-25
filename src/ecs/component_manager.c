#include "component_manager.h"
#include "assert.h"
#include <string.h>


component_manager_t* component_manager_create() {
	component_manager_t* c = (component_manager_t*)malloc(sizeof(component_manager_t));
	assert(c != NULL);
	c->components = (vector_t*)malloc(sizeof(vector_t) * NUM_COMPONENTS);
	vector_init(c->components + TRANSFORM_ID, sizeof(transform_t), MAX_ENTITIES);
	vector_init(c->components + SPRITE_ID, sizeof(sprite_t), MAX_ENTITIES);
	vector_init(c->components + SPRITE_ANIMATION_ID, sizeof(sprite_animation_t), MAX_ENTITIES);
	vector_init(c->components + CHARACTER_ID, sizeof(character_t), MAX_ENTITIES);
	vector_init(c->components + MOVEMENT_ID, sizeof(movement_t), MAX_ENTITIES);
	vector_init(c->components + COAST_ID, sizeof(coast_t), MAX_ENTITIES);
	vector_init(c->components + PLAYER_ID, sizeof(player_t), MAX_ENTITIES);
	vector_init(c->components + WATER_ID, sizeof(water_t), MAX_ENTITIES);
	vector_init(c->components + TRANSITION_ID, sizeof(transition_t), MAX_ENTITIES);
	for (int i = 0; i < NUM_COMPONENTS; i++) {
		vector_t* v = c->components + i;
		v->size = MAX_ENTITIES;
	}
	return c;
}


void component_manager_destroy(component_manager_t* c) {
	for (int i = 0; i < NUM_COMPONENTS; i++) 
		vector_close(c->components + i);
	free(c->components);
	free(c);
}


void* component_manager_at(component_manager_t* c, const entity_t e, const component_t id) {
	return vector_at(c->components + id, e);	
}
