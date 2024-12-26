#include "system_sprite.h"
#include "ecs_manager.h"


void sprite_draw(const entity_t e) {
	ecs_t* ecs = ecs_manager_get_current_ecs_instance();
	const transform_t* t = ecs_get_transform(ecs, e);
	const sprite_t* s = (const sprite_t*)ecs_get_component(ecs, e, SPRITE_ID);
	DrawTextureV(*s->texture, t->pos, WHITE);
}