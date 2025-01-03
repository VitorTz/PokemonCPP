#include "debug.h"


void debug_ecs(ECS* ecs) {	
	if (!DEBUG_MODE) {
		return;
	}	

	camera_begin_drawing(ecs->camera);
		
		// Collision
		Rectangle* rect_begin = (Rectangle*) vector_begin(ecs->static_collisions);
		Rectangle* rect_end = (Rectangle*)vector_end(ecs->static_collisions);
		for (Rectangle* rect = rect_begin; rect < rect_end; rect++) {
			DrawRectangleLinesEx(*rect, 2.0f, RED);
		}
		
		// PLAYER 
		entity_t* e = NULL;
		SetIterator* players = ecs_get_entities_by_component(ecs, PLAYER_ID);
		while ((e = (entity_t*)set_iter_next(players)) != NULL) {
			Player* player = (Player*)ecs_get_component(ecs, *e, PLAYER_ID);
			DrawRectangleLinesEx(player->collide_box, 2.0f, BLACK);
			DrawRectangleLinesEx(player->action_box, 2.0f, GREEN);
		}

	camera_end_drawing();

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