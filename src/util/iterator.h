#pragma once
#include <stdint.h>


typedef struct iterator {
	void* begin;
	void* end;
	size_t step;
} iterator_t;