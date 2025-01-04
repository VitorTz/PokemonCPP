#ifndef POKE_VECTOR_H
#define POKE_VECTOR_H
#include <stddef.h>


typedef struct _vector {
	char* data;
	size_t size;
	size_t type_size;
	size_t capacity;
} Vector;


Vector* vector_create(size_t type_size, size_t capacity);

void vector_destroy(Vector* vec);

void vector_init(Vector* vec, size_t type_size, size_t capacity);

void vector_close(const Vector* vec);

void vector_reserve(Vector* vec, size_t new_capacity);

void vector_cast(Vector* vec, size_t new_type_size);

void vector_push_back(Vector* vec, const void* item);

void vector_erase(Vector* vec, size_t i);

void vector_rmv(Vector* vec, const void* item, int (*cmp)(const void*, const void*));

void* vector_at(const Vector* vec, size_t i);

void* vector_allocate(Vector* vec);

char* vector_begin(const Vector* vec);

char* vector_end(const Vector* vec);

void vector_pop(Vector* vec, size_t i, void* dst);

void vector_pop_back(Vector* vec, void* dst);

void vector_pop_front(Vector* vec, void* dst);

void vector_clear(Vector* vec);


#endif // !POKE_VECTOR_H
