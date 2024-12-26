#include "entity_pair.h"


int entity_pair_compare(const void* l, const void* r) {
	const float a = ((const entity_pair_t*)l)->centery;
	const float b = ((const entity_pair_t*)r)->centery;
	return (a > b) - (a < b);
}