#ifndef POKE_TEXTURE_POOL_H
#define POKE_TEXTURE_POOL_H
#include <raylib.h>


void texture_pool_init();

Texture2D* texture_pool_get(const char* filepath);

void texture_pool_clear();

void texture_pool_erase(const char* filepath);

void texture_pool_close();

size_t texture_pool_num_unique_textures();

#endif // !POKE_TEXTURE_POOL_H
