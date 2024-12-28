#include "system.h"
#include "ecs_manager.h"


void sprite_draw(const entity_t e) {
	ecs_t* ecs = ecs_manager_get_current_ecs_instance();
	const sprite_t* sprite = (sprite_t*) ecs_get_component(ecs, e, SPRITE_ID);
	const transform_t* transform = ecs_get_transform(ecs, e);
	DrawTextureV(*sprite->texture, transform->pos, WHITE);
}


void sprite_animation_update(entity_t* begin, entity_t* end, const float dt) {
	ecs_t* ecs = ecs_manager_get_current_ecs_instance();
	for (entity_t* e = begin; e < end; e++) {
		sprite_animation_t* s_animation = (sprite_animation_t*)ecs_get_component(ecs, *e, SPRITE_ANIMATION_ID);
		s_animation->current_frame++;
		if (s_animation->current_frame >= s_animation->max_frame) {
			s_animation->current_frame = 0;
			s_animation->current_sprite = (s_animation->current_sprite + 1) % s_animation->max_sprite;
			s_animation->texture_rect.x = (s_animation->current_sprite / s_animation->cols) * s_animation->texture_rect.width;
			s_animation->texture_rect.y = (s_animation->current_sprite % s_animation->cols) * s_animation->texture_rect.height;
		}
	}
}


void sprite_animation_draw(const entity_t e) {
	ecs_t* ecs = ecs_manager_get_current_ecs_instance();
	const sprite_animation_t* s_animation = (sprite_animation_t*)ecs_get_component(ecs, e, SPRITE_ANIMATION_ID);
	const transform_t* transform = ecs_get_transform(ecs, e);
	DrawTextureRec(*s_animation->texture, s_animation->texture_rect, transform->pos, WHITE);
}