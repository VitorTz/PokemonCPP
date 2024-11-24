#include "set.h"
#include <string.h>


set_t* set_create(const size_t v_size, size_t(*hash)(const void*)) {
	set_t* s = (set_t*)malloc(sizeof(set_t));	
	s->root = NULL;
	s->hash = hash;
	s->size = 0;
	s->v_size = v_size;
	s->vec = vector_create(v_size, 16);
	return s;
}


void set_init(set_t* s, const size_t v_size, size_t (*hash)(const void*)) {
	s->root = NULL;
	s->hash = hash;
	s->v_size = v_size;
	s->size = 0;
	s->vec = vector_create(v_size, 16);
}


static void set_destroy_aux(set_node_t* node) {
	if (node == NULL) { return; }
	set_destroy_aux(node->left);
	set_destroy_aux(node->right);
	if (node->data != NULL) { free(node->data); }
	free(node);
}


void set_close(set_t* s) {
	set_destroy_aux(s->root);
	vector_destroy(s->vec);
}




void set_destroy(set_t* s) {
	set_destroy_aux(s->root);
	vector_destroy(s->vec);
	free(s);
}


static set_node_t* set_create_node(set_t* t, const size_t key, const void* data) {
	set_node_t* node = (set_node_t*)malloc(sizeof(set_node_t));
	if (node == NULL) { return NULL; }
	node->key = key;
	node->data = malloc(t->v_size);
	node->height = 0;
	node->left = NULL;
	node->right = NULL;
	memcpy(node->data, data, t->v_size);
	return node;
}


static int set_node_height(set_node_t* node) {
	if (node == NULL) {
		return 0;
	}
	return node->height;
}


static set_node_t* set_right_rotate(set_node_t* y) {
	set_node_t* x = y->left;
	set_node_t* T2 = x->right;

	x->right = y;
	y->left = T2;

	y->height = 1 + max(set_node_height(y->left), set_node_height(y->right));
	x->height = 1 + max(set_node_height(x->left), set_node_height(x->right));

	return x;
}


static set_node_t* set_left_rotate(set_node_t* x) {
	set_node_t* y = x->right;
	set_node_t* T2 = y->left;

	y->left = x;
	x->right = T2;

	x->height = 1 + max(set_node_height(x->left), set_node_height(x->right));
	y->height = 1 + max(set_node_height(y->left), set_node_height(y->right));

	return y;
}


static int set_get_balance(set_node_t* N) {
	if (N == NULL) return 0;
	return set_node_height(N->left) - set_node_height(N->right);
}


static set_node_t* set_insert_aux(
	set_t* t,
	set_node_t* node,
	const size_t key,
	const void* data
) {
	if (node == NULL) {
		t->size++;
		return set_create_node(t, key, data);
	}

	if (key < node->key) {
		node->left = set_insert_aux(t, node->left, key, data);
	}
	else if (key > node->key) {
		node->right = set_insert_aux(t, node->right, key, data);
	}
	else {
		return node;
	}

	node->height = 1 + max(set_node_height(node->left), set_node_height(node->right));

	const int balance = set_get_balance(node);

	// Left Left
	if (balance > 1 && key < node->left->key) {
		return set_right_rotate(node);
	}

	// Right Right
	if (balance < -1 && key > node->right->key) {
		return set_left_rotate(node);
	}

	// Left Right
	if (balance > 1 && key > node->left->key) {
		node->left = set_left_rotate(node->left);
		return set_right_rotate(node);
	}

	// Right Left
	if (balance < -1 && key < node->right->key) {
		node->right = set_right_rotate(node->right);
		return set_left_rotate(node);
	}

	return node;
}


void set_insert(set_t* t, const void* data) {
	t->root = set_insert_aux(t, t->root, t->hash(data), data);
}


static set_node_t* set_min_node(set_node_t* node) {
	set_node_t* current = node;
	while (current->left != NULL)
		current = current->left;
	return current;
}

static void set_copy_node(set_node_t* dst, set_node_t* src, const size_t v_size) {
	dst->key = src->key;
	dst->height = src->height;
	dst->left = src->left;
	dst->right = src->right;
	if (src->data != NULL) {
		memcpy(dst->data, src->data, v_size);
	}
}


static set_node_t* set_erase_aux(set_t* s, set_node_t* root, const size_t key) {
	if (root == NULL) return root;

	if (key < root->key) {
		root->left = set_erase_aux(s, root->left, key);
	}
	else if (key > root->key) {
		root->right = set_erase_aux(s, root->right, key);
	}
	else {
		s->size--;
		if (root->left == NULL || root->right == NULL) {
			set_node_t* temp = root->left != NULL ? root->left : root->right;
			if (temp == NULL) {
				if (root->data != NULL) {
					free(root->data);
				}
				temp = root;
				root = NULL;
			}
			else {
				*root = *temp;
			}
			free(temp);
		}
		else {
			set_node_t* temp = set_min_node(root->right);
			root->key = temp->key;
			root->right = set_erase_aux(s, root->right, temp->key);
		}
	}

	if (root == NULL) {
		return root;
	}

	root->height = 1 + max(set_node_height(root->left), set_node_height(root->right));

	const int balance = set_get_balance(root);

	// Left Left
	if (balance > 1 && set_get_balance(root->left) >= 0) {
		return set_right_rotate(root);
	}

	// Left Right Case
	if (balance > 1 && set_get_balance(root->left) < 0) {
		root->left = set_left_rotate(root->left);
		return set_right_rotate(root);
	}

	// Right Right Case
	if (balance < -1 && set_get_balance(root->right) <= 0) {
		return set_left_rotate(root);
	}

	// Right Left Case
	if (balance < -1 && set_get_balance(root->right) > 0) {
		root->right = set_right_rotate(root->right);
		return set_left_rotate(root);
	}

	return root;
}


void set_erase(set_t* t, const void* key) {
	t->root = set_erase_aux(t, t->root, t->hash(key));
}


static int set_contains_aux(set_node_t* node, const size_t key) {
	if (node == NULL) return 0;
	return node->key == key || set_contains_aux(node->left, key) || set_contains_aux(node->right, key);
}


int set_contains(set_t* s, const void* data) {	
	return set_contains_aux(s->root, s->hash(data));
}


void set_clear(set_t* t) {
	set_destroy_aux(t->root);
	t->root = NULL;
	t->size = 0;
}


int set_is_empty(set_t* t) {
	return t->root == NULL;
}


size_t set_size(set_t* t) {
	return t->size;
}


static set_iter_aux(set_node_t* node, vector_t* vec) {
	if (node == NULL) {
		return;
	}
	if (node->data != NULL) {
		vector_push_back(vec, node->data);
	}
	set_iter_aux(node->left, vec);
	set_iter_aux(node->right, vec);
}

iterator_t set_iter(set_t* t) {
	vector_clear(t->vec);
	set_iter_aux(t->root, t->vec);
	return vector_iter(t->vec);
}