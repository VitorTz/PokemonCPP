#include "components.h"
#include "../util/texture_pool.h"


void transform_init(transform_t* t, const zindex_t zindex) {
	t->pos = (Vector2){ 0 };
	t->size = (Vector2){ 0 };
	t->zindex = zindex;
}


void sprite_init(sprite_t* s, const char* filepath) {
	s->texture = texture_pool_get(filepath);
}