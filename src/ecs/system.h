#ifndef POKE_SYSTEM_H
#define POKE_SYSTEM_H
#include "../util/set.h"


typedef struct _system {
	void (*update)(SetIterator*, float);
	void (*draw)(entity_t);
} System;


void sprite_draw(entity_t e);

void sprite_animation_update(SetIterator* iter, float dt);

void sprite_animation_draw(entity_t e);

void shadow_draw(entity_t e);

void player_update(SetIterator* iter, float dt);

#endif // !POKE_SYSTEM_H
