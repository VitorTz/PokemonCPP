#ifndef POKE_ITERATOR_H
#define POKE_ITERATOR_H
#include <stddef.h>


typedef struct iterator {
	char* begin;
	char* end;
	size_t step;
} iter_t;


#endif // !POKE_ITERATOR_H
