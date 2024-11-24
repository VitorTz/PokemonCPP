#pragma once
#include <stdlib.h>
#include "vector.h"
#include "query.h"


typedef struct avl_node {
	size_t key;
	void* data;
	int height;	
	struct avl_node* left;
	struct avl_node* right;
} avl_node_t;


typedef struct avl_tree {
	avl_node_t* root;
	size_t(*hash)(const void*);	
	size_t v_size;
	size_t size;
	vector_t* vec;
} avl_tree_t;


avl_tree_t* avl_tree_create(size_t v_size, size_t(*hash)(const void*));

void avl_tree_destroy(avl_tree_t* t);

void avl_tree_insert(avl_tree_t* t, const void* key, const void* data);

void avl_tree_erase(avl_tree_t* t, const void* key);

void* avl_tree_at(avl_tree_t* t, const void* key);

void* avl_tree_allocate(avl_tree_t* t, const void* key);

void avl_tree_clear(avl_tree_t* t);

int avl_tree_is_empty(avl_tree_t* t);

size_t avl_tree_size(avl_tree_t* t);

iterator_t avl_tree_iter(avl_tree_t* t);