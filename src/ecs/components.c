#include "components.h"
#include "../constants.h"
#include "../util/texture_pool.h"


void transform_init(transform_t* t, const zindex_t z) {
	t->pos = (Vector2){ 0.0f, 0.0f };
	t->size = (Vector2){ 0.0f, 0.0f };
	t->last_direction = t->direction = 'd';
	t->last_is_idle = t->is_idle = 1;
	t->zindex = z;
}


void sprite_init(sprite_t* s, const char* filepath) {
	s->texture = texture_pool_get(filepath);
}


void sprite_animation_init(
	sprite_animation_t* s,
	const char* filepath,
	const float width,
	const float height,
	const uint8_t speed
) {
	s->texture = texture_pool_get(filepath);
	s->rect = (Rectangle){ 0.0f, 0.0f, width, height };
	s->frame = 0;
	s->max_frame = speed;
	s->index = 0;
	s->max_index = (float) s->texture.width / width;
}


void sprite_animation_init_character(sprite_animation_t* s, const char* filepath) {
	sprite_animation_init(s, filepath, GAME_CHARACTER_SIZE, GAME_CHARACTER_SIZE, SPRITE_ANIMATION_SPEED_NORMAL);
}


void character_init(character_t* character, const enum CharacterID id) {
	character->id = id;	
}


void movement_init(
	movement_t* movement, 
	const float speed,
	const float collision_width,
	const float collision_height
) {
	movement->speed = speed;
	movement->last_horizontal_move = movement->last_vertical_move = 0.0f;
	movement->collision_box = (Rectangle){ 0.0f, 0.0f, collision_width, collision_height };
}


void coast_init(coast_t* coast, const int terrain, const int n) {
	coast->terrain = terrain;
	coast->n = n;
}

void player_init(player_t* player, const entity_t shadow_entity) {
	player->shadow_entity = shadow_entity;	
}


void transition_init(transition_t* t, const int scene_id) {
	t->scene_id = (enum SceneId)scene_id;
	t->is_hovered = 0;
}