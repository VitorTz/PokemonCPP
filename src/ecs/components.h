#pragma once
#include <raylib.h>
#include "../util/types.h"


#define NUM_COMPONENTS 3
#define TRANSFORM_ID 0
#define SPRITE_ID 1
#define SPRITE_ANIMATION_ID 2


typedef struct transform {
	Vector2 pos;
	Vector2 size;
	zindex_t zindex;
} transform_t;


typedef struct sprite {
	Texture2D texture;
} sprite_t;


typedef struct sprite_animation {
	Texture2D texture;
	Rectangle rect;
	uint8_t frame;
	uint8_t max_frame;
	uint8_t index;
	uint8_t max_index;
} sprite_animation_t;