#ifndef POKE_VECTOR_H
#define POKE_VECTOR_H
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"


typedef struct _vector {
	char* data;
	size_t size;
	size_t type_size;
	size_t capacity;
} vector;



void vector_init(vector* vec, size_t type_size, size_t capacity);

void vector_close(vector* vec);

void vector_reserve(vector* vec, size_t new_capacity);

void vector_cast(vector* vec, size_t new_type_size);

void vector_push_back(vector* vec, const void* item);

void vector_erase(vector* vec, size_t i);

void vector_rmv(vector* vec, const void* item, int (*cmp)(const void*, const void*));

void* vector_at(vector* vec, size_t i);

void* vector_allocate(vector* vec);

char* vector_begin(vector* vec);

char* vector_end(vector* vec);

void vector_pop(vector* vec, size_t i, void* dst);

void vector_pop_back(vector* vec, void* dst);

void vector_pop_front(vector* vec, void* dst);

void vector_clear(vector* vec);

iter_t vector_iter(vector* vec);


#endif // !POKE_VECTOR_H

