#include <stdio.h>
#include "hash_map.h"
#include "texture_pool.h"
#include "util.h"


#define NUM_BUCKETS 128


static hash_map_t texture_pool = { 0 };


void texture_pool_init() {
	hash_map_init(
		&texture_pool,
		sizeof(Texture2D),
		NUM_BUCKETS,
		hash_str
	);
}

void texture_pool_close() {
	texture_pool_clear();
	vector_close(&texture_pool.buckets);
}

Texture2D* texture_pool_get(const char* filepath) {
	Texture2D* texture_ptr = (Texture2D*) hash_map_at(&texture_pool, filepath);
	if (texture_ptr == NULL) {
		Texture t = LoadTexture(filepath);
		texture_ptr = hash_map_insert(&texture_pool, filepath, &t);
		printf("New Texture Loaded -> %s\n", filepath);
	}
	return texture_ptr;
}

void texture_pool_erase(const char* filepath) {
	Texture2D* t = hash_map_at(&texture_pool, filepath);
	if (t != NULL) {
		UnloadTexture(*t);
		hash_map_erase(&texture_pool, filepath);
	}
}

void texture_pool_clear() {
	iterator_t iter = hash_map_iter(&texture_pool);
	for (char* p = iter.begin; p < iter.end; p += iter.step) {
		UnloadTexture(*((Texture2D*)p));
	}
	hash_map_clear(&texture_pool);	
}

size_t texture_pool_size() {
	return texture_pool.size;
}
