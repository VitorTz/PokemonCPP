#ifndef POKE_VECTOR_H
#define POKE_VECTOR_H
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>


typedef struct vector_iterator {
	char* begin;
	char* end;
	size_t step;
} vector_iterator_t;


typedef struct vector {
	char* data;
	size_t type_size;
	size_t size;
	size_t capacity;
} vector_t;


void vector_init(vector_t* vec, size_t type_size, size_t capacity);

void vector_close(vector_t* vec);

void vector_reserve(vector_t* vec, size_t num_elements);

void vector_push_back(vector_t* vec, const void* data);

void vector_erase(vector_t* vec, size_t i);

void* vector_allocate(vector_t* vec);

void* vector_at(vector_t* vec, size_t i);

void* vector_back(vector_t* vec);

void* vector_front(vector_t* vec);

void vector_pop_back(vector_t* vec, void* dst);

void vector_pop_front(vector_t* vec, void* dst);

void vector_clear(vector_t* vec);

vector_iterator_t vector_iter(vector_t* vec);


#endif