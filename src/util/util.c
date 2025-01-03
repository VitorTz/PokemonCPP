#include "util.h"
#include <stdio.h>


void print_vec(Vector2 vec) {
	printf("Vec(%.2f, %.2f)\n", vec.x, vec.y);
}

void print_rect(Rectangle rect) {
	printf("Rect(%.2f, %.2f, %.2f, %.2f)\n", rect.x, rect.y, rect.width, rect.height);
}