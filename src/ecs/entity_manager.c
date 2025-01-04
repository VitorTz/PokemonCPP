#include <assert.h>
#include <stdlib.h>
#include "entity_manager.h"
#include "../constants.h"


EntityManager* entity_manager_create() {
	EntityManager* entity_manager = (EntityManager*) malloc(sizeof(EntityManager));
	assert(entity_manager != NULL);
	
	entity_manager->entities = vector_create(sizeof(entity_t), MAX_ENTITIES);
	for (entity_t ent = 0; ent < (entity_t) MAX_ENTITIES; ent++) {
		const entity_t tmp = MAX_ENTITIES - 1 - ent;
		vector_push_back(entity_manager->entities, &tmp);
	}
	entity_manager->size = 0;
	entity_manager->top = MAX_ENTITIES - 1;
	return entity_manager;
}

void entity_manager_destroy(EntityManager* entity_manager) {
	vector_destroy(entity_manager->entities);
	free(entity_manager);
}

entity_t entity_manager_create_entity(EntityManager* entity_manager) {
	assert(entity_manager->size < MAX_ENTITIES);
	const entity_t* entity = (entity_t*) vector_at(entity_manager->entities, entity_manager->top--);
	entity_manager->size++;	
	return *entity;
}

void entity_manager_destroy_entity(EntityManager* entity_manager, const entity_t entity) {
	vector_push_back(entity_manager->entities, &entity);
	entity_manager->size--;
	entity_manager->top++;
}

void entity_manager_clear(EntityManager* entity_manager) {
	vector_clear(entity_manager->entities);
	for (entity_t ent = 0; ent < (entity_t) MAX_ENTITIES; ent++) {
		const entity_t tmp = MAX_ENTITIES - 1 - ent;
		vector_push_back(entity_manager->entities, &tmp);
	}
	entity_manager->size = 0;
	entity_manager->top = MAX_ENTITIES - 1;
}

size_t entity_manager_num_entities(const EntityManager* entity_manager) {
	return entity_manager->size;
}
