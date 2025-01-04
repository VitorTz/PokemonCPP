#ifndef POKE_COMPONENTS_H
#define POKE_COMPONENTS_H
#include <raylib.h>
#include "../util/types.h"


#define NUM_COMPONENTS 5
#define TRANSFORM_ID 0
#define SPRITE_ID 1
#define SPRITE_ANIMATION_ID 2
#define SHADOW_ID 3
#define PLAYER_ID 4


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
	uint8_t rows;
	uint8_t cols;
} SpriteAnimation;


typedef struct _shadow {
	Sprite sprite;	
	Vector2 offset;
} Shadow;

typedef struct _player {
	char last_direction[2];
	char direction[2];	
	Rectangle action_box;
	Rectangle collide_box;
} Player;


void entity_transform_init(EntityTransform* transform, zindex_t zindex);

void sprite_init(Sprite* sprite, const char* filepath);

void sprite_animation_init(
	SpriteAnimation* sprite_animation,
	const char* filepath,
	uint8_t speed,
	uint8_t rows,
	uint8_t cols
);

void shadow_init(Shadow* shadow, float x_offset, float y_offset, const char* filepath);

void player_init(Player* player);


#endif // !POKE_COMPONENTS_H
