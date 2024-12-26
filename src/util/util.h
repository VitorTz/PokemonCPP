#ifndef POKE_UTIL_H
#define POKE_UTIL_H
#include <stddef.h>
#include "types.h"


size_t hash_str(const void* p);

size_t hash_int(const void* p);

size_t hash_entity_t(const void* p);

size_t hash_component_t(const void* p);


#endif