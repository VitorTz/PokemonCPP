#include "entity_manager.h"
#include <assert.h>


void entity_manager_init(entity_manager_t* e) {
	vector_init(&e->entities, sizeof(entity_t), MAX_ENTITIES);
	entity_manager_clear(e);
}

void entity_manager_close(entity_manager_t* e) {
	vector_close(&e->entities);
	e->top = 0;
	e->size = 0;
}

entity_t entity_manager_create_entity(entity_manager_t* e) {
	assert(e->size < MAX_ENTITIES);
	const entity_t* ent = (entity_t*) vector_at(&e->entities, e->top--);
	e->size++;
	return *ent;
}

void entity_manager_destroy_entity(entity_manager_t* e, const entity_t ent) {
	vector_push_back(&e->entities, &ent);
	e->top++;
	e->size--;
}

void entity_manager_clear(entity_manager_t* e) {
	vector_clear(&e->entities);
	for (entity_t ent = MAX_ENTITIES; ent > 0; ent--) {
		const entity_t tmp = ent - 1;
		vector_push_back(&e->entities, &tmp);
	}
	e->top = MAX_ENTITIES - 1;
	e->size = 0;
}

size_t entity_manager_num_alive_entities(const entity_manager_t* e) {
	return e->size;
}