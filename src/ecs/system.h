#ifndef POKE_SYSTEM_H
#define POKE_SYSTEM_H
#include "../util/set.h"


typedef struct _system {
	void (*update)(set_iterator_t*, float);
	void (*draw)(entity_t);
} System;


void sprite_draw(entity_t e);

void sprite_animation_update(set_iterator_t* iter, float dt);

void sprite_animation_draw(entity_t e);


#endif // !POKE_SYSTEM_H
