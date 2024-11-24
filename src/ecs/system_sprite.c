#include "system_manager.h"
#include "ecs_manager.h"


void system_sprite_draw(const entity_t e) {
	ecs_t* ecs = ecs_manager_get_instance();
	const transform_t* t = ecs_get_transform(ecs, e);
	const sprite_t* s = (sprite_t*) ecs_component_at(ecs, e, SPRITE_ID);
	DrawTextureV(s->texture, t->pos, WHITE);
}