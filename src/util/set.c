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

set* set_create(const size_t type_size, size_t(*hash)(const void*)) {
	set* s = (set*)malloc(sizeof(set));
	assert(s != NULL);
	s->root = NULL;
	s->hash = hash;
	s->type_size = type_size;
	vector_init(&s->iter.node_arr, sizeof(set_node_t), 256);
	return s;
}


static void set_destroy_aux(set_node_t* node) {
	if (node == NULL) {
		return;
	}
	set_destroy_aux(node->left);
	set_destroy_aux(node->right);
	free(node->data);
	free(node);
}

void set_destroy(set* s) {
	if (s == NULL) {
		return;
	}
	set_destroy_aux(s->root);
	free(s);
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

static set_node_t* set_insert_aux(set_node_t* node, size_t type_size, size_t key, const void* data) {	
	if (node == NULL) {
		return set_node_create(key, type_size, data);
	}

	if (key < node->key) {
		node->left = set_insert_aux(node->left, type_size, key, data);
	}
	else if (key > node->key) {
		node->right = set_insert_aux(node->right, type_size, key, data);
	}
	else {
		return node;
	}

	// Update height
	node->height = 1 + max(set_height(node->left), set_height(node->right));
	
	const int balance = set_get_balance(node);
	

	// Left Left Case 
	if (balance > 1 && key < node->left->key) {
		return set_right_rotate(node);
	}

	// Right Right Case 
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

void set_insert(set* s, const void* key) {
	s->root = set_insert_aux(s->root, s->type_size, s->hash(key), key);
}

static struct set_node_t* set_min_value_node(set_node_t* node) {
	set_node_t* aux = node;
	while (aux->left != NULL) {
		aux = aux->left;
	}
	return aux;
}

static set_node_t* set_erase_aux(set_node_t* node, const size_t hash) {
	// STEP 1: PERFORM STANDARD BST DELETE

	if (node == NULL) {
		return node;
	}

	// If the key to be deleted is smaller than the
	// root's key, then it lies in left subtree
	if (hash < node->key) {
		node->left = set_erase_aux(node->left, hash);
	}
	else if (hash > node->key) {
		node->right = set_erase_aux(node->right, hash);
	}	
	else {		
		if ((node->left == NULL) || (node->right == NULL)) {
			set_node_t* temp = node->left ? node->left : node->right;
			
			if (temp == NULL) {
				temp = node;
				node = NULL;
			}
			else {
				*node = *temp;
			}						
			if (temp->data != NULL) {
				free(temp->data);
			}
			free(temp);
		}
		else {			
			set_node_t*temp = set_min_value_node(node->right);			
			node->key = temp->key;
			node->right = set_erase_aux(node->right, temp->key);
		}
	}
	
	if (node == NULL) {
		return node;
	}
	
	node->height = 1 + max(set_height(node->left), set_height(node->right));
	
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

void set_erase(set* s, const void* key) {
	s->root = set_erase_aux(s->root, s->hash(key));
}

static void set_clear_aux(set_node_t* node) {
	if (node == NULL) {
		return;
	}
	set_clear_aux(node->left);
	set_clear_aux(node->right);
	free(node->data);
	free(node);
	node = NULL;
}

void set_clear(set* s) {
	set_clear_aux(s->root);	
	s->root = NULL;
}

set_iterator_t* set_iter(set* s) {
	vector_clear(&s->iter.node_arr);
	if (s->root != NULL) {
		vector_push_back(&s->iter.node_arr, s->root);
	}
	s->iter.begin = (set_node_t*) vector_begin(&s->iter.node_arr);
	s->iter.end = (set_node_t*) vector_end(&s->iter.node_arr);
	return &s->iter;
}

void* set_iter_next(set_iterator_t* iter) {		
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
	iter->end = (set_node_t*) vector_end(&iter->node_arr);
	return data;	
}