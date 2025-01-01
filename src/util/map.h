#ifndef POKE_MAP_H
#define POKE_MAP_H
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include "vector.h"


typedef struct _map_node {
	struct _map_node* left;
	struct _map_node* right;
	size_t key;	
	void* data;
	int height;
} map_node_t;

typedef struct _map_iterator {
	Vector node_arr;
	map_node_t* begin;
	map_node_t* end;
} map_iterator_t;


typedef struct _map {
	map_node_t* root;	
	size_t(*hash)(const void*);
	size_t type_size;
	size_t size;
	map_iterator_t iter;
} Map;


Map* map_create(size_t type_size, size_t(*hash)(const void*));

void map_destroy(Map* map);

void map_insert(Map* map, const void* key, const void* value);

void* map_at(Map* map, const void* key);

int map_contains(Map* map, const void* key);

void map_erase(Map* map, const void* key);

void map_clear(Map* map);

map_iterator_t* map_iter(Map* map);

void* map_iter_next(map_iterator_t* iter);


#endif // !POKE_MAP_H
