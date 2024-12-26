#ifndef POKE_COMPONENTS_H
#define POKE_COMPONENTS_H
#include <raylib.h>
#include "../util/types.h"


#define NUM_COMPONENTS 3
#define NUM_UPDATABLE_COMPONENTS 1
#define NUM_DRAWABLE_COMPONENTS 2

#define TRANSFORM_ID 0
#define SPRITE_ID 1
#define SPRITE_ANIMATION_ID 2


typedef struct transform {
	Vector2 pos;
	Vector2 size;
	zindex_t zindex;
} transform_t;


typedef struct sprite {
	Texture2D* texture;
} sprite_t;

typedef struct sprite_animation {
	Texture2D* texture;
} sprite_animation_t;


void transform_init(transform_t* t, zindex_t zindex);

void sprite_init(sprite_t* s, const char* filepath);



#endif