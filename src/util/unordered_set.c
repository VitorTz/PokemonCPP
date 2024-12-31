#include "unordered_set.h"


unordered_set* unordered_set_create(const size_t type_size, size_t (*hash)(const void*)) {
	unordered_set* set = (unordered_set*)malloc(sizeof(unordered_set));
	assert(set != NULL);
	set->hash = hash;
	set->type_size = type_size;
	set->size = 0;
	for (int i = 0; i < SET_NBUCKETS; i++) {
		vector_init(set->buckets + i, sizeof(size_t) + type_size, 4);
	}
	return set;
}

void unordered_set_destroy(unordered_set* set) {
	if (set == NULL) { return; }
	for (int i = 0; i < SET_NBUCKETS; i++) {
		vector_close(set->buckets + i);
	}
	free(set);
}

void unordered_set_insert(unordered_set* set, const void* key) {
	const size_t hash = set->hash(key);
	vector* vec = set->buckets + (hash % SET_NBUCKETS);
	for (char* p = vector_begin(vec); p < vector_end(vec); p += vec->type_size) {
		if (
			*((size_t*)(p + set->type_size)) == hash
		) {
			return;
		}
	}
	char* p = (char*) vector_allocate(vec);
	memcpy(p, key, set->type_size);
	memcpy(p + set->type_size, &hash, sizeof(size_t));
	set->size++;
}

void unordered_set_erase(unordered_set* set, const void* key) {
	const size_t hash = set->hash(key);
	vector* vec = set->buckets + (hash % SET_NBUCKETS);
	size_t i = 0;
	for (char* p = vector_begin(vec); p < vector_end(vec); p += vec->type_size) {
		if (
			*((size_t*)(p + vec->type_size)) == hash
			) {
			vector_erase(vec, i);
			set->size--;
			return;
		}
		i++;
	}
}

void unordered_set_clear(unordered_set* set) {
	for (int i = 0; i < SET_NBUCKETS; i++) {
		vector_clear(set->buckets + i);
	}
	set->size = 0;
}

vector* unordered_set_begin(unordered_set* set) {
	return set->buckets;
}

vector* unordered_set_end(unordered_set* set) {
	return set->buckets + SET_NBUCKETS;
}