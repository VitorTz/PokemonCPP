#include "components.h"
#include "../util/texture_pool.h"
#include "../constants.h"


void entity_transform_init(EntityTransform* transform, const zindex_t zindex) {
	transform->pos = (Vector2){ 0.0f, 0.0f };
	transform->size = (Vector2){ 0.0f, 0.0f };
	transform->zindex = zindex;
}

void sprite_init(Sprite* sprite, const char* filepath) {
	sprite->texture = texture_pool_get(filepath);
	sprite->size = (Vector2) {
		(float) sprite->texture->width,
		(float) sprite->texture->height
	};
}

void sprite_animation_init(
	SpriteAnimation* sprite_animation,
	const char* filepath,
	const uint8_t speed,
	const uint8_t rows,
	const uint8_t cols
) {
	sprite_animation->texture = texture_pool_get(filepath);
	sprite_animation->texture_rect = (Rectangle){
		0.0f,
		0.0f,
		(float)(sprite_animation->texture->width / cols),
		(float)(sprite_animation->texture->height / rows)
	};
	sprite_animation->current_frame = 0;
	sprite_animation->max_frame = speed;
	sprite_animation->current_sprite = 0;
	sprite_animation->max_sprite = rows * cols;
	sprite_animation->rows = rows;
	sprite_animation->cols = cols;
}

void shadow_init(Shadow* shadow, const float x_offset, const float y_offset, const char* filepath) {
	sprite_init(&shadow->sprite, filepath);	
	shadow->offset.x = x_offset - shadow->sprite.size.x / 2.0f;;
	shadow->offset.y = y_offset - shadow->sprite.size.y / 2.0f;;
}

void player_init(Player* player) {
	player->direction[0] = 'i';
	player->direction[1] = 'd';
	player->last_direction[0] = 'i';
	player->last_direction[1] = 'd';
	
	player->action_box = (Rectangle) { 0.0f, 0.0f, 0.0f, 0.0f };
	player->collide_box = (Rectangle) { 0.0f, 0.0f, TILE_SIZE * 0.8f, TILE_SIZE * 0.8f };
}