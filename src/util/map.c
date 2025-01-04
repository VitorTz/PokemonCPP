#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include "util.h"
#include "map.h"


Map* map_create(const size_t type_size, size_t(*hash)(const void*)) {
	// Map
	Map* map = malloc(sizeof(Map));
	assert(map != NULL);
	
	map->root = NULL;
	map->hash = hash;
	map->type_size = type_size;
	map->size = 0;
	
	// Map Iter
	map->iter.node_arr = vector_create(sizeof(MapNode), 256);	
	map->iter.begin = (MapNode*)vector_begin(map->iter.node_arr);
	map->iter.end = (MapNode*)vector_end(map->iter.node_arr);	
	return map;
}

static void map_destroy_aux(MapNode* node) {
	if (node == NULL) { return; }
	map_destroy_aux(node->left);
	map_destroy_aux(node->right);
	free(node->data);
	free(node);
}

void map_destroy(Map* map) {
	vector_destroy(map->iter.node_arr);	
	map_destroy_aux(map->root);
	free(map);
}

static MapNode* map_node_create(const size_t key, const size_t type_size, const void* data) {
	MapNode* node = malloc(sizeof(MapNode));
	assert(node != NULL);

	node->data = malloc(type_size);
	assert(node->data != NULL);
	memcpy(node->data, data, type_size);

	node->left = NULL; node->right = NULL;
	node->key = key;	
	node->height = 1;
	return node;
}

static MapNode* map_min_left_subtree(MapNode* node) {
	MapNode* aux = node;
	while (aux->left != NULL)
		aux = aux->left;
	return aux;
}


static int map_height(const MapNode* node) {
	if (node == NULL) return 0;
	else return node->height;
}

static MapNode* map_right_rotate(MapNode* y) {
	MapNode* x = y->left;
	MapNode* T2 = x->right;

	x->right = y;
	y->left = T2;

	y->height = 1 + max_int(map_height(y->left), map_height(y->right));
	x->height = 1 + max_int(map_height(x->left), map_height(x->right));

	return x;
}

static MapNode* map_left_rotate(MapNode* x) {
	MapNode* y = x->right;
	MapNode* T2 = y->left;

	y->left = x;
	x->right = T2;

	x->height = 1 + max_int(map_height(x->left), map_height(x->right));
	y->height = 1 + max_int(map_height(y->left), map_height(y->right));

	return y;
}

static int map_get_balance(const MapNode* node) {
	if (node == NULL) return 0;
	else return map_height(node->left) - map_height(node->right);
}

static MapNode* map_insert_aux(Map* map, MapNode* node, const size_t key, const void* value) {
	if (node == NULL) {
		map->size++;
		return map_node_create(key, map->type_size, value);
	}

	if (key < node->key) {
		node->left = map_insert_aux(map, node->left, key, value);
	}
	else if (key > node->key) {
		node->right = map_insert_aux(map, node->right, key, value);
	}
	else {
		return node;
	}
	
	node->height = 1 + max_int(map_height(node->left), map_height(node->right));

	const int balance = map_get_balance(node);

	// Left Case
	if (balance > 1 && key < node->left->key) {
		return map_right_rotate(node);
	}

	// Right Case
	if (balance < -1 && key > node->right->key) {
		return map_left_rotate(node);
	}

	// Left Right Case 
	if (balance > 1 && key > node->left->key) {
		node->left = map_left_rotate(node->left);
		return map_right_rotate(node);
	}

	// Right Left Case 
	if (balance < -1 && key < node->right->key) {
		node->right = map_right_rotate(node->right);
		return map_left_rotate(node);
	}

	return node;
}

void map_insert(Map* map, const void* key, const void* value) {
	map->root = map_insert_aux(map, map->root, map->hash(key), value);
}

void* map_at(const Map* map, const void* key) {
	const size_t hash = map->hash(key);
	const MapNode* node = map->root;

	while (node != NULL) {		
		if (hash < node->key)
			node = node->left;		
		else if (hash > node->key)
			node = node->right;
		else 
			return node->data;
	}
	return NULL;
}

int map_contains(const Map* map, const void* key) {
	const size_t hash = map->hash(key);
	const MapNode* node = map->root;

	while (node != NULL) {
		if (hash < node->key) {
			node = node->left;
		}
		else if (node->key > hash) {
			node = node->right;
		}
		else {
			return 1;
		}
	}
	return 0;
}

static MapNode* map_erase_aux(Map* map, MapNode* node, const size_t key) {
	if (node == NULL) {
		return node;
	}

	if (key == node->key) {
		if (node->left == NULL && node->right == NULL) {
			free(node->data);
			free(node);
			map->size--;
			return NULL;
		}
		if (node->left == NULL) {
			MapNode* tmp = node->right;
			free(node->data);
			free(node);
			map->size--;
			return tmp;
		}
		if (node->right == NULL) {
			MapNode* tmp = node->left;
			free(node->data);
			free(node);
			map->size--;
			return tmp;
		}
		const MapNode* tmp = map_min_left_subtree(node->right);

		node->key = tmp->key;
		memcpy(node->data, tmp->data, map->type_size);

		node->right = map_erase_aux(map, node->right, tmp->key);
	}
	else if (key < node->key) {
		node->left = map_erase_aux(map, node->left, key);
	}
	else {
		node->right = map_erase_aux(map, node->right, key);
	}

	node->height = 1 + max_int(map_height(node->left), map_height(node->right));

	const int balance = map_get_balance(node);

	if (balance > 1 && map_get_balance(node->left) >= 0) {
		return map_right_rotate(node);
	}

	if (balance > 1 && map_get_balance(node->left) < 0) {
		node->left = map_left_rotate(node->left);
		return map_right_rotate(node);
	}

	if (balance < -1 && map_get_balance(node->right) <= 0) {
		return map_left_rotate(node);
	}

	if (balance < -1 && map_get_balance(node->right) > 0) {
		node->right = map_right_rotate(node->right);
		return map_left_rotate(node);
	}

	return node;
}

void map_erase(Map* map, const void* key) {
	map->root = map_erase_aux(map, map->root, map->hash(key));
}

static void map_clear_aux(MapNode* node) {
	if (node == NULL) { return; }
	map_clear_aux(node->left);
	map_clear_aux(node->right);
	free(node->data);
	free(node);	
}

void map_clear(Map* map) {
	map_clear_aux(map->root);
	map->root = NULL;
	map->size = 0;
}

MapIterator* map_iter(Map* map) {
	vector_clear(map->iter.node_arr);
	vector_reserve(map->iter.node_arr, map->size);
	if (map->root != NULL) {
		vector_push_back(map->iter.node_arr, map->root);
	}
	map->iter.begin = (MapNode*)vector_begin(map->iter.node_arr);
	map->iter.end = (MapNode*)vector_end(map->iter.node_arr);	
	return &map->iter;
}

void* map_iter_next(MapIterator* iter) {
	if (iter->begin >= iter->end) {
		return NULL;
	}
	void* data = iter->begin->data;
	if (iter->begin->left != NULL) {
		vector_push_back(iter->node_arr, iter->begin->left);
	}
	if (iter->begin->right != NULL) {
		vector_push_back(iter->node_arr, iter->begin->right);
	}
	iter->begin++;
	iter->end = (MapNode*) vector_end(iter->node_arr);
	return data;
}
