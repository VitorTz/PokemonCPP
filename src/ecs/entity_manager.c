#include "entity_manager.h"
#include "../constants.h"


EntityManager* entity_manager_create() {
	EntityManager* e = (EntityManager*) malloc(sizeof(EntityManager));
	assert(e != NULL);

	vector_init(&e->entities, sizeof(entity_id), MAX_ENTITIES);
	for (entity_id ent = 0; e < MAX_ENTITIES; ent++) {
		const entity_id tmp = MAX_ENTITIES - 1 - ent;
		vector_push_back(&e->entities, &tmp);
	}
	e->size = 0;
	e->top = MAX_ENTITIES - 1;
}

void entity_manager_destroy(EntityManager* e) {
	vector_close(&e->entities);
	free(e);
}

entity_id entity_manager_create_entity(EntityManager* e) {
	assert(e->size < MAX_ENTITIES);
	entity_id* ent = (entity_id*) vector_at(&e->entities, e->top);
	e->size++;
	e->top--;
	return *ent;
}

void entity_manager_destroy_entity(EntityManager* e, const entity_id ent) {
	vector_push_back(&e->entities, &ent);
	e->size--;
	e->top++;
}

void entity_manager_clear(EntityManager* e) {
	vector_clear(&e->entities);
	for (entity_id ent = 0; e < MAX_ENTITIES; ent++) {
		const entity_id tmp = MAX_ENTITIES - 1 - ent;
		vector_push_back(&e->entities, &tmp);
	}
	e->size = 0;
	e->top = MAX_ENTITIES - 1;
}

size_t entity_manager_num_entities(EntityManager* e) {
	return e->size;
}
