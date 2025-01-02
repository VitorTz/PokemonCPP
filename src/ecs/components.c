#include "components.h"
#include "../util/texture_pool.h"


void entity_tranform_init(EntityTransform* transform, const zindex_t zindex) {
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
	SpriteAnimation* sprite,
	const char* filepath,
	const uint8_t speed,
	const uint8_t rows,
	const uint8_t cols
) {
	sprite->texture = texture_pool_get(filepath);
	sprite->texture_rect = (Rectangle){
		0.0f,
		0.0f,
		(float)(sprite->texture->width / cols),
		(float)(sprite->texture->height / rows)
	};
	sprite->current_frame = 0;
	sprite->max_frame = speed;
	sprite->current_sprite = 0;
	sprite->max_sprite = rows * cols;
	sprite->cols = cols;
}

void shadow_init(Shadow* shadow, const Vector2 offset, const char* filepath) {
	sprite_init(&shadow->sprite, filepath);	
	shadow->offset.x = offset.x - shadow->sprite.size.x / 2.0f;;
	shadow->offset.y = offset.y - shadow->sprite.size.y / 2.0f;;
}