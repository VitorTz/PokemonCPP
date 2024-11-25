#include "system_manager.h"
#include "ecs_manager.h"
#include "../scene/scene.h"
#include "../util/tiled_map.h"


#define TRANSITION_FONT_SIZE 20


void system_transition_update(const float dt, const iterator_t iter) {
	ecs_t* ecs = ecs_manager_get_instance();
	const iterator_t chr_iter = set_iter(ecs->system->entities_set_by_component + CHARACTER_ID);

	for (entity_t* e = iter.begin; e < iter.end; e++) {
		transition_t* transition = (transition_t*)ecs_component_at(ecs, *e, TRANSITION_ID);
		transform_t* t = ecs_get_transform(ecs, *e);
		transition->is_hovered = 0;
		for (entity_t* ee = chr_iter.begin; ee < chr_iter.end; ee++) {
			character_t* character = (character_t*)ecs_component_at(ecs, *ee, CHARACTER_ID);
			transition->is_hovered = CheckCollisionRecs(character->action_box, (Rectangle) { t->pos.x, t->pos.y, t->size.x, t->size.y });
			if (transition->is_hovered && IsKeyPressed(ACTION_KEY)) {
				scene_manager_change_scene(transition->scene_id);				
			}
		}
	}
}


void system_transition_draw(const entity_t e) {
	ecs_t* ecs = ecs_manager_get_instance();
	const transition_t* transition = (transition_t*) ecs_component_at(ecs, e, TRANSITION_ID);
	const transform_t* transform = ecs_get_transform(ecs, e);

	if (transition->is_hovered) {
		const char* map_name = get_map_info(transition->scene_id)->name;
		const char* txt = TextFormat("Press F to enter %s", map_name);
		const int txt_width = MeasureText(txt, TRANSITION_FONT_SIZE);
		const Vector2 base_pos = GetScreenToWorld2D((Vector2){SCREEN_W / 2.0f, SCREEN_H - 80.0f}, ecs->camera->camera2D);
		DrawRectangleRec(
			(Rectangle) { base_pos.x - (txt_width + 40) / 2.0f, base_pos.y - TRANSITION_FONT_SIZE, txt_width + 40, 60 }, 
			(Color) { 0, 0, 0, 180 }
		);
		DrawText(txt, base_pos.x - txt_width / 2.0f, base_pos.y, TRANSITION_FONT_SIZE, WHITE);
	}

	if (DEBUG_MODE) {
		DrawRectangleLinesEx(
			(Rectangle){transform->pos.x, transform->pos.y, transform->size.x, transform->size.y},
			2.0f,
			LIME
		);
	}
}	