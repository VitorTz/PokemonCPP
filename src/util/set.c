#include "set.h"
#include <math.h>


static set_node_t* set_node_create(const size_t key, const size_t type_size, const void* data) {
	set_node_t* node = (set_node_t*)malloc(sizeof(set_node_t));
	assert(node != NULL);
	node->data = malloc(type_size);
	assert(node->data != NULL);
	node->left = NULL;
	node->right = NULL;
	node->key = key;
	node->height = 1;
	memcpy(node->data, data, type_size);
	return node;
}

static void destroy_node(set_node_t* node) {
	if (node == NULL) {
		return;
	}
	destroy_node(node->left);
	destroy_node(node->right);
	free(node->data);
	free(node);
}

inline static int set_height(set_node_t* node) {
	if (node == NULL) {
		return 0;
	}
	return node->height;
}

static set_node_t* set_right_rotate(set_node_t* y) {
	set_node_t* x = y->left;
	set_node_t* T2 = x->right;

	// Perform rotation 
	x->right = y;
	y->left = T2;

	// Update heights 
	y->height = 1 + max(set_height(y->left), set_height(y->right));
	x->height = 1 + max(set_height(x->left), set_height(x->right));

	// Return new root 
	return x;
}

static set_node_t* set_left_rotate(set_node_t* x) {
	set_node_t* y = x->right;
	set_node_t* T2 = y->left;

	// Perform rotation 
	y->left = x;
	x->right = T2;

	// Update heights 
	x->height = 1 + max(set_height(x->left), set_height(x->right));
	y->height = 1 + max(set_height(y->left), set_height(y->right));

	// Return new root 
	return y;
}


static int set_get_balance(set_node_t* node) {
	if (node == NULL) {
		return 0;
	}
	return set_height(node->left) - set_height(node->right);
}

set* set_create(const size_t type_size, size_t(*hash)(const void*)) {
	set* s = (set*)malloc(sizeof(set));
	assert(s != NULL);
	s->root = NULL;
	s->info = (set_info){
		hash,
		type_size,
		0
	};	
	return s;
}

void set_destroy(set* s) {
	if (s == NULL) {
		return;
	}	
	destroy_node(s->root);
	free(s);
}

static set_node_t* set_insert_aux(set_node_t* node, size_t type_size, size_t key, const void* data) {
	// Perform the normal BST insertion
	if (node == NULL)
		return set_node_create(key, type_size, data);

	if (key < node->key) {
		node->left = insert(node->left, key);
	}
	else if (key > node->key) {
		node->right = insert(node->right, key);
	}
	else {
		return node;
	}

	// Update height of this ancestor node 
	node->height = 1 + max(set_height(node->left), set_height(node->right));

	// Get the balance factor of this ancestor node 
	int balance = set_get_balance(node);
	

	// Left Left Case 
	if (balance > 1 && key < node->left->key)
		return rightRotate(node);

	// Right Right Case 
	if (balance < -1 && key > node->right->key)
		return leftRotate(node);

	// Left Right Case 
	if (balance > 1 && key > node->left->key) {
		node->left = leftRotate(node->left);
		return rightRotate(node);
	}

	// Right Left Case 
	if (balance < -1 && key < node->right->key) {
		node->right = rightRotate(node->right);
		return leftRotate(node);
	}

	// Return the (unchanged) node pointer 
	return node;
}

void set_insert(set* s, const void* key) {

}