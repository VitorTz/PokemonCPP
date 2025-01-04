#include "util.h"
#include <stdio.h>
#include <stdlib.h>


void print_vec(const Vector2 vec) {
	printf("Vec(%.2f, %.2f)\n", vec.x, vec.y);
}

void print_rect(const Rectangle rect) {
	printf("Rect(%.2f, %.2f, %.2f, %.2f)\n", rect.x, rect.y, rect.width, rect.height);
}

int max_int(const int a, const int b) {
	return a > b ? a : b;
}

int randint(const int start, const int end) {
	return start + (rand() % (end - start));
}