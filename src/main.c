#include <raylib.h>
#include <stdio.h>
#include "constants.h"
#include "util/hash.h"
#include "util/set.h"


int main() {
	InitWindow(SCREEN_W, SCREEN_H, WINDOW_TITLE);
	SetTargetFPS(WINDOW_FPS);

	set* int_set = set_create(sizeof(int), hash_int);

	int total = 128;
	int sorted[128];
	for (int i = 0; i < total; i++) {
		set_insert(int_set, &i);
		sorted[i] = 0;
	}

	set_iterator_t* iter = set_iter(int_set);
	
	int* data;
	while ((data = (int*) set_iter_next(iter)) != NULL) {
		printf("%d\n", *data);
		sorted[*data] = 1;
	}

	printf("==========================================\n");

	for (int i = 0; i < total; i++) {
		if (sorted[i] == 0) {
			printf("%d\n", i);
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