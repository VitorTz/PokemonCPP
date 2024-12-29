#include "set.h"


void set_init(
	set_t* set,
	const size_t type_size,
	const size_t n_buckets,
	size_t(*hash)(const void*)
) {
	set->size = 0;
	set->type_size = type_size;
	set->n_buckets = n_buckets;
	set->hash = hash;
	set->buckets = (vector_t*)malloc(sizeof(vector_t) * n_buckets);
	assert(set->buckets != NULL);
	for (vector_t* v = set->buckets; v < set->buckets + n_buckets; v++) {
		vector_init(v, sizeof(size_t) + type_size, 4);
	}
}

void set_close(set_t* set) {
	for (vector_t* v = set->buckets; v < set->buckets + set->n_buckets; v++) {
		vector_close(v);
	}
	free(set->buckets);
}

void set_insert(set_t* set, const void* data) {
	const size_t hash = set->hash(data);
	vector_t* v = set->buckets + (hash % set->n_buckets);	
	for (char* p = vector_begin(v); p < vector_end(v); p += v->type_size) {
		const size_t* other_hash = (const size_t*) (p + set->type_size);
		if (*other_hash == hash) {
			return;
		}
	}
	char* p = (char*) vector_allocate(v);
	memcpy(p, data, set->type_size);
	memcpy(p + set->type_size, &hash, sizeof(size_t));
	set->size++;
}

void set_erase(set_t* set, const void* data) {
	const size_t hash = set->hash(data);
	vector_t* v = set->buckets + (hash % set->n_buckets);	
	size_t i = 0;
	for (char* p = vector_begin(v); p < vector_end(v); p += v->type_size) {
		const size_t* other_hash = (const size_t*)(p + set->type_size);
		if (*other_hash == hash) {
			vector_erase(v, i);
			set->size--;
			return;
		}
		i++;
	}
}

void set_clear(set_t* set) {
	for (vector_t* v = set->buckets; v < set->buckets + set->n_buckets; v++) {
		vector_clear(v);
	}
}

vector_t* set_begin(set_t* set) {
	return set->buckets;
}

vector_t* set_end(set_t* set) {
	return set->buckets + set->n_buckets;
}
