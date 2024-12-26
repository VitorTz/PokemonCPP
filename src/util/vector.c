#include "vector.h"


void vector_init(
	vector_t* v,
	const size_t v_size,
	const size_t capacity
) {
	v->capacity = capacity;
	v->v_size = v_size;
	v->size = 0;
	v->data = malloc(v_size * capacity);
}

vector_t* vector_create(const size_t v_size, const size_t capacity) {
	vector_t* v = (vector_t*)malloc(sizeof(vector_t));
	assert(v != NULL);	
	vector_init(v, v_size, capacity);
	return v;
}


void vector_close(vector_t* v) {
	if (v->data != NULL) {
		free(v->data);
	}
}

void vector_cast(vector_t* v, const size_t new_v_size) {
	if (new_v_size * v->capacity > v->v_size * v->capacity) {
		void* tmp = realloc(v->data, new_v_size * v->capacity);
		assert(tmp != NULL);
		v->data = tmp;
	}
	v->v_size = new_v_size;
}

void vector_destroy(vector_t* v) {
	if (v != NULL) {
		vector_close(v);
		free(v);
	}
}

inline static void vector_grow(vector_t* v) {
	if (v->size >= v->capacity) {
		void* tmp = realloc(v->data, v->capacity * 2 * v->v_size);
		if (tmp != NULL) {
			v->data = tmp;
			v->capacity *= 2;
		}
	}
}

void vector_push_back(vector_t* v, const void* data) {
	vector_grow(v);
	memcpy((char*) v->data + v->size * v->v_size, data, v->v_size);
	v->size++;
}

void* vector_allocate(vector_t* v) {
	vector_grow(v);
	return (char*)v->data + v->v_size * v->size++;	
}

int vector_is_empty(vector_t* v) {
	return v->size == 0;
}

void vector_erase(vector_t* v, const size_t i) {
	assert(i < v->size);
	memcpy((char*)v->data + i * v->v_size, (char*)v->data + (v->size - 1) * v->v_size , v->v_size);
	v->size--;
}

void vector_erase_back(vector_t* v) {
	if (v->size > 0) {
		v->size--;
	}
}

void vector_insert(vector_t* v, const void* data, const size_t i) {
	vector_grow(v);
	char* begin = (char*)v->data;
	for (size_t j = v->size - 1; j >= i; j--) {
		memcpy(
			begin + (j + 1) * v->v_size, // dest
			begin + j * v->v_size,       // src
			v->v_size
		);
	}
	memcpy(begin + i * v->v_size, data, v->v_size);
	v->size++;
}

void* vector_at(vector_t* v, const size_t i) {
	return (char*)v->data + i * v->v_size;
}

void* vector_pop(vector_t* v, const size_t i) {
	void* p = malloc(v->v_size);
	assert(i < v->size);
	assert(p != NULL);	
	memcpy(p, (char*)v->data + i * v->v_size, v->v_size);
	vector_erase(v, i);
	return p;
}

void* vector_pop_back(vector_t* v) {	
	return vector_pop(v, v->size - 1);
}

void* vector_pop_front(vector_t* v) {
	return vector_pop(v, 0);
}

void* vector_back(vector_t* v) {
	return vector_at(v, v->size - 1);
}

void* vector_front(vector_t* v) {
	return v->data;
}

void* vector_begin(vector_t* v) {
	return v->data;
}

void vector_clear(vector_t* v) {
	v->size = 0;
}

void* vector_end(vector_t* v) {
	return (char*) v->data + v->size * v->v_size;
}

iterator_t vector_iter(vector_t* v) {
	const iterator_t iter = {
		v->data,
		(char*)v->data + v->size * v->v_size,
		v->v_size
	};
	return iter;
}

size_t vector_size(const vector_t* v) {
	return v->size;
}