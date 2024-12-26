#ifndef POKE_TEXTURE_POOL_H
#define POKE_TEXTURE_POOL_H
#include <raylib.h>


void texture_pool_init();

void texture_pool_close();

Texture2D* texture_pool_get(const char* filepath);

void texture_pool_erase(const char* filepath);

size_t texture_pool_num_textures();

#endif