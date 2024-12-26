#include "util.h"


size_t hash_str(const void* p) {
    const char* str = (const char*)p;
    size_t hash = 0;
    while (*str) {
        hash = hash * 31 + *str;
        ++str;
    }
    return hash;
}

size_t hash_int(const void* p) {    
    const size_t hash = *((const int*)p);
    return hash;
}

size_t hash_entity_t(const void* p) {
    const size_t hash = *((const entity_t*)p);
    return hash;
}

size_t hash_component_t(const void* p) {
    const size_t hash = *((const component_t*)p);
    return hash;
}


int equal_entity_t(const void* l, const void* r) {
    return *((entity_t*)l) == *((entity_t*)r);
}

int equal_component_t(const void* l, const void* r) {
    return *((component_t*)l) == *((component_t*)r);
}