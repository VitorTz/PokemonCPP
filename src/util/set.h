#ifndef POKE_SET_H
#define POKE_SET_H
#include "vector.h"


typedef struct _set {
	vector_t* buckets;
	size_t size;
	size_t type_size;
	size_t n_buckets;
	size_t(*hash)(const void*);
} set_t;


void set_init(set_t* set, size_t type_size, size_t n_buckets, size_t(*hash)(const void*));

void set_close(set_t* set);

void set_insert(set_t* set, const void* data);

void set_erase(set_t* set, const void* data);

void set_clear(set_t* set);

vector_t* set_begin(set_t* set);

vector_t* set_end(set_t* set);

#endif // !POKE_SET_H
