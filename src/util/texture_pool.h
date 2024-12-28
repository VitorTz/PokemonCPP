#ifndef POKE_TEXTURE_POOL_H
#define POKE_TEXTURE_POOL_H
#include <raylib.h>


void texture_pool_init();

void texture_pool_close();

Texture2D* texture_pool_get(const char* filepath);


#endif // !POKE_TEXTURE_POOL_H
