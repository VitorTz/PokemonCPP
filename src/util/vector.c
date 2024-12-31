#include "vector.h"


void vector_init(vector* vec, const size_t type_size, const size_t capacity) {
	vec->size = 0;
	vec->type_size = type_size;
	vec->capacity = capacity;
	vec->data = (char*) malloc(type_size * capacity);
	assert(vec->data != NULL);
}

void vector_close(vector* vec) {
	if (vec == NULL || vec->data == NULL) { return; }
	free(vec->data);
}

void vector_reserve(vector* vec, const size_t new_capacity) {
	if (new_capacity > new_capacity) {
		void* tmp = realloc(vec->data, vec->type_size * new_capacity);
		if (tmp != NULL) {
			vec->data = tmp;
			vec->capacity = new_capacity;
		}
	}
}

inline static void vector_grow(vector* vec) {
	if (vec->size >= vec->capacity) {
		void* tmp = realloc(vec->data, vec->type_size * vec->capacity * 2);
		if (tmp != NULL) {
			vec->data = tmp;
			vec->capacity *= 2;
		}
	}
}

void vector_cast(vector* vec, const size_t new_type_size) {
	if (vec->type_size * vec->capacity < new_type_size * vec->capacity) {
		void* tmp = realloc(vec->data, new_type_size  * vec->capacity);
		if (tmp != NULL) {
			vec->data = tmp;
		}
	}
	vec->type_size = new_type_size;
}

void vector_push_back(vector* vec, const void* item) {
	vector_grow(vec);
	memcpy(vec->data + vec->type_size * vec->size++, item, vec->type_size);
}

void vector_erase(vector* vec, const size_t i) {
	if (vec->size <= 0) {
		return;
	}
	memcpy(
		vec->data + vec->type_size * i, 
		vec->data + vec->type_size * --vec->size, 
		vec->type_size
	);
}

void vector_rmv(vector* vec, const void* item, int (*cmp)(const void*, const void*)) {
	size_t i = 0;
	for (char* p = vec->data; p < vec->data + vec->type_size * vec->size; p += vec->type_size) {
		if (cmp(p, item)) {
			vector_erase(vec, i);
			return;
		}
		i++;
	}
}

void* vector_at(vector* vec, const size_t i) {
	return vec->data + vec->type_size * i;
}

void* vector_allocate(vector* vec) {
	vector_grow(vec);
	return vec->data + vec->type_size * vec->size++;
}

char* vector_begin(vector* vec) {
	return vec->data;
}

char* vector_end(vector* vec) {
	return vec->data + vec->type_size * vec->size;
}

void vector_pop(vector* vec, const size_t i, void* dst) {
	memcpy(dst, vec->data + vec->type_size * i, vec->type_size);
	vec->size--;
}

void vector_pop_back(vector* vec, void* dst) {
	memcpy(dst, vec->data + vec->type_size * --vec->size, vec->type_size);
}

void vector_pop_front(vector* vec, void* dst) {
	memcpy(dst, vec->data, vec->type_size);
	vec->size--;
}

void vector_clear(vector* vec) {
	vec->size = 0;
}

iter_t vector_iter(vector* vec) {
	const iter_t iter = {
		vec->data,
		vec->data + vec->type_size * vec->size,
		vec->type_size
	};
	return iter;
}