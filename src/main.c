#include <raylib.h>
#include <stdio.h>
#include "constants.h"
#include "util/hash.h"
#include "util/unordered_set.h"


int main() {
	InitWindow(SCREEN_W, SCREEN_H, WINDOW_TITLE);
	SetTargetFPS(WINDOW_FPS);


	unordered_set* set = unordered_set_create(sizeof(int), hash_int);

	const int total = 100;
	for (int i = 0; i < total; i++) {
		unordered_set_insert(set, &i);
	}

	for (vector* v = unordered_set_begin(set); v < unordered_set_end(set); v++) {		
		for (char* p = vector_begin(v); p < vector_end(v); p += v->type_size) {
			printf("%d\n", *((int*)p));
		}
	}

	while (!WindowShouldClose()) {		
		BeginDrawing();
		ClearBackground(BLACK);
			if (DEBUG_MODE) {
				DrawFPS(20, 20);
			}
		EndDrawing();
	}
	
	CloseWindow();
	return 0;
}