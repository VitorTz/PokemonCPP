#ifndef POKE_HASH_H
#define POKE_HASH_H
#include <stddef.h>


size_t hash_entity_id(const void* p);

size_t hash_component_id(const void* p);

size_t hash_int(const void* p);

size_t hash_str(const void* p);


#endif // !POKE_HASH_H
