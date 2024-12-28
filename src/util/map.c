#include "map.h"


void map_init(
	map_t* map,
	const size_t type_size,
	const size_t n_buckets,
	const size_t(*hash)(const void*)
) {
	map->size = 0;
	map->type_size = type_size;
	map->n_buckets = n_buckets;
	map->buckets = (vector_t*)malloc(sizeof(vector_t) * n_buckets);
	for (vector_t* v = map->buckets; v < map->buckets + map->n_buckets; v++) {
		vector_init(v, sizeof(size_t) + map->type_size, 4);
	}
}

void map_close(map_t* map) {
	for (vector_t* v = map->buckets; v < map->buckets + map->n_buckets; v++) {
		vector_close(v);
	}
}

void map_insert(map_t* map, const void* key, const void* data) {
	const size_t hash = map->hash(key);
	vector_t* v = map->buckets + (hash & map->n_buckets);
	iter_t iter = vector_iter(v);
	for (char* p = iter.begin; p < iter.end; p += iter.step) {
		const size_t* other_hash = (const size_t*)(p + map->type_size);
		if (other_hash == hash) {
			return;
		}
	}
	char* p = (char*)vector_allocate(v);
	memcpy(p, data, map->type_size);
	memcpy(p + sizeof(size_t), &hash, sizeof(size_t));
	map->size++;
	return;
}

void* map_at(map_t* map, const void* key) {
	const size_t hash = map->hash(key);
	vector_t* v = map->buckets + (hash & map->n_buckets);
	iter_t iter = vector_iter(v);
	for (char* p = iter.begin; p < iter.end; p += iter.step) {
		const size_t* other_hash = (const size_t*)(p + map->type_size);
		if (other_hash == hash) {
			return p;
		}
	}
	return NULL;
}

void map_erase(map_t* map, const void* key) {
	const size_t hash = map->hash(key);
	vector_t* v = map->buckets + (hash & map->n_buckets);
	size_t i = 0;
	iter_t iter = vector_iter(v);
	for (char* p = iter.begin; p < iter.end; p += iter.step) {
		const size_t* other_hash = (const size_t*)(p + map->type_size);
		if (other_hash == hash) {
			vector_erase(v, i);
			map->size--;
			return;
		}
		i++;
	}
}

void map_clear(map_t* map) {
	for (vector_t* v = map->buckets; v < map->buckets + map->n_buckets; v++) {
		vector_clear(v);
	}
	map->size = 0;
}

iter_t map_iter(map_t* map) {
	const iter_t iter = {
		map->buckets,
		map->buckets + map->n_buckets,
		1
	};
	return iter;
}