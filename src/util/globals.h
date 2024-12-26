#ifndef POKE_GLOBALS_H
#define POKE_GLOBALS_H
#include "vector.h"


void globals_init();

void globals_close();

vector_t* globals_get_aux_vec();


#endif