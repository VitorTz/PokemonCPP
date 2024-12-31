#ifndef POKE_SET_H
#define POKE_SET_H
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>


typedef struct _set_node {
	struct _set_node* left;
	struct _set_node* right;
	size_t hash;
	void* data;
	int height;
} set_node_t;


typedef struct _set_info {
	size_t(*hash)(const void*);
	size_t type_size;
	size_t size;
} set_info;


typedef struct _set {
	set_node_t* root;
	set_info info;
} set;


set* set_create(size_t type_size, size_t(*hash)(const void*));

void set_destroy(set* s);

void set_insert(set* s, const void* key);

void set_erase(set* s, const void* key);

void set_clear(set* s);

void* set_begin(set* s);

void* set_end(set* s);


#endif // !POKE_SET_H
