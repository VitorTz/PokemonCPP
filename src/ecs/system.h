#ifndef POKE_SYSTEM_H
#define POKE_SYSTEM_H
#include "../util/types.h"
#include "../util/iterator.h"


typedef struct _system {
	void (*update)(entity_t*, entity_t*, float);
	void (*draw)(entity_t);
} system_t;


void sprite_draw(entity_t e);

void sprite_animation_update(entity_t* begin, entity_t* end, float dt);
void sprite_animation_draw(entity_t e);


#endif // POKE_SYSTEM_H
