#include "globals.h"


static vector_t aux_vec = { 0 };


void globals_init() {
	vector_init(&aux_vec, sizeof(void*), 1024);
}

void globals_close() {
	vector_close(&aux_vec);
}

vector_t* globals_get_aux_vec() {
	return &aux_vec;
}