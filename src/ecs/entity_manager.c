#include "entity_manager.h"


entity_manager_t* entity_manager_create() {
	entity_manager_t* ent = (entity_manager_t*)malloc(sizeof(entity_manager_t));	
	ent->vec = vector_create(sizeof(entity_t), MAX_ENTITIES);
	for (entity_t e = 0; e < MAX_ENTITIES; e++) {
		vector_push_back(ent->vec, &e);
	}
	ent->top = MAX_ENTITIES - 1;
	ent->size = 0;
	return ent;
}


void entity_manager_destroy(entity_manager_t* ent) {
	vector_destroy(ent->vec);
	free(ent);
}


entity_t entity_manager_create_entity(entity_manager_t* ent) {
	assert(!vector_is_empty(ent->vec));
	const entity_t e = *((entity_t*)vector_at(ent->vec, ent->top--));
	ent->size++;
	return e;
}


void entity_manager_destroy_entity(entity_manager_t* ent, const entity_t e) {
	vector_push_back(ent->vec, &e);
	ent->top++;
	ent->size--;
}

void entity_manager_clear(entity_manager_t* ent) {
	vector_clear(ent->vec);
	for (entity_t e = 0; e < MAX_ENTITIES; e++) {
		vector_push_back(ent->vec, &e);
	}
	ent->top = MAX_ENTITIES - 1;
	ent->size = 0;
}


size_t entity_manager_num_entities(entity_manager_t* ent) {
	return ent->size;
}