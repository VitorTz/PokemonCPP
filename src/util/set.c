#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include "util.h"
#include "set.h"


static SetNode* set_node_create(const size_t key, const size_t type_size, const void* data) {
	SetNode* node = malloc(sizeof(SetNode));
	assert(node != NULL);

	node->data = malloc(type_size);
	assert(node->data != NULL);
	memcpy(node->data, data, type_size);

	node->left = NULL; node->right = NULL;
	node->key = key;	
	node->height = 1;
	return node;
}

void set_init(Set* set, const size_t type_size, size_t(*hash)(const void*)) {
	assert(set != NULL);
	set->root = NULL;
	set->hash = hash;
	set->type_size = type_size;
	set->size = 0;

	// Set Iter
	set->iter.node_arr = vector_create(sizeof(SetNode), 256);	
	set->iter.begin = (SetNode*)vector_begin(set->iter.node_arr);
	set->iter.end = (SetNode*)vector_end(set->iter.node_arr);	
}

Set* set_create(const size_t type_size, size_t (*hash)(const void*)) {	
	Set* set = (Set*) malloc(sizeof(Set));
	set_init(set, type_size, hash);
	return set;
}

static void set_destroy_aux(SetNode* node) {
	if (node == NULL) { return; }
	set_destroy_aux(node->left);
	set_destroy_aux(node->right);
	free(node->data);
	free(node);
}

void set_close(Set* set) {
	if (set == NULL) { return; }	
	vector_destroy(set->iter.node_arr);
	set_destroy_aux(set->root);
	set->root = NULL;
	set->size = 0;
}

void set_destroy(Set* set) {
	if (set == NULL) { return; }
	set_close(set);
	free(set);
}

static int set_height(const SetNode* node) {
	if (node == NULL) return 0;
	else return node->height;
}

static SetNode* set_right_rotate(SetNode* y) {
	SetNode* x = y->left;
	SetNode* T2 = x->right;
	
	x->right = y;
	y->left = T2;

	y->height = 1 + max_int(set_height(y->left), set_height(y->right));
	x->height = 1 + max_int(set_height(x->left), set_height(x->right));
	
	return x;
}

static SetNode* set_left_rotate(SetNode* x) {
	SetNode* y = x->right;
	SetNode* T2 = y->left;

	y->left = x;
	x->right = T2;
	
	x->height = 1 + max_int(set_height(x->left), set_height(x->right));
	y->height = 1 + max_int(set_height(y->left), set_height(y->right));
	
	return y;
}


inline static int set_get_balance(SetNode* node) {
	if (node == NULL) return 0;
	else return set_height(node->left) - set_height(node->right);	
}

static SetNode* set_insert_aux(Set* set, SetNode* node, const size_t key, const void* data) {	
	if (node == NULL) { 
		set->size++;
		return set_node_create(key, set->type_size, data);
	}

	if (key < node->key) {
		node->left = set_insert_aux(set, node->left, key, data);
	}
	else if (key > node->key) {
		node->right = set_insert_aux(set, node->right, key, data);
	}
	else {
		return node;
	}
	
	node->height = 1 + max_int(set_height(node->left), set_height(node->right));
	
	const int balance = set_get_balance(node);
	
	// Left Case
	if (balance > 1 && key < node->left->key) {
		return set_right_rotate(node);
	}

	// Right Case
	if (balance < -1 && key > node->right->key) {
		return set_left_rotate(node);
	}

	// Left Right Case 
	if (balance > 1 && key > node->left->key) {
		node->left = set_left_rotate(node->left);
		return set_right_rotate(node);
	}

	// Right Left Case 
	if (balance < -1 && key < node->right->key) {
		node->right = set_right_rotate(node->right);
		return set_left_rotate(node);
	}
	
	return node;
}

void set_insert(Set* set, const void* key) {
	set->root = set_insert_aux(set, set->root, set->hash(key), key);
}

inline static SetNode* set_min_left_subtree(SetNode* node) {
	SetNode* aux = node;
	while (aux->left != NULL)
		aux = aux->left;
	return aux;
}

static SetNode* set_erase_aux(Set* set, SetNode* node, const size_t hash) {
	if (node == NULL) {
		return node;
	}

	if (hash == node->key) {
		if (node->left == NULL && node->right == NULL) {
			free(node->data);
			free(node);
			set->size--;
			return NULL;
		}
		if (node->left == NULL) {
			SetNode* tmp = node->right;
			free(node->data);
			free(node);
			set->size--;
			return tmp;
		}
		if (node->right == NULL) {
			SetNode* tmp = node->left;
			free(node->data);
			free(node);
			set->size--;
			return tmp;
		}
		const SetNode* tmp = set_min_left_subtree(node->right);
			
		node->key = tmp->key;
		memcpy(node->data, tmp->data, set->type_size);
		node->right = set_erase_aux(set, node->right, tmp->key);
	} 
	else if (hash < node->key) {
		node->left = set_erase_aux(set, node->left, hash);
	}
	else {
		node->right = set_erase_aux(set, node->right, hash);
	}
	
	node->height = 1 + max_int(set_height(node->left), set_height(node->right));
	
	const int balance = set_get_balance(node);
	
	if (balance > 1 && set_get_balance(node->left) >= 0) {
		return set_right_rotate(node);
	}
	
	if (balance > 1 && set_get_balance(node->left) < 0) {
		node->left = set_left_rotate(node->left);
		return set_right_rotate(node);
	}
	
	if (balance < -1 && set_get_balance(node->right) <= 0) {
		return set_left_rotate(node);
	}
		
	if (balance < -1 && set_get_balance(node->right) > 0) {
		node->right = set_right_rotate(node->right);
		return set_left_rotate(node);
	}

	return node;
}

void set_erase(Set* set, const void* key) {
	set->root = set_erase_aux(set, set->root, set->hash(key));
}

static void set_clear_aux(SetNode* node) {
	if (node == NULL) { return; }
	set_clear_aux(node->left);
	set_clear_aux(node->right);
	free(node->data);
	free(node);	
	node = NULL;
}

void set_clear(Set* set) {
	set_clear_aux(set->root);
	set->root = NULL;
	set->size = 0;
}

SetIterator* set_iter(Set* set) {
	vector_clear(set->iter.node_arr);
	vector_reserve(set->iter.node_arr, set->size);
	if (set->root != NULL) {
		vector_push_back(set->iter.node_arr, set->root);
	}
	set->iter.begin = (SetNode*) vector_begin(set->iter.node_arr);
	set->iter.end = (SetNode*) vector_end(set->iter.node_arr);	
	return &set->iter;
}

void* set_iter_next(SetIterator* iter) {		
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
	iter->end = (SetNode*) vector_end(iter->node_arr);
	return data;	
}