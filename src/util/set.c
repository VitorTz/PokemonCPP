#include "set.h"


set_iterator_t set_iter(set_t* set) {
	set_iterator_t iter = {
		set->buckets,
		set->buckets + set->n_buckets,
		set->n_buckets
	};
	return iter;
}

void set_init(
	set_t* set, 
	const size_t type_size, 
	const size_t n_buckets,
	size_t(*hash)(const void*)
) {
	set->n_buckets = n_buckets;
	set->type_size = type_size;
	set->hash = hash;
	set->size = 0;
	set->buckets = (vector_t*)malloc(sizeof(vector_t) * n_buckets);	
	assert(set->buckets != NULL);
	set_iterator_t iter = set_iter(set);
	for (vector_t* v = iter.begin; v < iter.end; v++) {
		vector_init(v, sizeof(size_t) + type_size, 4);
	}
}

void set_close(set_t* set) {
	set_iterator_t iter = set_iter(set);
	for (vector_t* v = iter.begin; v < iter.end; v++) {
		vector_close(v);
	}
	free(set->buckets);
}

void set_insert(set_t* set, const void* data) {
	const size_t hash = set->hash(data);
	const size_t ibucket = hash % set->n_buckets;
	vector_t* vec = set->buckets + ibucket;
	vector_iterator_t iter = vector_iter(vec);
	for (char* p = iter.begin; p < iter.end; p += iter.step) {
		if (*((size_t*)(p + set->type_size)) == hash) {
			return;
		}
	}
	char* p = (char*)vector_allocate(vec);
	memcpy(p, data, set->type_size);
	memcpy(p + set->type_size, &hash, sizeof(size_t));	
	set->size++;
}

void set_erase(set_t* set, const void* data) {
	const size_t hash = set->hash(data);
	const size_t ibucket = hash % set->n_buckets;
	vector_t* vec = set->buckets + ibucket;
	vector_iterator_t iter = vector_iter(vec);
	size_t i = 0;
	for (char* p = iter.begin; p < iter.end; p += iter.step) {
		if (*((size_t*)(p + set->type_size)) == hash) {
			vector_erase(vec, i);
			set->size--;
			return;
		}
		i++;
	}
}

int set_contains(set_t* set, const void* data) {
	const size_t hash = set->hash(data);
	const size_t ibucket = hash % set->n_buckets;
	vector_t* vec = set->buckets + ibucket;
	vector_iterator_t iter = vector_iter(vec);
	for (char* p = iter.begin; p < iter.end; p += iter.step) {
		if (*((size_t*)(p + set->type_size)) == hash) {
			return 1;
		}
	}
	return 0;
}

void set_clear(set_t* set) {
	set_iterator_t iter = set_iter(set);
	for (vector_t* v = iter.begin; v < iter.end; v++) {
		vector_clear(v);
	}
	set->size = 0;
}
