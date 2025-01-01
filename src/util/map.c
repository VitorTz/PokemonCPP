#include "map.h"

Map* map_create(size_t type_size, size_t(*hash)(const void*)) {
	// Map
	Map* map = (Map*)malloc(sizeof(Map));
	assert(map != NULL);
	map->root = NULL;
	map->hash = hash;
	map->type_size = type_size;
	map->size = 0;
	
	// Map Iter
	vector_init(&map->iter.node_arr, sizeof(map_node_t), 256);
	map->iter.begin = (map_node_t*)vector_begin(&map->iter.node_arr);
	map->iter.end = (map_node_t*)vector_end(&map->iter.node_arr);
	return map;
}

static void map_destroy_aux(map_node_t* node) {
	if (node == NULL) { return; }
	map_destroy_aux(node->left);
	map_destroy_aux(node->right);
	free(node->data);
	free(node);
}

void map_destroy(Map* map) {
	vector_close(&map->iter.node_arr);
	map_destroy_aux(map->root);
	free(map);
}

static map_node_t* map_node_create(const size_t key, const size_t type_size, const void* data) {
	map_node_t* node = (map_node_t*)malloc(sizeof(map_node_t));
	assert(node != NULL);

	node->data = malloc(type_size);
	assert(node->data != NULL);
	memcpy(node->data, data, type_size);

	node->left = NULL; node->right = NULL;
	node->key = key;	
	node->height = 1;
	return node;
}

inline static map_node_t* map_min_left_subtree(map_node_t* node) {
	map_node_t* aux = node;
	while (aux->left != NULL)
		aux = aux->left;
	return aux;
}


inline static int map_height(map_node_t* node) {
	if (node == NULL) return 0;
	else return node->height;
}

static map_node_t* map_right_rotate(map_node_t* y) {
	map_node_t* x = y->left;
	map_node_t* T2 = x->right;

	x->right = y;
	y->left = T2;

	y->height = 1 + max(map_height(y->left), map_height(y->right));
	x->height = 1 + max(map_height(x->left), map_height(x->right));

	return x;
}

static map_node_t* map_left_rotate(map_node_t* x) {
	map_node_t* y = x->right;
	map_node_t* T2 = y->left;

	y->left = x;
	x->right = T2;

	x->height = 1 + max(map_height(x->left), map_height(x->right));
	y->height = 1 + max(map_height(y->left), map_height(y->right));

	return y;
}

inline static int map_get_balance(map_node_t* node) {
	if (node == NULL) return 0;
	else return map_height(node->left) - map_height(node->right);
}

static map_node_t* map_insert_aux(Map* map, map_node_t* node, const size_t key, const void* value) {
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
	
	node->height = 1 + max(map_height(node->left), map_height(node->right));

	const int balance = map_get_balance(node);

	// Left Left Case 
	if (balance > 1 && key < node->left->key) {
		return map_right_rotate(node);
	}

	// Right Right Case 
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

void* map_at(Map* map, const void* key) {
	const size_t hash = map->hash(key);
	map_node_t* node = map->root;

	while (node != NULL) {		
		if (hash < node->key) {
			node = node->left;
		} 
		else if (node->key > hash) {
			node = node->right;
		}
		else {
			return node->data;
		}
	}
	return NULL;
}

int map_contains(Map* map, const void* key) {
	const size_t hash = map->hash(key);
	map_node_t* node = map->root;

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

static map_node_t* map_erase_aux(Map* map, map_node_t* node, const size_t key) {
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
		else if (node->left == NULL) {
			map_node_t* tmp = node->right;
			free(node->data);
			free(node);
			map->size--;
			return tmp;
		}
		else if (node->right == NULL) {
			map_node_t* tmp = node->left;
			free(node->data);
			free(node);
			map->size--;
			return tmp;
		}
		else {
			map_node_t* tmp = map_min_left_subtree(node->right);

			node->key = tmp->key;
			memcpy(node->data, tmp->data, map->type_size);

			node->right = map_erase_aux(map, node->right, tmp->key);
		}
	}
	else if (key < node->key) {
		node->left = map_erase_aux(map, node->left, key);
	}
	else {
		node->right = map_erase_aux(map, node->right, key);
	}

	node->height = 1 + max(map_height(node->left), map_height(node->right));

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

static void map_clear_aux(map_node_t* node) {
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

map_iterator_t* map_iter(Map* map) {
	vector_clear(&map->iter.node_arr);
	vector_reserve(&map->iter.node_arr, map->size);
	if (map->root != NULL) {
		vector_push_back(&map->iter.node_arr, map->root);
	}
	map->iter.begin = (map_node_t*)vector_begin(&map->iter.node_arr);
	map->iter.end = (map_node_t*)vector_end(&map->iter.node_arr);
	return &map->iter;
}

void* map_iter_next(map_iterator_t* iter) {
	if (iter->begin >= iter->end) {
		return NULL;
	}
	void* data = iter->begin->data;
	if (iter->begin->left != NULL) {
		vector_push_back(&iter->node_arr, iter->begin->left);
	}
	if (iter->begin->right != NULL) {
		vector_push_back(&iter->node_arr, iter->begin->right);
	}
	iter->begin++;
	iter->end = (map_node_t*) vector_end(&iter->node_arr);
	return data;
}
