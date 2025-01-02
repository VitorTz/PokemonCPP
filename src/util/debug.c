#include "debug.h"


void debug_ecs(ECS* ecs) {	
	if (!DEBUG_MODE) {
		return;
	}
	const int y = 10;
	const int y_offset = 18;

	DrawFPS(10, y);

	DrawText(
		TextFormat("ENTITIES: %d", ecs->entity->size),
		10,
		y + y_offset * 1,
		16,
		LIME
	);

	DrawText(
		TextFormat("CAMERA ENTITIES: %d", ecs->camera->size),
		10,
		y + y_offset * 2,
		16,
		LIME
	);

	DrawText(
		TextFormat("CAMERA ZOOM: %.2f", ecs->camera->camera2D.zoom),
		10,
		y + y_offset * 3,
		16,
		LIME
	);

	DrawText(
		TextFormat("CAMERA TARGET: %.2f, %.2f", ecs->camera->camera2D.target.x, ecs->camera->camera2D.target.y),
		10,
		y + y_offset * 4,
		16,
		LIME
	);
}