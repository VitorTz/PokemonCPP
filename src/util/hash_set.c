#include "hash_set.h"
#include <assert.h>


void hash_set_init(
	hash_set_t* s,
	size_t v_size,
	size_t n_buckets,
	size_t(*hash)(const void*),
	int (*equal)(const void*, const void*)
) {
	s->buckets = (vector_t*)malloc(sizeof(vector_t) * n_buckets);
	assert(s->buckets != NULL);
	s->n_buckets = n_buckets;
	s->hash = hash;
	s->equal = equal;
	s->v_size = v_size;
	s->size = 0;

	for (int i = 0; i < n_buckets; i++) {
		vector_init(s->buckets + i, v_size, 4);
	}
}

hash_set_t* hash_set_create(
	size_t v_size,
	size_t n_buckets,
	size_t(*hash)(const void*),
	int (*equal)(const void*, const void*)
) {
	hash_set_t* s = (hash_set_t*)malloc(sizeof(hash_set_t));
	assert(s != NULL);
	hash_set_init(s, v_size, n_buckets, hash, equal);
	return s;
}

void hash_set_close(hash_set_t* s) {
	for (int i = 0; i < s->n_buckets; i++) {
		vector_close(s->buckets + i);
	}
	s->size = 0;
}

void hash_set_destroy(hash_set_t* s) {
	hash_set_close(s);
	free(s);
}

void hash_set_insert(hash_set_t* s, const void* data) {
	const size_t hash = s->hash(data);
	const size_t i = hash % s->n_buckets;
	vector_t* vec = s->buckets + i;
	iterator_t iter = vector_iter(vec);
	for (char* p = iter.begin; p < iter.end; p += iter.step) {
		if (s->equal(data, p)) {
			return;
		}
	}
	void* p = vector_allocate(vec);
	memcpy(p, data, s->v_size);
	s->size++;
}

void hash_set_erase(hash_set_t* s, const void* data) {
	const size_t hash = s->hash(data);	
	vector_t* vec = s->buckets + (hash % s->n_buckets);
	iterator_t iter = vector_iter(vec);
	size_t i = 0;
	for (char* p = iter.begin; p < iter.end; p += iter.step) {
		if (s->equal(data, p)) {
			vector_erase(vec, i);
			s->size--;
			return;
		}
		i++;
	}
}

int hash_set_contains(hash_set_t* s, const void* data) {
	const size_t hash = s->hash(data);
	const size_t i = hash % s->n_buckets;
	vector_t* vec = s->buckets + i;
	iterator_t iter = vector_iter(vec);
	for (char* p = iter.begin; p < iter.end; p += iter.step) {
		if (s->equal(data, p)) {
			return 1;
		}
	}
	return 0;
}

void hash_set_clear(hash_set_t* s) {
	for (vector_t* vec = s->buckets; vec < s->buckets + s->n_buckets; vec++) {
		vector_clear(vec);
	}
	s->size = 0;
}

size_t hash_set_size(const hash_set_t* s) {
	return s->size;
}

int hash_set_is_empty(const hash_set_t* s) {
	return s->size == 0;
}

iterator_t hash_set_iter(hash_set_t* s) {
	vector_t* vec_aux = globals_get_aux_vec();
	vector_clear(vec_aux);
	vector_cast(vec_aux, sizeof(void*));

	for (vector_t* v = s->buckets; v < s->buckets + s->n_buckets; v++) {
		iterator_t iter = vector_iter(v);
		for (char* p = iter.begin; p < iter.end; p += iter.step) {
			vector_push_back(vec_aux, p);
		}
	}

	return vector_iter(vec_aux);
}