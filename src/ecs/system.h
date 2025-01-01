#ifndef POKE_SYSTEM_H
#define POKE_SYSTEM_H
#include "../util/set.h"


typedef struct _system {
	void (*update)(set_iterator_t*, float);
	void (*draw)(entity_id);
} System;



#endif // !POKE_SYSTEM_H
