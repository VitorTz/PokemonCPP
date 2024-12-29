#ifndef POKE_SYSTEM_H
#define POKE_SYSTEM_H
#include "../util/types.h"
#include "../util/iterator.h"


typedef struct _system {
	void (*update)(iter_t iter, float);
	void (*draw)(entity_t);
} system_t;


void sprite_draw(entity_t e);

void sprite_animation_update(iter_t iter, float dt);
void sprite_animation_draw(entity_t e);


#endif // POKE_SYSTEM_H
