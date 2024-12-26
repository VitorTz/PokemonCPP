#ifndef POKE_UTIL_H
#define POKE_UTIL_H
#include <stdint.h>
#include "types.h"


size_t hash_str(const void * p);

size_t hash_int(const void* p);

size_t hash_entity_t(const void* p);

size_t hash_component_t(const void* p);

int equal_entity_t(const void* l, const void *r);

int equal_component_t(const void* l, const void* r);


#endif // !POKE_UTIL_H
