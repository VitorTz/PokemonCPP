#include "texture_pool.h"
#include "map.h"
#include "util.h"


static map_t map;


void texture_pool_init() {
	map_init(&map, sizeof(Texture2D), 256, hash_str);
}

void texture_pool_close() {
	map_iterator_t iter = map_iter(&map);
	for (vector_t* v = iter.begin; v < iter.end; v++) {
		vector_iterator_t v_iter = vector_iter(v);
		for (char* p = v_iter.begin; p < v_iter.end; p += v_iter.step) {
			UnloadTexture(*((Texture2D*)p));
		}
	}
	map_clear(&map);
}

Texture2D* texture_pool_get(const char* filepath) {
	Texture2D* pTexture = (Texture2D*) map_at(&map, filepath);
	if (pTexture == NULL) {
		Texture2D t = LoadTexture(filepath);
		map_insert(&map, filepath, &t);		
		pTexture = (Texture2D*) map_at(&map, filepath);
	}
	return pTexture;
}


void texture_pool_erase(const char* filepath) {
	Texture2D* pTexture = (Texture2D*)map_at(&map, filepath);
	if (pTexture != NULL) {
		UnloadTexture(*pTexture);
		map_erase(&map, filepath);		
	}
}

size_t texture_pool_num_textures() {
	return map.size;
}
