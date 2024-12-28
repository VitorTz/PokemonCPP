#include "texture_pool.h"
#include "map.h"
#include "util.h"

static map_t pool = { 0 };


void texture_pool_init() {
	map_init(&pool, sizeof(Texture2D), 256, hash_str);
}

void texture_pool_close() {
	for (vector_t* v = pool.buckets; v < pool.buckets + pool.n_buckets; v++) {
		iter_t iter = vector_iter(v);
		for (char* p = iter.begin; p < iter.end; p += iter.step) {
			UnloadTexture(*((Texture2D*)p));
		}
	}	
	map_close(&pool);
}

Texture2D* texture_pool_get(const char* filepath) {
	Texture2D* p_texture = (Texture2D*) map_at(&pool, filepath);
	if (p_texture == NULL) {
		Texture2D t = LoadTexture(filepath);
		map_insert(&pool, filepath, &t);
		Texture2D* p_texture = (Texture2D*) map_at(&pool, filepath);
	}
	return p_texture;
}
