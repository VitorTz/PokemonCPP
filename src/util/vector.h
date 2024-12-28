#ifndef POKE_VECTOR_H
#define POKE_VECTOR_H
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "iterator.h"


typedef struct _vector {
	char* data;
	size_t size;
	size_t type_size;
	size_t capacity;
} vector_t;


void vector_init(vector_t* vec, size_t type_size, size_t capacity);

void vector_close(vector_t* vec);

void vector_reserve(vector_t* vec, size_t new_capacity);

void vector_push_back(vector_t* vec, const void* data);

void* vector_allocate(vector_t* vec);

void* vector_at(vector_t* vec, size_t i);

void vector_erase(vector_t* vec, size_t i);

void vector_pop_back(vector_t* vec, void* dst);

void vector_clear(vector_t* vec);

void vector_cast(vector_t* vec, size_t type_size);

char* vector_begin(vector_t* vec);

char* vector_end(vector_t* vec);

int vector_is_empty(vector_t* vec);

void vector_sort(vector_t* vec, int (*cmp)(const void*, const void*));

iter_t vector_iter(vector_t* vec);

#endif // !POKE_VECTOR_H
