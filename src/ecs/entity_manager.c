#include "entity_manager.h"
#include <stdio.h>


void entity_manager_init(entity_manager_t* e) {
	e->entities = (entity_t*)malloc(sizeof(entity_t) * MAX_ENTITIES);
	assert(e->entities != NULL);
	for (entity_t ent = 0; ent < MAX_ENTITIES; ent++) {
		e->entities[ent] = MAX_ENTITIES - ent - 1;
	}
	e->top = MAX_ENTITIES - 1;
	e->size = 0;
}

void entity_manager_close(entity_manager_t* e) {
	free(e->entities);
}

entity_t entity_manager_create_entity(entity_manager_t* e) {
	assert(e->size < MAX_ENTITIES);
	e->size++;
	return e->entities[e->top--];	
}

void entity_manager_destroy_entity(entity_manager_t* e, const entity_t ent) {
	e->entities[++e->top] = ent;
	e->size--;
}

void entity_manager_clear(entity_manager_t* e) {
	for (entity_t ent = 0; ent < MAX_ENTITIES; ent++) {
		e->entities[ent] = MAX_ENTITIES - ent - 1;
	}
	e->top = MAX_ENTITIES - 1;
	e->size = 0;
}
