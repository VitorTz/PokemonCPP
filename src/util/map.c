#include "map.h"


map_iterator_t map_iter(map_t* map) {
	const map_iterator_t iter = {
		map->buckets,
		map->buckets + map->n_buckets,
		map->n_buckets
	};
	return iter;
}

void map_init(
	map_t* map,
	const size_t type_size,
	const size_t n_buckets,
	const size_t(*hash)(const void*)
) {
	map->hash = hash;
	map->n_buckets = n_buckets;
	map->type_size = type_size;
	map->size = 0;
	map->buckets = (vector_t*)malloc(sizeof(vector_t) * n_buckets);
	assert(map->buckets != NULL);
	map_iterator_t iter = map_iter(map);
	for (vector_t* v = iter.begin; v < iter.end; v++) {
		vector_init(v, sizeof(size_t) + type_size, 4);
	}
}

void map_close(map_t* map) {
	if (map == NULL) {
		return;
	}
	map_iterator_t iter = map_iter(map);
	for (vector_t* v = iter.begin; v < iter.end; v++) {
		vector_close(v);
	}
	if (map->buckets != NULL) {
		free(map->buckets);
	}
}

void map_insert(map_t* map, const void* key, const void* value) {
	const size_t hash = map->hash(key);
	const size_t ibucket = hash % map->n_buckets;
	vector_t* vec = map->buckets + ibucket;
	vector_iterator_t iter = vector_iter(vec);
	for (char* p = iter.begin; p < iter.end; p += iter.step) {
		if (*((size_t*)(p + map->type_size)) == hash) {
			return;
		}
	}
	char* p = (char*)vector_allocate(vec);
	memcpy(p, value, map->type_size);
	memcpy(p + map->type_size, &hash, sizeof(size_t));	
	map->size++;	
}

void* map_at(map_t* map, const void* key) {
	const size_t hash = map->hash(key);
	const size_t ibucket = hash % map->n_buckets;
	vector_t* vec = map->buckets + ibucket;
	vector_iterator_t iter = vector_iter(vec);
	for (char* p = iter.begin; p < iter.end; p += iter.step) {
		if (*((size_t*)(p + map->type_size)) == hash) {
			return p;
		}
	}
	return NULL;
}

void map_erase(map_t* map, const void* key) {
	const size_t hash = map->hash(key);
	const size_t ibucket = hash % map->n_buckets;
	vector_t* vec = map->buckets + ibucket;
	vector_iterator_t iter = vector_iter(vec);
	size_t i = 0;
	for (char* p = iter.begin; p < iter.end; p += iter.step) {
		if (*((size_t*)(p + map->type_size)) == hash) {
			vector_erase(vec, i);
			map->size--;
			return;
		}
		i++;
	}
}

int map_contains(map_t* map, const void* key) {
	const size_t hash = map->hash(key);
	const size_t ibucket = hash % map->n_buckets;
	vector_t* vec = map->buckets + ibucket;
	vector_iterator_t iter = vector_iter(vec);
	for (char* p = iter.begin; p < iter.end; p += iter.step) {
		if (*((size_t*)(p + map->type_size)) == hash) {
			return 1;
		}
	}
	return 0;
}

void map_clear(map_t* map) {
	map_iterator_t iter = map_iter(map);
	for (vector_t* v = iter.begin; v < iter.end; v++) {
		vector_clear(v);
	}
	map->size = 0;
}
