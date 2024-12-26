#ifndef POKE_SET_H
#define POKE_SET_H
#include "vector.h"


typedef struct __set_iterator {
	vector_t* begin;
	vector_t* end;
	size_t size;
} set_iterator_t;


typedef struct __set {
	vector_t* buckets;
	size_t(*hash)(const void*);	
	size_t n_buckets;
	size_t type_size;
	size_t size;
} set_t;


void set_init(set_t* set, size_t type_size, size_t n_buckets, size_t (*hash)(const void*));

void set_close(set_t* set);

void set_insert(set_t* set, const void* data);

void set_erase(set_t* set, const void* data);

int set_contains(set_t* set, const void* data);

void set_clear(set_t* set);

set_iterator_t set_iter(set_t* set);


#endif // !POKE_SET_H

