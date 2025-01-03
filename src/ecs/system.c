#include <raylib.h>
#include <raymath.h>
#include <stdio.h>
#include "system.h"
#include "ecs_manager.h"
#include "../util/util.h"


void sprite_draw(const entity_t e) {	
	ECS* ecs = ecs_manager_get_current_ecs_instance();
	const Sprite* sprite = (Sprite*)ecs_get_component(ecs, e, SPRITE_ID);
	const EntityTransform* transform = ecs_get_transform(ecs, e);
	DrawTextureV(*sprite->texture, transform->pos, WHITE);
}


void sprite_animation_update(SetIterator* iter, const float dt) {
	EntityPair* pair = NULL;
	ECS* ecs = ecs_manager_get_current_ecs_instance();
	while ((pair = (EntityPair*)set_iter_next(iter)) != NULL) {
		SpriteAnimation* sprite_animation = (SpriteAnimation*)ecs_get_component(ecs, pair->entity, SPRITE_ANIMATION_ID);
		sprite_animation->current_frame++;
		if (sprite_animation->current_frame > sprite_animation->max_frame) {
			sprite_animation->current_frame = 0;
			sprite_animation->current_sprite = (sprite_animation->current_sprite + 1) % sprite_animation->max_sprite;
			sprite_animation->texture_rect.x = (sprite_animation->current_sprite % sprite_animation->cols) * sprite_animation->texture_rect.width;
			sprite_animation->texture_rect.y = (sprite_animation->current_sprite / sprite_animation->cols) * sprite_animation->texture_rect.height;
		}
	}
}

void sprite_animation_draw(const entity_t e) {
	ECS* ecs = ecs_manager_get_current_ecs_instance();
	const EntityTransform* transform = ecs_get_transform(ecs, e);
	const SpriteAnimation* sprite_animation = (SpriteAnimation*)ecs_get_component(ecs, e, SPRITE_ANIMATION_ID);
	DrawTextureRec(
		*sprite_animation->texture, 
		sprite_animation->texture_rect, 
		transform->pos, 
		WHITE
	);
}

void shadow_draw(const entity_t e) {
	ECS* ecs = ecs_manager_get_current_ecs_instance();
	const EntityTransform* transform = ecs_get_transform(ecs, e);
	const Shadow* shadow = (Shadow*)ecs_get_component(ecs, e, SHADOW_ID);	
	DrawTextureV(*shadow->sprite.texture, Vector2Add(transform->pos, shadow->offset), WHITE);
}


void player_update(SetIterator* iter, const float dt) {	
	EntityPair* pair = NULL;
	Vector2 direction = { 0.0f, 0.0f };
	ECS* ecs = ecs_manager_get_current_ecs_instance();

	while ((pair = (EntityPair*)set_iter_next(iter)) != NULL) {
		Player* player = (Player*) ecs_get_component(ecs, pair->entity, PLAYER_ID);
		SpriteAnimation* sprite_animation = (SpriteAnimation*)ecs_get_component(ecs, pair->entity, SPRITE_ANIMATION_ID);
		EntityTransform* transform = ecs_get_transform(ecs, pair->entity);

		// MOVEMENT

			player->last_direction[0] = player->direction[0];
			player->last_direction[1] = player->direction[1];

			direction.x = 0.0f;
			direction.y = 0.0;
			player->direction[0] = 'i';

			if (IsKeyDown(POKE_UP_KEY)) {
				direction.y = -1.0f;
				player->direction[0] = 'm';
				player->direction[1] = 'u';
			}
			else if (IsKeyDown(POKE_DOWN_KEY)) {
				direction.y = 1.0f;
				player->direction[0] = 'm';
				player->direction[1] = 'd';
			}

			if (IsKeyDown(POKE_LEFT_KEY)) {
				direction.x = -1.0f;
				player->direction[0] = 'm';
				player->direction[1] = 'l';
			}
			else if (IsKeyDown(POKE_RIGHT_KEY)) {
				direction.x = 1.0f;
				player->direction[0] = 'm';
				player->direction[1] = 'r';
			}

			direction = Vector2Normalize(direction);

			// HORIZONTAL MOVEMENT
			transform->pos.x += direction.x * dt * PLAYER_SPEED;
			player->collide_box.x = transform->pos.x + transform->size.x / 2.0f - player->collide_box.width / 2.0f;
			player->collide_box.y = transform->pos.y + transform->size.y - player->collide_box.height;
			if (ecs_check_static_collision(ecs, player->collide_box)) {				
				transform->pos.x -= direction.x * dt * PLAYER_SPEED;
			}
			
			// VERTICAL MOVEMENT
			transform->pos.y += direction.y * dt * PLAYER_SPEED;
			player->collide_box.x = transform->pos.x + transform->size.x / 2.0f - player->collide_box.width / 2.0f;
			player->collide_box.y = transform->pos.y + transform->size.y - player->collide_box.height;
			if (ecs_check_static_collision(ecs, player->collide_box)) {				
				transform->pos.y -= direction.y * dt * PLAYER_SPEED;
			}
			
		// SPRITE ANIMATION
			switch (player->direction[1]) {
				case 'd':
					sprite_animation->texture_rect.y = 0.0f;
					break;
				case 'l':
					sprite_animation->texture_rect.y = CHARACTER_SIZE;
					break;
				case 'r':
					sprite_animation->texture_rect.y = CHARACTER_SIZE * 2.0f;
					break;
				case 'u':
					sprite_animation->texture_rect.y = CHARACTER_SIZE * 3.0f;
					break;
				default:
					break;
			}

			if (
				player->direction[0] == 'i'
			) {
				sprite_animation->texture_rect.x = 0.0f;
				sprite_animation->current_frame = 0;
				sprite_animation->current_sprite = 1;
			}
			else if (
				player->last_direction[1] != player->direction[1] ||
				player->last_direction[0] != player->direction[0]
			) {
				sprite_animation->texture_rect.x = CHARACTER_SIZE;
				sprite_animation->current_frame = 0;
				sprite_animation->current_sprite = 1;
			}

	}
}