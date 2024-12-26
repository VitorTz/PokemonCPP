#pragma once
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "iterator.h"

	
typedef struct vector {
	void* data;
	size_t capacity;
	size_t size;
	size_t v_size;
} vector_t;


vector_t* vector_create(size_t v_size, size_t capacity);

void vector_cast(vector_t* v, size_t v_size);

void vector_init(vector_t* v, size_t v_size, size_t capacity);

void vector_close(vector_t* v);

void vector_destroy(vector_t* v);

void* vector_allocate(vector_t* v);

void vector_push_back(vector_t* v, const void* data);

void vector_erase(vector_t* v, size_t i);

int vector_is_empty(vector_t* v);

void vector_insert(vector_t* v, const void* data, size_t i);

void* vector_at(vector_t* v, size_t i);

void* vector_pop(vector_t* v, size_t i);

void* vector_pop_back(vector_t* v);

void* vector_pop_front(vector_t* v);

void* vector_begin(vector_t* v);

void vector_clear(vector_t* v);

void* vector_end(vector_t* v);

void* vector_back(vector_t* v);

void* vector_front(vector_t* v);

iterator_t vector_iter(vector_t* v);
