#ifndef POKE_SET_H
#define POKE_SET_H
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include "vector.h"


typedef struct _set_node {
	struct _set_node* left;
	struct _set_node* right;
	size_t key;
	void* data;
	int height;
} set_node_t;


typedef struct _set_iterator {
	vector node_arr;
	set_node_t* begin;
	set_node_t* end;	
} set_iterator_t;

typedef struct _set {
	set_node_t* root;
	size_t(*hash)(const void*);
	size_t type_size;	
	set_iterator_t iter;
} set;


set* set_create(size_t type_size, size_t(*hash)(const void*));

void set_destroy(set* s);

void set_insert(set* s, const void* key);

void set_erase(set* s, const void* key);

void set_clear(set* s);

set_iterator_t* set_iter(set* s);

void* set_iter_next(set_iterator_t* iter);


#endif // !POKE_SET_H
