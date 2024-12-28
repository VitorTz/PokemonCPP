#include "texture_pool.h"
#include "map.h"
#include "util.h"

static map_t pool = { 0 };


void texture_pool_init() {
	map_init(&pool, sizeof(Texture2D), 256, hash_str);
}

void texture_pool_close() {
	for (vector_t* v = map_begin(&pool); v < map_end(&pool); v++) {
		for (char* p = vector_begin(v); p < vector_end(v); p += v->type_size) {
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
		p_texture = (Texture2D*) map_at(&pool, filepath);
	}
	return p_texture;
}
