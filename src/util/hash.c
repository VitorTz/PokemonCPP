#include "hash.h"
#include "types.h"


size_t hash_int(const void* p) {
	return *((int*)p);
}

size_t hash_str(const void* p) {
    const char* str = (const char*)p;
    size_t hash = 0;
    while (*str) {
        hash = hash * 31 + *str;
        ++str;
    }
    return hash;
}

size_t hash_entity_id(const void* p) {
    return *((entity_t*)p);
}

size_t hash_component_id(const void* p) {
    return *((component_t*)p);
}