#ifndef POKE_SET_H
#define POKE_SET_H
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <math.h>
#include "vector.h"


typedef struct _set_node {
	struct _set_node* left;
	struct _set_node* right;
	size_t key;	
	void* data;
	int height;
} SetNode;


typedef struct _set_iterator {
	Vector* node_arr;
	SetNode* begin;
	SetNode* end;
	size_t size;
} SetIterator;

typedef struct _set {
	SetNode* root;
	size_t (*hash)(const void*);
	size_t type_size;	
	size_t size;
	SetIterator iter;
} Set;


Set* set_create(size_t type_size, size_t(*hash)(const void*));

void set_init(Set* set, size_t type_size, size_t(*hash)(const void*));

void set_destroy(Set* s);

void set_close(Set* set);

void set_insert(Set* s, const void* key);

void set_erase(Set* s, const void* key);

void set_clear(Set* s);

SetIterator* set_iter(Set* s);

void* set_iter_next(SetIterator* iter);


#endif // !POKE_SET_H
