#include "system_manager.h"
#include "ecs_manager.h"
#include <raymath.h>


static Vector2 d;


void system_movement_update(const float dt, const iterator_t iter) {
	ecs_t* ecs = ecs_manager_get_instance();
	for (entity_t* e = iter.begin; e < iter.end; e++) {
		movement_t* movement = (movement_t*)ecs_component_at(ecs, *e, MOVEMENT_ID);
		transform_t* transform = ecs_get_transform(ecs, *e);
		const float delta = dt * movement->speed;

		d.x = d.y = 0.0f;
		transform->last_is_idle = transform->is_idle;
		transform->last_direction = transform->direction;
		transform->is_idle = 1;

		if (IsKeyDown(UP_KEY)) {
			d.y = -1.0f;
			transform->is_idle = 0;
			transform->direction = 'u';
		} else if (IsKeyDown(DOWN_KEY)) {
			d.y = 1.0f;
			transform->is_idle = 0;
			transform->direction = 'd';
		}

		if (IsKeyDown(LEFT_KEY)) {
			d.x = -1.0f;
			transform->is_idle = 0;
			transform->direction = 'l';
		}
		else if (IsKeyDown(RIGHT_KEY)) {
			d.x = 1.0f;
			transform->is_idle = 0;
			transform->direction = 'r';
		}

		d = Vector2Normalize(d);
		// Horizontal movement
		movement->last_horizontal_move = delta * d.x;
		transform->pos.x += delta * d.x;
		movement->collision_box.x = transform->pos.x + transform->size.x / 2.0f - movement->collision_box.width / 2.0f;
		movement->collision_box.y = transform->pos.y + transform->size.y - movement->collision_box.height;
		if (ecs_check_collision(ecs, movement->collision_box)) {
			transform->pos.x -= delta * d.x;
			movement->last_horizontal_move = 0.0f;
		}
		
		// Vertical movement
		movement->last_vertical_move = delta * d.y;
		transform->pos.y += delta * d.y;
		movement->collision_box.x = transform->pos.x + transform->size.x / 2.0f - movement->collision_box.width / 2.0f;
		movement->collision_box.y = transform->pos.y + transform->size.y - movement->collision_box.height;
		if (ecs_check_collision(ecs, movement->collision_box)) {
			transform->pos.y -= delta * d.y;
			movement->last_vertical_move = 0.0f;
		}
	}
}