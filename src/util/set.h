#pragma once
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "vector.h"


typedef struct set_node {
	size_t key;
	void* data;
	int height;
	struct set_node* left;
	struct set_node* right;
} set_node_t;


typedef struct set {
	set_node_t* root;
	size_t(*hash)(const void*);
	size_t v_size;
	size_t size;
	vector_t* vec;
} set_t;


set_t* set_create(size_t v_size, size_t(*hash)(const void*));

void set_init(set_t* s, size_t v_size, size_t (*hash)(const void*));

void set_close(set_t* s);

void set_destroy(set_t* s);

void set_insert(set_t* s, const void* data);

void set_erase(set_t* s, const void* data);

int set_contains(set_t* s, const void* data);

void set_clear(set_t* s);

int set_is_empty(set_t* s);

size_t set_size(set_t* s);

iterator_t set_iter(set_t* s);