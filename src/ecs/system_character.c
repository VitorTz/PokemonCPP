#include "system_manager.h"
#include "ecs_manager.h"


void system_character_update(const float dt, const iterator_t iter) {
	ecs_t* ecs = ecs_manager_get_instance();
	for (entity_t* e = iter.begin; e < iter.end; e++) {
		character_t* character = (character_t*) ecs_component_at(ecs, *e, CHARACTER_ID);
		sprite_animation_t* sprite_animation = (sprite_animation_t*)ecs_component_at(ecs, *e, SPRITE_ANIMATION_ID);
		transform_t* transform = ecs_get_transform(ecs, *e);

		switch (transform->direction) {
			case 'd':
				sprite_animation->rect.y = 0.0f;
				break;
			case 'l':
				sprite_animation->rect.y = GAME_CHARACTER_SIZE;
				break;
			case 'r':
				sprite_animation->rect.y = GAME_CHARACTER_SIZE * 2.0f;
				break;
			case 'u':
				sprite_animation->rect.y = GAME_CHARACTER_SIZE * 3.0f;
				break;
			default:
				break;
		}
		
		if (
			transform->last_direction != transform->direction ||
			transform->last_is_idle != transform->is_idle
			) {
			sprite_animation->frame = 0;
			sprite_animation->index = 1;
			sprite_animation->rect.x = GAME_CHARACTER_SIZE;
		}

		if (transform->is_idle) {
			sprite_animation->rect.x = 0.0f;
		}

		// Action Box
		const float width = TILE_SIZE * 1.8f;
		const float height = TILE_SIZE;
		character->action_box.width = width;
		character->action_box.height = height;

		switch (transform->direction) {
			case 'd':
				character->action_box.x = transform->pos.x + transform->size.x / 2.0f - height / 2.0f;
				character->action_box.y = transform->pos.y + transform->size.y / 2.0f + 20.0f;
				character->action_box.width = height;
				character->action_box.height = width;
				break;
			case 'u':
				character->action_box.x = transform->pos.x + transform->size.x / 2.0f - height / 2.0f;
				character->action_box.y = transform->pos.y + transform->size.y / 2.0f - height - 20.0f;
				character->action_box.width = height;
				character->action_box.height = width;
				break;
			case 'l':
				character->action_box.x = transform->pos.x + transform->size.x / 2.0f - width;
				character->action_box.y = transform->pos.y + transform->size.y - height;
				break;
			case 'r':
				character->action_box.x = transform->pos.x + transform->size.x / 2.0f;
				character->action_box.y = transform->pos.y + transform->size.y - height;
				break;
			default:
				break;	
		}		
	}
}
