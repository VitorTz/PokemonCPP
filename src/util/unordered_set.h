#ifndef POKE_SET_H
#define POKE_SET_H
#include "vector.h"


#define SET_NBUCKETS 1024


typedef struct _set {
	vector buckets[SET_NBUCKETS];
	size_t(*hash)(const void*);
	size_t type_size;
	size_t size;
} unordered_set;


unordered_set* unordered_set_create(size_t type_size, size_t(*hash)(const void*));

void unordered_set_destroy(unordered_set* set);

void unordered_set_insert(unordered_set* set, const void* key);

void unordered_set_erase(unordered_set* set, const void* key);

void unordered_set_clear(unordered_set* set);

vector* unordered_set_begin(unordered_set* set);

vector* unordered_set_end(unordered_set* set);


#endif // !POKE_SET_H
