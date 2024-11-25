#pragma once
#include "types.h"


typedef struct tile {
	float x;
	float y;
	float width;
	float height;
	int objid;
	zindex_t zindex;
	int terrain;
	int n;
	char direction;
} tile_t;