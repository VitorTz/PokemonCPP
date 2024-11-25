#include "vector.h"


vector_t* vector_create(const size_t v_size, const size_t capacity) {
	vector_t* v = (vector_t*) malloc(sizeof(vector_t));
	if (v == NULL) { return NULL; }
	v->data = (char*) malloc(v_size * capacity);
	v->tmp_data = (char*)malloc(v_size);
	v->v_size = v_size;
	v->capacity = capacity;
	v->size = 0;
	return v;
}


void vector_init(vector_t* v, const size_t v_size, const size_t capacity) {
	v->data = (char*)malloc(v_size * capacity);
	v->tmp_data = (char*)malloc(v_size);
	v->v_size = v_size;
	v->capacity = capacity;
	v->size = 0;
}


void vector_close(vector_t* v) {
	free(v->data);
}


void vector_destroy(vector_t* v) {
	free(v->data);
	free(v);
}


static void vector_grow(vector_t* v) {
	void* tmp = realloc(v->data, v->v_size * v->capacity * 2);
	if (tmp != NULL) {
		v->data = tmp;
		v->capacity *= 2;
	}
}


void vector_push_back(vector_t* v, const void* data) {
	if (v->size >= v->capacity) {
		vector_grow(v);
	}
	memcpy(v->data + v->v_size * v->size++, data, v->v_size);
}


void* vector_begin(vector_t* v) {
	return v->data;
}


void* vector_end(vector_t* v) {
	return v->data + v->v_size * v->size;
}


void* vector_allocate(vector_t* v) {
	return v->data + v->v_size * v->size++;
}


void* vector_back(vector_t* v) {
	return v->data + v->v_size * v->size;
}


void vector_pop_back(vector_t* v, void* dst) {
	if (v->size > 0) {
		memcpy(dst, v->data + v->v_size * v->size, v->v_size);
		v->size--;
	}
}


void* vector_at(vector_t* v, const size_t i) {
	return v->data + v->v_size * i;
}


void vector_erase(vector_t* v, const size_t i) {
	memcpy(v->data + v->v_size * i, v->data + v->v_size * v->size, v->v_size);
	v->size--;
}


void vector_swap(vector_t* v, const size_t i, const size_t j) {
	memcpy(v->tmp_data, v->data + v->v_size * i, v->v_size);
	memcpy(v->data + v->v_size * i, v->data + v->v_size * j, v->v_size);
	memcpy(v->data + v->v_size * j, v->tmp_data, v->v_size);
}


void vector_convert(vector_t* v, const size_t new_v_size, const size_t new_capacity) {	
	if (v->capacity * v->v_size < new_v_size * new_capacity) {
		void* tmp = realloc(v->data, new_v_size * new_capacity);
		assert(tmp != NULL);
		v->data = tmp;
	}
	v->capacity = new_capacity;
	v->v_size = new_v_size;
	v->size = 0;
}


void vector_clear(vector_t* v) {
	v->size = 0;
}


int vector_is_empty(vector_t* v) {
	return v->size == 0;
}


size_t vector_size(vector_t* v) {
	return v->size;
}


iterator_t vector_iter(vector_t* v) {
	const iterator_t iter = { v->data, v->data + v->v_size * v->size, v->v_size };
	return iter;
}