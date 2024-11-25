#pragma once
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "iterator.h"


typedef struct vector {
	char* data;
	char* tmp_data;
	size_t v_size;
	size_t capacity;
	size_t size;
} vector_t;


vector_t* vector_create(size_t v_size, size_t capacity);

void vector_init(vector_t* v, size_t v_size, size_t capacity);

void vector_close(vector_t* v);

void vector_destroy(vector_t* v);

void* vector_begin(vector_t* v);

void* vector_end(vector_t* v);

void vector_push_back(vector_t* v, const void* data);

void* vector_allocate(vector_t* v);

void* vector_at(vector_t* v, size_t i);

void* vector_back(vector_t* v);

void vector_convert(vector_t* v, size_t v_size, size_t capacity);

void vector_pop_back(vector_t* v, void* dst);

void vector_erase(vector_t* v, size_t i);

void vector_swap(vector_t* v, size_t i, size_t j);

void vector_clear(vector_t* v);

int vector_is_empty(vector_t* v);

size_t vector_size(vector_t* v);

iterator_t vector_iter(vector_t* v);
