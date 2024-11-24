#include "system_manager.h"
#include "ecs_manager.h"


void system_sprite_animation_update(const float dt, const iterator_t iter) {
	ecs_t* ecs = ecs_manager_get_instance();
	for (entity_t* e = iter.begin; e < iter.end; e++) {
		sprite_animation_t* s = (sprite_animation_t*)ecs_component_at(ecs, e, SPRITE_ANIMATION_ID);
	}
}


void system_sprite_animation_draw(const entity_t e) {
	ecs_t* ecs = ecs_manager_get_instance();
	transform_t* t = ecs_get_transform(ecs, e);
	sprite_animation_t* s = (sprite_animation_t*) ecs_component_at(ecs, e, SPRITE_ANIMATION_ID);
	DrawTextureRec(s->texture, s->rect, t->pos, WHITE);
}