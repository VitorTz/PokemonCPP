#ifndef POKE_COMPONENTS_H
#define POKE_COMPONENTS_H
#include <raylib.h>
#include "../util/types.h"


#define NUM_COMPONENTS 3
#define NUM_DRAWABLE_COMPONENTS 2


typedef struct _transform {
	Vector2 pos;
	Vector2 size;
	zindex_t zindex;
} Transform;

typedef struct _sprite {
	Texture2D* texture;
} Sprite;


typedef struct _sprite_animation {
	Texture2D* texture;
	Rectangle texture_rect;
	uint8_t current_frame;
	uint8_t max_frame;
	uint8_t current_sprite;
	uint8_t max_sprite;
	uint8_t cols;
} SpriteAnimation;


void tranform_init(Transform* transform, zindex_t zindex);

void sprite_init(Sprite* sprite, const char* filepath);

void sprite_animation_init(
	SpriteAnimation* sprite_animation,
	const char* filepath,
	uint8_t speed,
	uint8_t cols,
	uint8_t rows
);


#endif // !POKE_COMPONENTS_H
