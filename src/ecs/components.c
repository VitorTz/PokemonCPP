#include "components.h"
#include "../util/texture_pool.h"


const static component_t DRAWABLE_COMPONENTS_ARR[NUM_COMPONENTS] = {
	0,  // TRANSFORM
	1,  // SPRITE
	1   // SPRITE ANIMATION
};

int component_is_drawable(const component_t id) {
	return DRAWABLE_COMPONENTS_ARR[id];
}

void transform_init(transform_t* t, const zindex_t zindex) {
	t->pos = (Vector2){ 0 };
	t->size = (Vector2){ 0 };
	t->zindex = zindex;
}

void sprite_init(sprite_t* s, const char* filepath) {
	s->texture = texture_pool_get(filepath);
}

void sprite_animation_init(
	sprite_animation_t* s,
	const char* filepath,
	const float sprite_width,
	const float sprite_height,
	const uint8_t speed,
	const uint8_t rows,
	const uint8_t cols
) {
	*s = (sprite_animation_t){
		texture_pool_get(filepath),
		(Rectangle) { 0.0f, 0.0f, sprite_width, sprite_height },
		0, speed, 0, rows * cols, cols
	};
}