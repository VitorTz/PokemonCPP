#include "util.h"


size_t hash_int(const void* p) {
	const size_t ret = *((int*)p);
	return ret;
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

size_t hash_entity_t(const void* p) {
	const size_t hash = *((entity_t*)p);
	return hash;
}

size_t hash_component_t(const void* p) {
	const size_t hash = *((component_t*)p);
	return hash;
}