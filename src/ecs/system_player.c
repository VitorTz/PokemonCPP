#include "system_manager.h"
#include "ecs_manager.h"


void system_player_update(const float dt, const iterator_t iter) {
	ecs_t* ecs = ecs_manager_get_instance();

	for (entity_t* e = iter.begin; e < iter.end; e++) {
		transform_t* player_transform = ecs_get_transform(ecs, *e);
		player_t* player = (player_t*) ecs_component_at(ecs, *e, PLAYER_ID);
		
		// Camera
		ecs_set_camera_target(
			ecs, 
			player_transform->pos.x + player_transform->size.x / 2.0f, 
			player_transform->pos.y + player_transform->size.y / 2.0f
		);
	}
}