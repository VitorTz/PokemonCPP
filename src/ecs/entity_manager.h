#ifndef POKE_ENTITY_H
#define POKE_ENTITY_H
#include "../util/types.h"
#include "../util/vector.h"



typedef struct _entity_manager {
	Vector* entities;
	size_t top;
	size_t size;
} EntityManager;


EntityManager* entity_manager_create();

void entity_manager_destroy(EntityManager* entity_manager);

entity_t entity_manager_create_entity(EntityManager* entity_manager);

void entity_manager_destroy_entity(EntityManager* entity_manager, entity_t entity);

void entity_manager_clear(EntityManager* entity_manager);

size_t entity_manager_num_entities(EntityManager* entity_manager);


#endif // !POKE_ENTITY_H
