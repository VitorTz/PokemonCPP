#ifndef POKE_HASH_MAP_H
#define POKE_HASH_MAP_H
#include "vector.h"


typedef struct hash_map {
	vector_t buckets;
	size_t(*hash)(const void*);
	size_t n_buckets;
	size_t v_size;
	size_t size;
} hash_map_t;


hash_map_t* hash_map_create(size_t v_size, size_t n_buckets, size_t(*hash)(const void*));

void hash_map_init(
	hash_map_t* h,
	size_t v_size,
	size_t n_buckets,
	size_t(*hash)(const void*)
);


void hash_map_destroy(hash_map_t* h);

void hash_map_close(hash_map_t* h);

void* hash_map_insert(hash_map_t* h, const void* key, const void* data);

void* hash_map_at(hash_map_t* h, const void* key);

int hash_map_erase(hash_map_t* h, const void* key);

void hash_map_clear(hash_map_t* h);

size_t hash_map_size(hash_map_t* h);

int hash_map_is_empty(hash_map_t* h);

iterator_t hash_map_iter(hash_map_t* h);

#endif