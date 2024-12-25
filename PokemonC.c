#include <raylib.h>
#include <stdio.h>
#include "src/constants.h"
#include "src/util/vector.h"


int main() {
	InitWindow(SCREEN_W, SCREEN_H, WINDOW_TITLE);
	SetTargetFPS(FPS);

	vector_t* vec = vector_create(sizeof(int), 8);

	for (int i = 0; i < 100; i++) {
		vector_push_back(vec, &i);
	}

	iterator_t iter = vector_iter(vec);
	int* begin = (int*) vector_begin(vec);
	int* end = (int*) vector_end(vec);
	for (int* p = begin; p < end; p++) {
		printf("%d\n", *p);
	}

	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(BLACK);
		EndDrawing();
	}

	CloseWindow();
	return 0;
}
