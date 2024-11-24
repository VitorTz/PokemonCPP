#pragma once
#include <assert.h>
#include "../constants.h"
#include "../util/types.h"
#include "../util/vector.h"


typedef struct entity_manager {
	vector_t* vec;
	size_t top;
	size_t size;
} entity_manager_t;


entity_manager_t* entity_manager_create();

void entity_manager_destroy(entity_manager_t* ent);

entity_t entity_manager_create_entity(entity_manager_t* ent);

void entity_manager_destroy_entity(entity_manager_t* ent, entity_t e);

void entity_manager_clear(entity_manager_t* ent);

size_t entity_manager_num_entities(entity_manager_t* ent);