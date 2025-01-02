#ifndef POKE_COMPONENTS_H
#define POKE_COMPONENTS_H
#include <raylib.h>
#include "../util/types.h"


#define NUM_COMPONENTS 4
#define TRANSFORM_ID 0
#define SPRITE_ID 1
#define SPRITE_ANIMATION_ID 2
#define SHADOW_ID 3


typedef struct _transform {
	Vector2 pos;
	Vector2 size;
	zindex_t zindex;
} EntityTransform;

typedef struct _sprite {
	Texture2D* texture;
	Vector2 size;
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


typedef struct _shadow {
	Sprite sprite;	
	Vector2 offset;
} Shadow;


void entity_tranform_init(EntityTransform* transform, zindex_t zindex);

void sprite_init(Sprite* sprite, const char* filepath);

void sprite_animation_init(
	SpriteAnimation* sprite_animation,
	const char* filepath,
	uint8_t speed,
	uint8_t cols,
	uint8_t rows
);

void shadow_init(Shadow* shadow, Vector2 offset, const char* filepath);


#endif // !POKE_COMPONENTS_H
