#include "avl_tree.h"
#include <string.h>


avl_tree_t* avl_tree_create(const size_t v_size, size_t(*hash)(const void*)) {
	avl_tree_t* tree = (avl_tree_t*)malloc(sizeof(avl_tree_t));
	if (tree == NULL) { return NULL; }
	tree->root = NULL;
	tree->hash = hash;	
	tree->v_size = v_size;
	tree->vec = vector_create(v_size, 16);
	return tree;
}


static void avl_tree_destroy_aux(avl_node_t* node) {
	if (node == NULL) { return; }
	avl_tree_destroy_aux(node->left);
	avl_tree_destroy_aux(node->right);
	if (node->data != NULL) { free(node->data); }
	free(node);
}


void avl_tree_destroy(avl_tree_t* t) {
	avl_tree_destroy_aux(t->root);
	vector_destroy(t->vec);
	free(t);
}


static avl_node_t* avl_tree_create_node(avl_tree_t* t, const size_t key, const void* data) {
	avl_node_t* node = (avl_node_t*)malloc(sizeof(avl_node_t));
	if (node == NULL) { return NULL; }
	node->key = key;
	node->data = malloc(t->v_size);
	node->height = 0;
	node->left = NULL;
	node->right = NULL;	
	memcpy(node->data, data, t->v_size);
	return node;
}


static avl_node_t* avl_tree_create_empty_node(avl_tree_t* t, const size_t key, void* new_data) {
	avl_node_t* node = (avl_node_t*)malloc(sizeof(avl_node_t));
	if (node == NULL) { return NULL; }
	node->key = key;
	node->data = malloc(t->v_size);
	node->height = 0;
	node->left = NULL;
	node->right = NULL;	
	new_data = node->data;
	return node;
}


static int avl_tree_node_height(avl_node_t* node) {
	if (node == NULL) {
		return 0;
	}
	return node->height;
}


static avl_node_t* avl_tree_right_rotate(avl_node_t* y) {
	avl_node_t* x = y->left;
	avl_node_t* T2 = x->right;	
	
	x->right = y;
	y->left = T2;

	y->height = 1 + max(avl_tree_node_height(y->left), avl_tree_node_height(y->right));
	x->height = 1 + max(avl_tree_node_height(x->left), avl_tree_node_height(x->right));

	return x;
}


static avl_node_t* avl_tree_left_rotate(avl_node_t* x) {
	avl_node_t* y = x->right;
	avl_node_t* T2 = y->left;
	
	y->left = x;
	x->right = T2;
	
	x->height = 1 + max(avl_tree_node_height(x->left), avl_tree_node_height(x->right));
	y->height = 1 + max(avl_tree_node_height(y->left), avl_tree_node_height(y->right));
	
	return y;
}


static int avl_tree_get_balance(avl_node_t* N) {
	if (N == NULL) return 0;
	return avl_tree_node_height(N->left) - avl_tree_node_height(N->right);
}


static avl_node_t* avl_tree_insert_aux(
	avl_tree_t* t, 
	avl_node_t* node, 
	const size_t key, 
	const void* data
) {	
	if (node == NULL) {
		t->size++;
		return avl_tree_create_node(t, key, data);
	}		

	if (key < node->key) {
		node->left = avl_tree_insert_aux(t, node->left, key, data);
	} else if (key > node->key) {
		node->right = avl_tree_insert_aux(t, node->right, key, data);
	} else {
		return node;
	}
	
	node->height = 1 + max(avl_tree_node_height(node->left), avl_tree_node_height(node->right));
	
	const int balance = avl_tree_get_balance(node);
	
	// Left Left
	if (balance > 1 && key < node->left->key) {
		return avl_tree_right_rotate(node);
	}

	// Right Right
	if (balance < -1 && key > node->right->key) {
		return avl_tree_left_rotate(node);
	}

	// Left Right
	if (balance > 1 && key > node->left->key) {
		node->left = avl_tree_left_rotate(node->left);
		return avl_tree_right_rotate(node);
	}

	// Right Left
	if (balance < -1 && key < node->right->key) {
		node->right = avl_tree_right_rotate(node->right);
		return avl_tree_left_rotate(node);
	}
	
	return node;
}


void avl_tree_insert(avl_tree_t* t, const void* key, const void* data) {	
	t->root = avl_tree_insert_aux(t, t->root, t->hash(key), data);
}


