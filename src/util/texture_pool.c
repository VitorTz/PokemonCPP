#include "texture_pool.h"
#include "hash.h"
#include "map.h"

static Map* pool = NULL;

void texture_pool_init() {
	pool = map_create(sizeof(Texture2D), hash_str);
}

void texture_pool_close() {
	MapIterator* iter = map_iter(pool);
	Texture2D* t;
	while ((t = (Texture2D*)map_iter_next(iter)) != NULL) {
		UnloadTexture(*t);
	}
	map_destroy(pool);
}

Texture2D* texture_pool_get(const char* filepath) {
	Texture2D* t = map_at(pool, filepath);
	if (t == NULL) {
		const Texture2D new_texture = LoadTexture(filepath);
		map_insert(pool, filepath, &new_texture);
		t = (Texture2D*) map_at(pool, filepath);
	}
	return t;
}

void texture_pool_erase(const char* filepath) {
	const Texture2D* t = map_at(pool, filepath);
	if (t != NULL) {
		UnloadTexture(*t);
		map_erase(pool, filepath);
	}
}

void texture_pool_clear() {
	MapIterator* iter = map_iter(pool);
	Texture2D* t;
	while ((t = (Texture2D*) map_iter_next(iter)) != NULL) {
		UnloadTexture(*t);
	}
	map_clear(pool);
}

size_t texture_pool_num_unique_textures() {
	return pool->size;
}
