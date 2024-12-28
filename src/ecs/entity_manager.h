#ifndef POKE_ENTITY_MANAGER_H
#define POKE_ENTITY_MANAGER_H
#include "../util/types.h"


typedef struct _entity_manager {
	entity_t* entities;
	size_t top;
	size_t size;
} entity_manager_t;

void entity_manager_init(entity_manager_t* e);

void entity_manager_close(entity_manager_t* e);

entity_t entity_manager_create_entity(entity_manager_t* e);

void entity_manager_destroy_entity(entity_manager_t* e, entity_t ent);

void entity_manager_clear(entity_manager_t* e);


#endif // !POKE_ENTITY_MANAGER_H
