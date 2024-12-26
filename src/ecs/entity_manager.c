#include "entity_manager.h"


void entity_manager_init(entity_manager_t* e) {
	e->size = 0;	
	e->entities = (entity_t*)malloc(sizeof(entity_t) * MAX_ENTITIES);
	assert(e->entities != NULL);
	for (entity_t ent = 0; ent < MAX_ENTITIES; ent++) {
		e->entities[ent] = ent;
	}
}

void entity_manager_close(entity_manager_t* e) {	
	if (e != NULL && e->entities != NULL) {
		free(e->entities);
	}
}

entity_t entity_manager_create_entity(entity_manager_t* e) {
	assert(e->size < MAX_ENTITIES);
	return e->entities[e->size++];	
}


void entity_manager_destroy_entity(entity_manager_t* e, const entity_t ent) {
	e->entities[e->size--] = ent;
}

void entity_manager_clear(entity_manager_t* e) {
	for (entity_t ent = 0; ent < MAX_ENTITIES; ent++) {
		e->entities[ent] = ent;
	}
	e->size = 0;
}

size_t entity_manager_num_alive_entities(const entity_manager_t* e) {
	return e->size;
}
