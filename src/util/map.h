#ifndef POKE_MAP_H
#define POKE_MAP_H
#include "vector.h"


typedef struct __map_iterator {
	vector_t* begin;
	vector_t* end;
	size_t size;
} map_iterator_t;

typedef struct __map {
	vector_t* buckets;
	size_t(*hash)(const void*);
	size_t n_buckets;
	size_t type_size;
	size_t size;
} map_t;

void map_init(map_t* map, size_t type_size, size_t n_buckets, size_t(*hash)(const void*));

void map_close(map_t* map);

void map_insert(map_t* map, const void* key, const void* value);

void* map_at(map_t* map, const void* key);

void map_erase(map_t* map, const void* key);

int map_contains(map_t* map, const void* key);

void map_clear(map_t* map);

map_iterator_t map_iter(map_t* map);


#endif