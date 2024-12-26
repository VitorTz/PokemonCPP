#ifndef POKE_HASH_SET_H
#define POKE_HASH_SET_H
#include <stdlib.h>
#include "vector.h"
#include "globals.h"


typedef struct hash_set {
	vector_t* buckets;
	size_t v_size;
	size_t n_buckets;
	size_t size;
	size_t(*hash)(const void*);
	int (*equal)(const void*, const void*);
} hash_set_t;


hash_set_t* hash_set_create(
	size_t v_size,
	size_t n_buckets,
	size_t(*hash)(const void*),
	int (*equal)(const void*, const void*)
);

void hash_set_init(
	hash_set_t* s,
	size_t v_size,
	size_t n_buckets,
	size_t(*hash)(const void*),
	int (*equal)(const void*, const void*)
);

void hash_set_destroy(hash_set_t* s);

void hash_set_close(hash_set_t* s);

void hash_set_insert(hash_set_t* s, const void* data);

void hash_set_erase(hash_set_t* s, const void* data);

void hash_set_clear(hash_set_t* s);

int hash_set_contains(hash_set_t* s, const void* data);

size_t hash_set_size(const hash_set_t* s);

int hash_set_is_empty(const hash_set_t* s);

iterator_t hash_set_iter(hash_set_t* s);


#endif