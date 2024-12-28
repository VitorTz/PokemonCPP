#ifndef POKE_MAP_H
#define POKE_MAP_H
#include "vector.h"


typedef struct _map {
	vector_t* buckets;
	size_t size;
	size_t type_size;
	size_t n_buckets;
	size_t(*hash)(const void*);
} map_t;


void map_init(map_t* map, size_t type_size, size_t n_buckets, size_t(*hash)(const void*));

void map_close(map_t* map);

void map_insert(map_t* map, const void* key, const void* data);

void* map_at(map_t* map, const void* key);

void map_erase(map_t* map, const void* key);

void map_clear(map_t* map);

iter_t map_iter(map_t* map);


#endif // !POKE_MAP_H
