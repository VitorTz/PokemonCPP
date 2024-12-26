#ifndef POKE_ENTITY_PAIR_H
#define POKE_ENTITY_PAIR_H
#include "types.h"


typedef struct entity_pair {
	float centery;
	entity_t e;
} entity_pair_t;


int entity_pair_compare(const void* l, const void* r);


#endif