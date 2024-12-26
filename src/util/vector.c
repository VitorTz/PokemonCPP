#include "vector.h"


void vector_init(vector_t* vec, const size_t type_size, const size_t capacity) {
	vec->type_size = type_size;
	vec->capacity = capacity;
	vec->size = 0;
	vec->data = (char*) malloc(type_size * capacity);
	assert(vec->data != NULL);
}

void vector_close(vector_t* vec) {
	if (vec == NULL) {
		return;
	}
	if (vec->data != NULL) {
		free(vec->data);
	}	
}

void vector_reserve(vector_t* vec, const size_t num_elements) {
	if (num_elements > vec->capacity) {
		if (vec->data == NULL) {
			vec->data = (char*)malloc(vec->type_size * num_elements);
			vec->capacity = num_elements;
			return;
		}
		void* tmp = realloc(vec->data, vec->type_size * num_elements);
		if (tmp != NULL) {
			vec->data = tmp;
			vec->capacity = num_elements;
		}
	}
}

inline static void vector_grow(vector_t* vec) {
	if (vec->size >= vec->capacity) {
		void* tmp = realloc(vec->data, vec->type_size * vec->capacity * 2);
		if (tmp != NULL) {
			vec->data = tmp;
			vec->capacity *= 2;
		}
	}
}

void vector_push_back(vector_t* vec, const void* data) {
	vector_grow(vec);
	memcpy(vec->data + vec->type_size * vec->size++, data, vec->type_size);
}

void vector_erase(vector_t* vec, const size_t i) {
	if (vec->size == 0) {
		return;
	}
	memcpy(
		vec->data + vec->type_size * i,
		vec->data + vec->type_size * (vec->size - 1),
		vec->type_size
	);
	vec->size--;
}

void* vector_allocate(vector_t* vec) {
	vector_grow(vec);
	return vec->data + vec->type_size * vec->size++;
}

void* vector_at(vector_t* vec, const size_t i) {
	return vec->data + vec->type_size * i;
}

void* vector_back(vector_t* vec) {
	if (vec->size == 0) {
		return NULL;
	}
	return vec->data + vec->type_size * (vec->size - 1);
}

void* vector_front(vector_t* vec) {
	return vec->data;
}

void vector_pop_back(vector_t* vec, void* dst) {
	if (vec->size == 0) {
		return;
	}
	memcpy(dst, vec->data + vec->type_size * (vec->size - 1), vec->type_size);
	vec->size--;
}

void vector_pop_front(vector_t* vec, void* dst) {
	if (vec->size == 0) {
		return;
	}
	memcpy(dst, vec->data, vec->type_size);
	vec->size--;
}

void vector_clear(vector_t* vec) {
	vec->size = 0;
}

vector_iterator_t vector_iter(vector_t* vec) {
	const vector_iterator_t iter = {
		vec->data,
		vec->data + vec->type_size * vec->size,
		vec->type_size
	};
	return iter;
}
