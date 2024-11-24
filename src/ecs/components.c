#include "components.h"
#include "../util/texture_pool.h"


void transform_init(transform_t* t, const zindex_t z) {
	t->pos = (Vector2){ 0.0f, 0.0f };
	t->size = (Vector2){ 0.0f, 0.0f };
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
	s->max_index = (float)s->texture.width / width;
}