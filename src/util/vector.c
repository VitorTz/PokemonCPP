#include "vector.h"


void vector_init(vector_t* vec, const size_t type_size, const size_t capacity) {
	vec->size = 0;
	vec->type_size = type_size;
	vec->capacity = capacity;
	vec->data = (char*) malloc(type_size * capacity);
	assert(vec->data != NULL);
}

void vector_close(vector_t* vec) {
	if (vec == NULL) { return; }
	free(vec->data);
}

void vector_reserve(vector_t* vec, const size_t new_capacity) {
	if (new_capacity > vec->capacity) {
		void* tmp = realloc(vec->data, vec->type_size * new_capacity);
		if (tmp != NULL) {
			vec->data = (char*) tmp;
			vec->capacity = new_capacity;
		}
	}
}

inline static void vector_grow(vector_t* vec) {
	if (vec->size >= vec->capacity) {
		void* tmp = realloc(vec->data, vec->type_size * vec->capacity * 2);
		if (tmp != NULL) {
			vec->data = (char*) tmp;
			vec->capacity *= 2;
		}
	}
}

void vector_push_back(vector_t* vec, const void* data) {
	vector_grow(vec);
	memcpy(vec->data + vec->type_size * vec->size++, data, vec->type_size);
}

void* vector_allocate(vector_t* vec) {
	vector_grow(vec);
	return vec->data + vec->type_size * vec->size++;
}

void* vector_at(vector_t* vec, const size_t i) {
	return vec->data + vec->type_size * i;
}

void vector_erase(vector_t* vec, const size_t i) {
	if (vec->size > 0) {
		memcpy(
			vec->data + vec->type_size * i, 
			vec->data + vec->type_size * --vec->size, 
			vec->type_size
		);
	}
}

void vector_pop_back(vector_t* vec, void* dst) {
	if (vec->size > 0) {
		memcpy(
			dst,
			vec->data + vec->type_size * --vec->size,
			vec->type_size
		);
	}
}

void vector_clear(vector_t* vec) {
	vec->size = 0;
}

void vector_cast(vector_t* vec, const size_t new_type_size) {
	if (vec->type_size * vec->capacity < new_type_size * vec->capacity) {
		void* tmp = realloc(vec->data, new_type_size * vec->capacity);
		if (tmp != NULL) {
			vec->data = tmp;
		}
	}
	vec->type_size = new_type_size;
}

char* vector_begin(vector_t* vec) {
	return vec->data;
}

char* vector_end(vector_t* vec) {
	return vec->data + vec->type_size * vec->size;
}

int vector_is_empty(vector_t* vec) {
	return vec->size == 0;
}

void vector_sort(vector_t* vec, int (*cmp)(const void*, const void*)) {
	qsort(vec->data, vec->size, vec->type_size, cmp);
}

iter_t vector_iter(vector_t* vec) {
	const iter_t iter = {
		vec->data,
		vec->data + vec->type_size * vec->size,
		vec->type_size
	};
	return iter;
}
