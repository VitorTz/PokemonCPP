#pragma once
#include "avl_tree.h"
#include <raylib.h>


void texture_pool_init();

Texture2D texture_pool_get(const char* s);

void texture_pool_erase(const char* s);

void texture_pool_close();