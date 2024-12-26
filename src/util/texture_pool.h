#ifndef POKE_TEXTURE_POOL_H
#define POKE_TEXTURE_POOL_H
#include <stdint.h>
#include <raylib.h>


void texture_pool_init();

Texture2D* texture_pool_get(const char* filepath);

void texture_pool_erase(const char* filepath);

void texture_pool_clear();

size_t texture_pool_size();

void texture_pool_close();


#endif // !POKE_TEXTURE_POOL_H
