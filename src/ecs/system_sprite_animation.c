#include "system_sprite_animation.h"
#include "ecs_manager.h"


void sprite_animation_update(iterator_t* iter, const float dt) {
	ecs_t* ecs = ecs_manager_get_current_ecs_instance();
	for (entity_t* e = iter->begin; e < iter->end; e++) {
		sprite_animation_t* s = (sprite_animation_t*)ecs_get_component(ecs, *e, SPRITE_ANIMATION_ID);
		s->current_frame++;
		if (s->current_frame > s->max_frame) {
			s->current_frame = 0;
			s->current_sprite = (s->current_sprite + 1) % s->max_sprite;
			s->texture_rect.x = (s->current_sprite % s->cols) * s->texture_rect.width;
			s->texture_rect.y = (s->current_sprite / s->cols) * s->texture_rect.height;
		}
	}
}

void sprite_animation_draw(const entity_t e) {
	ecs_t* ecs = ecs_manager_get_current_ecs_instance();
	const sprite_animation_t* s = (const sprite_animation_t*)ecs_get_component(ecs, e, SPRITE_ANIMATION_ID);
	const transform_t* t = ecs_get_transform(ecs, e);	
	DrawTextureRec(*s->texture, s->texture_rect, t->pos, WHITE);
}