#ifndef POKE_ENTITY_PAIR_H
#define POKE_ENTITY_PAIR_H
#include "types.h"


typedef struct _entity_pair {
	float centery;
	entity_t entity;
} entity_pair_t;


int entity_pair_compare(const void* l, const void* r);


#endif // !POKE_ENTITY_PAIR_H