static avl_node_t* avl_tree_allocate_aux(
	avl_tree_t* t,
	avl_node_t* node,
	const size_t key,
	void* new_data
) {
	if (node == NULL) {
		t->size++;
		return avl_tree_create_empty_node(t, key, new_data);
	}

	if (key < node->key) {
		node->left = avl_tree_allocate_aux(t, node->left, key, new_data);
	}
	else if (key > node->key) {
		node->right = avl_tree_allocate_aux(t, node->right, key, new_data);
	}
	else {
		return node;
	}

	node->height = 1 + max(avl_tree_node_height(node->left), avl_tree_node_height(node->right));

	const int balance = avl_tree_get_balance(node);

	// Left Left
	if (balance > 1 && key < node->left->key) {
		return avl_tree_right_rotate(node);
	}

	// Right Right
	if (balance < -1 && key > node->right->key) {
		return avl_tree_left_rotate(node);
	}

	// Left Right
	if (balance > 1 && key > node->left->key) {
		node->left = avl_tree_left_rotate(node->left);
		return avl_tree_right_rotate(node);
	}

	// Right Left
	if (balance < -1 && key < node->right->key) {
		node->right = avl_tree_right_rotate(node->right);
		return avl_tree_left_rotate(node);
	}

	return node;
}


void* avl_tree_allocate(avl_tree_t* t, const void* key) {
	void* p = avl_tree_at(t, t->hash(key));
	if (p != NULL) {
		return p;
	}
	p = malloc(t->v_size);
	t->root = avl_tree_allocate_aux(t, t->root, t->hash(key), p);
	return p;
}

static avl_node_t* avl_tree_min_node(avl_node_t* node) {
	avl_node_t* current = node;	
	while (current->left != NULL)
		current = current->left;
	return current;
}

static void avl_tree_copy_node(avl_node_t* dst, avl_node_t* src, const size_t v_size) {
	dst->key = src->key;
	dst->height = src->height;
	dst->left = src->left;
	dst->right = src->right;
	if (src->data != NULL) {
		memcpy(dst->data, src->data, v_size);
	}
}


static avl_node_t* avl_tree_erase_aux(avl_tree_t* t, avl_node_t* root, const size_t key) {	
	if (root == NULL) return root;
	
	if (key < root->key) {
		root->left = avl_tree_erase_aux(t, root->left, key);
	} else if (key > root->key) {
		root->right = avl_tree_erase_aux(t, root->right, key);
	} else {
		t->size--;
		if (root->left == NULL || root->right == NULL) {
			avl_node_t* temp = root->left != NULL ? root->left : root->right;			
			if (temp == NULL) {
				if (root->data != NULL) {
					free(root->data);
				}
				temp = root;
				root = NULL;
			} else {
				*root = *temp;				
			}			
			free(temp);
		} else {
			avl_node_t* temp = avl_tree_min_node(root->right);
			root->key = temp->key;			
			root->right = avl_tree_erase_aux(t, root->right, temp->key);
		}
	}
	
	if (root == NULL) {
		return root;
	}
	
	root->height = 1 + max(avl_tree_node_height(root->left), avl_tree_node_height(root->right));

	const int balance = avl_tree_get_balance(root);

	// Left Left
	if (balance > 1 && avl_tree_get_balance(root->left) >= 0) {
		return avl_tree_right_rotate(root);
	}

	// Left Right Case
	if (balance > 1 && avl_tree_get_balance(root->left) < 0) {
		root->left = avl_tree_left_rotate(root->left);
		return avl_tree_right_rotate(root);
	}

	// Right Right Case
	if (balance < -1 && avl_tree_get_balance(root->right) <= 0) {
		return avl_tree_left_rotate(root);
	}

	// Right Left Case
	if (balance < -1 && avl_tree_get_balance(root->right) > 0) {
		root->right = avl_tree_right_rotate(root->right);
		return avl_tree_left_rotate(root);
	}

	return root;
}


void avl_tree_erase(avl_tree_t* t, const void* key) {
	t->root = avl_tree_erase_aux(t, t->root, t->hash(key));
}


void* avl_tree_at(avl_tree_t* t, const void* key) {
	avl_node_t* node = t->root;
	const size_t k = t->hash(key);

	while (1) {
		if (node == NULL) {
			return NULL;
		}
		if (node->key == k) {
			return node->data;
		}
		if (k < node->key) {
			node = node->left;
		} else {
			node = node->right;
		}
	}
}


void avl_tree_clear(avl_tree_t* t) {
	avl_tree_destroy_aux(t->root);
	t->root = NULL;
	t->size = 0;
}


int avl_tree_is_empty(avl_tree_t* t) {
	return t->root == NULL;
}


size_t avl_tree_size(avl_tree_t* t) {
	return t->size;
}


static avl_tree_iter_aux(avl_node_t* node, vector_t* vec) {
	if (node == NULL) {
		return;
	}
	avl_tree_iter_aux(node->left, vec);
	avl_tree_iter_aux(node->right, vec);
	if (node->data != NULL) {
		vector_push_back(vec, node->data);
	}
}

iterator_t avl_tree_iter(avl_tree_t* t) {
	vector_clear(t->vec);
	avl_tree_iter_aux(t->root, t->vec);
	return vector_iter(t->vec);
}