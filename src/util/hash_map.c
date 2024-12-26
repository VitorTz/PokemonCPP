#include <assert.h>
#include "globals.h"
#include "hash_map.h"


void hash_map_init(
	hash_map_t* h,
	const size_t v_size,
	const size_t n_buckets,
	const size_t(*hash)(const void*)
) {
	vector_init(&h->buckets, sizeof(vector_t), n_buckets);
	for (size_t i = 0; i < n_buckets; i++) {
		vector_t* vec = (vector_t*) vector_allocate(&h->buckets);
		vector_init(vec, sizeof(size_t) + v_size, 4);
	}
	h->hash = hash;
	h->n_buckets = n_buckets;
	h->v_size = v_size;
	h->size = 0;
}

hash_map_t* hash_map_create(
	const size_t v_size, 
	const size_t n_buckets, 
	size_t(*hash)(const void*)
) {
	hash_map_t* h = (hash_map_t*)malloc(sizeof(hash_map_t));
	assert(h != NULL);
	hash_map_init(h, v_size, n_buckets, hash);
	return h;
}

void hash_map_close(hash_map_t* h) {
	const iterator_t iter = vector_iter(&h->buckets);
	const vector_t* begin = (vector_t*)iter.begin;
	const vector_t* end = (vector_t*)iter.end;
	for (vector_t* v = begin; v < end; v++) {
		vector_close(v);
	}
	vector_close(&h->buckets);
}

void hash_map_destroy(hash_map_t* h) {
	hash_map_close(h);
	free(h);
}

void* hash_map_insert(hash_map_t* h, const void* key, const void* data) {
	const size_t hash = h->hash(key);
	const size_t ibucket = hash % h->n_buckets;
	vector_t* vec = vector_at(&h->buckets, ibucket);
	const iterator_t iter = vector_iter(vec);

	for (char* p = iter.begin; p < iter.end; p += iter.step) {
		if (*((size_t*)p) == hash) {
			return p + sizeof(size_t);
		}
	}
	char* p = (char*) vector_allocate(vec);
	*((size_t*)p) = hash;
	void* ret = p + sizeof(size_t);
	memcpy(ret, data, h->v_size);
	h->size++;
	return ret;
}

void* hash_map_at(hash_map_t* h, const void* key) {
	const size_t hash = h->hash(key);
	const size_t ibucket = hash % h->n_buckets;
	vector_t* vec = vector_at(&h->buckets, ibucket);
	const iterator_t iter = vector_iter(vec);
	
	for (char* p = iter.begin; p < iter.end; p += iter.step) {
		if (*((size_t*)p) == hash) {
			return p + sizeof(size_t);
		}
	}
	return NULL;
}

int hash_map_erase(hash_map_t* h, const void* key) {
	const size_t hash = h->hash(key);
	const size_t ibucket = hash % h->n_buckets;
	vector_t* vec = vector_at(&h->buckets, ibucket);
	const iterator_t iter = vector_iter(vec);
	size_t i = 0;
	for (char* p = iter.begin; p < iter.end; p += iter.step) {
		if (*((size_t*)p) == hash) {
			vector_erase(vec, i);
			h->size--;
			return 1;
		}
		i++;
	}
	return 0;
}

void hash_map_clear(hash_map_t* h) {
	iterator_t iter = vector_iter(&h->buckets);
	vector_t* begin = (vector_t*)iter.begin;
	vector_t* end = (vector_t*)iter.end;
	for (vector_t* v = begin; v < end; v++) {
		vector_clear(v);
	}
	h->size = 0;
}

size_t hash_map_size(hash_map_t* h) {
	return h->size;
}

int hash_map_is_empty(hash_map_t* h) {
	return h->size == 0;
}

iterator_t hash_map_iter(hash_map_t* h) {	
	vector_t* aux_vec = globals_get_aux_vec();
	vector_clear(&aux_vec);
	vector_cast(aux_vec, sizeof(void*));

	iterator_t iter = vector_iter(&h->buckets);
	vector_t* begin = (vector_t*)iter.begin;
	vector_t* end = (vector_t*)iter.end;

	for (vector_t* v = begin; v < end; v++) {
		iter = vector_iter(v);
		for (char* p = iter.begin; p < iter.end; p += iter.step) {
			vector_push_back(aux_vec, p + sizeof(size_t));
		}
	}

	return vector_iter(aux_vec);
}