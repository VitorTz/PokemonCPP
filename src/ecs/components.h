#pragma once
#include <raylib.h>
#include "../util/scene_id.h"
#include "../util/CharacterID.h"
#include "../util/types.h"


#define NUM_COMPONENTS 9
#define NUM_UPDATABLE_COMPONENTS 7
#define TRANSFORM_ID 0
#define SPRITE_ID 1
#define SPRITE_ANIMATION_ID 2
#define CHARACTER_ID 3
#define MOVEMENT_ID 4
#define COAST_ID 5
#define PLAYER_ID 6
#define WATER_ID 7
#define TRANSITION_ID 8


typedef struct transform {
	Vector2 pos;
	Vector2 size;
	zindex_t zindex;
	int last_is_idle;
	int is_idle;
	char last_direction;
	char direction;
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


typedef struct character {
	enum CharacterID id;
	Rectangle action_box;
} character_t;


typedef struct movement {
	float speed;
	float last_horizontal_move;
	float last_vertical_move;
	Rectangle collision_box;
} movement_t;


typedef struct coast {
	int terrain;
	int n;
} coast_t;


typedef struct player {
	entity_t shadow_entity;		
} player_t;


typedef struct water {
	char x; // not used
} water_t;


typedef struct transition {
	enum SceneID scene_id;
	int is_hovered;
} transition_t;


void transform_init(transform_t* t, zindex_t z);

void sprite_init(sprite_t* s, const char* filepath);

void sprite_animation_init(
	sprite_animation_t* s,
	const char* filepath,
	float width,
	float height,
	uint8_t speed
);

void sprite_animation_init_character(
	sprite_animation_t* s,
	const char* filepath
);

void character_init(character_t* character, enum CharacterID id);

void movement_init(movement_t* movement, float speed, float collision_width, float collision_height);

void coast_init(coast_t* coast, int terrain, int n);

void player_init(player_t* player, entity_t shadow_entity);

void transition_init(transition_t* t, int scene_id);