#include "hash.h"


size_t hash_int(const void* p) {
	return (size_t)(*((int*)p));
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
    return (size_t)(*((entity_t*)p));
}

size_t hash_component_id(const void* p) {
    return (size_t)(*((component_t*)p));
}